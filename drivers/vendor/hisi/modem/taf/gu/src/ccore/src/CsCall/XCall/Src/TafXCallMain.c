

/*****************************************************************************
  1 头文件包含
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
  2 全局变量定义
*****************************************************************************/
/* TAF XCALL 模块处理来自AT/STK消息函数对应表*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcAppTab[]=
{
    /* 消息ID */                                /* 消息处理函数 */
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

/* TAF XCALL 模块处理来自XCC消息函数对应表*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcXccTab[]=
{
    /* 消息ID */                                /* 消息处理函数 */
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

/* TAF XCALL 模块处理来自MMA消息函数对应表*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcMmaTab[]=
{
    {MMA_TAF_POWER_OFF_IND,                   TAF_XCALL_RcvMmaPowerOffInd},
    {ID_MMA_TAF_POWER_ON_IND,                 TAF_XCALL_RcvMmaPowerOnInd},
    {ID_MMA_TAF_1X_SERVICE_STATUS_IND,           TAF_XCALL_RcvMmaServiceStatusInd}
};

/* TAF XCALL 模块处理来自VC消息函数对应表*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcVcTab[]=
{
    /* 消息ID */                              /* 消息处理函数 */
    {VC_CALL_END_CALL,                      TAF_XCALL_RcvVcEndCall},
};

const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcTimerTab[]=
{
    /* 消息ID */                                                /* 消息处理函数 */
    {TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD,                      TAF_XCALL_RcvTiWaitCallRedialPeriodExpired},

    {TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL,                    TAF_XCALL_RcvTiWaitCallRedialIntervalExpired},

    {TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,            TAF_XCALL_RcvTiStartAndStopContDtmfIntervalExpired}
};

/* TAF XCALL 模块处理来自USIM消息函数对应表*/
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
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_XCALL_ProcAppReqMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* 在g_astTafXcallMsgProcAppTab中查找对应的消息处理函数 */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcAppTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcAppTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id 匹配 */
            pProcMsgFunc = g_astTafXcallMsgProcAppTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* 消息处理前勾一下呼叫实体信息 */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* 消息处理后勾一下呼叫实体信息 */
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

    /* 在g_astTafXcallMsgProcXccTab中查找对应的消息处理函数 */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcXccTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcXccTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id 匹配 */
            pProcMsgFunc = g_astTafXcallMsgProcXccTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* 消息处理前勾一下呼叫实体信息 */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* 消息处理后勾一下呼叫实体信息 */
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

    /* 在g_astTafXcallMsgProcVcTab中查找对应的消息处理函数 */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcVcTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcVcTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id 匹配 */
            pProcMsgFunc = g_astTafXcallMsgProcVcTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* 如果处理函数存在则调用 */
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

    /* 在g_astTafXcallMsgProcMmaTab中查找对应的消息处理函数 */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcMmaTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcMmaTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id 匹配 */
            pProcMsgFunc = g_astTafXcallMsgProcMmaTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* 消息处理前勾一下呼叫实体信息 */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* 消息处理后勾一下呼叫实体信息 */
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

    /* 在g_astTafXcallMsgProcTimerTab中查找对应的消息处理函数 */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcTimerTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcTimerTab[ulIndex].ulMsgType == enTimerId)
        {
            /* Msg Id 匹配 */
            pProcMsgFunc = g_astTafXcallMsgProcTimerTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* 消息处理前勾一下呼叫实体信息 */
        TAF_XCALL_MNTN_LogCallInfo();

        TAF_XCALL_StopTimer(enTimerId, (VOS_UINT8)pTmrMsg->ulPara);

        pProcMsgFunc(pTmrMsg);

        /* 消息处理后勾一下呼叫实体信息 */
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

    /* 在g_astTafXcallMsgProcUsimTab中查找对应的消息处理函数 */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcUsimTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcUsimTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id 匹配 */
            pProcMsgFunc = g_astTafXcallMsgProcUsimTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* 消息处理前勾一下呼叫实体信息 */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* 消息处理后勾一下呼叫实体信息 */
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




