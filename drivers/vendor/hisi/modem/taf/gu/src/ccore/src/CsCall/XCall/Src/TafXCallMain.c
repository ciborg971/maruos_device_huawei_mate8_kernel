

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallMain.h"
#include "TafXCallProcApp.h"
#include "TafXCallProcXcc.h"
#include "TafXCallProcMma.h"
#include "TafXCallProcVc.h"
#include "TafXCallMntn.h"
#include "AtMnInterface.h"
#include "xcc_xcall_pif.h"
#include "VcCallInterface.h"
#include "TafXCallProcTimer.h"
#include "TafXCallProcUsim.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* TAF XCALL ģ�鴦������AT/STK��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcAppTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {MN_CALL_APP_ORIG_REQ,                    TAF_XCALL_RcvAppCallOrigReq},
    {MN_CALL_APP_SUPS_CMD_REQ,                TAF_XCALL_RcvAppSupsCmdReq},
    {TAF_CALL_APP_SEND_FLASH_REQ,             TAF_XCALL_RcvAppSendFlashReq},
    {TAF_CALL_APP_SEND_BURST_DTMF_REQ,        TAF_XCALL_RcvAppSendBurstDTMFReq},
    {ID_TAFAGENT_MN_GET_CALL_INFO_REQ,        TAF_XCALL_RcvAgentGetCallInfoReq},
    {MN_CALL_APP_GET_INFO_REQ,                TAF_XCALL_RcvAppGetCallInfoReq},
    {MN_CALL_APP_XLEMA_REQ,                   TAF_XCALL_RcvAppXlemaReq},
    {TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ,       TAF_XCALL_RcvAppCustomDialReq},
    /* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
    {TAF_CALL_APP_SEND_CONT_DTMF_REQ,         TAF_XCALL_RcvAppSendContDTMFReq},
    /* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */
    {TAF_CALL_APP_SEND_CCLPR_REQ,             TAF_XCALL_RcvAtCclprGetReq}
};

/* TAF XCALL ģ�鴦������XCC��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcXccTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_XCC_XCALL_ORIG_CALL_CNF,              TAF_XCALL_RcvXccCallOrigCnf},

    {ID_XCC_XCALL_HANGUP_CALL_CNF,            TAF_XCALL_RcvXccCallHangUpCnf},

    {ID_XCC_XCALL_CALL_DISC_IND,              TAF_XCALL_RcvXccCallDiscInd},

    {ID_XCC_XCALL_INCOMING_CALL_IND,          TAF_XCALL_RcvXccCallIncomingInd},
    {ID_XCC_XCALL_ANSWER_CALL_CNF,            TAF_XCALL_RcvXccCallAnswerCnf},
    {ID_XCC_XCALL_CALL_CONNECT_IND,           TAF_XCALL_RcvXccCallConnectInd},

    {ID_XCC_XCALL_SEND_FLASH_CNF,             TAF_XCALL_RcvXccSendFlashCnf},

    {ID_XCC_XCALL_INFO_REC_IND,               TAF_XCALL_RcvXccInfoRecInd},

    {ID_XCC_XCALL_SEND_BURST_DTMF_CNF,        TAF_XCALL_RcvXccSendBurstDTMFCnf},

    {ID_XCC_XCALL_CODEC_OPEN_IND,             TAF_XCALL_RcvXccCodecOpenInd},
    {ID_XCC_XCALL_CODEC_CLOSE_IND,            TAF_XCALL_RcvXccCodecCloseInd},
    {ID_XCC_XCALL_CODEC_CHANGED_IND,          TAF_XCALL_RcvXccCodecChangedInd},
    {ID_XCC_XCALL_SO_CTRL_MSG_IND,            TAF_XCALL_RcvXccSoCtrlMsgInd},
    {ID_XCC_XCALL_SO_CTRL_ORDER_IND,          TAF_XCALL_RcvXccSoCtrlOrderInd},

    {ID_XCC_XCALL_NDSS_RESULT_IND,            TAF_XCALL_RcvXccNdssResultInd},

    /* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
    {ID_XCC_XCALL_SEND_CONT_DTMF_CNF,         TAF_XCALL_RcvXccSendContDTMFCnf},
    /* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */

    {ID_XCC_XCALL_BURST_DTMF_IND,             TAF_XCALL_RcvXccBurstDtmfInd},

    /* Added by k902809 for CDMA Iteration 16, 2015-7-25, begin */
    {ID_XCC_XCALL_CONT_DTMF_IND,             TAF_XCALL_RcvXccContDtmfInd}
    /* Added by k902809 for CDMA Iteration 16, 2015-7-25, end */
};

/* TAF XCALL ģ�鴦������MMA��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcMmaTab[]=
{
    {MMA_TAF_POWER_OFF_IND,                   TAF_XCALL_RcvMmaPowerOffInd},
    {ID_MMA_TAF_POWER_ON_IND,                 TAF_XCALL_RcvMmaPowerOnInd},
    {ID_MMA_TAF_1X_SERVICE_STATUS_IND,           TAF_XCALL_RcvMmaServiceStatusInd}
};

/* TAF XCALL ģ�鴦������VC��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcVcTab[]=
{
    /* ��ϢID */                              /* ��Ϣ������ */
    {VC_CALL_END_CALL,                      TAF_XCALL_RcvVcEndCall},
};

const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcTimerTab[]=
{
    /* ��ϢID */                                                /* ��Ϣ������ */
    {TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD,                      TAF_XCALL_RcvTiWaitCallRedialPeriodExpired},

    {TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL,                    TAF_XCALL_RcvTiWaitCallRedialIntervalExpired},

    {TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,            TAF_XCALL_RcvTiStartAndStopContDtmfIntervalExpired}
};

/* TAF XCALL ģ�鴦������USIM��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcUsimTab[]=
{
    {USIMM_READFILE_CNF,                   TAF_XCALL_RcvUsimReadFileCnf}
};

const VOS_UINT32 g_ulTafXcallMsgProcAppTabSize  = sizeof(g_astTafXcallMsgProcAppTab) / sizeof(g_astTafXcallMsgProcAppTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcXccTabSize  = sizeof(g_astTafXcallMsgProcXccTab) / sizeof(g_astTafXcallMsgProcXccTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcMmaTabSize  = sizeof(g_astTafXcallMsgProcMmaTab) / sizeof(g_astTafXcallMsgProcMmaTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcVcTabSize   = sizeof(g_astTafXcallMsgProcVcTab) / sizeof(g_astTafXcallMsgProcVcTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcTimerTabSize = sizeof(g_astTafXcallMsgProcTimerTab) / sizeof(g_astTafXcallMsgProcTimerTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcUsimTabSize  = sizeof(g_astTafXcallMsgProcUsimTab) / sizeof(g_astTafXcallMsgProcUsimTab[0]);


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_XCALL_ProcAppReqMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcAppTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcAppTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcAppTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcAppTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}
VOS_VOID TAF_XCALL_ProcXccMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcXccTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcXccTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcXccTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcXccTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}
VOS_VOID TAF_XCALL_ProcVcMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcVcTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcVcTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcVcTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcVcTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        pProcMsgFunc(pstMsg);
    }

    return;
}
VOS_VOID TAF_XCALL_ProcMmaMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcMmaTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcMmaTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcMmaTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcMmaTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}
VOS_VOID TAF_XCALL_ProcTimerOutMsg(
    REL_TIMER_MSG                      *pTmrMsg
)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId;

    enTimerId = pTmrMsg->ulName;

    /* ��g_astTafXcallMsgProcTimerTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcTimerTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcTimerTab[ulIndex].ulMsgType == enTimerId)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcTimerTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        TAF_XCALL_StopTimer(enTimerId, (VOS_UINT8)pTmrMsg->ulPara);

        pProcMsgFunc(pTmrMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}
VOS_VOID TAF_XCALL_ProcUsimMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcUsimTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcUsimTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcUsimTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcUsimTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}


/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




