/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaImsAdaption.c
  Description     : ��C�ļ�ʵ��IMS��ص����书�ܣ����ַ�ת����
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaImsAdaption.h"
#include "ImsaPublic.h"
#include "ImsaImsInterface.h"
#include "ImsaImsApi.h"
#include "VcImsaInterface.h"
#include "ImsaProcImsRegMsg.h"
#include "ImsCodecInterface.h"
#include "ImsaProcImsCallMsg.h"
#include "ImsaProcImsSmsMsg.h"
#include "ImsaImsInterface.h"
#include "MnClient.h"
#include "NasCommPrint.h"
/* jiaguocai 00355737 begin for ccwa notify  2015-09-07 */
#include "ImsaProcSpmMsg.h"
/* jiaguocai 00355737 end for ccwa notify 2015-09-07 */

/* modify by jiqiang 2014.03.25 pclint fix error begin */
#include "ImsaProcImsUssdMsg.h"
/* modify by jiqiang 2014.03.25 pclint fix error end */

#include "ImsaProcAtMsg.h"
#include "ImsaRegManagement.h"

/* lihong00150010 hifi sync begin */
#include "ImsaLrrcInterface.h"
/* lihong00150010 hifi sync end */

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_IMSAIMSADAPTION_C
#define    THIS_NAS_FILE_ID    NAS_FILE_ID_IMSAIMSADAPTION_C
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
HTIMER    aphTimer[IMSA_IMS_TIMER_NAME_BUTT] = {0};


extern VOS_VOID IMSA_ImsMsgDistr(const VOS_VOID *pRcvMsg );
extern VOS_VOID IMSA_SndVcStartHifiMsg(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType );
extern VOS_VOID IMSA_SndVcChangeHifiParaMsg(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType );
extern VOS_VOID IMSA_SndVcStopHifiMsg(VOS_VOID);
extern VOS_VOID IMSA_SndSpmOpenCodecChannel(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType);
extern VOS_VOID IMSA_SndSpmCloseCodecChannel(VOS_VOID);


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_ImsaIntraMsgDistr()
 Description    : IMS��Ϣ�ַ�������ͨ��IMS��Ϣ���¼����жϷַ�����ͬ���ڲ�ģ�鴦��
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsMsgDistr(const VOS_VOID *pRcvMsg )
{
    /* ������Ϣͷָ��*/
    ImsaImsInterface_MSG          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (ImsaImsInterface_MSG *) pRcvMsg;

    /*�����¼�����*/
    switch(pHeader->stMsgData.ulMsgId)
    {
        case ID_IMS_IMSA_OUTPUT_SERVICE_MSG:
            IMSA_ImsMsgServiceEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_CALL_MSG:
            IMSA_ImsMsgCallEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_SMS_MSG:
            IMSA_ImsMsgSmsEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_SYSTEM_MSG:
            IMSA_ImsMsgSystemEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_PARA_MSG:
            IMSA_ImsMsgParaEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_USSD_MSG:
            IMSA_ImsMsgUssdEvent(&pHeader->stMsgData.aucMsg[0]);
            break;

        case ID_IMS_IMSA_OUTPUT_NV_INFO_MSG:
            IMSA_ImsMsgNvInfoEvent(&pHeader->stMsgData.aucMsg[0]);
            break;


        default:
            break;

    }
}
VOS_VOID IMSA_ProcHifiMsgTxDataInd
(
    const VOICE_IMSA_TX_DATA_IND_STRU  *pstTxDataInd
)
{
    IMSA_TX_VOICE_PARA_STRU             stTxPara = {0};

    IMSA_INFO_LOG("IMSA_ProcHifiMsgTxDataInd: enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcHifiMsgTxDataInd_ENUM, LNAS_ENTRY);

    stTxPara.usFrameType = pstTxDataInd->usFrameType;
    stTxPara.usStatus    = pstTxDataInd->usStatus;

    IMSA_Send2ImsTxVoiceData(&stTxPara,pstTxDataInd->ausData);
}

/*****************************************************************************
 Function Name  : IMSA_ProcHifiMsgRxDataAck()
 Description    : ����HIFI�ظ�ack�ĺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcHifiMsgRxDataAck
(
    const VOICE_IMSA_RX_DATA_ACK_STRU  *pstRxDataAck
)
{
    VOS_UINT8                           i;
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode = VOS_NULL_PTR;

    /* ���opid��ƥ�䣬����Դ���Ϣ */
    if (pstRxDataAck->ulOpid != IMSA_GetHifiDataOpid())
    {
        return;
    }

    /* ֹͣack������ʱ�� */
    IMSVA_StopTimer(&IMSA_GetHifiDataAckProtectTimer());

    /* ����������0 */
    IMSA_GetHifiDataSentDataNum() = 0;

    /* ����NV���õ������� �������Ϣ */
    for (i = 0 ; i < IMSA_GetHifiDataNeedAckNum() ; i ++)
    {
        /* ����������û����Ϣ����ֱ�ӷ��� */
        if ((0 == IMSA_GetHifiDataBufferDataNum()) || (VOS_NULL_PTR == IMSA_GetHifiDataBufferDataHead()))
        {
            IMSA_GetHifiDataBufferDataNum() = 0;
            /* �ͷ����� */
            while (VOS_NULL_PTR != IMSA_GetHifiDataBufferDataHead())
            {
                /* �ͷŽڵ� */
                pstTempNode = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
#if(VOS_WIN32 == VOS_OS_VER)
                /*PC���ԣ���Ҫ����MemFree���ͷ��ڴ�*/
                IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#else
                IMSA_FREE_MSG(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#endif
                IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());
                IMSA_GetHifiDataBufferDataHead() = pstTempNode;
            }
            IMSA_GetHifiDataBufferDataHead()     = VOS_NULL_PTR;
            IMSA_GetHifiDataBufferDataTail()     = VOS_NULL_PTR;
            return;
        }

        IMSA_GetHifiDataSentDataNum() ++;
        /* ���������Ϣ�ﵽ5��������Ҫ���ظ���־��ΪTRUE */
        if(IMSA_GetHifiDataNeedAckNum() != IMSA_GetHifiDataSentDataNum())
        {
            IMSA_SendOneBufferData(VOS_FALSE);
        }
        else
        {
            IMSA_SendOneBufferData(VOS_TRUE);

            /* ����ack������ʱ�� */
            IMSVA_StartTimer(&IMSA_GetHifiDataAckProtectTimer());
        }
    }
    return;
}


VOS_VOID IMSVA_ProcHifiMsg(const VOS_VOID *pRcvMsg )
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_VOICE_IMSA_TX_DATA_IND:
            IMSA_ProcHifiMsgTxDataInd((VOICE_IMSA_TX_DATA_IND_STRU*)pRcvMsg);
            break;

        default:

            /*��ӡ�쳣��Ϣ*/
            IMSA_WARN_LOG("IMSVA_ProcHifiMsg:Msg Id is err!");
            TLPS_PRINT2LAYER_WARNING(IMSVA_ProcHifiMsg_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSVA_ProcHifiRtMsg()
 Description    : IMSVA����VOICE_RT���͵���Ϣ�Ĵ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSVA_ProcHifiRtMsg(const VOS_VOID *pRcvMsg )
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;
    VOS_INT32                    intLockLevel;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_VOICE_IMSA_CFG_CNF:

            IMSA_INFO_LOG1("IMSA_VOICE_CFG_CNF,result=",((VOICE_IMSA_CFG_CNF_STRU*)pRcvMsg)->ulResult);
            TLPS_PRINT2LAYER_INFO1(IMSVA_ProcHifiMsg_ENUM, 1, ((VOICE_IMSA_CFG_CNF_STRU*)pRcvMsg)->ulResult);
            break;

        case ID_VOICE_IMSA_RX_DATA_ACK:

            /* ������� */
            intLockLevel = VOS_SplIMP();

            IMSA_ProcHifiMsgRxDataAck((VOICE_IMSA_RX_DATA_ACK_STRU*)pRcvMsg);

            /* ������� */
            VOS_Splx(intLockLevel);
            break;

        default:

            /*��ӡ�쳣��Ϣ*/
            IMSA_WARN_LOG("IMSVA_ProcHifiMsg:Msg Id is err!");
            TLPS_PRINT2LAYER_WARNING(IMSVA_ProcHifiMsg_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
/*****************************************************************************
 Function Name  : IMSVA_TimerMsgDistr()
 Description    : TIMER��Ϣ�ַ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-13  Draft Enact
*****************************************************************************/
VOS_VOID IMSVA_TimerMsgDistr(const REL_TIMER_MSG *pRcvMsg )
{
    IMSA_TIMER_ID_ENUM_UINT16           enTimerName;

    enTimerName = (VOS_UINT16)PS_GET_REL_TIMER_NAME(pRcvMsg);

    /* Ŀǰֻ����HIFI�ظ� */
    if ( TI_IMSA_HIFI_ACK_PROTECT == enTimerName )
    {
        IMSA_ProcTimerMsgHifiAckProtect(pRcvMsg);
    }

    else
    {
        /*lint -e961*/
        IMSA_ERR_LOG1("IMSVA_TimerMsgDistr: Unexpected event received! <enTimerName>",
            enTimerName);
        /*lint +e961*/

    }

    return;

}
/* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */



VOS_VOID IMSA_Snd2ImsaCallMsg
(
    const IMSA_IMS_OUTPUT_CALL_EVENT_STRU      *pstOutputCallEvent
)
{
    IMS_IMSA_OUTPUT_CALL_MSG_STRU      *pstMsgOutputCall = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgOutputCall = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_CALL_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputCall )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaCallMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaCallMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgOutputCall), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgOutputCall));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputCall,ID_IMS_IMSA_OUTPUT_CALL_MSG);

    IMSA_MEM_CPY(&pstMsgOutputCall->stOutputCall, \
                 pstOutputCallEvent, \
                 sizeof(IMSA_IMS_OUTPUT_CALL_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputCall);
}

/*****************************************************************************
 Function Name  : IMSA_Snd2ImsaSmsMsg()
 Description    : ��IMSA����SMS��Ϣ
 Input          : pstHicsmOutputSms
 Output         : VOS_VOID
 Return Value   : unsigned int ���ؽ�� 0�ɹ���1ʧ��

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_Snd2ImsaSmsMsg(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU *pstImsaImsOutputSms)
{
    IMS_IMSA_OUTPUT_SMS_MSG_STRU                *pstMsgOutputSms;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgOutputSms = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_SMS_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputSms )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaSmsMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaSmsMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgOutputSms), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgOutputSms));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputSms,ID_IMS_IMSA_OUTPUT_SMS_MSG);

    IMSA_MEM_CPY(&pstMsgOutputSms->stOutputSms, \
                 pstImsaImsOutputSms, \
                 sizeof(IMSA_IMS_OUTPUT_SMS_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputSms);

}

/*****************************************************************************
 Function Name  : IMSA_Snd2ImsaServiceMsg()
 Description    : ��IMSA����SERVCIE��Ϣ
 Input          : pstHicsmOutputService
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_Snd2ImsaServiceMsg(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU *pstOutputService)
{
    IMS_IMSA_OUTPUT_SERVICE_MSG_STRU      *pstMsgOutputService;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgOutputService = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_SERVICE_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputService )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaServiceMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaServiceMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgOutputService), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgOutputService));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputService,ID_IMS_IMSA_OUTPUT_SERVICE_MSG);

    IMSA_MEM_CPY(&pstMsgOutputService->stOutputService, \
                 pstOutputService, \
                 sizeof(IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputService);

}


VOS_VOID IMSA_Snd2ImsaParaMsg(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutputService)
{
    IMS_IMSA_OUTPUT_PARA_MSG_STRU      *pstMsgOutputPara;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgOutputPara = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_PARA_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputPara )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaParaMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaParaMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgOutputPara), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgOutputPara));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputPara,ID_IMS_IMSA_OUTPUT_PARA_MSG);

    IMSA_MEM_CPY(&pstMsgOutputPara->stOutputPara, \
                 pstOutputService, \
                 sizeof(IMSA_IMS_OUTPUT_PARA_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputPara);

}


VOS_VOID IMSA_Snd2ImsaSystemMsg(const IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU *pstOutputSystem)
{
    IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU      *pstMsgOutputSystem;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgOutputSystem = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgOutputSystem )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_Snd2ImsaSystemMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Snd2ImsaSystemMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgOutputSystem), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgOutputSystem));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMSA_MSG_HEAD(pstMsgOutputSystem,ID_IMS_IMSA_OUTPUT_SYSTEM_MSG);

    IMSA_MEM_CPY(&pstMsgOutputSystem->stOutputSystem, \
                 pstOutputSystem, \
                 sizeof(IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU));

    IMSA_SND_MSG(pstMsgOutputSystem);

}





unsigned int IMSA_Send2ImsaMsg(void *pstOutputEvent)
{
    IMSA_IMS_OUTPUT_EVENT_STRU  *pstImsaImsOutputEvent = pstOutputEvent;

    if( VOS_NULL_PTR == pstImsaImsOutputEvent)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_Send2ImsaMsg:ERROR:Para is null!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Send2ImsaMsg_ENUM, LNAS_NULL_PTR);
        return VOS_ERR;
    }

    switch(pstImsaImsOutputEvent->enEventType)
    {
        case IMSA_IMS_EVENT_TYPE_CALL:
            IMSA_Snd2ImsaCallMsg(&pstImsaImsOutputEvent->evt.stOutputCallEvent);
            break;
        case IMSA_IMS_EVENT_TYPE_SMS:
            IMSA_Snd2ImsaSmsMsg(&pstImsaImsOutputEvent->evt.stOutputSmsEvent);
            break;
        case IMSA_IMS_EVENT_TYPE_SERVICE:
            IMSA_Snd2ImsaServiceMsg(&pstImsaImsOutputEvent->evt.stOutputServiceEvent);
            break;

        case IMSA_IMS_EVENT_TYPE_PARA:
            IMSA_Snd2ImsaParaMsg(&pstImsaImsOutputEvent->evt.stOutputParaEvent);
            break;
        case IMSA_IMS_EVENT_TYPE_SYSTEM:
            IMSA_Snd2ImsaSystemMsg(&pstImsaImsOutputEvent->evt.stOutputSystemEvent);
            break;
        default:
            IMSA_WARN_LOG("IMSA_Snd2ImsaMsg:Type is err!");
            TLPS_PRINT2LAYER_ERROR(IMSA_Send2ImsaMsg_ENUM, LNAS_MSG_INVALID);
            break;
    }

    return VOS_OK;

}
VOS_VOID IMSA_SndHifiCfgReq( unsigned long ulTransTime, unsigned long ulSendBitrate )
{
    IMSA_VOICE_CFG_REQ_STRU                 *pstImsaCfgReq = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaCfgReq = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VOICE_CFG_REQ_STRU));

    if ( VOS_NULL_PTR == pstImsaCfgReq )
    {
       /*��ӡ�쳣��Ϣ*/
       IMSA_ERR_LOG("IMSA_SndHifiCfgReq:ERROR:Alloc Msg fail!");
       TLPS_PRINT2LAYER_ERROR(IMSA_SndHifiCfgReq_ENUM, LNAS_NULL_PTR);
       return ;
    }

    pstImsaCfgReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstImsaCfgReq->ulSenderPid      = PS_PID_IMSVA;

    /*CPU ID����Ҫ��д��OSA�����Ŀ��pid�ó�CPU ID���ٸ���CPU ID������Ϣ���͵���Ӧ��CPU��*/
    pstImsaCfgReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstImsaCfgReq->ulReceiverPid    = DSP_PID_VOICE;

    pstImsaCfgReq->usMsgId          = ID_IMSA_VOICE_CFG_REQ;

    pstImsaCfgReq->ulTransTime      = ulTransTime;

    pstImsaCfgReq->ulSendBitrate    = ulSendBitrate;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstImsaCfgReq);
}


/*****************************************************************************
 Function Name  : IMSA_SndVcStartHifiMsg()
 Description    : ��VC��������HIFI��Ϣ
 Input          : enCodecType
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndVcStartHifiMsg(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType )
{
    IMSA_VC_START_HIFI_NTF_STRU         *pstStartHifiNtf;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstStartHifiNtf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VC_START_HIFI_NTF_STRU));

    if ( VOS_NULL_PTR == pstStartHifiNtf )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndVcStartHifiMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndVcStartHifiMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*��д��Ϣͷ*/
    IMSA_WRITE_VC_MSG_HEAD(pstStartHifiNtf,ID_IMSA_VC_START_HIFI_NTF);

    pstStartHifiNtf->enMode = IMSA_VC_MODE_EUTRAN_IMS;

    switch(enCodecType)
    {
        case IMSA_VOICE_CODEC_AMR_NB:
        case IMSA_VOICE_CODEC_AMR_NB2:
            pstStartHifiNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMR;
            break;

        case IMSA_VOICE_CODEC_AMR_WB:
            pstStartHifiNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMRWB;
            break;

        case IMSA_VOICE_CODEC_G711:
            pstStartHifiNtf->enCodeType = IMSA_VC_CODEC_TYPE_G711;
            break;

        default:
            IMSA_WARN_LOG("IMSA_SndVcStartHifiMsg:codec type is err!");
            TLPS_PRINT2LAYER_ERROR(IMSA_SndVcStartHifiMsg_ENUM, LNAS_PARAM_INVALID);
            pstStartHifiNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMR;
            break;
    }

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstStartHifiNtf);

}

/*****************************************************************************
 Function Name  : IMSA_SndVcChangeHifiParaMsg()
 Description    : ��VC����codec�����Ϣ
 Input          : enCodecType
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndVcChangeHifiParaMsg(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType )
{
    IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU  *pstHifiParaChangeNtf;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstHifiParaChangeNtf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU));

    if ( VOS_NULL_PTR == pstHifiParaChangeNtf )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndVcChangeHifiParaMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndVcChangeHifiParaMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*��д��Ϣͷ*/
    IMSA_WRITE_VC_MSG_HEAD(pstHifiParaChangeNtf,ID_IMSA_VC_HIFI_PARA_CHANGED_NTF);

    pstHifiParaChangeNtf->enMode = IMSA_VC_MODE_EUTRAN_IMS;

    switch(enCodecType)
    {
        case IMSA_VOICE_CODEC_AMR_NB:
        case IMSA_VOICE_CODEC_AMR_NB2:
            pstHifiParaChangeNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMR;
            break;

        case IMSA_VOICE_CODEC_AMR_WB:
            pstHifiParaChangeNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMRWB;
            break;

        case IMSA_VOICE_CODEC_G711:
            pstHifiParaChangeNtf->enCodeType = IMSA_VC_CODEC_TYPE_G711;
            break;

        default:
            IMSA_WARN_LOG("IMSA_SndVcChangeHifiParaMsg:codec type is err!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SndVcChangeHifiParaMsg_ENUM, LNAS_PARAM_INVALID);
            pstHifiParaChangeNtf->enCodeType = IMSA_VC_CODEC_TYPE_AMR;
            break;
    }

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstHifiParaChangeNtf);

}

/*****************************************************************************
 Function Name  : IMSA_SndVcStopHifiMsg()
 Description    : ��VC����ֹͣHIFI��Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndVcStopHifiMsg(VOS_VOID)
{
    IMSA_VC_STOP_HIFI_NTF_STRU          *pstStopHifiNtf;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstStopHifiNtf = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VC_STOP_HIFI_NTF_STRU));

    if ( VOS_NULL_PTR == pstStopHifiNtf )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndVcStopHifiMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndVcStopHifiMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*��д��Ϣͷ*/
    IMSA_WRITE_VC_MSG_HEAD(pstStopHifiNtf,ID_IMSA_VC_STOP_HIFI_NTF);

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstStopHifiNtf);
}


/*****************************************************************************
 Function Name  : IMSA_SndSpmOpenCodecChannel
 Description    : IMSA��SPM���ʹ�ͨ������Ϣ
 Input          : enCodecType     ��������
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.sunbing 49683      2013-08-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndSpmOpenCodecChannel(IMSA_VOICE_CODEC_ENUM_UINT16 enCodecType)
{
    IMSA_SPM_CHANNEL_INFO_IND_STRU *pstSpmChannelInfoMsg = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstSpmChannelInfoMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CHANNEL_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSpmChannelInfoMsg)
    {
        IMSA_ERR_LOG("IMSA_SndSpmOpenCodecChannel: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndSpmOpenCodecChannel_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstSpmChannelInfoMsg), 0,IMSA_GET_MSG_LENGTH(pstSpmChannelInfoMsg));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmChannelInfoMsg, ID_IMSA_SPM_CHANNEL_INFO_IND);

    /* ����Client Id */
    pstSpmChannelInfoMsg->usClientId                          = MN_CLIENT_ID_BROADCAST;

    pstSpmChannelInfoMsg->ucIsLocalAlertingFlag               = VOS_FALSE;

    switch(enCodecType)
    {
        case IMSA_VOICE_CODEC_AMR_NB:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;
        case IMSA_VOICE_CODEC_EFR:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_EFR;
            break;
        case IMSA_VOICE_CODEC_FR:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_FR;
            break;
        case IMSA_VOICE_CODEC_HR:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_HR;
            break;
        case IMSA_VOICE_CODEC_AMR_NB2:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_AMR2;
            break;
        case IMSA_VOICE_CODEC_AMR_WB:
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_AMRWB;
            break;
        case IMSA_VOICE_CODEC_G711:
            pstSpmChannelInfoMsg->enCodecType = IMSA_VOICE_CODEC_G711;
            break;
        default:
            IMSA_WARN_LOG("IMSA_SndSpmOpenCodecChannel:codec type is err!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SndSpmOpenCodecChannel_ENUM, LNAS_PARAM_INVALID);
            pstSpmChannelInfoMsg->enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;

    }

    /* lihong00150010 ��ȫ���Ӷ� 2014-04-21 begin */
    /*pstSpmChannelInfoMsg->enChannelEvent                      = MN_CALL_EVT_CHANNEL_OPEN;
    pstSpmChannelInfoMsg->stChannelInfo.bChannelEnable        = VOS_TRUE;
    pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enMode = MN_CALL_RADIO_MODE_IMS_EUTRAN;

    switch(enCodecType)
    {
        case IMSA_VOICE_CODEC_AMR_NB:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;

        case IMSA_VOICE_CODEC_EFR:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_EFR;
            break;

        case IMSA_VOICE_CODEC_FR:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_FR;
            break;

        case IMSA_VOICE_CODEC_HR:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_HR;
            break;

        case IMSA_VOICE_CODEC_AMR_NB2:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_AMR2;
            break;

        case IMSA_VOICE_CODEC_AMR_WB:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_AMRWB;
            break;

        case IMSA_VOICE_CODEC_G711:
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = MN_CALL_CODEC_TYPE_G711;
            break;

        default:
            IMSA_WARN_LOG("IMSA_SndSpmOpenCodecChannel:codec type is err!");
            pstSpmChannelInfoMsg->stChannelInfo.stChannelParam.enCodecType = IMSA_VC_CODEC_TYPE_AMR;
            break;
    }*/
    /* lihong00150010 ��ȫ���Ӷ� 2014-04-21 end */

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstSpmChannelInfoMsg);
}

/*****************************************************************************
 Function Name  : IMSA_SndSpmCloseCodecChannel
 Description    : IMSA��SPM���͹ر�ͨ������Ϣ
 Input          : enCodecType     ��������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndSpmCloseCodecChannel(VOS_VOID)
{

}

/* lihong00150010 hifi sync begin */

VOS_VOID IMSA_SndLRrcHifiSyncSwtichInd
(
    VOS_UINT8                           ucHifiSyncEnalbed
)
{
    IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU    *pstRrcHifiSyncSwtichInd = VOS_NULL_PTR;

    /* ����DOPRA��Ϣ */
    pstRrcHifiSyncSwtichInd = (VOS_VOID *) IMSA_ALLOC_MSG(sizeof(IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU));
    if(VOS_NULL_PTR == pstRrcHifiSyncSwtichInd)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        IMSA_INFO_LOG("IMSA_SndLRrcHifiSyncSwtichInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndLRrcHifiSyncSwtichInd_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_INFO_LOG2("IMSA_SndLRrcHifiSyncSwtichInd: ucHifiSyncEnalbed = , ucPowerState = ",
                   ucHifiSyncEnalbed, IMSA_GetPowerState());
    TLPS_PRINT2LAYER_INFO2(IMSA_SndLRrcHifiSyncSwtichInd_ENUM, 1, ucHifiSyncEnalbed, IMSA_GetPowerState());

    /* ����Ϊ0 */
    IMSA_MEM_SET(pstRrcHifiSyncSwtichInd,0,sizeof(IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU));

    /*��д��Ϣͷ*/
    IMSA_WRITE_LRRC_MSG_HEAD(pstRrcHifiSyncSwtichInd,ID_IMSA_LRRC_HIFI_SYNC_SWITCH_IND,
                             sizeof(IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU));

    /* �����Ϣ�� */
    pstRrcHifiSyncSwtichInd->ucHifiSyncEnabled  = ucHifiSyncEnalbed;
    pstRrcHifiSyncSwtichInd->ucPowerState = IMSA_GetPowerState();

    /* ����DOPRA��Ϣ */
    IMSA_SND_MSG(pstRrcHifiSyncSwtichInd);

    return;
}

/* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
/*****************************************************************************
 �� �� ��  : IMSA_SndHifiDataInfo
 ��������  : ��IMSA�Ŀ��Ƶ�HIFI��Ϣ�Ķ����ͻ������ ��Ϣ����HIDS
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��13��
    ��    ��   : z00308719
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_SndHifiDataInfo(VOS_VOID)
{
    IMSA_HIFI_DATA_INFO_IND_STRU       *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndHifiDataInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_HIFI_DATA_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndHifiDataInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsg), 0, \
                                IMSA_GET_MSG_LENGTH(pstMsg));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstMsg,
                                ID_IMSA_HIFI_DATA_INFO_IND,
                                sizeof(IMSA_HIFI_DATA_INFO_IND_STRU));

    pstMsg->ulDataLoseNum        = IMSA_GetHifiDataDataLoseNum();
    pstMsg->ulTotalDataLoseNum   = IMSA_GetHifiDataTotalDataLoseNum();
    pstMsg->ulDataBufferNum      = IMSA_GetHifiDataDataBufferNum();
    pstMsg->ulTotalDataBufferNum = IMSA_GetHifiDataTotalDataBufferNum();

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}
/* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

unsigned int IMSA_StartVoiceDsp
(
    IMSA_VOICE_CODEC_ENUM_UINT16    enCodecType,
    unsigned long                   ulPacketTime,
    unsigned long                   ulSendBitrate
)
{
    IMSA_INFO_LOG("IMSA_StartVoiceDsp:the function is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StartVoiceDsp_ENUM, LNAS_ENTRY);

    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
    /*������صĻ���*/
    IMSA_ClearHifiData();
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

    /*֪ͨVC������HIFI*/
    IMSA_SndVcStartHifiMsg(enCodecType);

    /*֪ͨVC��codec���*/
    IMSA_SndVcChangeHifiParaMsg(enCodecType);

    /*֪ͨSPM����ģ��codec*/
    IMSA_SndSpmOpenCodecChannel(enCodecType);

    /*�������������Ϣ*/
    IMSA_CallClearLocalAlertInfo();

    /* ֪ͨHIFI�����ý������� */
    IMSA_SndHifiCfgReq(ulPacketTime, ulSendBitrate);

    /* lihong00150010 hifi sync begin */
    IMSA_SndLRrcHifiSyncSwtichInd(IMSA_TRUE);
    /* lihong00150010 hifi sync end */

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_StopVoiceDsp()
 Description    : ��˼�ṩ��D2 tech��API������D2 IMSЭ��ջ�ڹҶ����е绰�����
                  �ڸ�API�У�IMSA��֪ͨHIFI,ֹͣ���������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
*****************************************************************************/
unsigned int IMSA_StopVoiceDsp(void)
{
    IMSA_INFO_LOG("IMSA_StopVoiceDsp:the function is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StopVoiceDsp_ENUM, LNAS_ENTRY);

    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
    /* ��ά�ɲ� */
    IMSA_SndHifiDataInfo();

    /*������صĻ���*/
    IMSA_ClearHifiData();
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

    /*֪ͨVC��ֹͣHIFI*/
    IMSA_SndVcStopHifiMsg();

    /*ֹͣcodecͨ��*/
    /* IMSA_SndSpmCloseCodecChannel(); */

    /* lihong00150010 hifi sync begin */
    IMSA_SndLRrcHifiSyncSwtichInd(IMSA_FALSE);
    /* lihong00150010 hifi sync end */

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_Send2HifiRxVoiceData()
 Description    : D2IMSЭ��ջ���ã����ڽ������������ݷ��͸�HIFI��HIFI�յ����������
 Input          : usLength ��ʾ�������ݳ��ȣ�pcData���ݴ�ŵ�ַ(�ڴ��ɵ������ͷ�)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-15  Draft Enact
*****************************************************************************/
unsigned int IMSA_Send2HifiRxVoiceData(const IMSA_RX_VOICE_PARA_STRU *pstVoicePara,
                                               const unsigned short *pusData)
{
    IMSA_VOICE_RX_DATA_IND_STRU                 *pstRxDataInd;
    VOS_INT32                                    intLockLevel;

    if((VOS_NULL_PTR == pstVoicePara)
        ||(VOS_NULL_PTR == pusData))
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_Send2HifiRxVoiceData:ERROR Input Para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Send2HifiRxVoiceData_ENUM, LNAS_PARAM_INVALID);
        return VOS_ERR;
    }

    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRxDataInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_VOICE_RX_DATA_IND_STRU));

    if ( VOS_NULL_PTR == pstRxDataInd )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_Send2HifiRxVoiceData:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Send2HifiRxVoiceData_ENUM, LNAS_NULL_PTR);
        return VOS_ERR;
    }

    /* ��װ��Ϣ */
    pstRxDataInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstRxDataInd->ulSenderPid      = PS_PID_IMSVA;

    /*CPU ID����Ҫ��д��OSA�����Ŀ��pid�ó�CPU ID���ٸ���CPU ID������Ϣ���͵���Ӧ��CPU��*/
    pstRxDataInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstRxDataInd->ulReceiverPid    = DSP_PID_VOICE_RT;

    pstRxDataInd->usMsgId          = ID_IMSA_VOICE_RX_DATA_IND;

    pstRxDataInd->usCodecType      = pstVoicePara->enCodecType;
    pstRxDataInd->usDtxEnable      = pstVoicePara->usDtxEnable;
    pstRxDataInd->usErrorFlag      = pstVoicePara->usErrorFlag;
    pstRxDataInd->usRateMode       = pstVoicePara->usRateMode;
    pstRxDataInd->usFrameType      = pstVoicePara->usFrameType;
    pstRxDataInd->usQualityIdx     = pstVoicePara->usQualityIdx;
    pstRxDataInd->usSN             = pstVoicePara->usSN;
    pstRxDataInd->ulTS             = pstVoicePara->ulTS;
    pstRxDataInd->ulSSRC           = pstVoicePara->ulSsrc;

    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
    pstRxDataInd->ulNeedAckFlag    = VOS_FALSE;
    pstRxDataInd->ulOpid           = 0;
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

    IMSA_MEM_CPY(pstRxDataInd->ausData, pusData, IMSA_CODEC_MAX_DATA_LEN*sizeof(unsigned short));

    /* ���NVû�д򿪣��򲻽��д�������ԭ����ֱ�ӷ��� */
    if (VOS_FALSE == IMSA_GetHifiDataControlFlag())
    {
        /* ������Ϣ���ͺ�����HIFI������������£�����Ϣ����ʧ�ܣ��ᶪ������Ϣ�������������λ */
        /*IMSA_SND_MSG(pstRxDataInd);*/
        IMSA_SND_MSG_NORMALLY(pstRxDataInd);
        return VOS_OK;
    }

    /* ������͹�����Ϣ������Ϊ���õ�������˵��HIFI֮ǰ��û�лظ�����ʱ���� */
    /* ������� */
    intLockLevel = VOS_SplIMP();
    if (IMSA_GetHifiDataNeedAckNum() <= IMSA_GetHifiDataSentDataNum())
    {
        /* ���溯�� */
        IMSA_AddDataToBuffer(pstRxDataInd);

        /* ������� */
        VOS_Splx(intLockLevel);
        return VOS_OK;
    }

    /* ������Ϣ����+1 */
    IMSA_GetHifiDataSentDataNum() ++;

    /* ������� */
    VOS_Splx(intLockLevel);
    /* ������͵���Ϣ�����������õ�����������ҪHIFI�ظ� */
    if (IMSA_GetHifiDataNeedAckNum() <= IMSA_GetHifiDataSentDataNum())
    {
        pstRxDataInd->ulNeedAckFlag = VOS_TRUE;
        /* ����OPID */
        IMSA_GetHifiDataOpid() ++;
        pstRxDataInd->ulOpid        = IMSA_GetHifiDataOpid();
        /* ����ack������ʱ�� */
        IMSVA_StartTimer(&IMSA_GetHifiDataAckProtectTimer());
    }
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */


    /* ������Ϣ���ͺ�����HIFI������������£�����Ϣ����ʧ�ܣ��ᶪ������Ϣ�������������λ */
    /*IMSA_SND_MSG(pstRxDataInd);*/
    IMSA_SND_MSG_NORMALLY(pstRxDataInd);

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_SndD2ImsMsgStopReq()
 Description    : ��IMS���͹ػ���Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgStopReq(VOS_VOID  )
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgStopReq:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgStopReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstImsaImsInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SYSTEM;

    pstImsaImsInputEvent->evt.stInputSystemEvent.enInputSysReason = IMSA_IMS_INPUT_SYSTEM_REASON_STOP;

    pstImsaImsInputEvent->evt.stInputSystemEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgSystemEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);

}


/*****************************************************************************
 Function Name  : IMSA_SndD2ImsMsgStartReq()
 Description    : ��IMS���Ϳ�����Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgStartReq(VOS_VOID  )
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgStartReq:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgStartReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstImsaImsInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SYSTEM;

    pstImsaImsInputEvent->evt.stInputSystemEvent.enInputSysReason = IMSA_IMS_INPUT_SYSTEM_REASON_START;

    pstImsaImsInputEvent->evt.stInputSystemEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgSystemEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);

}


VOS_VOID IMSA_SndImsMsgSystemEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent)
{
    IMSA_IMS_INPUT_SYSTEM_MSG_STRU              *pstMsgInputSystem;

    IMSA_INFO_LOG("IMSA_SndImsMsgSystemEvent:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndImsMsgSystemEvent_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgInputSystem = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_SYSTEM_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputSystem )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndD2ImsMsgSystemEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgSystemEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgInputSystem), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgInputSystem));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputSystem,ID_IMSA_IMS_INPUT_SYSTEM_MSG);

    IMSA_MEM_CPY(&pstMsgInputSystem->stInputSystem, \
                 &pstImsaImsInputEvent->evt.stInputSystemEvent, \
                 sizeof(IMSA_IMS_INPUT_SYSTEM_EVENT_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsgInputSystem);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputSystem);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsgInputSystem);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}
VOS_VOID IMSA_SndImsMsgParaEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent)
{
    IMSA_IMS_INPUT_PARA_MSG_STRU              *pstMsgInputPara;

    IMSA_INFO_LOG("IMSA_SndImsMsgParaEvent:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndImsMsgParaEvent_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgInputPara = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_PARA_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputPara )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgParaEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgParaEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgInputPara), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgInputPara));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputPara,ID_IMSA_IMS_INPUT_PARA_MSG);

    IMSA_MEM_CPY(&pstMsgInputPara->stInputPara, \
                 &pstImsaImsInputEvent->evt.stInputParaEvent, \
                 sizeof(IMSA_IMS_INPUT_PARA_EVENT_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsgInputPara);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputPara);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsgInputPara);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}
VOS_VOID IMSA_SndImsMsgNvInfoEvent
(
    IMSA_IMS_INPUT_EVENT_STRU   *pstImsaImsInputEvent,
    VOS_UINT32                  ulNvInfoStruLen
)
{
    IMSA_IMS_INPUT_NV_INFO_MSG_STRU     *pstMsgInputNvInfo;

    IMSA_INFO_LOG("IMSA_SndImsMsgNvInfoEvent:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndImsMsgNvInfoEvent_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgInputNvInfo = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_NV_INFO_MSG_STRU)
                                                    + ulNvInfoStruLen - IMSA_NV_INFO_LEN);

    if ( VOS_NULL_PTR == pstMsgInputNvInfo )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgParaEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgNvInfoEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgInputNvInfo), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgInputNvInfo));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputNvInfo,ID_IMSA_IMS_INPUT_NV_INFO_MSG);

    IMSA_MEM_CPY(&pstMsgInputNvInfo->stInputNvInfo, \
                 &pstImsaImsInputEvent->evt.stInputNvInfoEvent, \
                 sizeof(IMSA_IMS_INPUT_NV_INFO_EVENT_STRU)+ ulNvInfoStruLen - IMSA_NV_INFO_LEN);


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsgInputNvInfo);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputNvInfo);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsgInputNvInfo);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}


/*****************************************************************************
 Function Name  : IMSA_SndImsMsgServiceEvent()
 Description    : ��IMS����Service�¼�
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgServiceEvent(IMSA_IMS_INPUT_EVENT_STRU *pstHiInputEvent)
{
    IMSA_IMS_INPUT_SERVICE_MSG_STRU              *pstMsgInputSevice;

    IMSA_INFO_LOG("IMSA_SndImsMsgServiceEvent:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndImsMsgServiceEvent_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgInputSevice = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_SERVICE_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputSevice )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgServiceEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgServiceEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgInputSevice), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgInputSevice));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputSevice,ID_IMSA_IMS_INPUT_SERVICE_MSG);



    IMSA_MEM_CPY(&pstMsgInputSevice->stInputService, \
                 &pstHiInputEvent->evt.stInputServiceEvent, \
                 sizeof(IMSA_IMS_INPUT_SERVICE_EVENT_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsgInputSevice);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputSevice);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsgInputSevice);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstHiInputEvent);

#endif

}
VOS_VOID IMSA_SndImsMsgCallEvent(const IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent)
{
    IMSA_IMS_INPUT_CALL_MSG_STRU                 *pstMsgInputCall;

    if(VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_SndImsMsgCallEvent:Input para err!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgCallEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgInputCall = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_CALL_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputCall )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgCallEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgCallEvent_ENUM, 2);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgInputCall), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgInputCall));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputCall,ID_IMSA_IMS_INPUT_CALL_MSG);

    IMSA_MEM_CPY(&pstMsgInputCall->stInputCall, \
                 &pstInputEvent->evt.stInputCallEvent, \
                 sizeof(IMSA_IMS_INPUT_CALL_EVENT_STRU));

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsgInputCall);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputCall);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsgInputCall);

    IMSA_NORM_LOG1("before write ims event,tick value:", PS_GET_TICK());
    TLPS_PRINT2LAYER_INFO1(IMSA_SndImsMsgCallEvent_ENUM, IMSA_TICK, PS_GET_TICK());

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstInputEvent);

    IMSA_NORM_LOG1("after write ims event,tick value:", PS_GET_TICK());
    TLPS_PRINT2LAYER_INFO1(IMSA_SndImsMsgCallEvent_ENUM, IMSA_TICK, PS_GET_TICK());

#endif

}


/*****************************************************************************
 Function Name  : IMSA_SndImsMsgSmsEvent()
 Description    : ��IMS����Sms�¼�
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndImsMsgSmsEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent)
{
    IMSA_IMS_INPUT_SMS_MSG_STRU                  *pstMsgInputSms;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgInputSms = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_SMS_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputSms )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgSmsEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgSmsEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgInputSms), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgInputSms));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputSms,ID_IMSA_IMS_INPUT_SMS_MSG);

    IMSA_MEM_CPY(&pstMsgInputSms->stInputSms, \
                 &pstImsaImsInputEvent->evt.stInputSmsEvent, \
                 sizeof(IMSA_IMS_INPUT_SMS_EVENT_STRU));

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsgInputSms);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputSms);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsgInputSms);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}
VOS_VOID IMSA_SndImsMsgUssdEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent)
{
    IMSA_IMS_INPUT_USSD_MSG_STRU                  *pstMsgInputUssd;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstMsgInputUssd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_IMS_INPUT_USSD_MSG_STRU));

    if ( VOS_NULL_PTR == pstMsgInputUssd )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgUssdEvent:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgUssdEvent_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgInputUssd), 0, \
               IMSA_GET_MSG_LENGTH(pstMsgInputUssd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_IMS_MSG_HEAD(pstMsgInputUssd,ID_IMSA_IMS_INPUT_USSD_MSG);

    IMSA_MEM_CPY(&pstMsgInputUssd->stInputUssd, \
                 &pstImsaImsInputEvent->evt.stInputUssdEvent, \
                 sizeof(IMSA_IMS_INPUT_USSD_EVENT_STRU));

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsgInputUssd);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsgInputUssd);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsgInputUssd);

    (VOS_VOID)IMSA_WriteImsEvent((VOS_VOID*)pstImsaImsInputEvent);

#endif

}
VOS_UINT32 IMSA_ImsInputParaMsgSave(const IMSA_IMS_INPUT_PARA_EVENT_STRU *pstParaEvt)
{
    IMSA_ENTITY_STRU *pstImsaEntity = IMSA_CtxGet();

    IMSA_INFO_LOG("IMSA_ImsInputParaMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ImsInputParaMsgSave_ENUM, LNAS_ENTRY);

    pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmId     = pstParaEvt->ulOpId;
    pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmReason = pstParaEvt->enInputParaReason;

    return VOS_TRUE;
}


VOS_VOID IMSA_ImsInputParaMsgClear(VOS_VOID)
{
    IMSA_ENTITY_STRU *pstImsaEntity = IMSA_CtxGet();

    IMSA_INFO_LOG("IMSA_ImsInputParaMsgClear is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ImsInputParaMsgClear_ENUM, LNAS_ENTRY);

    pstImsaEntity->stImsaControlManager.stImsMsg.bitOpImsMsg = IMSA_FALSE;
    pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmId     = 0;
    pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmReason = 0xffffffff;
}


VOS_VOID IMSA_SendImsVolteImpuQryReq(VOS_VOID)
{
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SendImsVolteImpuQryReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendImsVolteImpuQryReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SendImsVolteImpuQryReq:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendImsVolteImpuQryReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstImsaImsInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_PARA;
    pstImsaImsInputEvent->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_QUERY_IMPU;
    pstImsaImsInputEvent->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /* �����ѯIMPU����Ϣ */
    (VOS_VOID)IMSA_ImsInputParaMsgSave(&pstImsaImsInputEvent->evt.stInputParaEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);

    return;
}
VOS_VOID IMSA_SendImsCcwaiSetReq(VOS_UINT8 ucCallWaiting)
{
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SendImsCcwaiSetReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendImsCcwaiSetReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SendImsCcwaiSetReq:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendImsCcwaiSetReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstImsaImsInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_PARA;
    pstImsaImsInputEvent->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_CALL_WAITING;
    pstImsaImsInputEvent->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    pstImsaImsInputEvent->evt.stInputParaEvent.u.stUeCapability.ucCallWaiting = ucCallWaiting;

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /* ��������CCWAI����Ϣ */
    (VOS_VOID)IMSA_ImsInputParaMsgSave(&pstImsaImsInputEvent->evt.stInputParaEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);

    return;
}
VOS_VOID IMSA_ProcImsMsgQryVolteImpuCnf(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutPara)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    VOS_UINT32                          ulImpuLen = 0;
    VOS_CHAR                            aucImpu[IMSA_IMS_EVENT_STRING_SZ+1] = {0};

    IMSA_INFO_LOG("IMSA_ProcImsMsgQryVolteImpuCnf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgQryVolteImpuCnf_ENUM, LNAS_ENTRY);

    if (VOS_TRUE == pstOutPara->bitOpResult)
    {
        ulResult = pstOutPara->ulResult;
    }

    if (VOS_TRUE == pstOutPara->bitOpImpu)
    {
        ulImpuLen = pstOutPara->ulImpuLen;

        IMSA_MEM_CPY(aucImpu, \
                 pstOutPara->aucImpu, \
                 IMSA_IMS_EVENT_STRING_SZ+1);
    }

    IMSA_SndMsgAtQryVolteImpuCnf(ulResult, ulImpuLen, aucImpu);

}


VOS_VOID IMSA_ProcImsMsgCcwaiSetCnf(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutPara)
{
    VOS_UINT32                          ulResult = VOS_ERR;
    /*jiaguocai 00355737 begin for ccwa 2015-09-07*/
    IMSA_AT_CONTROL_STRU                *pstImsaAtControl;

    pstImsaAtControl = IMSA_GetAtControlAddress();
    /*jaiguocai 00355737 end for ccwa 2015-09-07*/

    IMSA_INFO_LOG("IMSA_ProcImsMsgCcwaiSetCnf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, LNAS_ENTRY);

    if (IMSA_IMS_OUTPUT_PARA_REASON_SET_OK == pstOutPara->enOutputParaReason)
    {
        ulResult = VOS_OK;

        /*jiaguocai 00355737 begin for ccwa 2015-09-07*/
        /*��TAF����ccwa������Ϣ*/
        IMSA_CallSendCcwaCapInfo(pstImsaAtControl->enMode);
        /*jiaguocai 00355737 end for ccwa 2015-09-07*/
    }

    IMSA_SndMsgAtCcwaiSetCnf(ulResult);
}





/*****************************************************************************
 Function Name  : IMSA_ImsStartTimer()
 Description    : IMSЭ��ջ���ã�����������ʱ��
 Input          : pstTimerPara ��ʱ��������ŵ�ַ(�ڴ��ɵ������ͷ�)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-25  Draft Enact
*****************************************************************************/
unsigned int IMSA_ImsStartTimer(const IMSA_TIMER_PARA_STRU  *pstTimerPara)
{
    if((VOS_NULL_PTR == pstTimerPara)
        ||(pstTimerPara->ulTimerName >= IMSA_IMS_TIMER_NAME_BUTT))
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ImsStartTimer:ERROR input para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, LNAS_PARAM_INVALID);
        return VOS_ERR;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != aphTimer[pstTimerPara->ulTimerName])
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(aphTimer[pstTimerPara->ulTimerName])))
        {
            /*��ӡ�쳣��Ϣ*/
            IMSA_WARN_LOG("IMSA_D2ImsStartTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, IMSA_CALL_API_ERROR);
            return VOS_ERR;
        }

        /*��ӡ�쳣��Ϣ*/
        IMSA_WARN_LOG1("(TimerType) Timer not close!",pstTimerPara->ulTimerName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, IMSA_TIMER_PARA, pstTimerPara->ulTimerName);
    }

    if (pstTimerPara->ulLen == 0)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ImsStartTimer:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, 1);
        return VOS_ERR;
    }

    /*�趨��ʱ��NAME����ʧ���򱨾�����*/
    if (VOS_OK !=\
            PS_START_CALLBACK_REL_TIMER(&(aphTimer[pstTimerPara->ulTimerName]),\
                                        PS_PID_IMSVA,  pstTimerPara->ulLen, \
                                        pstTimerPara->ulTimerName,\
                                        pstTimerPara->ulParam, pstTimerPara->ucMode,\
                                        (REL_TIMER_FUNC)pstTimerPara->TimeOutRoutine, \
                                        pstTimerPara->enPrecision))
    {
          /*��ӡ�쳣��Ϣ*/
          IMSA_WARN_LOG("IMSA_ImsStartTimer:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_WARNING(IMSA_ProcImsMsgCcwaiSetCnf_ENUM, 2);
          return VOS_ERR;
    }

    return VOS_OK;

}


/*****************************************************************************
 Function Name  : IMSA_D2ImsStartTimer()
 Description    : IMSЭ��ջ���ã�����ֹͣ��ʱ��
 Input          : pstTimerPara ��ʱ��������ŵ�ַ(�ڴ��ɵ������ͷ�)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-25  Draft Enact
*****************************************************************************/
unsigned int IMSA_ImsStopTimer(unsigned int  ulTimerName)
{
    if(ulTimerName >= IMSA_IMS_TIMER_NAME_BUTT)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ImsStopTimer:ERROR input para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ImsStopTimer_ENUM, LNAS_PARAM_INVALID);
        return VOS_ERR;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != aphTimer[ulTimerName])
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(aphTimer[ulTimerName])))
        {
            /*��ӡ�쳣��Ϣ*/
            IMSA_WARN_LOG("IMSA_ImsStopTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_ImsStopTimer_ENUM, IMSA_CALL_API_ERROR);
            return VOS_ERR;
        }

        aphTimer[ulTimerName] = VOS_NULL_PTR;
    }

    return VOS_OK;

}

/*****************************************************************************
 Function Name  : IMSVA_StartTimer()
 Description    : IMSVA���ã�����������ʱ��
 Input          : pstTimerPara ��ʱ��������ŵ�ַ(�ڴ��ɵ������ͷ�)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSVA_StartTimer(IMSA_TIMER_STRU *pstTimer)
{
    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            IMSA_WARN_LOG("IMSVA_StartTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_StartTimer_ENUM, LNAS_ERROR);
            return;
        }

        /*��ӡ�쳣��Ϣ*/
        IMSA_WARN_LOG1("(TimerType) Timer not close!",pstTimer->usName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_StartTimer_ENUM, 2, pstTimer->usName);
    }

    if (pstTimer->ulTimerLen == 0)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSVA_StopTimer:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(IMSA_StartTimer_ENUM, 3);
        return;
    }

    /*�趨��ʱ��NAME����ʧ���򱨾�����*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimer->phTimer),PS_PID_IMSVA,\
                                pstTimer->ulTimerLen,(VOS_UINT32)pstTimer->usName,\
                                pstTimer->usPara,pstTimer->ucMode))
    {
          /*��ӡ�쳣��Ϣ*/
          IMSA_WARN_LOG("IMSVA_StartTimer:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_WARNING(IMSA_StartTimer_ENUM, 4);
          return;
    }

}

/*****************************************************************************
 Function Name  : IMSVA_StopTimer()
 Description    : IMSVA���ã�����ֹͣ��ʱ��
 Input          : pstTimerPara ��ʱ��������ŵ�ַ(�ڴ��ɵ������ͷ�)
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSVA_StopTimer(IMSA_TIMER_STRU *pstTimer)
{
    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            IMSA_WARN_LOG("IMSA_StopTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_StopTimer_ENUM, IMSA_CALL_API_ERROR);
            return;
        }

        pstTimer->phTimer = VOS_NULL_PTR;

        IMSA_INFO_LOG1("(TimerType) Timer closed!",pstTimer->usName);
        TLPS_PRINT2LAYER_INFO(IMSA_StopTimer_ENUM, LNAS_TIMER_STOP);
    }

}


/* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
/*****************************************************************************
 Function Name  : IMSA_ImsAdaption_Init()
 Description    : ��ʼ���ӿ���صĺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsAdaption_Init(VOS_VOID)
{
    IMSA_HIFI_DATA_MANAGER_STRU        *pstHifiDataManager;
    pstHifiDataManager = IMSA_GetHifiDataManagerAddress();
    IMSA_ClearHifiData();
    /*���ö�ʱ�����ȣ����Ƶ�*/
    pstHifiDataManager->stHifiAckProtectTimer.usName     = TI_IMSA_HIFI_ACK_PROTECT;
    pstHifiDataManager->stHifiAckProtectTimer.ulTimerLen = IMSA_HIFI_ACK_PROTECT_LENGTH;
    pstHifiDataManager->stHifiAckProtectTimer.ucMode     = 0;
    pstHifiDataManager->ulTotalDataLoseNum               = 0;
    pstHifiDataManager->ulTotalDataBufferNum             = 0;
}

/*****************************************************************************
 Function Name  : IMSA_ClearHifiData()
 Description    : ���HIFI���ƺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ClearHifiData(VOS_VOID)
{
    /* IMSA��Ҫ���Ƹ�HIFI����Ϣ���ٶȣ���ֹ��λ�� */
    IMSA_HIFI_DATA_MANAGER_STRU        *pstHifiDataManager;
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode = VOS_NULL_PTR;
    pstHifiDataManager = IMSA_GetHifiDataManagerAddress();

    /* �ͷ����� */
    while (VOS_NULL_PTR != pstHifiDataManager->pstBufferDataHead)
    {
        /* �ͷŽڵ� */
        pstTempNode = pstHifiDataManager->pstBufferDataHead->pstNextBufferData;
    #if(VOS_WIN32 == VOS_OS_VER)
        /*PC���ԣ���Ҫ����MemFree���ͷ��ڴ�*/
        IMSA_MEM_FREE(pstHifiDataManager->pstBufferDataHead->pstRxDataInd);
    #else
        IMSA_FREE_MSG(pstHifiDataManager->pstBufferDataHead->pstRxDataInd);
    #endif
        IMSA_MEM_FREE(pstHifiDataManager->pstBufferDataHead);
        pstHifiDataManager->pstBufferDataHead = pstTempNode;
    }
    pstHifiDataManager->pstBufferDataHead     = VOS_NULL_PTR;
    pstHifiDataManager->pstBufferDataTail     = VOS_NULL_PTR;
    pstHifiDataManager->ucBufferDataNum       = 0;
    pstHifiDataManager->ucSentDataNum         = 0;
    pstHifiDataManager->ulOpid                = 0;
    pstHifiDataManager->ulDataLoseNum         = 0;
    pstHifiDataManager->ulDataBufferNum       = 0;
}

/*****************************************************************************
 Function Name  : IMSA_AddDataToBuffer()
 Description    : ����Ϣ��ӵ�����������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_AddDataToBuffer(IMSA_VOICE_RX_DATA_IND_STRU *pstRxDataInd)
{
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode;
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode2;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /* ��������ڵ��ڴ� */
    pstTempNode = (VOS_VOID*)IMSA_MEM_ALLOC(sizeof(IMSA_HIFI_DATA_BUFFER_NODE_STRU));
    if ( VOS_NULL_PTR == pstTempNode )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_AddDataToBuffer:ERROR:Alloc Msg fail!");
        return;
    }
    pstTempNode->pstRxDataInd      = pstRxDataInd;
    pstTempNode->pstNextBufferData = VOS_NULL_PTR;

    /* ��ά�ɲ� */
    IMSA_GetHifiDataDataBufferNum() ++;
    IMSA_GetHifiDataTotalDataBufferNum() ++;

    /* �������Ϊ�գ����ʼ����������Ϣ�������ͷ��㣬��ǰ�ڵ�ָ���ͷ���ָ����ͬ */
    if (0 == IMSA_GetHifiDataBufferDataNum() || VOS_NULL_PTR == IMSA_GetHifiDataBufferDataHead())
    {
        IMSA_GetHifiDataBufferDataNum() = 0;

        /* �ͷ����� */
        while (VOS_NULL_PTR != IMSA_GetHifiDataBufferDataHead())
        {
            /* �ͷŽڵ� */
            pstTempNode2 = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
#if(VOS_WIN32 == VOS_OS_VER)
            /*PC���ԣ���Ҫ����MemFree���ͷ��ڴ�*/
            IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#else
            IMSA_FREE_MSG(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#endif
            IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());
            IMSA_GetHifiDataBufferDataHead() = pstTempNode2;
        }
        IMSA_GetHifiDataBufferDataHead()     = VOS_NULL_PTR;
        IMSA_GetHifiDataBufferDataTail()     = pstTempNode;

        /* �����ǳ�ʼ������ͷ����β�ڵ���ͬһ���ڵ� */
        IMSA_GetHifiDataBufferDataHead() = IMSA_GetHifiDataBufferDataTail();

        /* �ڵ����+1 */
        IMSA_GetHifiDataBufferDataNum()++;
        return;
    }

    /* ����Ϣ��ӵ��������� */
    /* ȡ��һ���ڵ�ĵ�ַ����Ϊ�µĵ�ǰ�ڵ��ַ */
    IMSA_GetHifiDataBufferDataTail()->pstNextBufferData = pstTempNode;
    IMSA_GetHifiDataBufferDataTail() = IMSA_GetHifiDataBufferDataTail()->pstNextBufferData;


    /* �ڵ����+1 */
    IMSA_GetHifiDataBufferDataNum()++;

    /* ����������ˣ���ɾ��ͷ��㣬���ڶ����ڵ���Ϊͷ��� */
    while (IMSA_GetHifiDataMaxBufferNum() < IMSA_GetHifiDataBufferDataNum())
    {
        /* ��ά�ɲ� */
        IMSA_GetHifiDataDataLoseNum() ++;
        IMSA_GetHifiDataTotalDataLoseNum() ++;

        /* �ͷŵ�ͷ�����ڴ� */
        pstTempNode = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
        IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());

        /* ���ڶ����ڵ���Ϊ�µ�ͷ��� */
        IMSA_GetHifiDataBufferDataHead() = pstTempNode;
        IMSA_GetHifiDataBufferDataNum() --;
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_SendOneBufferData()
 Description    : �ӻ���������ȡ��һ�����ͳ�ȥ
 Input          : ucNeedAckFlag ��ҪHIFI�ظ��ı�־
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SendOneBufferData(VOS_UINT8 ulNeedAckFlag)
{
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode;
    IMSA_VOICE_RX_DATA_IND_STRU        *pstRxDataInd;

    pstRxDataInd = IMSA_GetHifiDataBufferDataHead()->pstRxDataInd;
    pstRxDataInd->ulNeedAckFlag = ulNeedAckFlag;
    if (VOS_TRUE == ulNeedAckFlag)
    {
        IMSA_GetHifiDataOpid() ++;
        pstRxDataInd->ulOpid        = IMSA_GetHifiDataOpid();
    }
    IMSA_SND_MSG_NORMALLY(pstRxDataInd);

    /* �ͷŵ�ͷ�����ڴ� */
    pstTempNode = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
    IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());

    /* ���ڶ����ڵ���Ϊ�µ�ͷ��� */
    IMSA_GetHifiDataBufferDataHead() = pstTempNode;

    /* �ڵ����-1 */
    IMSA_GetHifiDataBufferDataNum()--;

    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgHifiAckProtect()
 Description    : ����HIFI��ִ������ʱ����ʱ�ĺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-11-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgHifiAckProtect(const VOS_VOID *pRcvMsg)
{
    VOS_INT32                           intLockLevel;
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstTempNode = VOS_NULL_PTR;

    /* ������� */
    intLockLevel = VOS_SplIMP();

    /* �����ǰû�л������Ϣ���򽫷�������-1 */
    if (0 == IMSA_GetHifiDataBufferDataNum() || VOS_NULL_PTR == IMSA_GetHifiDataBufferDataHead())
    {
        IMSA_GetHifiDataBufferDataNum() = 0;
        /* �ͷ����� */
        while (VOS_NULL_PTR != IMSA_GetHifiDataBufferDataHead())
        {
            /* �ͷŽڵ� */
            pstTempNode = IMSA_GetHifiDataBufferDataHead()->pstNextBufferData;
#if(VOS_WIN32 == VOS_OS_VER)
            /*PC���ԣ���Ҫ����MemFree���ͷ��ڴ�*/
            IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#else
            IMSA_FREE_MSG(IMSA_GetHifiDataBufferDataHead()->pstRxDataInd);
#endif
            IMSA_MEM_FREE(IMSA_GetHifiDataBufferDataHead());
            IMSA_GetHifiDataBufferDataHead() = pstTempNode;
        }
        IMSA_GetHifiDataBufferDataHead()     = VOS_NULL_PTR;
        IMSA_GetHifiDataBufferDataTail()     = VOS_NULL_PTR;
        IMSA_GetHifiDataSentDataNum() --;

        /* ������� */
        VOS_Splx(intLockLevel);
        return;
    }

    /* �����ǰ�л������Ϣ���򽫻���������ͷ������Ϣ������������ʱ�� */
    IMSA_SendOneBufferData(VOS_TRUE);

    /* ������� */
    VOS_Splx(intLockLevel);

    /* ����ack������ʱ�� */
    IMSVA_StartTimer(&IMSA_GetHifiDataAckProtectTimer());
    return;
}
/* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

/*lint +e961*/
/*lint +e960*/


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaImsAdaption.c */



