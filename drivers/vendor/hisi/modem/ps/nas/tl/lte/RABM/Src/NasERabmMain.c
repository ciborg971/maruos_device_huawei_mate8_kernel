

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmMain.h"
#include  "LRrcLNasInterface.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasERabmETcMsgProc.h"
#include  "NasIpInterface.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmIpfOm.h"
#include  "NasERabmCdsMsgProc.h"
#include  "CdsErabmInterface.h"
#include  "PsRrmInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMMAIN_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
NAS_ERABM_ENTITY_STRU   g_stNasERabmEntity;                /*RABMʵ�嶨��*/
NAS_ERABM_ENTITY_STRU   *pg_stNasERabmEntity = &g_stNasERabmEntity;
VOS_UINT8              g_aucERabmIpData[NAS_ERABM_IP_HEADER_BUFFER_LEN] = {0};        /* ���ڴ洢ת����ʽ���IP��ͷ */
NAS_ERABM_SERVICE_STATE_ENUM_UINT32 g_enERabmSrState;           /*֪ͨEMM����Service req���̱�ʶ*/
EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32    g_enERabmUlDataPending = EMM_ERABM_NO_UP_DATA_PENDING;
VOS_UINT32             g_ulERabmBufTimerLength  = 60000;   /* ���ػ��涨ʱ������ʼ��Ϊ60�� */

NAS_COMM_PRINT_LIST_STRU g_astERabmRrcMsgIdArray[] =
{
    {   ID_LRRC_LRABM_QOS_UPDATE_REQ      ,
            "MSG:  ID_LRRC_LRABM_QOS_UPDATE_REQ                      ",
        VOS_NULL_PTR},
    {   ID_LRRC_LRABM_RAB_RSP             ,
            "MSG:  ID_LRRC_LRABM_RAB_RSP                             ",
        VOS_NULL_PTR},
    {   ID_LRRC_LRABM_RAB_IND             ,
            "MSG:  ID_LRRC_LRABM_RAB_IND                             ",
        NAS_ERABM_PrintRabmRrcRabInd},
    {   ID_LRRC_LRABM_STATUS_IND          ,
            "MSG:  ID_LRRC_LRABM_STATUS_IND                          ",
        NAS_ERABM_PrintRabmRrcStatusInd},
    {   ID_LRRC_LRABM_STATUS_RSP          ,
            "MSG:  ID_LRRC_LRABM_STATUS_RSP                          ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astERabmStateTimerArray[] =
{
    {   NAS_ERABM_WAIT_EPSB_ACT_TIMER               ,
            "STATE TI:  NAS_ERABM_WAIT_EPSB_ACT_TIMER                           "},
    {   NAS_ERABM_WAIT_RB_REEST_TIMER               ,
            "STATE TI:  NAS_ERABM_WAIT_RB_REEST_TIMER                           "}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astERabmAppMsgIdArray[] =
{
    {   ID_APP_ERABM_DATA_TRANS_REQ               ,
            "MSG:  ID_APP_ERABM_DATA_TRANS_REQ                           "},
    {   ID_APP_ERABM_DATA_TRANS_CNF               ,
            "MSG:  ID_APP_ERABM_DATA_TRANS_CNF                           "},
    {   ID_APP_ERABM_SERVICE_REQ                  ,
            "MSG:  ID_APP_ERABM_SERVICE_REQ                              "}
};

/* CDS-RABM ��Ϣ��ӡ���� */
NAS_COMM_PRINT_MSG_LIST_STRU g_astERabmCdsMsgIdArray[] =
{
    {   ID_CDS_ERABM_SERVICE_NOTIFY               ,
            "MSG:  ID_CDS_ERABM_SERVICE_NOTIFY                           "},
    {   ID_ERABM_CDS_SEND_BUFF_DATA_IND               ,
            "MSG:  ID_ERABM_CDS_SEND_BUFF_DATA_IND                       "},
    {   ID_ERABM_CDS_FREE_BUFF_DATA_IND                  ,
            "MSG:  ID_ERABM_CDS_FREE_BUFF_DATA_IND                       "},
    {   ID_QOS_FC_ERABM_RAB_CREATE_IND                  ,
            "MSG:  ID_QOS_FC_ERABM_RAB_CREATE_IND                       "},
    {   ID_QOS_FC_ERABM_RAB_RELEASE_IND                  ,
            "MSG:  ID_QOS_FC_ERABM_RAB_RELEASE_IND                       "}


};
NAS_ERABM_IPV4_SEGMENT_BUFF_STRU        g_stErabmIpv4SegBuff  = {NAS_ERABM_NULL};


/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ERABM_TaskEntry( MsgBlock* pMsg )
{
    PS_MSG_HEADER_STRU       *pHeader = VOS_NULL_PTR;              /*������Ϣͷָ��*/

    /* �ж���ڲ����Ƿ�Ϸ�*/
    if (VOS_NULL_PTR == pMsg)
    {
        /*���������Ϣ*/
        NAS_ERABM_WARN_LOG("NAS_ERABM_TaskEntry:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TaskEntry_ENUM, LNAS_ERABM_NoMsg);
        return;
    }

#if (VOS_WIN32 != VOS_OS_VER)
    TLPS_ExcLog_SaveMsgList(pMsg);
#endif


    pHeader = (PS_MSG_HEADER_STRU *)pMsg;          /* ��ȡ��Ϣͷָ��*/

    NAS_ERABM_PrintRabmRevMsg(pHeader,NAS_COMM_GET_ESM_PRINT_BUF());

    /*�жϽ��յ�����Ϣ,���зַ�����*/
    switch (pHeader->ulSenderPid)
    {
        /*�����SM��Ϣ������SM�ַ�����*/
        case PS_PID_ESM:
            NAS_ERABM_EsmMsgDistr(pMsg);
            break;

        /*�����EMM��Ϣ������EMM�ַ�����*/
        case PS_PID_MM:
            NAS_ERABM_EmmMsgDistr(pMsg);
            break;

        /*�����RRC��Ϣ������RRC�ַ�����*/
        case PS_PID_ERRC:
            NAS_ERABM_RrcMsgDistr(pMsg);
            break;

        /*�����Timer��Ϣ������Timer����ַ�����*/
        case VOS_PID_TIMER:
            NAS_ERABM_TimerMsgDistr(pMsg);
            break;

        /*�����APP��Ϣ������APP�ַ�����*/
        case PS_PID_APP:
            NAS_ERABM_AppMsgDistr(pMsg);
            break;

        case PS_PID_TC:
            NAS_ERABM_TcMsgDistr(pMsg);
            break;
        case UEPS_PID_CDS:
            NAS_ERABM_CdsMsgDistr(pMsg);
            break;
        /* ����RRM��Ϣ���� */
        case UEPS_PID_RRM:
            NAS_ERABM_RrmMsgDistr(pMsg);
            break;
        /*���Ͷ�����󣬱���*/
        default:
            NAS_ERABM_LOG1("NAS_ERABM_TaskEntry:NORM: Error SenderPid :",(VOS_INT32)pHeader->ulSenderPid);
            TLPS_PRINT2LAYER_INFO1(NAS_ERABM_TaskEntry_ENUM, LNAS_ERABM_ErrorSenderPid, (VOS_INT32)pHeader->ulSenderPid);
            break;
    }
    /* add by yanglei 00307272 for PRINTLOG_SEND,2015-08-14,begin */
    /* RABM��Ϣ���������ʹ�ӡ */
    TLPS_SendPrintBufferInfo();
    /* add by yanglei 00307272 for PRINTLOG_SEND,2015-08-14,end */

}
VOS_VOID NAS_ERABM_TimerStart
(
    VOS_UINT32                          ulTimerLen,
    NAS_ERABM_TIMER_NAME_ENUM_UINT8     enTimerName,
    VOS_UINT32                          ulTimerPara
)
{
    NAS_ERABM_START_TIMER_STRU       *pstTimerInfo = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_TimerStart is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_ENTRY);

    /*��ȡRABMʵ���еĶ�ʱ���ṹ��ַָ��*/
    pstTimerInfo = NAS_ERABM_GetRbTimer(enTimerName);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerStart: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerStart_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return ;
    }

    /*�ж϶�ʱ���Ƿ�򿪣�����ر�*/
    if (VOS_NULL_PTR != pstTimerInfo->stHTimer)
    {
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->stHTimer)))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_TimerStart: start reltimer error1 ");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL1);
            return;
        }

        NAS_ERABM_LOG1("(TimerType) Timer not close!", (VOS_INT32)enTimerName);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_TimerStart_ENUM, LNAS_ERABM_TimerName, (VOS_INT32)enTimerName);
    }

    if(NAS_ERABM_NULL == ulTimerLen)
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerStart:WARN: TimerLen = 0");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL2);
        return;
    }
    /* lihong00150010 emergency tau&service begin */
    /*�趨��ʱ��LENGTH��NAME����ʧ���򱨾�����*/
    if (VOS_OK !=
            PS_START_REL_TIMER(&(pstTimerInfo->stHTimer),PS_PID_RABM,
                                ulTimerLen,(VOS_UINT32)enTimerName, ulTimerPara,
                                VOS_RELTIMER_NOLOOP))
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerStart:WARN: start reltimer error2");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL3);
        return;
    }
    /* lihong00150010 emergency tau&service end */

    /*������ǰ�Ķ�ʱ����Ϣ */
    NAS_ERABM_SndOmErabmTimerStatus(NAS_ERABM_TIMER_RUNNING, enTimerName, ulTimerLen);


    /*���¶�ʱ��������Ϣ�Ͷ�ʱ�����*/
    pstTimerInfo->enName   = enTimerName;

    /*���ݶ�ʱ���Ĳ�ͬ����,��ӡ��Ӧ��Ϣ*/
    switch (enTimerName)
    {
        case NAS_ERABM_WAIT_EPSB_ACT_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_RB_WAIT_EPSB_ACT_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL5);
            break;

        case NAS_ERABM_WAIT_RB_REEST_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_WAIT_RB_REEST_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL6);
            break;

        case NAS_ERABM_WAIT_RB_RESUME_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_WAIT_RB_RESUME_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL7);
            break;

        case NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL8);
            break;
        case NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStart:NORM:RABM TimerStart: NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL9);
            break;
        default:
            NAS_ERABM_ERR_LOG("NAS_ERABM_TimerStart:ERROR: start unreasonable reltimer.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_TimerStart_ENUM, LNAS_FUNCTION_LABEL10);
            break;
    }
}
VOS_VOID NAS_ERABM_TimerStop( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    NAS_ERABM_START_TIMER_STRU       *pstTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                        ulTimerRemainLen;

    /*���ucTimerName��Ӧ�Ķ�ʱ����������״̬����ֹͣ�����򣬺���*/
    pstTimerInfo = NAS_ERABM_GetRbTimer(enTimerName);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerStop: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerStop_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return ;
    }

    if (VOS_NULL_PTR != pstTimerInfo->stHTimer)
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerInfo->stHTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->stHTimer)))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_TimerStop: stop reltimer fail ");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL1);
            return;
        }

        /*���¶�ʱ����ʱ����*/
        pstTimerInfo->ucExpireTimes = 0;


        /*������ǰ�Ķ�ʱ����Ϣ */
        NAS_ERABM_SndOmErabmTimerStatus(NAS_ERABM_TIMER_STOPED, enTimerName, ulTimerRemainLen);


        /*���ݶ�ʱ���Ĳ�ͬ����,��ӡ��Ӧ��Ϣ*/
        switch (enTimerName)
        {
            case NAS_ERABM_WAIT_EPSB_ACT_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_RB_WAIT_EPSB_ACT_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL2);
                break;

            case NAS_ERABM_WAIT_RB_REEST_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_WAIT_RB_REEST_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL3);
                break;

            case NAS_ERABM_WAIT_RB_RESUME_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_WAIT_RB_RESUME_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL4);
                break;

            case NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL5);
                break;
            case NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER:
                NAS_ERABM_NORM_LOG("NAS_ERABM_TimerStop:NORM:RABM TimerStop: NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER");
                TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL6);
                break;
            default:
                NAS_ERABM_ERR_LOG("NAS_ERABM_TimerStop:ERROR: stop unreasonable reltimer.");
                TLPS_PRINT2LAYER_ERROR(NAS_ERABM_TimerStop_ENUM, LNAS_FUNCTION_LABEL7);
                break;
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_IsTimerRunning
 Description     : ��ѯ��ʱ���Ƿ�������
 Input           : None
 Output          : None
 Return          : NAS_ERABM_TIMER_STATE_ENUM_UINT32

 History         :
    1.sunbing49683      2010-9-20  Draft Enact

*****************************************************************************/
NAS_ERABM_TIMER_STATE_ENUM_UINT32  NAS_ERABM_IsTimerRunning( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    NAS_ERABM_START_TIMER_STRU       *pstTimerInfo = VOS_NULL_PTR;

    /*���ucTimerName��Ӧ�Ķ�ʱ����������״̬����ֹͣ�����򣬺���*/
    pstTimerInfo = NAS_ERABM_GetRbTimer(enTimerName);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_NORM_LOG("NAS_ERABM_IsTimerRunning: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_IsTimerRunning_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return NAS_ERABM_TIMER_STATE_BUTT;
    }

    /*����״̬��ʱ���Ƿ�������*/
    if ( VOS_NULL_PTR != pstTimerInfo->stHTimer )
    {
        return NAS_ERABM_TIMER_STATE_RUNNING;
    }
    else
    {
        return NAS_ERABM_TIMER_STATE_STOPED;
    }

}


VOS_VOID NAS_ERABM_Init(VOS_VOID)
{
    VOS_UINT8                     ucTimerIndex  = 0;
    VOS_UINT32                    ulEpsbId      = 0;
    VOS_UINT32                    ulLoop        = 0;
    APP_ESM_IP_ADDR_STRU         *pstPdnAddr    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM                          START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_Init_ENUM, LNAS_ENTRY);

    /*��ʼ��RABMʵ��*/
    NAS_ERABM_MEM_SET((VOS_VOID*)NAS_ERABM_Entity(), NAS_ERABM_NULL, sizeof(NAS_ERABM_ENTITY_STRU));

    /* ��ʼ��RABMͳ����Ϣ */
    NAS_ERABM_DebugInit();

    /*����SERVICE����û������״̬*/
    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

    /*����RABMû�еȴ�EPS���ؼ�����Ϣ*/
    NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);

    /*����L MODE��״̬ΪSUSPENDED*/
    NAS_ERABM_SetLModeStatus(NAS_ERABM_L_MODE_STATUS_SUSPENDED);

    /*����RRC������RB�ĸ���Ϊ0*/
    NAS_ERABM_SetRbNumInfo(0);

    /*����Ψһ������û��TFT�ĳ��غ�ΪNAS_ERABM_ILL_EPSB_ID*/
    NAS_ERABM_GetOnlyActiveAndNoUlTftEpsbId() = NAS_ERABM_ILL_EPSB_ID;

    /*���ò�����������������*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    /*��ʼ����ʱ����Ϣ*/
    for ( ucTimerIndex = 0; ucTimerIndex < NAS_NAS_ERABM_TIMER_NAME_BUTT; ucTimerIndex++ )
    {
        NAS_ERABM_TimerStop(ucTimerIndex);
    }

    /*��ʼ��EPS�����б�*/
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);
        NAS_ERABM_SetEpsbIdInfo(ulEpsbId, ulEpsbId);
        NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId, NAS_ERABM_ILL_RB_ID);
        NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_DISCONNECTED);
        NAS_ERABM_MEM_SET(pstPdnAddr, NAS_ERABM_NULL, sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ERABM_ClearEpsbResource(ulEpsbId);
    }

    /*��ʼ��RB������ʱ����Ϣ*/
    for (ulLoop = 0; ulLoop < NAS_ERABM_MAX_EPSB_NUM; ulLoop++)
    {
        NAS_ERABM_SetRbSetupEpsbIdInfo(ulLoop, NAS_ERABM_ILL_EPSB_ID);
        NAS_ERABM_SetRbSetupRbIdInfo(ulLoop, NAS_ERABM_ILL_RB_ID);
    }

    /*��ʼ��RABM��������Ϣ*/
    NAS_ERABM_StAppDataBitIpv4(NAS_ERABM_OP_FALSE);
    NAS_ERABM_StAppDataBitIpv6(NAS_ERABM_OP_FALSE);
    NAS_ERABM_SetAppDataRmtPortIpv4(NAS_ERABM_NULL);
    NAS_ERABM_SetAppDataRmtPortIpv6(NAS_ERABM_NULL);
    NAS_ERABM_SetAppDataOperateType(APP_ERABM_DATA_TRANS_OPERATE_BUTT);
    NAS_ERABM_MEM_SET(NAS_ERABM_GetAppDataRemoteIpv4Addr(), NAS_ERABM_NULL,\
                sizeof(NAS_ERABM_GetAppDataRemoteIpv4Addr())/sizeof(VOS_UINT8));
    NAS_ERABM_MEM_SET(NAS_ERABM_GetAppDataRemoteIpv6Addr(), NAS_ERABM_NULL,\
                sizeof(NAS_ERABM_GetAppDataRemoteIpv6Addr())/sizeof(VOS_UINT8));

    NAS_ERABM_MEM_SET(NAS_ERABM_GET_IP_HEADER_BUFFER(), NAS_ERABM_NULL, NAS_ERABM_IP_HEADER_BUFFER_LEN);

    NAS_ERABM_MEM_SET(  NAS_ERABM_GetIpv4SegBuffAddr(),
                        NAS_ERABM_NULL,
                        sizeof(NAS_ERABM_IPV4_SEGMENT_BUFF_STRU));


    /* ��ʼ������NDIS Filter��Ч */
    NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);

    /* ��ʼ������NDIS��Ҫʹ�õ�IP Filter���� */
    NAS_ERABM_IpfUlNdisFilterInit();

    /* ��ʼ��IPFͳ����Ϣ */
    NAS_ERABM_IpfOmInit();
}


VOS_UINT32 NAS_ERABM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch ( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    NAS_ERABM_Init();
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SetEmmSrState
 Description     : ����Service���̷����ʶ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2010-9-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_SetEmmSrState( NAS_ERABM_SERVICE_STATE_ENUM_UINT32 enSrState )
{

    VOS_INT32     intLockLevel;

    if(enSrState >= NAS_ERABM_SERVICE_STATE_BUTT )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_SetEmmSrState: Para is err.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_SetEmmSrState_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    intLockLevel = VOS_SplIMP();

    g_enERabmSrState = enSrState;

    VOS_Splx(intLockLevel);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_GetEmmSrState
 Description     : ��ȡService���̷����ʶ
 Input           : None
 Output          : None
 Return          : NAS_ERABM_SERVICE_STATE_ENUM_UINT32

 History         :
    1.sunbing49683      2010-9-16  Draft Enact

*****************************************************************************/
NAS_ERABM_SERVICE_STATE_ENUM_UINT32  NAS_ERABM_GetEmmSrState( VOS_VOID )
{
    return g_enERabmSrState;
}



VOS_VOID NAS_ERABM_ClearRabmResource( VOS_VOID )
{
    VOS_UINT8                     ucTimerIndex  = NAS_ERABM_NULL;
    VOS_UINT32                    ulLoop        = NAS_ERABM_NULL;
    VOS_UINT32                    ulEpsbId      = NAS_ERABM_NULL;
    APP_ESM_IP_ADDR_STRU        *pstPdnAddr    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_ClearRabmResource is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_ClearRabmResource_ENUM, LNAS_ENTRY);

    /* ֹͣ�Ѿ������Ķ�ʱ�� */
    for (ucTimerIndex = 0; ucTimerIndex < NAS_NAS_ERABM_TIMER_NAME_BUTT; ucTimerIndex++)
    {
        NAS_ERABM_TimerStop(ucTimerIndex);
    }
    /* ������ڼ�����أ���֪ͨCDS�ͷŻ�������ݰ������ϴ��ж���Ϊ�˱����ظ�
       ֪ͨCDS�ͷŻ������ݰ� */
    if (0 != NAS_ERABM_GetActiveEpsBearerNum())
    {
        /* ֪ͨCDS�ͷŻ�������ݰ� */
        NAS_ERABM_SndErabmCdsFreeBuffDataInd();
    }
    /*��ʼ��RABMʵ��*/
    NAS_ERABM_MEM_SET((VOS_VOID*)NAS_ERABM_Entity(), NAS_ERABM_NULL, sizeof(NAS_ERABM_ENTITY_STRU));

    /* ��ʼ��RABMͳ����Ϣ */
    NAS_ERABM_DebugInit();

    /*����SERVICE����û������״̬*/
    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

    /*����RABMû�еȴ�EPS���ؼ�����Ϣ*/
    NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);

    /*����RRC������RB�ĸ���Ϊ0*/
    NAS_ERABM_SetRbNumInfo(0);

    /*����Ψһ������û��TFT�ĳ��غ�ΪNAS_ERABM_ILL_EPSB_ID*/
    NAS_ERABM_GetOnlyActiveAndNoUlTftEpsbId() = NAS_ERABM_ILL_EPSB_ID;

    /*���ò�����������������*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    /*��ʼ��EPS�����б�*/
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);
        NAS_ERABM_SetEpsbIdInfo(ulEpsbId, ulEpsbId);
        NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId, NAS_ERABM_ILL_RB_ID);
        NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_DISCONNECTED);
        NAS_ERABM_MEM_SET(pstPdnAddr, NAS_ERABM_NULL, sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ERABM_ClearEpsbResource(ulEpsbId);
    }

    /*��ʼ��RB������ʱ����Ϣ*/
    for (ulLoop = 0; ulLoop < NAS_ERABM_MAX_EPSB_NUM; ulLoop++)
    {
        NAS_ERABM_SetRbSetupEpsbIdInfo(ulLoop, NAS_ERABM_ILL_EPSB_ID);
        NAS_ERABM_SetRbSetupRbIdInfo(ulLoop, NAS_ERABM_ILL_RB_ID);
    }

    /*��ʼ��RABM��������Ϣ*/
    NAS_ERABM_StAppDataBitIpv4(NAS_ERABM_OP_FALSE);
    NAS_ERABM_StAppDataBitIpv6(NAS_ERABM_OP_FALSE);
    NAS_ERABM_SetAppDataRmtPortIpv4(NAS_ERABM_NULL);
    NAS_ERABM_SetAppDataRmtPortIpv6(NAS_ERABM_NULL);
    NAS_ERABM_SetAppDataOperateType(APP_ERABM_DATA_TRANS_OPERATE_BUTT);
    NAS_ERABM_MEM_SET(NAS_ERABM_GetAppDataRemoteIpv4Addr(), NAS_ERABM_NULL,\
             sizeof(NAS_ERABM_GetAppDataRemoteIpv4Addr())/sizeof(VOS_UINT8));
    NAS_ERABM_MEM_SET(NAS_ERABM_GetAppDataRemoteIpv6Addr(), NAS_ERABM_NULL,\
             sizeof(NAS_ERABM_GetAppDataRemoteIpv6Addr())/sizeof(VOS_UINT8));

    NAS_ERABM_MEM_SET(NAS_ERABM_GET_IP_HEADER_BUFFER(), NAS_ERABM_NULL, NAS_ERABM_IP_HEADER_BUFFER_LEN);

    NAS_ERABM_MEM_SET(  NAS_ERABM_GetIpv4SegBuffAddr(),
                        NAS_ERABM_NULL,
                        sizeof(NAS_ERABM_IPV4_SEGMENT_BUFF_STRU));

    /* �������FILTER���� */
    NAS_ERABM_MEM_SET(   NAS_ERABM_IPF_GET_DL_FILTER_PTR(0),
                        NAS_ERABM_NULL,
                        (NAS_ERABM_IPF_MAX_DL_FILTER * sizeof(IPF_FILTER_CONFIG_S)));
    NAS_ERABM_IPF_SET_DL_FILTER_NUM(0);

    /* ��ʼ������NDIS Filter��Ч */
    NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);
}
VOS_INT32  NAS_ERABM_PrintRabmRrcStatusInd
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT32                          ulLoop      = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    LRRC_LRABM_STATUS_IND_STRU           *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :LRRC_LRABM_STATUS_IND_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ��Ϣ��ÿ������*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enStatus = %d \r\n",
                       pstRcvMsg->enStatus,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulRabCnt = %d \r\n",
                       pstRcvMsg->ulRabCnt,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->ulRabCnt; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " aulRabId[%d] = %d \r\n",
                           ulLoop,
                           pstRcvMsg->aulRabId[ulLoop],
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :LRRC_LRABM_STATUS_IND_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}
VOS_INT32  NAS_ERABM_PrintRabmRrcRabInd
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT32                          ulLoop      = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    LRRC_LRABM_RAB_IND_STRU              *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;


    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :LRRC_LRABM_RAB_IND_STRU****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ��Ϣ��ÿ������*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " ulRabCnt = %d \r\n",
                       pstRcvMsg->ulRabCnt,
                       &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for (ulLoop = 0; ulLoop < pstRcvMsg->ulRabCnt; ulLoop++)
    {
        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " astRabInfo[%d].enRabChangeType = %d \r\n",
                           ulLoop,
                           pstRcvMsg->astRabInfo[ulLoop].enRabChangeType,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " astRabInfo[%d].ulRabId = %d \r\n",
                           ulLoop,
                           pstRcvMsg->astRabInfo[ulLoop].ulRabId,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_2(pcBuff,
                           usTotalLen,
                           " astRabInfo[%d].ulRbId = %d \r\n",
                           ulLoop,
                           pstRcvMsg->astRabInfo[ulLoop].ulRbId,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :LRRC_LRABM_RAB_IND_STRU****************",
                    &ilOutPutLen);

   usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}
VOS_INT32  NAS_ERABM_PrintRabmRrcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRabmRrcMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulRabmRrcMsgNum = sizeof(g_astERabmRrcMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulRabmRrcMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astERabmRrcMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulRabmRrcMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usOffset,
                         (VOS_CHAR *)(g_astERabmRrcMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astERabmRrcMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astERabmRrcMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ERABM_LOG1("NAS_ERABM_PrintRabmRrcMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_PrintRabmRrcMsg_ENUM, LNAS_PARAM_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  NAS_ERABM_PrintRabmAppMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRabmAppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulRabmAppMsgNum = sizeof(g_astERabmAppMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulRabmAppMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astERabmAppMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulRabmAppMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astERabmAppMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ERABM_LOG1("NAS_ERABM_PrintRabmAppMsg, Invalid enMsgId: ",enMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_PrintRabmAppMsg_ENUM, LNAS_PARAM_INVALID, enMsgId);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  NAS_ERABM_PrintRabmTimer
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    VOS_UINT32                           ulTimerType
)

{
    VOS_UINT32                          ulRabmTimerNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulRabmTimerNum = sizeof(g_astERabmStateTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulTimerType < ulRabmTimerNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astERabmStateTimerArray[ulTimerType].aucPrintString),
                         &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ERABM_LOG1("NAS_ERABM_PrintRabmTimer, Invalid enMsgId: ",ulTimerType);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_PrintRabmTimer_ENUM, LNAS_PARAM_INVALID, ulTimerType);
    }

    return (usTotalLen - usOffset);

}


VOS_INT32  NAS_ERABM_PrintRabmCdsMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    CDS_ERABM_MSG_ID_ENUM_UINT32         enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRabmAppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulRabmAppMsgNum = sizeof(g_astERabmCdsMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulRabmAppMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astERabmCdsMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulRabmAppMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astERabmCdsMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_ERABM_LOG1("NAS_ERABM_PrintRabmCdsMsg, Invalid enMsgId: ",enMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_PrintRabmCdsMsg_ENUM, LNAS_PARAM_INVALID, enMsgId);
    }

    return (usTotalLen - usOffset);

}
VOS_VOID NAS_ERABM_PrintRabmRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "NAS RABM Receive Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_PrintRabmRevMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_PrintRabmRevMsg_ENUM, LNAS_ReceiveMsgHeaderException);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ����PID����Ϣ */
    switch ( pstMsg->ulSenderPid )
    {
        case PS_PID_ESM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "ESM-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEsmRabmMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);

            break;

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "MM-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmRabmMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);

            break;

        case PS_PID_ERRC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RRC-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmRrcMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);

            break;

        case PS_PID_OM  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "APP(OM)-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmAppMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;

        case PS_PID_TC  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TC-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintRabmTcMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);
            break;


        case VOS_PID_TIMER  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TIMER-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmTimer(pcBuff,
                                            usTotalLen,
                                           ((REL_TIMER_MSG *)(VOS_VOID *) pstMsg)->ulPara);
            break;

        case UEPS_PID_CDS  :
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "CDS-->RABM\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmCdsMsg(    pcBuff,
                                                        usTotalLen,
                                                        pstMsg->ulMsgName);
            break;
        default:
            NAS_ERABM_LOG2("NAS_ERABM_PrintRabmRevMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulSenderPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_INFO2(NAS_ERABM_PrintRabmRevMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulSenderPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_ERABM_LOG2("NAS_ERABM_PrintRabmRevMsg, print return zero length.SenderPid, MsgId: ",
                      pstMsg->ulSenderPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO2(NAS_ERABM_PrintRabmRevMsg_ENUM, LNAS_FUNCTION_LABEL2, pstMsg->ulSenderPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}
VOS_VOID NAS_ERABM_PrintRabmSendMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)

{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "NAS RABM Send Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_PrintRabmSendMsg, Print send msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_PrintRabmSendMsg_ENUM, LNAS_SendMsgHeaderException);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    /* ��ӡ����PID����Ϣ */
    switch ( pstMsg->ulReceiverPid )
    {
        case PS_PID_ESM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->ESM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEsmRabmMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);
            break;

        case PS_PID_MM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->MM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmRabmMsg(
                                             pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);
            break;

        case PS_PID_ERRC :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->RRC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmRrcMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg);
            break;

        case PS_PID_OM  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->APP(OM)\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmAppMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;

        case PS_PID_TC  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->TC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintRabmTcMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;
        case UEPS_PID_CDS  :
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "RABM-->CDS\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ERABM_PrintRabmCdsMsg(    pcBuff,
                                                        usTotalLen,
                                                        pstMsg->ulMsgName);
            break;
        default:
            NAS_ERABM_LOG2("NAS_ERABM_PrintRabmSendMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulReceiverPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_INFO2(NAS_ERABM_PrintRabmSendMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_ERABM_LOG2("NAS_ERABM_PrintRabmSendMsg, print return zero length. ReceiverPid, MsgId: ",
                      pstMsg->ulReceiverPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO2(NAS_ERABM_PrintRabmSendMsg_ENUM, LNAS_FUNCTION_LABEL2, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff,usTotalLen);

    return ;

}

/*****************************************************************************
 Function Name   : NAS_ERABM_GetActiveEpsBearerNum
 Description     : ��ȡ����EPS������
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

  History        :
  1.lihong00150010      2011-12-05      Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ERABM_GetActiveEpsBearerNum( VOS_VOID )
{
    VOS_UINT32                 ulEpsbId     = NAS_ERABM_MIN_EPSB_ID;
    VOS_UINT32                 ulActiveNum  = NAS_ERABM_NULL;

    for ( ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++ )
    {
        if ( NAS_ERABM_EPSB_INACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            continue;
        }
        else
        {
            ulActiveNum++;
        }
    }

    return ulActiveNum;
}


VOS_VOID  NAS_ERABM_SndOmErabmTimerStatus(
    NAS_ERABM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus,
    NAS_ERABM_TIMER_NAME_ENUM_UINT8           enTimerId,
    VOS_UINT32                              ulTimerRemainLen
)
{
    NAS_ERABM_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_ERABM_TIMER_INFO_STRU*)NAS_ERABM_MEM_ALLOC(sizeof(NAS_ERABM_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndOmErabmTimerStatus: mem alloc fail!.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_RABM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ERABM_TIMER_INFO_STRU) - 20;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId + PS_MSG_ID_ERABM_TO_ERABM_OM_BASE;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->enTimerId                   = enTimerId;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_ERABM_MEM_FREE(pstMsg);

}

VOS_VOID NAS_REABM_RcvRabmRrmStatusInd()
{
    /* ��NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER�����ڼ䳢��RB�ؽ� */
    if(NAS_ERABM_TIMER_STATE_RUNNING == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
    {
        /* NAS_ERABM_WAIT_RB_REEST_TIMER��ʱ��δ���� */
        if (NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_WAIT_RB_REEST_TIMER))
        {
            NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_RB_REEST_LENGTH,
                                    NAS_ERABM_WAIT_RB_REEST_TIMER,
                                    VOS_FALSE);
            NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_INIT);
            NAS_ERABM_SndRabmEmmReestReq(VOS_FALSE);
        }
    }
    return;
}

VOS_VOID NAS_ERABM_RrmMsgDistr(VOS_VOID *pRcvMsg)
{
    PS_MSG_HEADER_STRU            *pRrcMsg;

    pRrcMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;
    switch(pRrcMsg->ulMsgName)
    {
        /* ID_RRM_PS_STATUS_IND��Ϣ���� */
        case ID_RRM_PS_STATUS_IND:
            NAS_REABM_RcvRabmRrmStatusInd();
            break;
        default:
            break;
    }
    return;
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


