

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "CssProcLphyMsg.h"
#include    "CssProcSrchRslt.h"
#include    "CssProcCommMsg.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCLPHYMSG_C

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

/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID CSS_AssignLphyOpid
(
    VOS_UINT16                          *pusOpid
)
{
    VOS_UINT16                           usOpid = CSS_NULL;

    /*获取当前最大OPID*/
    usOpid = (VOS_UINT16)CSS_GetLphyCurOpid();

    /*如果还未到最大值，直接加1*/
    if( usOpid < CSS_MAX_OPID)
    {
        *pusOpid = usOpid + 1;
    }
    else/*如果已经是最大值，从初值开始分配*/
    {
        (*pusOpid) = CSS_MIN_OPID;
    }

    CSS_SetLphyCurOpid(*pusOpid);

    CSS_INFO_LOG1("CSS_AssignLphyOpid,normal,assin opid:", (*pusOpid));
    TLPS_PRINT2LAYER_INFO1(CSS_AssignLphyOpid_ENUM, LNAS_FUNCTION_LABEL1, (*pusOpid));
}
VOS_VOID CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl;

    CSS_INFO_LOG("CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc ENTER");
    TLPS_PRINT2LAYER_INFO(CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc_ENUM, LNAS_ENTRY);

    pstCssControl = CSS_GetControlAddr();

    /* 如请求的是MCC扫频 目前不处理 */
    if (CSS_BAND_SCAN_MCC_BASED == pstCssControl->stCommMsg.enBandScanType)
    {
    }
    else
    {
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);
        CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_BAND_SCAN_IND);

        CSS_SndLphyMsgCommBandScanReq(CSS_GetCommScanBandListCurrNode(),
                                      CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                      CSS_GetCommScanCurFreqRangeIdx());

    }
}
VOS_VOID CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl = CSS_GetControlAddr();
    if (CSS_BAND_SCAN_MCC_BASED == pstCssControl->stCommMsg.enBandScanType)
    {
    }
    else
    {
        CSS_SndCommMsgBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                    pstCssControl->stCommMsg.ulOpid,
                                    CSS_MULTI_BAND_SCAN_RESULT_SUCC);
    }

}




VOS_VOID CSS_SndLphyMsgStopBandScanReq
(
    VOS_VOID
)
{
    CSS_LPHY_STOP_BAND_SCAN_REQ_STRU *pstCssStopBandScanReq;
    VOS_UINT16                           usOpid = CSS_NULL;

    /*分配消息空间*/
    pstCssStopBandScanReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_STOP_BAND_SCAN_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssStopBandScanReq)
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET( CSS_GET_MSG_ENTITY(pstCssStopBandScanReq), 0, CSS_GET_MSG_LENGTH(pstCssStopBandScanReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssStopBandScanReq,ID_CSS_LPHY_STOP_BAND_SCAN_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssStopBandScanReq->usOpId = usOpid;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssStopBandScanReq);

    return ;
}


VOS_VOID CSS_SndLphyMsgSetWorkModeReq
(
    CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16       enWorkModeType
)
{
    CSS_LPHY_SET_WORK_MODE_REQ_STRU     *pstCssSetModeInactive;
    VOS_UINT16                          usOpid = CSS_NULL;

    /*分配消息空间*/
    pstCssSetModeInactive = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_SET_WORK_MODE_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssSetModeInactive)
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET( CSS_GET_MSG_ENTITY(pstCssSetModeInactive), 0, CSS_GET_MSG_LENGTH(pstCssSetModeInactive));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssSetModeInactive,ID_CSS_LPHY_SET_WORK_MODE_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssSetModeInactive->usOpId = usOpid;
    pstCssSetModeInactive->enWorkModeType = enWorkModeType;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssSetModeInactive);

    #if (VOS_OS_VER != VOS_WIN32)
    NAS_TRACE_HIGH(" CSS_SndLphyMsgSetWorkModeReq pstCssSetModeInactive->enWorkModeType = %d", pstCssSetModeInactive->enWorkModeType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgSetWorkModeReq_EUM, LNAS_WorkModeType, pstCssSetModeInactive->enWorkModeType);
    #endif

    return ;
}



VOS_VOID CSS_SndLphyMsgCommBandScanReq
(
    CSS_COMM_SCAN_BAND_NODE_STRU               *pstBandNode,
    CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16         enScanType,
    VOS_UINT8                                   ucCurFreqRangeIdx
)
{
    CSS_LPHY_BAND_SCAN_REQ_STRU        *pstCssBandScanReq;
    VOS_UINT16                          usOpid = CSS_NULL;

    if (VOS_NULL_PTR == pstBandNode)
    {
        /*打印异常信息*/
        CSS_WARN_LOG("CSS_SndLphyMsgBandScanReq:BAND NODE is NULL!");
        TLPS_PRINT2LAYER_WARNING(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_BandNodeIsNULL);
        return ;
    }

    /*分配消息空间*/
    pstCssBandScanReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_BAND_SCAN_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssBandScanReq)
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SndLphyMsgBandScanReq:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET( CSS_GET_MSG_ENTITY(pstCssBandScanReq), 0, CSS_GET_MSG_LENGTH(pstCssBandScanReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssBandScanReq,ID_CSS_LPHY_BAND_SCAN_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssBandScanReq->usOpId                       = usOpid;
    pstCssBandScanReq->enBandScanType               = enScanType;
    pstCssBandScanReq->enBandInd                    = pstBandNode->stBandInfo.ucBandInd;
    pstCssBandScanReq->enLteModeType                = CSS_GetLteModeTypeByBandInd(pstBandNode->stBandInfo.ucBandInd);
    pstCssBandScanReq->stFreqRangeInfo.usFreqBegin  = pstBandNode->stBandInfo.pstScanReqArray[ucCurFreqRangeIdx].usFreqBegin;
    pstCssBandScanReq->stFreqRangeInfo.usFreqEnd    = pstBandNode->stBandInfo.pstScanReqArray[ucCurFreqRangeIdx].usFreqEnd;
    pstCssBandScanReq->bitOpLteSupport              = pstBandNode->stBandInfo.bitOpLteSupport;
    pstCssBandScanReq->bitOpWcdmaSupport            = pstBandNode->stBandInfo.bitOpWcdmaSupport;
    pstCssBandScanReq->bitOpGsmSupport              = pstBandNode->stBandInfo.bitOpGsmSupport;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssBandScanReq);

    #if (VOS_OS_VER != VOS_WIN32)
    NAS_TRACE_HIGH(" CSS_SndLphyMsgCommBandScanReq pstCssBandScanReq->enBandInd = %d, %d, %d", pstCssBandScanReq->enBandInd,
                    pstCssBandScanReq->stFreqRangeInfo.usFreqBegin,
                    pstCssBandScanReq->stFreqRangeInfo.usFreqEnd);
    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_BandInd, pstCssBandScanReq->enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_FreqRangeBegin, pstCssBandScanReq->stFreqRangeInfo.usFreqBegin);
    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_FreqRangeEnd, pstCssBandScanReq->stFreqRangeInfo.usFreqEnd);
    #endif

    return ;
}
VOS_VOID CSS_ProcLphyMsgScanInd
(
    const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* 如果OPID不匹配，则直接退出 */
    if (pstCssControl->ulCssLphyOpid != pRcvMsg->usOpId)
    {
        /*打印出错信息*/
        CSS_WARN_LOG("CSS_ProcLphyMsgScanInd: opid mismatch!");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_OpidMismatch);
        return;
    }

    /*检查状态是否匹配，若不匹配，退出*/
    if (CSS_MS_SCAN != CSS_GetCurMainStatus() || CSS_SS_WAIT_BAND_SCAN_IND != CSS_GetCurSubStatus())
    {
        /*打印出错信息*/
        CSS_WARN_LOG("CSS_ProcLphyMsgScanInd: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_STATE_ERR);
        return;
    }

    /*检查上报的BAND是否和当前正在处理的BAND是否一致*/
    if (pRcvMsg->stBandScanResult.enBandInd != CSS_GetCommScanBandListCurrNode()->stBandInfo.ucBandInd)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgScanInd: wrong band indicate!");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_WrongBand);
        return;
    }

    CSS_StopTimer(&pstCssControl->stBandScanIndTimer);

    #if (VOS_OS_VER != VOS_WIN32)
    NAS_TRACE_HIGH(" CSS_ProcLphyMsgScanInd enBandInd = %d, usFreqRangeNum = %d", pRcvMsg->stBandScanResult.enBandInd,
                    pRcvMsg->stBandScanResult.usFreqRangeNum);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanInd_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanInd_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum);
    #endif

    /*如果遇到异常错误则返回*/
    if (CSS_CAUSE_NULL_PTR == CSS_ProcLphyBandScanRslt(&(pRcvMsg->stBandScanResult)))
    {
        return;
    }

    /*判断是否需要进行下一次扫频*/
    if (CSS_TRUE == CSS_IsNeedSndLphyNextBandScanReq())
    {
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);
        CSS_SndLphyMsgCommBandScanReq(CSS_GetCommScanBandListCurrNode(),
                                          CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                          CSS_GetCommScanCurFreqRangeIdx());
    }
    /*所有的频点都扫完了，此处有后续处理，转状态或其他处理*/
    else
    {
        /* 将LPHY设置为从模 */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

        CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    }

    /* print */
    CSS_INFO_LOG2("CSS_ProcLphyBandScanRslt:enBandInd = %d, usFreqRangeNum = %d", pRcvMsg->stBandScanResult.enBandInd,
                    pRcvMsg->stBandScanResult.usFreqRangeNum);
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanInd_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd,1);
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanInd_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum,1);

    return ;
}


VOS_VOID CSS_ProcLphyMsgStopScanCnf
(
    const CSS_LPHY_STOP_BAND_SCAN_CNF_STRU  *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* 如果OPID匹配不成功，则直接丢弃 */
    if (CSS_GetLphyCurOpid() != pRcvMsg->usOpId)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgStopScanCnf opid mismatch ");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgStopScanCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* 停止定时器 */
    CSS_StopTimer(&pstCssControl->stStopBandScanTimer);

    /* 如果停止扫频失败，则直接调用底软接口复位 */
    if(CSS_LPHY_RESULT_FAIL == pRcvMsg->enStopBandScanRslt)
    {
        CSS_ClearLocalResource();

        /* 设置从模失败，调用底软接口，直接复位 */
        (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_STOP_SCAN_FAIL, (__LINE__), (THIS_FILE_ID) );

        return ;
    }

    /* 如果OPID匹配成功，且状态为STOP_SCAN+CSS_SS_WAIT_STOP_SCAN_CNF,则需要将LPHY设置为从模 */
    if ((CSS_MS_STOP_SCAN == CSS_GetCurMainStatus()) && (CSS_SS_WAIT_STOP_SCAN_CNF == CSS_GetCurSubStatus()))
    {

        /* 收到LPHY的停止扫频消息后，将LPHY设置为从模 */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);
        CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    }

    return ;
}

VOS_VOID CSS_MsScanProcLphyMsgSetModeCnf
(
    const CSS_LPHY_SET_WORK_MODE_CNF_STRU   *pstSetModeCnf
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    if (CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF == CSS_GetCurSubStatus())
    {
        CSS_StopTimer(&pstCssControl->stSetactiveModeTimer);

        if (CSS_LPHY_RESULT_SUCC == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc();
        }
        else
        {
            /* 存储扫频结果的空间释放 */
            CSS_FreeCommScanRsltMemory();
            /* 转状态 */
            CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

            /* 如果设置主模失败，则通知扫频失败，停止定时器，迁移状态 */
            CSS_SndCommMsgBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                      pstCssControl->stCommMsg.ulOpid,
                                      CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);

        }
    }
    else if (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == CSS_GetCurSubStatus())
    {
        CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);

        /* 如果是扫频结束，收到设置从模的回复后，需要给GUNAS/AS发送扫频结果 */
        /* 如果设置从模失败，则直接复位 */
        if (CSS_LPHY_RESULT_FAIL == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_ClearLocalResource();

            /* 设置从模失败，调用底软接口，直接复位 */
            (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL, (__LINE__), (THIS_FILE_ID) );

            return;
        }

        /* 给GUNSA/AS发送扫频结果 */
        CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);
        CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc();

        /* 将本地保存的扫频结果钩到HIDS上 */
        CSS_SendOmBandScanResultInfoInd();
    }
}

VOS_VOID CSS_ProcLphyMsgSetModeCnf
(
    const CSS_LPHY_SET_WORK_MODE_CNF_STRU   *pstSetModeCnf
)
{
    CSS_MAIN_STATE_ENUM_UINT16  enMainState;    /* 当前处于的主状态 */
    CSS_SUB_STATE_ENUM_UINT16   enSubState;     /* 当前处于的子状态 */
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();

    /* 如果OPID匹配不成功，则直接丢弃 */
    if (CSS_GetLphyCurOpid() != pstSetModeCnf->usOpId)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgSetModeCnf opid mismatch");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgSetModeCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* 如果主状态是扫频，且设置主模成功，则给LPHY发送扫频请求 */
    if (CSS_MS_SCAN == enMainState)
    {
        CSS_MsScanProcLphyMsgSetModeCnf(pstSetModeCnf);
    }
    else if ((CSS_MS_STOP_SCAN == enMainState) && (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == enSubState))
    {
        /* 停止定时器 */
        CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);

        /* 如果设置从模失败，则直接复位 */
        if (CSS_LPHY_RESULT_FAIL == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_ClearLocalResource();

            /* 设置从模失败，调用底软接口，直接复位 */
            (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL, (__LINE__), (THIS_FILE_ID) );

            return;
        }

        /* 进入该状态有两种情况: GUNAS/AS通知CSS模块停止扫频；或者是扫频过程中，出现异常，CSS模块主动通知LPHY停止扫频 */
        /* 如果保存的消息是停止扫频，则直接回复停止扫频成功 */
        if ((CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg) &&
            (ID_CSS_STOP_BAND_SCAN_REQ == pstCssControl->stCommMsg.enMsgId))
        {
            CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

            CSS_SndCommMsgStopBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                           CSS_RESULT_SUCC );


        }

        /* 如果是扫频过程中出现异常，则回复扫频失败 */
        if ((CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg) &&
            (ID_CSS_MULTI_BAND_SCAN_REQ == pstCssControl->stCommMsg.enMsgId))
        {
            CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

            CSS_SndCommMsgBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                      pstCssControl->stCommMsg.ulOpid,
                                      CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
        }

        /* 停止扫频或者扫频过程中异常，需要将存储扫频结果的空间释放 */
        CSS_FreeCommScanRsltMemory();
    }

    return ;
}
VOS_VOID CSS_ProcLphyMsg(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_CSS_LPHY_BAND_SCAN_IND:
            CSS_ProcLphyMsgScanInd((const CSS_LPHY_BAND_SCAN_IND_STRU *)pRcvMsg);
            break;

        case ID_CSS_LPHY_STOP_BAND_SCAN_CNF:
            CSS_ProcLphyMsgStopScanCnf((const CSS_LPHY_STOP_BAND_SCAN_CNF_STRU *)pRcvMsg);
            break;

        case ID_CSS_LPHY_SET_WORK_MODE_CNF:
            CSS_ProcLphyMsgSetModeCnf((const CSS_LPHY_SET_WORK_MODE_CNF_STRU *)pRcvMsg);
            break;

        default:
            break;
    }
}

#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif




