


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasETcMain.h"
#include  "NasETcEmmMsgProc.h"
#include  "NasETcPdcpMsgProc.h"
#include  "NasETcERabmMsgProc.h"
#include  "NasCommPrint.h"
#include  "NasETcPublic.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_NASTCMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCMAIN_C
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
/* Lģ״̬ */
NAS_ETC_L_MODE_STATUS_ENUM_UINT8         g_enEtcLModeStatus = NAS_ETC_L_MODE_STATUS_SUSPENDED;

NAS_ETC_MODE_TYPE_ENUM_UINT32            g_enEtcModeType = NAS_ETC_MODE_TYPE_NORMAL;

NAS_COMM_PRINT_MSG_LIST_STRU g_astETcPdcpMsgIdArray[] =
{
    {   ID_LTC_LPDCP_ACTIVATE_TEST_MODE               ,
            "MSG:  ID_LTC_LPDCP_ACTIVATE_TEST_MODE                           "},
    {   ID_LTC_LPDCP_ACTIVATE_TEST_MODE_CNF               ,
            "MSG:  ID_LTC_LPDCP_ACTIVATE_TEST_MODE_CNF                           "},
    {   ID_LTC_LPDCP_START_TEST_LOOP               ,
            "MSG:  ID_LTC_LPDCP_START_TEST_LOOP                           "},
    {   ID_LTC_LPDCP_START_TEST_LOOP_CNF               ,
            "MSG:  ID_LTC_LPDCP_START_TEST_LOOP_CNF                           "},
    {   ID_LTC_LPDCP_STOP_TEST_LOOP               ,
            "MSG:  ID_LTC_LPDCP_STOP_TEST_LOOP                           "},
    {   ID_LTC_LPDCP_STOP_TEST_LOOP_CNF               ,
            "MSG:  ID_LTC_LPDCP_STOP_TEST_LOOP_CNF                           "},
    {   ID_LTC_LPDCP_DEACTIVATE_TEST_MODE               ,
            "MSG:  ID_LTC_LPDCP_DEACTIVATE_TEST_MODE                           "},
    {   ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF               ,
            "MSG:  ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF                           "}

};

NAS_COMM_PRINT_MSG_LIST_STRU g_astETcCdsMsgIdArray[] =
{
    {   ID_ETC_CDS_ACT_TEST_MODE_NOTIFY               ,
            "MSG:  ID_ETC_CDS_ACT_TEST_MODE_NOTIFY                           "},
    {   ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY               ,
            "MSG:  ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY                           "}
};


NAS_COMM_PRINT_MSG_LIST_STRU g_astETcMtcMsgIdArray[] =
{
    {   ID_NAS_MTC_TC_STATUS_INFO_IND               ,
            "MSG:  ID_NAS_MTC_TC_STATUS_INFO_IND                           "}
};




/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ETC_TaskEntry( MsgBlock* pMsg )
{
    PS_MSG_HEADER_STRU       *pHeader = VOS_NULL_PTR;              /*������Ϣͷָ��*/

    /* �ж���ڲ����Ƿ�Ϸ�*/
    if (VOS_NULL_PTR == pMsg)
    {
        /*���������Ϣ*/
        NAS_ETC_WARN_LOG("NAS_ETC_TaskEntry:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_TaskEntry_ENUM, LNAS_TC_NoMsg);
        return;
    }

    pHeader = (PS_MSG_HEADER_STRU *)pMsg;          /* ��ȡ��Ϣͷָ��*/

    NAS_ETC_PrintTcRevMsg(pHeader,NAS_COMM_GET_ESM_PRINT_BUF());

    /*�жϽ��յ�����Ϣ,���зַ�����*/
    switch (pHeader->ulSenderPid)
    {
        /*�����EMM��Ϣ������EMM�ַ�����*/
        case PS_PID_MM:
            NAS_ETC_EmmMsgDistr(pMsg);
            break;

        /*�����RABM��Ϣ������RABM�ַ�����*/
        case PS_PID_RABM:
            NAS_ETC_RabmMsgDistr(pMsg);
            break;

        /*�����PDCP UL��Ϣ������PDCP UL�ַ�����*/
        case PS_PID_PDCP_UL:
            NAS_ETC_PdcpUlMsgDistr(pMsg);
            break;

        /*���Ͷ�����󣬱���*/
        default:
            NAS_ETC_LOG1("NAS_ETC_TaskEntry:NORM: Error SenderPid :",(VOS_INT32)pHeader->ulSenderPid);
            TLPS_PRINT2LAYER_INFO1(NAS_ETC_TaskEntry_ENUM, LNAS_TC_ErrorSenderPid, (VOS_INT32)pHeader->ulSenderPid);
            break;
    }
    /* add by yanglei 00307272 for PRINTLOG_SEND,2015-08-14,begin */
    /* ETC��Ϣ���������ʹ�ӡ */
    TLPS_SendPrintBufferInfo();
    /* add by yanglei 00307272 for PRINTLOG_SEND,2015-08-14,end */
}


VOS_VOID NAS_ETC_Init(VOS_VOID)
{
    /*����L MODE��״̬ΪSUSPENDED*/
    NAS_ETC_SetLModeStatus(NAS_ETC_L_MODE_STATUS_SUSPENDED);
}
VOS_UINT32 NAS_ETC_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch ( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    NAS_ETC_Init();
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


VOS_INT32  NAS_ETC_PrintTcPdcpMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTcPdcpMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulTcPdcpMsgNum = sizeof(g_astETcPdcpMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulTcPdcpMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astETcPdcpMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulTcPdcpMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astETcPdcpMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
    }
    else
    {
        NAS_ETC_LOG1("NAS_ETC_PrintTcPdcpMsg, Invalid enMsgId: ",enMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_ETC_PrintTcPdcpMsg_ENUM, LNAS_MSG_INVALID, enMsgId);
    }

    return ilOutPutLen;

}
VOS_INT32  NAS_COMM_PrintEtcCdsMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTcPdcpMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulTcPdcpMsgNum = sizeof(g_astETcCdsMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulTcPdcpMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astETcCdsMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulTcPdcpMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astETcCdsMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
    }
    else
    {
        NAS_ETC_LOG1("NAS_COMM_PrintEtcCdsMsg, Invalid enMsgId: ",enMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_COMM_PrintEtcCdsMsg_ENUM, LNAS_MSG_INVALID, enMsgId);
    }

    return ilOutPutLen;

}
VOS_INT32  NAS_COMM_PrintEtcMtcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    MTC_NAS_MSG_ID_ENUM_UINT32           enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTcMtcMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulTcMtcMsgNum = sizeof(g_astETcMtcMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulTcMtcMsgNum ; ulLoop++)
    {
        if (enMsgId == g_astETcMtcMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulTcMtcMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astETcMtcMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
    }
    else
    {
        NAS_ETC_LOG1("NAS_COMM_PrintEtcMtcMsg, Invalid enMsgId: ",enMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_COMM_PrintEtcMtcMsg_ENUM, LNAS_MSG_INVALID, enMsgId);
    }

    return ilOutPutLen;

}
VOS_VOID NAS_ETC_PrintTcRevMsg
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
                     "NAS TC Receive Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_ETC_WARN_LOG("NAS_ETC_PrintTcRevMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_PrintTcRevMsg_ENUM, LNAS_ReceiveMsgHeaderException);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ����PID����Ϣ */
    switch ( pstMsg->ulSenderPid )
    {

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "MM-->TC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmTcMsg(pcBuff,
                                                   usTotalLen,
                                                   pstMsg->ulMsgName);

            break;

        case PS_PID_RABM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "RABM-->TC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintRabmTcMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);

            break;

        case PS_PID_PDCP_UL:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "PDCP-->TC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ETC_PrintTcPdcpMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);

            break;

        default:
            NAS_ETC_LOG2("NAS_ETC_PrintTcRevMsg,Invalid Pid, MsgId: ",
                        pstMsg->ulSenderPid,
                        pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_INFO2(NAS_ETC_PrintTcRevMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulSenderPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_ETC_LOG2("NAS_ETC_PrintTcRevMsg, print return zero length.SenderPid, MsgId: ",
                    pstMsg->ulSenderPid,
                    pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO2(NAS_ETC_PrintTcRevMsg_ENUM, LNAS_FUNCTION_LABEL1, pstMsg->ulSenderPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}
VOS_VOID NAS_ETC_PrintTcSendMsg
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
                     "NAS TC Send Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_ETC_WARN_LOG("NAS_ETC_PrintTcSendMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_PrintTcSendMsg_ENUM, LNAS_ReceiveMsgHeaderException);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ����PID����Ϣ */
    switch ( pstMsg->ulReceiverPid )
    {

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TC-->MM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmTcMsg(pcBuff,
                                               usTotalLen,
                                               pstMsg->ulMsgName);

            break;

        case PS_PID_RABM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TC-->RABM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintRabmTcMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);

            break;

        case PS_PID_PDCP_UL:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TC-->PDCP\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_ETC_PrintTcPdcpMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);

            break;

        case UEPS_PID_CDS:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TC-->CDS\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEtcCdsMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);

            break;
        case UEPS_PID_MTC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TC-->MTC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintEtcMtcMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);
            break;
        default:
            NAS_ETC_LOG2("NAS_ETC_PrintTcSendMsg,Invalid Pid, MsgId: ",
                        pstMsg->ulSenderPid,
                        pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_INFO2(NAS_ETC_PrintTcSendMsg_ENUM, LNAS_PARAM_INVALID, pstMsg->ulSenderPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_ETC_LOG2("NAS_ETC_PrintTcSendMsg, print return zero length.SenderPid, MsgId: ",
                    pstMsg->ulSenderPid,
                    pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_INFO2(NAS_ETC_PrintTcSendMsg_ENUM, LNAS_FUNCTION_LABEL1, pstMsg->ulSenderPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ���յ�����Ϣʱ��Ӧ��ϵͳTICKֵ */
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "[ TICK : %ld ]",
                       PS_GET_TICK(),
                       &ilOutPutLen);
    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


