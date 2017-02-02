
#include "smsinclude.h"
#include "NasGmmInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -save -e958 */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SMC_SMRAPI_C

/*lint -e438 -e830*/

VOS_VOID SMR_SndReportReq(
    VOS_UINT8    ucMti,                                        /* ��Ϣ����ָʾ                             */
    VOS_UINT8    ucFcs,                                        /* ����ԭ��ֵ                               */
    VOS_UINT8    ucRpCause,                                    /* Rpԭ��ֵ                                 */
    VOS_UINT8    ucMoreMsg                                     /* �����Ƿ��и������Ϣ�ı�־             */
)
{

    SMT_SMR_DATA_STRU    *pSndMsg;                                           /* �����ŷ�����Ϣ��ָ��                   */
    SMT_SMR_DATA_TEMP_STRU  *pTempMsg=VOS_NULL_PTR;
    VOS_UINT8            ucSndMsgLen;                                        /* ���巢�͵�ԭ��ĳ���                     */

    if( MN_MSG_RP_MTI_UP_RP_ERR == ucMti )
    {                                                                           /* ���͵�ΪRP-ERROR                         */
        ucSndMsgLen = (VOS_UINT8)sizeof( SMT_SMR_DATA_STRU ) + (VOS_UINT8)(sizeof( VOS_UINT8 ) * 5);     /* �������ݳ���                             */
        pSndMsg     = (SMT_SMR_DATA_STRU *)SMS_Malloc(ucSndMsgLen);        /* ���뷢��ԭ��Ŀռ�                       */
        if ( VOS_NULL_PTR == pSndMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMR_SndReportReq:ERROR: Memory allocation fails" );
            return;
        }
        pTempMsg = (SMT_SMR_DATA_TEMP_STRU *)pSndMsg;
        SMS_Memset(pTempMsg,0,ucSndMsgLen);                                      /* ��ʼ������                               */
        pTempMsg->ulDataLen   = (sizeof( VOS_UINT8 ) * 4) + (sizeof( VOS_UINT8 ) * 5);       /* ��д���ݳ���                             */
        pTempMsg->aucData[0]  = ucMti;                                           /* ��д��Ϣ����                             */
        pTempMsg->aucData[2]  = 1;                                               /* ��дRPԭ��ֵ����                         */
        pTempMsg->aucData[3]  = ucRpCause;                                       /* ��дRPԭ��ֵ                             */
        pTempMsg->aucData[4]  = MN_MSG_RP_USER_DATA_IEI;                            /* ��д�û���������                         */
        pTempMsg->aucData[5]  = sizeof( VOS_UINT8 ) * 3;                             /* ��дTPDU����                             */
        pTempMsg->aucData[6]  = 0;                                               /* ��дTPDU��Ϣ����                         */
        pTempMsg->aucData[6] |= MN_MSG_TP_MTI_DELIVER_REPORT;                       /* ��дTPDU��Ϣ����                         */
        pTempMsg->aucData[7]  = ucFcs;                                           /* ��дTPԭ��ֵ                             */
        pTempMsg->aucData[8]  = 0x00;                                            /* ��д����ָʾTP-PI                        */
    }
    else
    {                                                                           /* ���͵�ΪRP-ACK                           */
        pSndMsg = (SMT_SMR_DATA_STRU *)
                    SMS_Malloc( sizeof( SMT_SMR_DATA_STRU ) );               /* ���뷢��ԭ��Ŀռ�                       */
        if ( VOS_NULL_PTR == pSndMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMR_SndReportReq:ERROR: Memory allocation fails" );
            return;
        }
        SMS_Memset(pSndMsg,0,sizeof( SMT_SMR_DATA_STRU ));                   /* ��ʼ������                               */
        pSndMsg->ulDataLen  = 2;                                                /* ��д���ݳ���                             */
        pSndMsg->aucData[0] = ucMti;                                            /* ��д��Ϣ����                             */
    }

    SMS_RcvMnReportReq(pSndMsg);                               /* ����SMRL_REPORT_REQԭ��                  */

    /*�ͷ�pSndMsg*/
    SMS_Free(pSndMsg);


}
/*lint +e438 +e830*/


VOS_VOID SMC_SmrApiDataReq(
                        VOS_UINT8     *pucData,                                     /* �����׵�ַ                               */
                        VOS_UINT16    usLen                                         /* ���ݳ���                                 */
                      )
{
    VOS_UINT16   usMsgLen;                                                          /* ����洢��Ϣ���ȵı���                   */
    VOS_UINT32   TempAddr;
    VOS_UINT8    aucSndMsg[255];

    if(SMC_MT_WAIT_FOR_RP_ACK == g_SmcPsEnt.SmcMt.ucState)
    {
        /* PS���ʵ���ڵȴ�RP-ACK                   */
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
        {
            usMsgLen = ((sizeof(SMS_LMM_DATA_REQ_STRU) - 4)
                                       + usLen) + SMC_MSG_HDR_LEN;                          /* �����Ϣ�ĳ���                           */
            if(usLen < SMC_SND_MSG_MIN_LEN)
            {                                                                   /* ��Ϣ�ĳ��Ƚ�С                           */
                usMsgLen = sizeof(SMS_LMM_DATA_REQ_STRU);
            }


            SMS_Memset( aucSndMsg,0,usMsgLen );                                 /* ��ʼ��Ϊ��                               */

            ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[0]
                            = (VOS_UINT8)(g_SmcPsEnt.SmcMt.ucTi << 4) | 0x80;              /* ��ֵTI                                   */
            ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[0]
                            |= NAS_PD_SMS;                                      /* ��дPD                                   */
            ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* ��д��Ϣ����                             */
            TempAddr = (VOS_UINT32)(&(((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[2]));


            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* ������Ϣ                                 */

            ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.ulSmsMsgSize =
                      usLen + SMC_MSG_HDR_LEN;                                  /* ��ֵ��Ϣ����                             */

            g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg     = SMS_Malloc(usMsgLen);        /* �����ڴ�                                 */
            if ( VOS_NULL_PTR == g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Memory allocation fails" );
                return;
            }
            SMS_Memset( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg,0,usMsgLen );          /* ��ʼ������                               */

            SMS_Memcpy( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg,
                        aucSndMsg,
                        usMsgLen );                                             /* ������Ϣ                                 */
            g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = usMsgLen;                    /* ������Ϣ����                             */

            /* ��ǻ������Ϣ���� */
            g_SmcPsEnt.SmcMt.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_LTE_MT_RP_ACK;

            /* ����timer tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiDataReq: TimerStart: tc1m" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_PS_TC1M_MT ) )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Start Tc1m fails" );
                SMS_Free( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg );                       /* �ͷŻ������Ϣ                           */
                g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                           /* ��ʼ����Ϣ����                           */
                g_SmcPsEnt.SmcMt.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_BUTT;
                return;
            }

            g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;

            NAS_SMS_ChangePsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);

            /* ����CP-DATA��Ϣ */
            if (VOS_FALSE == NAS_SMS_SndLmmCpDataReq(aucSndMsg, usMsgLen))
            {
                PS_MEM_FREE(WUEPS_PID_SMS, g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg);
                g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;
                g_SmcPsEnt.SmcMt.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
                return;
            }
        }
        else
#endif
        {                                                                       /* Message Reference���                    */
            usMsgLen = ((sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4)
                            + usLen) + SMC_MSG_HDR_LEN;                          /* �����Ϣ�ĳ���                           */
            if(usLen < SMC_SND_MSG_MIN_LEN)
            {                                                                   /* ��Ϣ�ĳ��Ƚ�С                           */
                usMsgLen = sizeof(PMMSMS_UNITDATA_REQ_STRU);
            }


            SMS_Memset( aucSndMsg,0,usMsgLen );                                 /* ��ʼ��Ϊ��                               */

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[0]
                            = (VOS_UINT8)(g_SmcPsEnt.SmcMt.ucTi << 4) | 0x80;              /* ��ֵTI                                   */
            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[0]
                            |= NAS_PD_SMS;                                      /* ��дPD                                   */
            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* ��д��Ϣ����                             */
            TempAddr = (VOS_UINT32)(&(((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[2]));


            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* ������Ϣ                                 */

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.ulNasMsgSize =
                      usLen + SMC_MSG_HDR_LEN;                                  /* ��ֵ��Ϣ����                             */

            g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg     = SMS_Malloc(usMsgLen);        /* �����ڴ�                                 */
            if ( VOS_NULL_PTR == g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Memory allocation fails" );
                return;
            }
            SMS_Memset( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg,0,usMsgLen );          /* ��ʼ������                               */

            SMS_Memcpy( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg,
                        aucSndMsg,
                        usMsgLen );                                             /* ������Ϣ                                 */
            g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = usMsgLen;                    /* ������Ϣ����                             */

            /* ��ǻ������Ϣ���� */
            g_SmcPsEnt.SmcMt.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_GU_MT_RP_ACK;

            /* ����timer tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiDataReq: TimerStart: tc1m" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_PS_TC1M_MT ) )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Start Tc1m fails" );
                SMS_Free( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg );                       /* �ͷŻ������Ϣ                           */
                g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                           /* ��ʼ����Ϣ����                           */
                g_SmcPsEnt.SmcMt.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_BUTT;
                return;
            }

            g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;

            NAS_SMS_ChangePsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);

            SMC_SndGmmMsg(aucSndMsg, PMMSMS_UNITDATA_REQ, usMsgLen);            /* ������Ϣ                                 */
        }
    }
    else if(SMC_MT_WAIT_FOR_RP_ACK == g_SmcCsEnt.SmcMt.ucState)
    {                                                                           /* CS���ʵ���ڵȴ�RP-ACK                   */
        {                                                                       /* Message Reference���                    */
            usMsgLen = ((sizeof(MMSMS_DATA_REQ_STRU)-4) + usLen) + SMC_MSG_HDR_LEN; /* �����Ϣ�ĳ���                           */
            if(usLen < SMC_SND_MSG_MIN_LEN)
            {                                                                   /* ��Ϣ�ĳ��Ƚ�С                           */
                usMsgLen = sizeof(MMSMS_DATA_REQ_STRU);
            }

            SMS_Memset(aucSndMsg,0,usMsgLen);                                   /* ��ʼ������                               */

            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->ulTi = g_SmcCsEnt.SmcMt.ucTi;  /* ��ֵTI                                   */
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[0]
                            = (VOS_UINT8)(g_SmcCsEnt.SmcMt.ucTi << 4) | 0x80;              /* ��д��Ϣ��cp_data��pd ti                 */
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[0]
                            |= NAS_PD_SMS;
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* ��д��Ϣ��cp_data����Ϣ����              */

           TempAddr = (VOS_UINT32)(&(((MMSMS_DATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[2]));

            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* ������Ϣ ��д����TAF��rpdu               */

            ((MMSMS_DATA_REQ_STRU *)aucSndMsg)->SmsMsg.ulNasMsgSize =
                           usLen + SMC_MSG_HDR_LEN;                             /* ��ֵ��Ϣ����                             */

            g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg     = (VOS_VOID *)SMS_Malloc(usMsgLen);/* �����ڴ�ռ�                             */
            if ( VOS_NULL_PTR == g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Memory allocation fails" );
                return;
            }
            SMS_Memcpy( g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg, aucSndMsg, usMsgLen); /* ������Ϣ                                 */
            g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = usMsgLen;                    /* ������Ϣ����                             */

            /* ������ʱ��tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiDataReq: TimerStart: tc1m" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_CS_TC1M_MT ) )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SmrApiDataReq: Start Tc1m fails" );
                SMS_Free(g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg);
                g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;                               /* �����Ϣ����                             */
                return;
            }

            SMC_SndMmMsg(aucSndMsg, MMSMS_DATA_REQ, usMsgLen);                  /* ����MM��Ϣ                               */

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiDataReq:NORMAL:SMS state = SMC_MT_WAIT_FOR_CP_ACK");
        }
    }
    else if(SMR_WAIT_FOR_RP_ACK == g_SmrEnt.SmrMo.ucState)
    {
        /*�ж�����Ҫ��PS���ͻ���CS����*/
        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {
            usMsgLen = ((sizeof(MMSMS_DATA_REQ_STRU)-4) + usLen) + SMC_MSG_HDR_LEN; /* �����Ϣ�ĳ���                           */
            if(usLen < SMC_SND_MSG_MIN_LEN)
            {                                                                   /* ��Ϣ�ĳ��Ƚ�С                           */
                usMsgLen = sizeof(MMSMS_DATA_REQ_STRU);
            }

            SMS_Memset(aucSndMsg,0,usMsgLen);                                   /* ��ʼ������                               */


            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->ulTi = g_SmcCsEnt.SmcMo.ucTi;
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[0]
                            = (VOS_UINT8)(g_SmcCsEnt.SmcMo.ucTi&0x07)<<4;
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[0]
                            |= NAS_PD_SMS;
            ((MMSMS_DATA_REQ_STRU *) aucSndMsg)->SmsMsg.aucNasMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* ��д��Ϣ��cp_data����Ϣ����              */

            TempAddr = (VOS_UINT32)(&(((MMSMS_DATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[2]));
            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );

            ((MMSMS_DATA_REQ_STRU *)aucSndMsg)->SmsMsg.ulNasMsgSize =
                           usLen + SMC_MSG_HDR_LEN;                             /* ��ֵ��Ϣ����                             */

            SMC_SndMmMsg(aucSndMsg, MMSMS_DATA_REQ, usMsgLen);                  /* ����MM��Ϣ                               */
        }
        else
        {
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                usMsgLen = ((sizeof(SMS_LMM_DATA_REQ_STRU) - 4)
                          + usLen) + SMC_MSG_HDR_LEN;                          /* �����Ϣ�ĳ���                           */
                if(usLen < SMC_SND_MSG_MIN_LEN)
                {                                                                   /* ��Ϣ�ĳ��Ƚ�С                           */
                    usMsgLen = sizeof(SMS_LMM_DATA_REQ_STRU);
                }

                SMS_Memset( aucSndMsg,0,usMsgLen );                                 /* ��ʼ��Ϊ��                               */

                ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[0]
                                = (VOS_UINT8)(g_SmcPsEnt.SmcMo.ucTi & 0x07)<<4;

                ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[0]
                                |= NAS_PD_SMS;                                      /* ��дPD                                   */
                ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[1]
                                = SMC_DATA_TYPE_CP_DATA;                            /* ��д��Ϣ����                             */

                TempAddr = (VOS_UINT32)(&(((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.aucSmsMsg[2]));

                SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* ������Ϣ                                 */

                ((SMS_LMM_DATA_REQ_STRU *)aucSndMsg)->stSmsMsg.ulSmsMsgSize =
                          usLen + SMC_MSG_HDR_LEN;                                  /* ��ֵ��Ϣ����                             */

                /* ����CP-DATA��Ϣ */
                (VOS_VOID)NAS_SMS_SndLmmCpDataReq(aucSndMsg, usMsgLen);
            }
            else
#endif
            {
                usMsgLen = ((sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4)
                          + usLen) + SMC_MSG_HDR_LEN;                          /* �����Ϣ�ĳ���                           */
                if(usLen < SMC_SND_MSG_MIN_LEN)
                {                                                                   /* ��Ϣ�ĳ��Ƚ�С                           */
                    usMsgLen = sizeof(PMMSMS_UNITDATA_REQ_STRU);
                }

            SMS_Memset( aucSndMsg,0,usMsgLen );                                 /* ��ʼ��Ϊ��                               */

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[0]
                            = (VOS_UINT8)(g_SmcPsEnt.SmcMo.ucTi & 0x07)<<4;

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[0]
                            |= NAS_PD_SMS;                                      /* ��дPD                                   */
            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[1]
                            = SMC_DATA_TYPE_CP_DATA;                            /* ��д��Ϣ����                             */

            TempAddr = (VOS_UINT32)(&(((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.aucNasMsg[2]));

            SMS_Memcpy((VOS_UINT32*)TempAddr, pucData, usLen );                                            /* ������Ϣ                                 */

            ((PMMSMS_UNITDATA_REQ_STRU *)aucSndMsg)->SmsMsg.ulNasMsgSize =
                      usLen + SMC_MSG_HDR_LEN;                                  /* ��ֵ��Ϣ����                             */

                SMC_SndGmmMsg(aucSndMsg, PMMSMS_UNITDATA_REQ, usMsgLen);
            }
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_ERROR, "SMC_SmrApiDataReq:ERROR:Invalid SMS-R state ");
    }
}
VOS_VOID SMC_SmrApiEstReq(
    VOS_UINT8                           ucCurSendDomain,
    VOS_UINT8                           *pucData,                                       /* �����׵�ַ                               */
    VOS_UINT32                          ulLen                                           /* ���ݳ���                                 */
)
{
    VOS_UINT8           aucTempMsg[255];
    VOS_UINT8           ucTi;

    SMS_LOG(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: step into function.");
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: ucCurSendDomain.", ucCurSendDomain);
    /*****************************����ʵ�ʵķ���******************************/
    if ((SMS_SEND_DOMAIN_CS != ucCurSendDomain)
     && ( SMS_SEND_DOMAIN_PS != ucCurSendDomain ))
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMC_SmrApiEstReq: invalid send domain." );
        return;
    }

    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: g_SmcCsEnt.SmcMo.ucState.", g_SmcCsEnt.SmcMo.ucState);
    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: g_SmcPsEnt.SmcMo.ucState.", g_SmcPsEnt.SmcMo.ucState);

    SMS_LOG1(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: ucCurSendDomain.", ucCurSendDomain);


    if ( SMS_SEND_DOMAIN_PS == ucCurSendDomain )
    {   /*�������PS����*/
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcCsEnt.SmcMo.ucState)
        {
            SMC_SndMmCpAckMsg(g_SmcCsEnt.SmcMo.ucTi);
            SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucTi);                                /* ָʾMM�ͷ�MM����                         */
            g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
            SMS_LOG(PS_LOG_LEVEL_NORMAL, "SMC_SmrApiEstReq: SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);

            SMS_SendMnMoLinkCloseInd();
        }

        SMS_LOG1(PS_LOG_LEVEL_NORMAL,
                 "SMC_SmrApiEstReq: g_SmcPsEnt.SmcMo.ucState.",
                 g_SmcPsEnt.SmcMo.ucState);
        if ((SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState)
         && (SMC_MO_WAIT_TO_SND_CP_ACK != g_SmcPsEnt.SmcMo.ucState))
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMC_SmrApiEstReq: PS entity is inavailable." );
            return;
        }

        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcPsEnt.SmcMo.ucState)
        {
            g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
            SMS_SendMnMoLinkCloseInd();
        }

        /* ʵ���ڿ���״̬                           */
        g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg  = (VOS_VOID *)SMS_Malloc( ulLen );    /* �洢����                                 */
        if ( VOS_NULL_PTR == g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMC_SmrApiEstReq: Memory allocation fails" );
            return;
        }
        SMS_Memcpy( g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg, pucData, ulLen );     /* ������Ϣ                                 */
        g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = ulLen;                       /* �洢���ݳ���                             */

        /* DSDS��Ҫ����Դ�����ٷ�est req�������� */
        NAS_SMS_ChangePsMoEntityState(SMC_MO_GMM_CONN_PENDING);

#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
        {
            /* ��ǰפ����Lģ */
            NAS_SMS_SndLmmEstReq(RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL);
        }
        else
#endif
        {
            SMS_Memset( aucTempMsg,0,sizeof(PMMSMS_EST_REQ_STRU) );             /* ��ʼ������                               */
            ((PMMSMS_EST_REQ_STRU *)aucTempMsg)->ulEstCause = RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL;  /* ��дԭ��ֵ                               */
            SMC_SndGmmMsg( aucTempMsg,
                           PMMSMS_EST_REQ,
                           sizeof(PMMSMS_EST_REQ_STRU) );                       /* ָʾGMM������������                      */
        }

        SMS_LOG( PS_LOG_LEVEL_NORMAL,
                 "SMC_SmrApiEstReq: SMS state = SMC_MO_GMM_CONN_PENDING" );
    }
    else
    {   /*�������CS����*/
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcPsEnt.SmcMo.ucState)
        {
            SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ACK,
                               0XFF,
                               g_SmcPsEnt.SmcMo.ucTi );                         /* �������ȷ��                             */
            g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
            SMS_LOG( PS_LOG_LEVEL_NORMAL,
                     "SMC_SmrApiEstReq: SMS state = SMC_MO_IDLE" );

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);

            SMS_SendMnMoLinkCloseInd();
        }

        /*ȷ��C��״̬�Ƿ���Է�����Ϣ*/
        if ((SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
         && (SMC_MO_WAIT_TO_SND_CP_ACK != g_SmcCsEnt.SmcMo.ucState))
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMC_SmrApiEstReq: CS entity is inavailable." );
            return;
        }

        /*����RP-DATA���ݶκͳ��ȵ�C�㻺�棻*/
        g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg  = (VOS_VOID *)SMS_Malloc( ulLen );
        if ( VOS_NULL_PTR == g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMC_SmrApiEstReq: Memory allocation fails" );
            return;
        }
        SMS_Memcpy(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg, pucData, ulLen);
        g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = ulLen;

        /*ָʾMM����MM����                    */
        /* ״̬Ǩ��                                 */
        SMS_Memset( aucTempMsg,0,sizeof(MMSMS_EST_REQ_STRU) );
        ucTi = (VOS_UINT8)(((g_SmcCsEnt.SmcMo.ucTi + 1) % 0x07) | 0x08);
        (( MMSMS_EST_REQ_STRU* )aucTempMsg)->ulTi       = ucTi;                      /* ��дTi                                   */
        (( MMSMS_EST_REQ_STRU* )aucTempMsg)->ulEstCause = RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL;   /* ��дԭ��ֵ                               */

        /* ����ǰһ��ti*/
        if (SMC_MO_WAIT_TO_SND_CP_ACK == g_SmcCsEnt.SmcMo.ucState)
        {
            g_SmcCsEnt.SmcMo.ucPreTi = g_SmcCsEnt.SmcMo.ucTi;
        }

        NAS_SMS_ChangeCsMoEntityState(SMC_MO_MM_CONN_PENDING);

        SMC_SndMmMsg( aucTempMsg, MMSMS_EST_REQ, sizeof(MMSMS_EST_REQ_STRU) );

        g_SmcCsEnt.SmcMo.ucTi = ucTi;

        SMS_LOG( PS_LOG_LEVEL_NORMAL,
                 "SMC_SmrApiEstReq: SMS state = SMC_MO_MM_CONN_PENDING" );
    }
    return;
}

VOS_VOID SMC_SmrApiAbortReq(
                        VOS_UINT8     ucCause                                       /* ��ֹԭ��                                 */
                        )
{
    if(SMR_SMC_ABORT_CAUSE_TR1M_EXP == ucCause)
    {                                                                           /* ԭ��ֵΪTR1M��ʱ                         */
        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {
            /* TR1M��ʱ��ABORT����������ָʾ����                           */
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_PROT_ERR_UNSPEC,
                              g_SmcCsEnt.SmcMo.ucTi );

            if(SMC_MO_MM_CONN_PENDING == g_SmcCsEnt.SmcMo.ucState)
            {                                                                   /* ʵ���״̬��SMC_MO_MM_CONN_PENDING       */
                if (0 != g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg);                     /* �ͷ���Ϣ                                 */
                    g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                       /* �����Ϣ����                             */
                }
                SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucTi);                           /* �ͷ�MM����                               */
            }
            else
            {
                if(0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg);
                    g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
                }

                /* ֹͣtimer tc1m */
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiAbortReq: TimerStop: TC1M" );
                if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
                {
                    return;
                }

                /* g_SmcCsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
                g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

                SMC_SndRelReq( g_SmcCsEnt.SmcMo.ucTi );                         /* �ͷ�MM����                               */
            }
            if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
            {
                g_SmcCsEnt.SmcMo.ucCpAckFlg              = SMS_FALSE;
                SMS_SendMnMoLinkCloseInd();
            }
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);
        }
        else
        {                                                                       /* PS���SMCʵ��״̬Ϊ�ǿ�                  */
            if(SMC_MO_GMM_CONN_PENDING == g_SmcPsEnt.SmcMo.ucState)
            {                                                                   /* ʵ���״̬SMC_MO_GMM_CONN_PENDING        */
                if (0 != g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg);                     /* �ͷ���Ϣ                                 */
                    g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                       /* �����Ϣ����                             */
                }
            }
            else
            {
                if (0 != g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg);
                    g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
                    g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
                }

                /* ֹͣtimer tc1m */
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiAbortReq: TimerStop: TC1M" );
                if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_PS_TC1M_MO ) )
                {
                    return;
                }

                /* g_SmcPsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
                g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

#if (FEATURE_ON == FEATURE_LTE)
                if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
                {
                    /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                    NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR, SMS_CP_ERR_PROT_ERR_UNSPEC, g_SmcPsEnt.SmcMo.ucTi);
                }
                else
#endif
                {
                    SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                                       SMS_CP_ERR_PROT_ERR_UNSPEC,
                                       g_SmcPsEnt.SmcMo.ucTi );                     /* ������ָʾ����                           */
                }

            }
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MO_IDLE");

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);
        }
    }
    else if(SMR_SMC_ABORT_CAUSE_TR2M_EXP == ucCause)
    {                                                                           /* ԭ��ֵΪTR2M��ʱ                         */
        /*begin add by zhoujun40661 2006-10-25 for CNMA*/
        if(SMC_MT_MM_CONN_EST == g_SmcCsEnt.SmcMt.ucState)
        {                                                                       /* CS���SMCʵ��״̬ΪSMC_MT_MM_CONN_EST    */
            SMC_SndMmDataReq( SMC_DATA_TYPE_CP_ERR,
                              SMS_CP_ERR_PROT_ERR_UNSPEC,
                              g_SmcCsEnt.SmcMt.ucTi );                          /* ������ָʾ����                           */
            SMC_SndRelReq( g_SmcCsEnt.SmcMt.ucTi );                             /* �ͷ�MM����                               */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MT_IDLE");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);
        }
        else if(SMC_MT_WAIT_FOR_RP_ACK == g_SmcCsEnt.SmcMt.ucState)
        {
            SMR_SndReportReq(MN_MSG_RP_MTI_UP_RP_ERR,
                             0xD2,
                             SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR,
                             0 );
            #if 0
            SMC_SndRelReq( g_SmcCsEnt.SmcMt.ucTi );                           /* �ͷ�MM����                               */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MT_IDLE");
            g_SmcCsEnt.SmcMt.ucState = SMC_MT_IDLE;
            #endif
        }
        else if(SMC_MT_WAIT_FOR_RP_ACK == g_SmcPsEnt.SmcMt.ucState )
        {
            SMR_SndReportReq( MN_MSG_RP_MTI_UP_RP_ERR,
                              0xD2,
                              SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR,
                              0 );
                        /* ������ָʾ����                           */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiAbortReq:NORMAL:SMS state = SMC_MT_IDLE");

            NAS_SMS_ChangePsMtEntityState(SMC_MT_IDLE);
        }
        else
        {

        }
        /*end by zhoujun40661 2006-10-25 for CNMA*/
    }
    else
    {

    }
}
VOS_VOID SMC_SmrApiRelReq(
                      VOS_UINT8     ucRelCause,                                     /* �ͷ�ԭ��                                 */
                      VOS_UINT8     ucMtFlg                                         /* ��MT����                                 */
                      )
{
    VOS_UINT8   aucTempMsg[255];

    if(SMS_FALSE == ucMtFlg)
    {                                                                           /* �ͷ�mo�����е�mm����                     */
        if(SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
        {                                                                       /* ��Ҫ����CP-ACK                           */
            SMS_Memset(aucTempMsg,0,sizeof(MMSMS_DATA_REQ_STRU));                /* ��ʼ������                               */

            if(SMR_SMC_REL_CAUSE_PS_MULTI == ucRelCause)
            {
                ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->ulTi =
                                        g_SmcCsEnt.SmcMo.ucPreTi;               /* ��ֵti                                   */

                ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[0] =
                                       (g_SmcCsEnt.SmcMo.ucPreTi & 0x07) << 4;  /* ��дti                                   */
            }
            else
            {
                ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->ulTi =
                                        g_SmcCsEnt.SmcMo.ucTi;                  /* ��ֵti                                   */

                ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[0] =
                                        (g_SmcCsEnt.SmcMo.ucTi & 0x07) << 4;    /* ��дti                                   */
            }
            ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.ulNasMsgSize
                = SMC_MSG_HDR_LEN;                                              /* ��ֵ��Ϣ����                             */
            ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[0]
                |= NAS_PD_SMS;                                                  /* ��дpd                                   */
            ((MMSMS_DATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[1]
                = SMC_DATA_TYPE_CP_ACK;                                         /* ��д��Ϣ����                             */
            SMC_SndMmMsg(aucTempMsg,MMSMS_DATA_REQ,sizeof(MMSMS_DATA_REQ_STRU)); /* ������Ϣ                                 */
        }


        if(SMC_MO_IDLE != g_SmcCsEnt.SmcMo.ucState)
        {                                                                       /* ʵ���ڵȴ�����CP_ACK                     */
            if(0 != g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
            {                                                                   /* �д洢�Ľ�����Ϣ                         */
                if(SMS_TRUE != g_SmcCsEnt.SmcMo.ucCpAckFlg)
                {
                    if (0 != g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                    {
                        SMS_Free(g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg);                 /* �ͷŴ洢����Ϣ                           */
                        g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                   /* �����Ϣ����                             */
                    }
                }
                else
                {
                }
            }
            else if(0 != g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen)
            {                                                                   /* �д洢�ķ�����Ϣ                         */
                SMS_Free(g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg);                     /* �ͷŴ洢����Ϣ                           */
                g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                       /* �����Ϣ����                             */
            }
            else
            {

            }

            /* ֹͣtimer tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: TimerStop: TC1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
            {
                    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: fail to stop TC1M." );
            }

            g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

            if (SMR_SMC_REL_CAUSE_PS_MULTI == ucRelCause)
            {
                SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucPreTi);                        /* ָʾMM�ͷ�MM����                         */
            }
            else
            {
                SMC_SndRelReq(g_SmcCsEnt.SmcMo.ucTi);                           /* ָʾMM�ͷ�MM����                         */

                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, ":NORMAL:SMS state = SMC_MO_IDLE");

                NAS_SMS_ChangeCsMoEntityState(SMC_MO_IDLE);
            }

            if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
            {
                g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
                SMS_SendMnMoLinkCloseInd();
            }
        }
        else if(SMC_MO_IDLE != g_SmcPsEnt.SmcMo.ucState)
        {
            if(SMR_SMC_REL_CAUSE_PS_MULTI == ucRelCause)
            {

            }
            else
            {
                if(0 != g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg);
                    g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;
                }
                else if(0 != g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
                {
                    SMS_Free(g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg);
                    g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
                    g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
                }
                else
                {

                }

                /* ֹͣtimer tc1m */
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: TimerStop: TC1M" );
                if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_PS_TC1M_MO ) )
                {
                    SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: fail to stop TC1M." );
                }

                /* g_SmcPsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
                g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiRelReq:NORMAL:SMS state = SMC_MO_IDLE");


                NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);
            }
        }
        else
        {

        }
    }
    else
    {
        if( (SMC_MT_WAIT_FOR_CP_ACK != g_SmcCsEnt.SmcMt.ucState)
                    && (SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState) )
        {
            /* ֹͣtimer tc1m */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_SmrApiRelReq: TimerStop: TC1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
            {
                return;
            }

            /* g_SmcCsEnt.SmcMt.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP; */
            g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;
        }
        if(SMC_MT_MM_CONN_EST == g_SmcCsEnt.SmcMt.ucState)
        {                                                                       /* ʵ���ڵȴ��߲��ȷ��                     */
            SMC_SndRelReq( g_SmcCsEnt.SmcMt.ucTi );                             /* ָʾMM�ͷ�MM����                         */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_SmrApiRelReq:NORMAL:SMS state = SMC_MT_IDLE");

            NAS_SMS_ChangeCsMtEntityState(SMC_MT_IDLE);
        }

    }
}
VOS_UINT32 SMR_SmcApiDataInd(
                       VOS_UINT8 *pucData,                                          /* �����׵�ַ                               */
                       VOS_UINT32  ulLen                                             /* ���ݳ���                                 */
                      )
{
    VOS_UINT32  ulRet = VOS_OK;
    NAS_OM_SMS_MO_REPORT_STRU stSmsMoReportPara;

    stSmsMoReportPara.ulCause = 0;
    stSmsMoReportPara.ucSmsMr = g_SmrEnt.SmrMo.ucMr;

    /*When a message is received that is too short to contain a complete message
    type information element and Message Reference, that message shall be ignored*/
    if(ulLen < 2)
    {                                                                       /* ������ǿ��IE                             */
        SMR_SndRpErrorReq(g_SmrEnt.SmrMo.ucMr,
                         SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ,
                         SMS_TRUE );

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcApiDataInd:WARNING:NW->SMS SMS ERROR Len is too short!");
        return SMR_MSG_TOO_SHORT_ERROR;
    }

    if (SMR_WAIT_FOR_RP_ACK == g_SmrEnt.SmrMo.ucState)
    {                                                                           /* ʵ���ڵȴ�RP_ACK                         */
        switch(pucData[0])
        {
        case SMR_NTM_DATA_TYPE_RP_DATA:
            /* ������ָʾ����          */
            SMR_SndRpErrorReq( g_SmrEnt.SmrMo.ucMr,
                               SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE,
                               SMS_TRUE );                                          /* ��Э��״̬����Ӧ,����RP_ERROR            */
            ulRet = SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE;
            break;

        case SMR_NTM_DATA_TYPE_RP_ACK:

            /*Whenever any RP ACK message is received specifying a Message Reference
            which is not associated with an active SM transfer, the mobile station
            shall discard the message and return an RP ERROR message with cause #81,
            "Invalid short message transfer reference value" using the received
            Message Reference, if an appropriate connection exists*/
            if(g_SmrEnt.SmrMo.ucMr != pucData[1])
            {
                SMR_SndRpErrorReq( pucData[1],
                               SMR_ERR_CAUSE_VALUE_INVALID_MR,
                               SMS_TRUE );
                ulRet = SMR_ERR_CAUSE_VALUE_INVALID_MR;
                break;
            }

            /* ֹͣtimer TR1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiDataInd: TimerStop: TR1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiDataInd: TimerStop: TR1M Failed" );
            }

            if (SMS_TRUE == g_SmrEnt.SmrMo.ucMemAvailFlg)
            {                                                                   /* �˹�����mem avail����                    */
                g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;                       /* ���mem avail��־                        */
                g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;              /* ��λ�ط���־                             */
            }

            g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* ״̬Ǩ�Ƶ�����״̬                       */

            SMS_SendMnReportReq(SMR_SMT_ERROR_NO_ERROR, pucData, ulLen);

            NAS_EventReport(WUEPS_PID_SMS, NAS_OM_EVENT_SMS_MO_SUCC,
                            &stSmsMoReportPara, sizeof(stSmsMoReportPara));
            break;
        case SMR_NTM_DATA_TYPE_RP_ERR:

            /*When an RP ERROR message is received specifying a Message
            Reference which is not associated with an active SM transfer, the
            mobile station shall discard the message*/
            /*�˴�����ͬ��Ϣ���ȹ��̣���ʱ����SMR_MSG_TOO_SHORT_ERROR*/
            if(g_SmrEnt.SmrMo.ucMr != pucData[1])
            {
                ulRet = SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR;
                break;
            }

            /* ֹͣtimer TR1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiDataInd: TimerStop: TR1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiDataInd: TimerStop: TR1M Failed" );
            }
            if (SMS_TRUE == g_SmrEnt.SmrMo.ucMemAvailFlg )
            {                                                                   /* �˹�����mem avail����                    */
                if ((SMR_ERR_CAUSE_TEMP_FAILURE   == pucData[3])
                    || (SMR_ERR_CAUSE_CONGESTION  == pucData[3])
                    || (SMR_ERR_CAUSE_RES_UNAVAIL == pucData[3])
                    || (SMR_ERR_CAUSE_NET_OUT_OF_ORDER == pucData[3]))
                {                                                               /* ��temporary error                        */
                    SMR_MemNotifyRetrans((SMR_SMT_ERROR_RP_ERROR_BEGIN | pucData[NAS_SMS_RP_ERROR_OFFSET]),
                                        pucData,
                                        ulLen);         /* �����ط����̵Ĵ���                       */
                }
                else
                {
                    SMS_SendMnReportReq((SMR_SMT_ERROR_RP_ERROR_BEGIN | pucData[NAS_SMS_RP_ERROR_OFFSET]),
                                        pucData,
                                        ulLen);                                 /* ��߲�ָʾ����                           */
                    g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;                   /* ���mem avail��־                        */
                    g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;          /* ��λ�ط���־                             */
                    PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_SmcApiDataInd:NORMAL:SMS state = SMR_IDLE");
                    g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* ״̬Ǩ�Ƶ�����״̬                       */
                }
            }
            else
            {                                                                   /* �˹�����MO����                           */
                SMS_SendMnReportReq((SMR_SMT_ERROR_RP_ERROR_BEGIN | pucData[NAS_SMS_RP_ERROR_OFFSET]),
                                    pucData,
                                    ulLen);                           /* ��߲�ָʾ����                           */
                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_SmcApiDataInd:NORMAL:SMS state = SMR_IDLE");
                g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* ״̬Ǩ�Ƶ�����״̬                       */
            }
            /* �ս�������Ϣ�����滹���ж�Ҫ��Ҫ���ԣ��˴���SMS MO FAIL̫�� */
            break;
        default:
            /* ������ָʾ����          */
            SMR_SndRpErrorReq(pucData[1],
                              SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST,
                              SMS_TRUE);
            ulRet = SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST;
            break;
        }

    }
    else
    {
        SMR_SndRpErrorReq(pucData[1],
                          SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE,
                          SMS_TRUE);
        ulRet = SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE;
    }
    return ulRet;
}

VOS_UINT32 SMR_SmcApiEstInd(
                      VOS_UINT8 *pucData,                                       /* �����׵�ַ           */
                      VOS_UINT32  ulLen,                                        /* ���ݳ���             */
                      VOS_UINT8   ucRcvDomain                                    /* ��������PS����CS�� */
                      )
{
    VOS_UINT8   ucChkError;                                                         /* ����洢��Ϣ������ı���               */
    VOS_UINT32  ulRet = VOS_OK;

    ucChkError      = SMR_SmcChk(pucData,ulLen);                                /* ������Ϣ���                             */
    if (ucChkError != SMR_MSG_CHK_SUCCESS)
    {                                                                           /* δͨ����Ϣ���                           */
        if(ucChkError == SMR_MSG_TOO_SHORT_ERROR)
        {                                                                       /* ��Ϣ����                                 */
            SMR_SndRpErrorReq(g_SmrEnt.SmrMt.ucMr,SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR ,SMS_TRUE );
        }
        else
        {
            SMR_SndRpErrorReq( pucData[1], ucChkError,SMS_TRUE );               /* ������෢�ʹ�����Ϣ                     */
            SMC_SmrApiRelReq( SMR_SMC_REL_CAUSE_DATA_ERR,SMS_TRUE );            /* ����MNSMS_REL_REQ                        */
        }
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMR_SmcApiEstInd:WARNING:ucChkError != SMR_MSG_CHK_SUCCESS ");
        return ucChkError;
    }

    if(SMR_IDLE == g_SmrEnt.SmrMt.ucState)
    {
        if ( SMR_NTM_DATA_TYPE_RP_DATA == pucData[0] )
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMR_SmcApiEstInd:NORMAL:SMS state = SMR_WAIT_TO_SND_RP_ACK");
            g_SmrEnt.SmrMt.ucState = SMR_WAIT_TO_SND_RP_ACK;                    /* ʵ��״̬Ǩ��                             */
            g_SmrEnt.SmrMt.ucMr    = pucData[1];

            /* ������ʱ��TR2M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiEstInd: TimerStart: TR2M" );
            if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR2M ) )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiEstInd: TimerStart: TR2M failed" );
            }
            /* �رն�ʱ��TRRM */
            if( SMS_TIMER_STATUS_RUN == g_SmrEnt.SmrMt.RelTimerInfo.ucTimerSta )
            {
                SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiEstInd: TimerStop: TRRM" );
            }
            /* ԭ���ĺ�����ΪSMS_SendMnDataReq�������޸�ΪSMS_SendMnEstInd��������ӷ����� */
            SMS_SendMnEstInd( pucData , ulLen, ucRcvDomain );                            /* ��TAF����SMRL_DATA_IND(RP-DATA)          */
        }
        else if(SMR_NTM_DATA_TYPE_RP_ACK == pucData[0])
        {
            SMR_SndRpErrorReq( pucData[1],
                               SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE,
                               SMS_TRUE );                                      /* ��Э��״̬����Ӧ,����RP_ERROR            */
            ulRet = SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE;
        }
        else if (SMR_NTM_DATA_TYPE_RP_ERR == pucData[0])
        {
            /*When an RP ERROR message is received specifying a Message
            Reference which is not associated with an active SM transfer, the
            mobile station shall discard the message*/
            /*�˴�����ͬ��Ϣ���ȹ��̣���ʱ����SMR_MSG_TOO_SHORT_ERROR*/
            ulRet = SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR;
        }
        else
        {
            SMR_SndRpErrorReq(pucData[1],
                              SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST,
                              SMS_TRUE);
            ulRet = SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST;
        }
    }
    else
    {
        SMR_SndRpErrorReq( g_SmrEnt.SmrMo.ucMr,
                           SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE,
                           SMS_TRUE );                                          /* ��Э��״̬����Ӧ,����RP_ERROR            */
        ulRet = SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE;
    }
    return ulRet;
}


VOS_VOID SMR_SmcApiErrorInd(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucMtFlag
)
{
    if (SMS_FALSE == ucMtFlag)
    {                                                                           /* ��MO����                                 */
        if (SMR_IDLE != g_SmrEnt.SmrMo.ucState)
        {
            SMS_SendMnReportReq(enErrorCode, VOS_NULL_PTR, 0);
            g_SmrEnt.SmrMo.ucRetransFlg = 0;                                    /* ��RETRANS FLAG����                       */

            /* ֹͣtimer TR1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiErrorInd: TimerStop: TR1M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
            {
                return;
            }

            /* ֹͣtimer TRAM */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiErrorInd: TimerStop: TRAM" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TRAM ) )
            {
                return;
            }

            if(SMS_TRUE == g_SmrEnt.SmrMo.ucMemAvailFlg)
            {
                g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;
                g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;              /* ��λ�ط���־     */
            }
        }
        g_SmrEnt.SmrMo.ucState = SMR_IDLE;                                      /* ״̬Ǩ�Ƶ�����״̬                       */
    }
    else
    {
        if (SMR_WAIT_TO_SND_RP_ACK == g_SmrEnt.SmrMt.ucState)
        {
            SMS_SendMnMtErrInd(enErrorCode);

            /* ֹͣtimer TR2M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMR_SmcApiErrorInd: TimerStop: TR2M" );
            if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR2M ) )
            {
                return;
            }

            /* g_SmrEnt.SmrMt.TimerInfo.ucTimerSta = SMS_TIMER_STATUS_STOP; */
            g_SmrEnt.SmrMt.ucState              = SMR_IDLE;                     /* ״̬Ǩ�Ƶ�����״̬                       */
        }
    }
    return;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

