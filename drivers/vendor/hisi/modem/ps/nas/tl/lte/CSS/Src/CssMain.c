

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "CssMain.h"


#define    THIS_FILE_ID        PS_FILE_ID_CSSMAIN_C

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
CSS_CONTROL_STRU                        g_stCssControl;
CSS_CONTROL_STRU                       *pgstCssControl = &g_stCssControl;

/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID CSS_MsgHandle(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;
    #if (VOS_WIN32 != VOS_OS_VER)
    TLPS_ExcLog_SaveMsgList((VOS_VOID *)pHeader);
    #endif

    #if (VOS_OS_VER != VOS_WIN32)
    NAS_TRACE_HIGH(" CSS_MsgHandle pHeader->ulMsgName = %d", pHeader->ulMsgName);
    TLPS_PRINT2LAYER_INFO1(CSS_MsgHandle_ENUM, LNAS_ENTRY, pHeader->ulMsgName);
    #endif

    CSS_PrintCssRevMsg(pHeader,CSS_GET_CSS_PRINT_BUF());

    switch(pHeader->ulSenderPid)
    {
        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case WUEPS_PID_MMC:
        case PS_PID_ERRC:
            CSS_ProcCommMsg(pRcvMsg);
            break;

        case PS_PID_MM:
            CSS_ProcLmmMsg(pRcvMsg);
            break;

        case PS_PID_HPA:
            CSS_ProcLphyMsg(pRcvMsg);
            break;

        case VOS_PID_TIMER:
            CSS_ProcTimerMsg((REL_TIMER_MSG *)pRcvMsg);
            break;

        default:
            break;

    }
}


VOS_VOID CSS_TaskEntry(MsgBlock * pMsg)/*lint -e818 -e830*/
{
    /* 判断入口参数是否合法*/
    if( VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 消息处理 */
    CSS_MsgHandle((const VOS_VOID *)pMsg);
    /* add by yanglei 00307272 for PRINTLOG_SEND,2015-08-14,begin */
    /* CSS消息处理完推送打印 */
    TLPS_SendPrintBufferInfo();
    /* add by yanglei 00307272 for PRINTLOG_SEND,2015-08-14,end */

}


VOS_UINT32 CSS_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:

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


VOS_UINT32 CSS_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                              ulRet;

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:

                ulRet = VOS_RegisterPIDInfo(PS_PID_CSS,
                                            CSS_PidInit,
                                            CSS_TaskEntry);

                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }


                ulRet = VOS_RegisterMsgTaskPrio(UEPS_FID_CSS, VOS_PRIORITY_M1);
                if( PS_SUCC != ulRet )
                {
                    return ulRet;
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
    }

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif



