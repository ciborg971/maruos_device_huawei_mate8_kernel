/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcImsSmsMsg.c
  Description     : ��C�ļ�ʵ��IMS������Ϣ�����IMS������Ϣ����
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaProcImsSmsMsg.h"
#include "ImsaEntity.h"
#include "ImsaImsInterface.h"
#include "ImsaProcSmsMsg.h"
#include "ImsaPublic.h"


/*lint -e767*/
#define    THIS_FILE_ID         PS_FILE_ID_IMSAPROCIMSSMSMSG_C
#define    THIS_NAS_FILE_ID     NAS_FILE_ID_IMSAPROCIMSSMSMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
extern VOS_VOID IMSA_SMS_SndMsgDataInd(const VOS_UINT8* ucData, VOS_UINT32 ulDataLen);
extern VOS_VOID IMSA_SMS_ProcNwSmsReceived(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);
extern VOS_VOID IMSA_SMS_ProcNwSmsErr(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);
extern VOS_VOID IMSA_SMS_ProcNwSmsRpError(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : IMSA_SMS_SndMsgDataInd()
 Description    : ����Data ind��Ϣ
 Input          : ucData MSG���ݣ�ulDataLen MSG����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_SndMsgDataInd(const VOS_UINT8* ucData, VOS_UINT32 ulDataLen)
{
    IMSA_MSG_DATA_IND_STRU      *pstDataInd;
    VOS_UINT32                   ulMsgDataLen;

    if(ulDataLen < 4)
    {
        ulMsgDataLen = sizeof(IMSA_MSG_DATA_IND_STRU);
    }
    else
    {
        /*lint -e961*/
        ulMsgDataLen = sizeof(IMSA_MSG_DATA_IND_STRU)+ ulDataLen -4;
        /*lint +e961*/
    }

    /*������Ϣ�ռ�*/
    pstDataInd = (VOS_VOID*)IMSA_ALLOC_MSG(ulMsgDataLen);

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstDataInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgDataInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgDataInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY_BY_NAME(pstDataInd),0,\
                 IMSA_GET_MSG_LENGTH(pstDataInd));

    IMSA_WRITE_MSG_MSG_HEAD(pstDataInd,ID_IMSA_MSG_DATA_IND);

    /*���Ž�����ΪPS��*/
    pstDataInd->ucRcvDomain = 0;

    /*��дSMS����*/
    pstDataInd->ulDataLen  = ulDataLen;
    IMSA_MEM_CPY(pstDataInd->aucData,ucData,ulDataLen);

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstDataInd);

}

/*****************************************************************************
 Function Name  : IMSA_SMS_SndMsgReportInd()
 Description    : ����report��Ϣ
 Input          : ucData MSG���ݣ�ulDataLen MSG����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_SndMsgReportInd(VOS_UINT32 ulErrCode,
                                              const VOS_UINT8* pucData,
                                              VOS_UINT32 ulDataLen)
{
    IMSA_MSG_REPORT_IND_STRU    *pstReportInd;

    /*��������*/
    if(ulDataLen > SMR_SMT_RP_USER_DATA_LENGTH)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgReportInd:Length is too long!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgReportInd_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    /*������Ϣ�ռ�*/
    pstReportInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSG_REPORT_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstReportInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgReportInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgReportInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY_BY_NAME(pstReportInd),0,\
                 IMSA_GET_MSG_LENGTH(pstReportInd));

    IMSA_WRITE_MSG_MSG_HEAD(pstReportInd,ID_IMSA_MSG_REPORT_IND);

    /*��дSMS����*/
    pstReportInd->enErrorCode           = ulErrCode;

    if(VOS_NULL_PTR != pucData)
    {
        pstReportInd->stRpduData.ulDataLen  = ulDataLen;
        IMSA_MEM_CPY(pstReportInd->stRpduData.aucData,pucData,ulDataLen);
    }

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstReportInd);

}

/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsErr()
 Description    : �յ�IMSЭ��ջ�Ķ��Ŵ���Ĵ�����
 Input          : HICSM_OutputSms  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsErr(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;
    VOS_UINT32                          ulErrCode;

    pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();
    if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsErr: Mo entity is not WAIT_FOR_RP_ACK!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsErr_ENUM, 1);
        return;
    }

    /*MOʵ��״̬���п���̬��ֹͣTI_IMSA_SMS_TR1M������ʱ��*/
    pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;

    pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                   /* ���mem avail��־                        */
    pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;          /* ��λ�ط���־                             */

    IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);
    ulErrCode = SMR_SMT_ERROR_IMS_ERROR_BEGIN + pstOutSms->stErrorCode.usSipStatusCode;

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MO_SMS);
    #endif

    IMSA_SMS_SndMsgReportInd(ulErrCode,VOS_NULL_PTR,0);
    /* zhaochen 00308719 begin for VoLTE 2015-08-25 */
    IMSA_CommonDeregProc();
    /* zhaochen 00308719 end for VoLTE 2015-08-25 */
}


VOS_VOID IMSA_SMS_ProcNwSmsRpError(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;

    IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: enter.");
    TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, LNAS_ENTRY);

    pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();

    if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: Mo entity is not WAIT_FOR_RP_ACK!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, 2);
        return;
    }

    if(pstOutSms->aucMessage[1] != pstSmrMoEntity->ucMessageReference)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: MR is not equel.");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, 3);
        return;
    }

    /*MOʵ��״̬���п���̬��ֹͣTI_IMSA_SMS_TR1M������ʱ��*/
    pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;
    IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MO_SMS);
    #endif

    if (IMSA_SMS_TRUE == pstSmrMoEntity->ucMemAvailFlg )
    {
        /* �˹�����mem avail����                    */
        /* �Դ���ԭ��ֵ�Ĵ����ο�GU����ʵ�֣���Э��Ҫ����#41ʱ���ش�RP-SMMA�Ļ����ϣ�
        ������ԭ��ֵΪ#42��47,38ʱ�ش�RP-SMMA */
        if ((IMSA_SMR_ERR_CAUSE_TEMP_FAILURE   == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_CONGESTION  == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_RES_UNAVAIL == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_NET_OUT_OF_ORDER == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET]))
        {                                                               /* ��temporary error                        */
            IMSA_SMS_MemNotifyRetrans(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET]);         /* �����ط����̵Ĵ���                       */
        }
        else
        {
            /*��������RP ERR��������Я���Ĵ�����*/
            IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET],
                                       (VOS_UINT8*)pstOutSms->aucMessage,\
                                        pstOutSms->ucMessageLen);
            pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                   /* ���mem avail��־                        */
            pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;          /* ��λ�ط���־                             */
            pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;                                      /* ״̬Ǩ�Ƶ�����״̬                       */
            /* zhaochen 00308719 begin for VoLTE 2015-08-25 */
            IMSA_CommonDeregProc();
            /* zhaochen 00308719 end for VoLTE 2015-08-25 */
        }
    }
    else
    {
        /*��������RP ERR��������Я���Ĵ�����*/
        IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET],
                           (VOS_UINT8*)pstOutSms->aucMessage,\
                            pstOutSms->ucMessageLen);
        /* zhaochen 00308719 begin for VoLTE 2015-08-25 */
        IMSA_CommonDeregProc();
        /* zhaochen 00308719 end for VoLTE 2015-08-25 */
    }
}


/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsReceived()
 Description    : �յ�����Ķ������ݵĴ�����
 Input          : HICSM_OutputSms  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsReceived(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;
    IMSA_SMS_SMR_MT_STRU                *pstSmrMtEntity;

    /*������Ϣ���ʹ���*/
    switch(pstOutSms->aucMessage[0])
    {
    /*MT RP Data*/
    case IMSA_SMS_NTM_DATA_TYPE_RP_DATA:
        pstSmrMtEntity = IMSA_SMS_GetSmrMtEntityAddress();
        if(pstSmrMtEntity->enState != IMSA_SMS_SMR_STATE_IDLE)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: Mt entity is not idle!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 1);
            break;
        }

        /*MT���ţ�MTʵ��ת״̬������MR������TI_IMSA_SMS_TR2M��ʱ��*/
        pstSmrMtEntity->enState = IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK;
        pstSmrMtEntity->ucMessageReference = (VOS_UINT8)pstOutSms->aucMessage[1];
        IMSA_StartTimer(&pstSmrMtEntity->stTimerInfo);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����begin notify��Ϣ��RRC��֪ͨRRC������Դ*/
        IMSA_SendRrcDsdsBeginNotify(IMSA_LRRC_SESSION_TYPE_MT_SMS);
        #endif

        /*�������ݷ���MSG*/
        IMSA_SMS_SndMsgDataInd((VOS_UINT8*)pstOutSms->aucMessage,\
                                pstOutSms->ucMessageLen);
        break;

    /*MO RP ACK*/
    case IMSA_SMS_NTM_DATA_TYPE_RP_ACK:
        pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();
        if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: Mo entity is not WAIT_FOR_RP_ACK!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 2);
            break;
        }

        if(pstOutSms->aucMessage[1] != pstSmrMoEntity->ucMessageReference)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: MR is not equel.");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 3);
            break;
        }

        /*MOʵ��״̬���п���̬��ֹͣTI_IMSA_SMS_TR1M������ʱ��*/
        pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;
        IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);

        if (IMSA_SMS_TRUE == pstSmrMoEntity->ucMemAvailFlg)
        {                                                                   /* �˹�����mem avail����                    */
            pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                       /* ���mem avail��־                        */
            pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;              /* ��λ�ط���־                             */
        }

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MO_SMS);
        #endif

        IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_NO_ERROR,
                           (VOS_UINT8*)pstOutSms->aucMessage,\
                            pstOutSms->ucMessageLen);
        /* zhaochen 00308719 begin for VoLTE 2015-08-25 */
        IMSA_CommonDeregProc();
        /* zhaochen 00308719 end for VoLTE 2015-08-25 */
        break;

    case IMSA_SMS_NTM_DATA_TYPE_RP_ERR:
        IMSA_SMS_ProcNwSmsRpError(pstOutSms);
        break;

    default:
        IMSA_WARN_LOG("IMSA_SMS_ProcNwReportReceived: Msg Type ERR.");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, LNAS_MSG_INVALID);
        break;
    }


}

/*****************************************************************************
 Function Name  : IMSA_D2ImsMsgSmsEvent()
 Description    : D2IMS�������͵��¼�������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsMsgSmsEvent(VOS_VOID *pSmsEvent)
{
    IMSA_IMS_OUTPUT_SMS_EVENT_STRU       *pstOutSms;

    pstOutSms = (IMSA_IMS_OUTPUT_SMS_EVENT_STRU*)pSmsEvent;

    if(IMSA_IMS_OUTPUT_SMS_REASON_SMS_RECEIVED == pstOutSms->enOutputSmsReason)
    {
        IMSA_SMS_ProcNwSmsReceived(pstOutSms);
    }
    /*������Ϣ�ظ�*/
    else if(IMSA_IMS_OUTPUT_SMS_REASON_OK == pstOutSms->enOutputSmsReason)
    {
        IMSA_INFO_LOG("IMSA_ImsMsgSmsEvent: Receive OK!");
        TLPS_PRINT2LAYER_INFO(IMSA_SMS_ProcNwSmsReceived_ENUM, 2);
    }
    /*������*/
    else if(IMSA_IMS_OUTPUT_SMS_REASON_ERROR == pstOutSms->enOutputSmsReason)
    {
        IMSA_SMS_ProcNwSmsErr(pstOutSms);
    }
    else
    {
    }

}



#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcImsSmsMsg.c */



