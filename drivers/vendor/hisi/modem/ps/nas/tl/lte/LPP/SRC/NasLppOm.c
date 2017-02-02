/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasLppOm.c
  版 本 号   : 初稿
  作    者   : XiaoJun
  生成日期   : 2015年8月14日
  最近修改   :
  功能描述   : LTE  LPP 的OM的功能接口
  函数列表   :
  修改历史   :
  1.日    期   : 2015年8月14日
    作    者   : XiaoJun
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "NasLppOm.h"
#include  "NasLppPublic.h"
#include  "PsLogdef.h"
#include  "NasFileId.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLPPOM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPOM_C


#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/* LPP-EMM 消息打印数组 */
NAS_COMM_PRINT_LIST_STRU g_astLrrcLppMsgArray[] =
{
    {   ID_LPP_LRRC_ECID_MEAS_REQ               ,
            "MSG:  ID_LPP_LRRC_ECID_MEAS_REQ                              ",
        VOS_NULL_PTR},
    {   ID_LRRC_LPP_ECID_MEAS_CNF               ,
            "MSG:  ID_LRRC_LPP_ECID_MEAS_CNF                              ",
        VOS_NULL_PTR},
    {   ID_LRRC_LPP_ECID_MEAS_IND               ,
            "MSG:  ID_LRRC_LPP_ECID_MEAS_IND                              ",
        VOS_NULL_PTR},
    {   ID_LPP_LRRC_OTDOA_MEAS_REQ               ,
            "MSG:  ID_LPP_LRRC_OTDOA_MEAS_REQ                              ",
        VOS_NULL_PTR},
    {   ID_LRRC_LPP_OTDOA_MEAS_CNF               ,
            "MSG:  ID_LRRC_LPP_OTDOA_MEAS_CNF                              ",
        VOS_NULL_PTR},
    {   ID_LRRC_LPP_OTDOA_MEAS_IND               ,
            "MSG:  ID_LRRC_LPP_OTDOA_MEAS_IND                              ",
        VOS_NULL_PTR}
};


/* LPP-EMM 消息打印数组 */
NAS_COMM_PRINT_LIST_STRU g_astMmLppMsgArray[] =
{
    {   ID_LPP_LMM_EST_REQ               ,
            "MSG:  ID_LPP_LMM_EST_REQ                              ",
        VOS_NULL_PTR},
    {   ID_LMM_LPP_EST_CNF               ,
            "MSG:  ID_LMM_LPP_EST_CNF                              ",
        VOS_NULL_PTR},
    {   ID_LPP_LMM_DATA_REQ               ,
            "MSG:  ID_LPP_LMM_DATA_REQ                              ",
        VOS_NULL_PTR},
    {   ID_LMM_LPP_DATA_CNF               ,
            "MSG:  ID_LMM_LPP_DATA_CNF                              ",
        VOS_NULL_PTR},
    {   ID_LMM_LPP_START_IND               ,
            "MSG:  ID_LMM_LPP_START_IND                              ",
        VOS_NULL_PTR},
    {   ID_LMM_LPP_STOP_IND               ,
            "MSG:  ID_LMM_LPP_STOP_IND                              ",
        VOS_NULL_PTR},
    {   ID_LMM_LPP_CELL_CHANGE_IND               ,
            "MSG:  ID_LMM_LPP_CELL_CHANGE_IND                              ",
        VOS_NULL_PTR},
    {   ID_LMM_LPP_DATA_IND               ,
            "MSG:  ID_LMM_LPP_DATA_IND                              ",
        VOS_NULL_PTR},
    {   ID_LMM_LPP_REL_IND               ,
            "MSG:  ID_LMM_LPP_REL_IND                              ",
        VOS_NULL_PTR}
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/




VOS_INT32   NAS_COMM_PrinLrrcLppMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmLppMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmLppMsgNum = sizeof(g_astLrrcLppMsgArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmLppMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astLrrcLppMsgArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmLppMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astLrrcLppMsgArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;


        if (VOS_NULL_PTR != g_astLrrcLppMsgArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astLrrcLppMsgArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_LPP_ERR_LOG1("NAS_COMM_PrinLrrcLppMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);

    }

    return (usTotalLen - usOffset);
}



VOS_INT32   NAS_COMM_PrintMmLppMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmLppMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmLppMsgNum = sizeof(g_astMmLppMsgArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmLppMsgNum; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astMmLppMsgArray[ulLoop].ulId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmLppMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmLppMsgArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astMmLppMsgArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astMmLppMsgArray[ulLoop].pfActionFun(pcBuff,
                                                                   usTotalLen,
                                                                   pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_LPP_ERR_LOG1("NAS_COMM_PrintMmLppMsg, Invalid enMsgId: ",
                           pstMsg->ulMsgName);

    }

    return (usTotalLen - usOffset);
}


VOS_VOID NAS_LPP_PrintLppRevMsg
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
                     "NAS LPP Receive Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_LPP_WARN_LOG("NAS_LPP_PrintLppRevMsg, Print receive msg header exception.");
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulSenderPid )
    {

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "MM-->LPP\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmLppMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg);

            break;

        case PS_PID_ERRC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "LRRC-->LPP\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrinLrrcLppMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        default:
            NAS_LPP_ERR_LOG2("NAS_LPP_PrintLppRevMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulSenderPid,
                          pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_PrintLppRevMsg, print return zero length.SenderPid, MsgId: ",
                      pstMsg->ulSenderPid,
                      pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}
VOS_VOID NAS_LPP_PrintLppSendMsg
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
                     "NAS LPP Send Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_LPP_WARN_LOG("NAS_LPP_PrintLppSendMsg, Print send msg header exception.");
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulReceiverPid )
    {
        case PS_PID_MM :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "LPP-->MM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmLppMsg(
                                            pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case PS_PID_ERRC :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "LPP-->LRRC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrinLrrcLppMsg(
                                            pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        default:
            NAS_LPP_ERR_LOG2( "NAS_LPP_PrintLppSendMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulReceiverPid,
                          pstMsg->ulMsgName);
            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_PrintLppSendMsg, print return zero length. ReceiverPid, MsgId: ",
                              pstMsg->ulReceiverPid,
                              pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff,usTotalLen);

    return ;
}

/*****************************************************************************
 Function Name   : NAS_LPP_OmStateChgInd\
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmStateChgInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndex,
    VOS_UINT8                           ucTransIndex,
    NAS_LPP_MAIN_STATE_ENUM_UINT32      enOldMsState,
    NAS_LPP_SUB_STATE_ENUM_UINT32       enOldSubState,
    NAS_LPP_MAIN_STATE_ENUM_UINT32      enNewMsState,
    NAS_LPP_SUB_STATE_ENUM_UINT32       enNewSubState
)
{
    NAS_LPP_OM_FSM_STATE_STRU   stOmFsm;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmFsm,ID_NAS_LPP_OM_FSM_STATE);
    stOmFsm.ulLength        = sizeof(NAS_LPP_OM_FSM_STATE_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmFsm.ucSessionIndex      = ucSessionIndex;
    stOmFsm.ucSessionTransIndex = ucSessionTransIndex;
    stOmFsm.ucTransIndex        = ucTransIndex;
    stOmFsm.enOldMainState      = enOldMsState;
    stOmFsm.enOldSubState       = enOldSubState;
    stOmFsm.enNewMainState      = enNewMsState;
    stOmFsm.enNewSubState       = enNewSubState;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmFsm) );
}

/*****************************************************************************
 Function Name   : VOS_VOID  NAS_LPP_OmTimerStartInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmTimerStartInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndex,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT32                          ulLen
)
{
    NAS_LPP_OM_TIMER_START_STRU stOmTimerStart;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmTimerStart,ID_NAS_LPP_OM_TIMER_START);
    stOmTimerStart.ulLength = sizeof(NAS_LPP_OM_TIMER_START_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmTimerStart.ucSessionIndex      = ucSessionIndex;
    stOmTimerStart.ucSessionTransIndex = ucSessionTransIndex;

    stOmTimerStart.enTimeName = enTimeName;
    stOmTimerStart.ulLen      = ulLen;


    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTimerStart) );

}
/*****************************************************************************
 Function Name   : NAS_LPP_OmTimerStopInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmTimerStopInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndex,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT32                          ulRemainTime
)
{
    NAS_LPP_OM_TIMER_STOP_STRU  stOmTimerStop;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmTimerStop,ID_NAS_LPP_OM_TIMER_STOP);
    stOmTimerStop.ulLength = sizeof(NAS_LPP_OM_TIMER_STOP_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmTimerStop.ucSessionIndex      = ucSessionIndex;
    stOmTimerStop.ucSessionTransIndex = ucSessionTransIndex;

    stOmTimerStop.enTimeName = enTimeName;
    stOmTimerStop.ulRemainTime = ulRemainTime;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTimerStop) );
}
/*****************************************************************************
 Function Name   : NAS_LPP_OmTimerExpireInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmTimerExpireInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndex,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName
)
{
    NAS_LPP_OM_TIMER_EXPIRE_STRU    stOmTimerExpire;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmTimerExpire,ID_NAS_LPP_OM_TIMER_EXPIRE);
    stOmTimerExpire.ulLength = sizeof(NAS_LPP_OM_TIMER_EXPIRE_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmTimerExpire.ucSessionIndex      = ucSessionIndex;
    stOmTimerExpire.ucSessionTransIndex = ucSessionTransIndex;

    stOmTimerExpire.enTimeName = enTimeName;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTimerExpire) );
}


/*****************************************************************************
 Function Name   : NAS_LPP_OmNvInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-17  Draft Enact

*****************************************************************************/
/*VOS_VOID  NAS_LPP_OmNvInd(  )
{
    NAS_LPP_OM_NV_STRU  stOmNv;

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmNv,ID_NAS_LPP_OM_NV);
    stOmNv.ulLength = sizeof(NAS_LPP_OM_NV_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmNv.ucSessionIndex      = ucSessionIndex;
    stOmNv.ucSessionTransIndex = ucSessionTransIndex;

    stOmNv.enTimeName = enTimeName;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmNv) );
}
*/
/*****************************************************************************
 Function Name   : NAS_LPP_OmSessionMallocSuccInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmSessionMallocInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulSessionPoolBitmap
)
{
    NAS_LPP_OM_SESSION_MALLOC_SUCC_STRU  stOmSessionMallocSuccInd;
    NAS_LPP_OM_SESSION_MALLOC_FAIL_STRU  stOmSessionMallocFailInd;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    if  (ucSessionIndex < NAS_LPP_MAX_SESSION_COUNT)
    {
        NAS_LPP_WRITE_OM_MSG_HEAD(&stOmSessionMallocSuccInd,ID_NAS_LPP_OM_SESSION_MALLOC_SUCC);
        stOmSessionMallocSuccInd.ulLength = sizeof(NAS_LPP_OM_SESSION_MALLOC_SUCC_STRU) - VOS_MSG_HEAD_LENGTH;

        stOmSessionMallocSuccInd.ucSessionIndex = ucSessionIndex;
        stOmSessionMallocSuccInd.ulSessionId    = ulSessionId;
        stOmSessionMallocSuccInd.ulSessionPoolBitmap = ulSessionPoolBitmap;

        (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmSessionMallocSuccInd) );
    }
    else
    {
        NAS_LPP_WRITE_OM_MSG_HEAD(&stOmSessionMallocFailInd,ID_NAS_LPP_OM_SESSION_MALLOC_FAIL);
        stOmSessionMallocFailInd.ulLength = sizeof(NAS_LPP_OM_SESSION_MALLOC_FAIL_STRU) - VOS_MSG_HEAD_LENGTH;

        stOmSessionMallocFailInd.ulSessionId    = ulSessionId;
        stOmSessionMallocFailInd.ulSessionPoolBitmap = ulSessionPoolBitmap;

        (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmSessionMallocFailInd) );
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_OmSessionRelInd
 Description     : 释放session
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmSessionRelInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulSessionPoolBitmap
)
{
    NAS_LPP_OM_SESSION_RELEASE_STRU stOmSessionRelInd;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmSessionRelInd,ID_NAS_LPP_OM_SESSION_RELEASE);
    stOmSessionRelInd.ulLength = sizeof(NAS_LPP_OM_SESSION_RELEASE_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmSessionRelInd.ucSessionIndex = ucSessionIndex;
    stOmSessionRelInd.ulSessionId    = ulSessionId;
    stOmSessionRelInd.ulSessionPoolBitmap = ulSessionPoolBitmap;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmSessionRelInd) );
}

/*****************************************************************************
 Function Name   : NAS_LPP_OmTransMallocInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmTransMallocInd
(
    VOS_UINT8                           ucTransIndex,
    VOS_UINT32                          ulTransPoolBitmap,
    NAS_LPP_TRANS_ID_STRU              *pstTransId
)
{
    NAS_LPP_OM_TRANS_MALLOC_SUCC_STRU   stOmTransMallocSucc;
    NAS_LPP_OM_TRANS_MALLOC_FAIL_STRU   stOmTransMallocFail;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    if (ucTransIndex < NAS_LPP_MAX_TRANS_POOL_COUNT)
    {
        NAS_LPP_WRITE_OM_MSG_HEAD(&stOmTransMallocSucc,ID_NAS_LPP_OM_TRANS_MALLOC_SUCC);
        stOmTransMallocSucc.ulLength = sizeof(NAS_LPP_OM_TRANS_MALLOC_SUCC_STRU) - VOS_MSG_HEAD_LENGTH;

        stOmTransMallocSucc.ucTransIndex      = ucTransIndex;
        stOmTransMallocSucc.ulTransPoolBitmap = ulTransPoolBitmap;
        stOmTransMallocSucc.enInitiator       = pstTransId->enInitiator;
        stOmTransMallocSucc.ucTransactionNumber = pstTransId->ucTransactionNumber;

        (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTransMallocSucc) );
    }
    else
    {
        NAS_LPP_WRITE_OM_MSG_HEAD(&stOmTransMallocFail,ID_NAS_LPP_OM_TRANS_MALLOC_FAIL);
        stOmTransMallocFail.ulLength = sizeof(NAS_LPP_OM_TRANS_MALLOC_FAIL_STRU) - VOS_MSG_HEAD_LENGTH;

        stOmTransMallocFail.ulTransPoolBitmap = ulTransPoolBitmap;
        stOmTransMallocFail.enInitiator       = pstTransId->enInitiator;
        stOmTransMallocFail.ucTransactionNumber = pstTransId->ucTransactionNumber;

        (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTransMallocFail) );
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_OmTransRelInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmTransRelInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucTransIndex,
    NAS_LPP_TRANSACTION_STRU           *pstLppTrans
)
{
    NAS_LPP_OM_TRANS_RELEASE_STRU       stOmTransRel;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmTransRel,ID_NAS_LPP_OM_TRANS_RELEASE);
    stOmTransRel.ulLength = sizeof(NAS_LPP_OM_TRANS_RELEASE_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmTransRel.ulTransPoolBitmap = NAS_LPP_GetLppTransEntityPool()->ulTransBitmap;
    stOmTransRel.ucSessionIndex    = ucSessionIndex;
    stOmTransRel.ucTransIndex      = ucTransIndex;
    NAS_LPP_MEM_CPY(&stOmTransRel.stLppTran, pstLppTrans, sizeof(NAS_LPP_TRANSACTION_STRU));

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmTransRel) );
}

/*****************************************************************************
 Function Name   : NAS_LPP_AddTransToSession
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmAddTransToSessionInd
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucTransIndex,
    NAS_LPP_TRANSACTION_STRU           *pstLppTrans
)
{
    NAS_LPP_OM_ADD_TRANS_TO_SESSION_STRU stOmAddTransToSession;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmAddTransToSession,ID_NAS_LPP_OM_ADD_TRANS_TO_SESSION);
    stOmAddTransToSession.ulLength = sizeof(NAS_LPP_OM_ADD_TRANS_TO_SESSION_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmAddTransToSession.ucSessionIndex    = ucSessionIndex;
    stOmAddTransToSession.ucTransIndex      = ucTransIndex;
    NAS_LPP_MEM_CPY(&stOmAddTransToSession.stLppTran, pstLppTrans, sizeof(NAS_LPP_TRANSACTION_STRU));

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmAddTransToSession) );
}

/*****************************************************************************
 Function Name   : NAS_LPP_OmCommCfgPoolMallocInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-18  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmCommCfgPoolMallocInd
(
    VOS_UINT8                           ucTransIndex,
    VOS_UINT8                           ucCommCfgIndex,
    VOS_UINT32                          ulCfgPoolBitmap
)
{
    NAS_LPP_OM_COMM_CFG_MALLOC_SUCC_STRU    stOmCommCfgMallocSucc;
    NAS_LPP_OM_COMM_CFG_MALLOC_FAIL_STRU    stOmCommCfgMallocFail;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    if (ucCommCfgIndex < NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_WRITE_OM_MSG_HEAD(&stOmCommCfgMallocSucc,ID_NAS_LPP_OM_COMM_CFG_MALLOC_SUCC);
        stOmCommCfgMallocSucc.ulLength = sizeof(NAS_LPP_OM_COMM_CFG_MALLOC_SUCC_STRU) - VOS_MSG_HEAD_LENGTH;

        stOmCommCfgMallocSucc.ucCfgIndex   = ucCommCfgIndex;
        stOmCommCfgMallocSucc.ucTransIndex = ucTransIndex;
        stOmCommCfgMallocSucc.ulCfgPoolBitmap = ulCfgPoolBitmap;

        (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmCommCfgMallocSucc) );
    }
    else
    {
        NAS_LPP_WRITE_OM_MSG_HEAD(&stOmCommCfgMallocFail,ID_NAS_LPP_OM_COMM_CFG_MALLOC_FAIL);
        stOmCommCfgMallocFail.ulLength = sizeof(NAS_LPP_OM_COMM_CFG_MALLOC_FAIL_STRU) - VOS_MSG_HEAD_LENGTH;

        stOmCommCfgMallocFail.ucCfgIndex   = ucCommCfgIndex;
        stOmCommCfgMallocFail.ucTransIndex = ucTransIndex;
        stOmCommCfgMallocFail.ulCfgPoolBitmap = ulCfgPoolBitmap;

        (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmCommCfgMallocFail) );
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_OmCommCfgPoolRelInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmCommCfgPoolRelInd
(
    VOS_UINT8                           ucTransIndex,
    VOS_UINT8                           ucCommCfgIndex,
    VOS_UINT32                          ulCfgPoolBitmap
)
{
    NAS_LPP_OM_COMM_CFG_RELEASE_STRU    stOmCommCfgRel;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmCommCfgRel,ID_NAS_LPP_OM_COMM_CFG_RELEASE);
    stOmCommCfgRel.ulLength = sizeof(NAS_LPP_OM_COMM_CFG_RELEASE_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmCommCfgRel.ucCfgIndex   = ucCommCfgIndex;
    stOmCommCfgRel.ucTransIndex = ucTransIndex;
    stOmCommCfgRel.ulCfgPoolBitmap = ulCfgPoolBitmap;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmCommCfgRel) );
}

/*****************************************************************************
 Function Name   : NAS_LPP_OmUpMsgBuffMallocSuccInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmUpMsgBuffMallocSuccInd
(
    VOS_UINT8                           ucUpLinkBuffIndex,
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
)
{
    NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC_STRU stOmUpMsgBuffMallocSucc;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmUpMsgBuffMallocSucc,ID_NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC);
    stOmUpMsgBuffMallocSucc.ulLength = sizeof(NAS_LPP_OM_UP_MSG_BUFF_MALLOC_SUCC_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmUpMsgBuffMallocSucc.ucUpLinkBuffIndex   = ucUpLinkBuffIndex;
    stOmUpMsgBuffMallocSucc.ulBitMap = ulBitMap;

    NAS_LPP_MEM_CPY( stOmUpMsgBuffMallocSucc.astUpmsgSeq,
                     pstUpmsgSeq,
                     NAS_LPP_MAX_BUFF_MSG_COUNT*sizeof(NAS_LPP_UP_MSG_SEQUENCE_STRU));

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmUpMsgBuffMallocSucc) );


}
/*****************************************************************************
 Function Name   : NAS_LPP_OmUpMsgBuffMallocFailInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmUpMsgBuffMallocFailInd
(
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
)
{
    NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL_STRU stOmUpMsgBuffMallocfail;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmUpMsgBuffMallocfail,ID_NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL);
    stOmUpMsgBuffMallocfail.ulLength = sizeof(NAS_LPP_OM_UP_MSG_BUFF_MALLOC_FAIL_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmUpMsgBuffMallocfail.ulBitMap = ulBitMap;

    NAS_LPP_MEM_CPY( stOmUpMsgBuffMallocfail.astUpmsgSeq,
                     pstUpmsgSeq,
                     NAS_LPP_MAX_BUFF_MSG_COUNT*sizeof(NAS_LPP_UP_MSG_SEQUENCE_STRU));

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmUpMsgBuffMallocfail) );

}

/*****************************************************************************
 Function Name   : NAS_LPP_OmUpMsgBuffRelInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmUpMsgBuffRelInd
(
    VOS_UINT8                           ucUpLinkBuffIndex,
    NAS_LPP_UP_MSG_SEQUENCE_STRU       *pstUpmsgSeq,
    VOS_UINT32                          ulBitMap
)
{
    NAS_LPP_OM_UP_MSG_BUFF_REL_STRU stOmUpMsgBuffRelInd;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmUpMsgBuffRelInd,ID_NAS_LPP_OM_UP_MSG_BUFF_RELEASE);
    stOmUpMsgBuffRelInd.ulLength = sizeof(NAS_LPP_OM_UP_MSG_BUFF_REL_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmUpMsgBuffRelInd.ucUpLinkBuffIndex   = ucUpLinkBuffIndex;
    stOmUpMsgBuffRelInd.ulBitMap = ulBitMap;

    NAS_LPP_MEM_CPY( stOmUpMsgBuffRelInd.astUpmsgSeq,
                     pstUpmsgSeq,
                     NAS_LPP_MAX_BUFF_MSG_COUNT*sizeof(NAS_LPP_UP_MSG_SEQUENCE_STRU));

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmUpMsgBuffRelInd) );
}

/*****************************************************************************
 Function Name   : NAS_LPP_OmConnMngInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmConnMngInd(  )
{

}


/*****************************************************************************
 Function Name   : NAS_LPP_OmAddLocTechInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmAddLocTechInd
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech,
    NAS_LPP_LOC_TECH_RUNING_STRU       *pstLocTechRunning
)
{
    NAS_LPP_OM_ADD_LOC_TECH_STRU    stOmAddLocTechInd;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmAddLocTechInd,ID_NAS_LPP_OM_ADD_LOC_TECH);
    stOmAddLocTechInd.ulLength = sizeof(NAS_LPP_OM_ADD_LOC_TECH_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmAddLocTechInd.enPositionTech   = enPositionTech;

    NAS_LPP_MEM_CPY( &stOmAddLocTechInd.stLocTechRunning,
                     pstLocTechRunning,
                     sizeof(NAS_LPP_LOC_TECH_RUNING_STRU));

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmAddLocTechInd) );
}
/*****************************************************************************
 Function Name   : NAS_LPP_OmDelLocTechInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OmDelLocTechInd
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPositionTech,
    NAS_LPP_LOC_TECH_RUNING_STRU       *pstLocTechRunning
)
{
    NAS_LPP_OM_DEL_LOC_TECH_STRU    stOmDelLocTechInd;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmDelLocTechInd,ID_NAS_LPP_OM_DEL_LOC_TECH);
    stOmDelLocTechInd.ulLength = sizeof(NAS_LPP_OM_DEL_LOC_TECH_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmDelLocTechInd.enPositionTech   = enPositionTech;

    NAS_LPP_MEM_CPY( &stOmDelLocTechInd.stLocTechRunning,
                     pstLocTechRunning,
                     sizeof(NAS_LPP_LOC_TECH_RUNING_STRU));

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmDelLocTechInd) );
}

/*****************************************************************************
 Function Name   : NAS_LPP_OM_LOG
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-21  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_OM_LOG
(
    NAS_LPP_OM_MSG_ENUM_UINT32          enLppOmMsg,
    NAS_FILE_ID_DEFINE_ENUM_UINT32      enNasFileName,
    VOS_UINT32                          ulLine,
    NAS_LPP_ERROR_CODE_ENUM_UINT32      enErrorCode,
    VOS_UINT8                           ucParaNum,
    VOS_UINT32                          ulPara1,
    VOS_UINT32                          ulPara2,
    VOS_UINT32                          ulPara3
)
{
    NAS_LPP_OM_LOG_STRU       stOmLogErrInd;
    if (NAS_LPP_NO_SLCT == NAS_LPP_GetLppLayerSwitchFlag())
    {
        return;
    }

    NAS_LPP_WRITE_OM_MSG_HEAD(&stOmLogErrInd,enLppOmMsg);
    stOmLogErrInd.ulLength = sizeof(NAS_LPP_OM_LOG_STRU) - VOS_MSG_HEAD_LENGTH;

    stOmLogErrInd.enNasFileName = enNasFileName;
    stOmLogErrInd.ulLine = ulLine;
    stOmLogErrInd.enErrorCode = enErrorCode;
    stOmLogErrInd.ucParaNum = ucParaNum;
    stOmLogErrInd.aulPara[0] = ulPara1;
    stOmLogErrInd.aulPara[1] = ulPara2;
    stOmLogErrInd.aulPara[2] = ulPara3;

    (VOS_VOID)LTE_MsgHook( (VOS_VOID*)(&stOmLogErrInd) );
}
#endif //#if (FEATURE_LPP == FEATURE_ON)


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

