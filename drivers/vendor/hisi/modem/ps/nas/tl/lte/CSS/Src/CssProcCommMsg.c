


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "CssProcLphyMsg.h"
#include "CssProcCommMsg.h"
#include "CssProcSrchRslt.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCCOMMMSG_C


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID  CSS_JudgeLowTypeScanRssiExistType
(
    VOS_UINT8                               *pucIsExistLLowFreq,
    VOS_UINT8                               *pucIsExistLHigFreq,
    VOS_UINT8                               *pucIsExistWLowFreq,
    VOS_UINT8                               *pucIsExistWHigFreq,
    VOS_UINT8                               *pucIsExistGLowFreq,
    VOS_UINT8                               *pucIsExistGHigFreq
)
{
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstBandNode;
    CSS_CONTROL_STRU                   *pstCssControl;
    VOS_UINT32                          ulBandNum;
    CSS_COMM_SCAN_BAND_LIST_STRU       *pstCommScanBandList;

    pstBandNode                         = CSS_GetCommScanBandListHeadNode();
    pstCommScanBandList                 = CSS_GetCommScanBandListAddr();
    pstCssControl                       = CSS_GetControlAddr();

    /* 初始化 */
    *pucIsExistLLowFreq = CSS_FALSE;
    *pucIsExistLHigFreq = CSS_FALSE;
    *pucIsExistWLowFreq = CSS_FALSE;
    *pucIsExistWHigFreq = CSS_FALSE;
    *pucIsExistGLowFreq = CSS_FALSE;
    *pucIsExistGHigFreq = CSS_FALSE;

    /* 判断是否存在G的高能量频点或者可驻留的频点 */
    for (ulBandNum = 0; ulBandNum < pstCommScanBandList->ucBandCount; ulBandNum++)
    {
        if (0 != pstBandNode->stBandInfo.ucScanRsltArrayCount)
        {
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpLteSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sLLowRssiThresHold))
                {
                    *pucIsExistLLowFreq = CSS_TRUE;
                }

                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sLHighRssiThresHold))
                {
                    *pucIsExistLHigFreq = CSS_TRUE;
                }
            }
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpWcdmaSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sWLowRssiThresHold))
                {
                    *pucIsExistWLowFreq = CSS_TRUE;
                }
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sWHighRssiThresHold))
                {
                    *pucIsExistWHigFreq = CSS_TRUE;
                }
            }
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpGsmSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sGLowRssiThresHold))
                {
                    *pucIsExistGLowFreq = CSS_TRUE;
                }

                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sGHighRssiThresHold))
                {
                    *pucIsExistGHigFreq = CSS_TRUE;
                }
            }
        }
        /* 如果三种接入技术都存在高能量频点，则直接退出 */
        if ((CSS_TRUE == *pucIsExistLHigFreq) && (CSS_TRUE == *pucIsExistWHigFreq) && (CSS_TRUE == *pucIsExistGHigFreq))
        {
            break;
        }
        pstBandNode = pstBandNode->pstNext;
    }

}
VOS_VOID  CSS_JudgeHighTypeScanRssiExistType
(
    VOS_UINT8                               *pucIsExistLHigFreq,
    VOS_UINT8                               *pucIsExistWHigFreq,
    VOS_UINT8                               *pucIsExistGHigFreq
)
{
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstBandNode;
    VOS_UINT32                          ulBandNum;
    CSS_COMM_SCAN_BAND_LIST_STRU       *pstCommScanBandList;
    CSS_CONTROL_STRU                   *pstCssControl;

    pstBandNode                         = CSS_GetCommScanBandListHeadNode();
    pstCommScanBandList                 = CSS_GetCommScanBandListAddr();
    pstCssControl                       = CSS_GetControlAddr();

    /* 初始化 */
    *pucIsExistLHigFreq = CSS_FALSE;
    *pucIsExistWHigFreq = CSS_FALSE;
    *pucIsExistGHigFreq = CSS_FALSE;

    for (ulBandNum = 0; ulBandNum < pstCommScanBandList->ucBandCount; ulBandNum++)
    {
        if (0 != pstBandNode->stBandInfo.ucScanRsltArrayCount)
        {
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpLteSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sLHighRssiThresHold))
                {
                    *pucIsExistLHigFreq = CSS_TRUE;
                }
            }
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpWcdmaSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sWHighRssiThresHold))
                {
                    *pucIsExistWHigFreq = CSS_TRUE;
                }
            }
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpGsmSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sGHighRssiThresHold))
                {
                    *pucIsExistGHigFreq = CSS_TRUE;
                }
            }
        }
        /* 如果三种接入技术都存在高能量频点，则直接退出 */
        if ((CSS_TRUE == *pucIsExistLHigFreq) && (CSS_TRUE == *pucIsExistWHigFreq) && (CSS_TRUE == *pucIsExistGHigFreq))
        {
            break;
        }
        pstBandNode = pstBandNode->pstNext;
    }
}


VOS_VOID  CSS_JudgeRssiExistType
(
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penGsmCoverageType,
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penUmtsFddCoverageType,
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penLteCoverageType
)
{
    CSS_CONTROL_STRU                        *pstCssControl;
    VOS_UINT8                               ucIsExistLLowFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistLHigFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistWLowFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistWHigFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistGLowFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistGHigFreq   = CSS_FALSE;

    pstCssControl                           = CSS_GetControlAddr();

    if (CSS_OP_TRUE != pstCssControl->stCommMsg.bitOpHighRssi) /* 如果是可驻留门限扫频 */
    {
        CSS_JudgeLowTypeScanRssiExistType(&ucIsExistLLowFreq, &ucIsExistLHigFreq,
                                            &ucIsExistWLowFreq, &ucIsExistWHigFreq,
                                            &ucIsExistGLowFreq, &ucIsExistGHigFreq);
    }
    else    /* 如果是高能量扫频 */
    {
        CSS_JudgeHighTypeScanRssiExistType(&ucIsExistLHigFreq, &ucIsExistWHigFreq, &ucIsExistGHigFreq);
    }

    /* 如果存在高能量的，则返回类型为高能量；如果仅存在可驻留的，则返回类型为可驻留；否则，返回NONE */
    if (CSS_TRUE == ucIsExistLHigFreq)
    {
        *penLteCoverageType = CSS_COVERAGE_TYPE_HIGH;
    }
    else if (CSS_TRUE == ucIsExistLLowFreq)
    {
        *penLteCoverageType = CSS_COVERAGE_TYPE_LOW;
    }
    else
    {
        *penLteCoverageType = CSS_COVERAGE_TYPE_NONE;
    }

    if (CSS_TRUE == ucIsExistWHigFreq)
    {
        *penUmtsFddCoverageType = CSS_COVERAGE_TYPE_HIGH;
    }
    else if (CSS_TRUE == ucIsExistWLowFreq)
    {
        *penUmtsFddCoverageType = CSS_COVERAGE_TYPE_LOW;
    }
    else
    {
        *penUmtsFddCoverageType = CSS_COVERAGE_TYPE_NONE;
    }

    if (CSS_TRUE == ucIsExistGHigFreq)
    {
        *penGsmCoverageType = CSS_COVERAGE_TYPE_HIGH;
    }
    else if (CSS_TRUE == ucIsExistGLowFreq)
    {
        *penGsmCoverageType = CSS_COVERAGE_TYPE_LOW;
    }
    else
    {
        *penGsmCoverageType = CSS_COVERAGE_TYPE_NONE;
    }
    return;
}
VOS_VOID CSS_SndCommMsgStopBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    CSS_RESULT_ENUM_UINT32                          enResult
)
{
    CSS_STOP_BAND_SCAN_CNF_STRU *pstCssStopBandScanCnf;

    /*分配消息空间*/
    pstCssStopBandScanCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_STOP_BAND_SCAN_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssStopBandScanCnf)
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET( CSS_GET_MSG_ENTITY(pstCssStopBandScanCnf), 0, CSS_GET_MSG_LENGTH(pstCssStopBandScanCnf));

    CSS_WRITE_COMM_MSG_HEAD(pstCssStopBandScanCnf,ID_CSS_STOP_BAND_SCAN_CNF, ulReceiverPid);

    pstCssStopBandScanCnf->enResult = enResult;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssStopBandScanCnf);

    return ;
}

VOS_VOID CSS_SndCommMsgBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    VOS_UINT32                                      ulOpid,
    CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8           enResult
)
{
    CSS_MULTI_BAND_SCAN_CNF_STRU *pstCssBandScanCnf;

    /*分配消息空间*/
    pstCssBandScanCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_MULTI_BAND_SCAN_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssBandScanCnf)
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET( CSS_GET_MSG_ENTITY(pstCssBandScanCnf), 0, CSS_GET_MSG_LENGTH(pstCssBandScanCnf));

    CSS_WRITE_COMM_MSG_HEAD(pstCssBandScanCnf,ID_CSS_MULTI_BAND_SCAN_CNF, ulReceiverPid);

    pstCssBandScanCnf->enResult = enResult;

    pstCssBandScanCnf->ulOpid = ulOpid;

    if (CSS_MULTI_BAND_SCAN_RESULT_SUCC == enResult)
    {
        /* 如果扫频请求中，仅请求G的，则其他两个接入技术不需要进行判断，直接填为NULL */
        CSS_JudgeRssiExistType(&pstCssBandScanCnf->enGsmCoverageType,
                                &pstCssBandScanCnf->enUmtsFddCoverageType,
                                &pstCssBandScanCnf->enLteCoverageType);
    }

    #if (VOS_OS_VER != VOS_WIN32)
    NAS_TRACE_HIGH(" CSS_SndCommMsgBandScanCnf pstCssBandScanCnf->enGsmHighRssiExitType = %d, %d, %d", pstCssBandScanCnf->enGsmCoverageType,
                    pstCssBandScanCnf->enUmtsFddCoverageType,
                    pstCssBandScanCnf->enLteCoverageType);
    TLPS_PRINT2LAYER_INFO2(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL1, pstCssBandScanCnf->enGsmCoverageType, pstCssBandScanCnf->enUmtsFddCoverageType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL1, pstCssBandScanCnf->enLteCoverageType);
    #endif
    CSS_INFO_LOG1(" CSS_SndCommMsgBandScanCnf pstCssBandScanCnf->enGsmHighRssiExitType = ", pstCssBandScanCnf->enGsmCoverageType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL2, pstCssBandScanCnf->enGsmCoverageType);
    CSS_INFO_LOG1(" CSS_SndCommMsgBandScanCnf pstCssBandScanCnf->enGsmHighRssiExitType = ", pstCssBandScanCnf->enUmtsFddCoverageType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL3, pstCssBandScanCnf->enUmtsFddCoverageType);
    CSS_INFO_LOG1(" CSS_SndCommMsgBandScanCnf pstCssBandScanCnf->enLteCoverageType = ", pstCssBandScanCnf->enLteCoverageType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL4, pstCssBandScanCnf->enLteCoverageType);


    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssBandScanCnf);


    return ;
}
VOS_VOID CSS_BandScanReqMsgSave(const CSS_MULTI_BAND_SCAN_REQ_STRU *pstBandScanReq)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    CSS_INFO_LOG("CSS_BandScanReqMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(CSS_BandScanReqMsgSave_ENUM, LNAS_ENTRY);

    /* 如果之前已经有保存，则返回失败 */
    if (CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg)
    {
        CSS_INFO_LOG("CSS_BandScanReqMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(CSS_BandScanReqMsgSave_ENUM, LNAS_BandScanReqMsgSave_Existed);
        CSS_MEM_SET(&(pstCssControl->stCommMsg), 0, sizeof(pstCssControl->stCommMsg));
    }

    /* 保存命令内容 */
    pstCssControl->stCommMsg.bitOpSaveMsg      = CSS_OP_TRUE;
    pstCssControl->stCommMsg.bitOpHighRssi     = pstBandScanReq->bitOpHighRssi;
    pstCssControl->stCommMsg.ulOpid            = pstBandScanReq->ulOpid;
    pstCssControl->stCommMsg.ulReceiverPid     = pstBandScanReq->ulSenderPid;
    pstCssControl->stCommMsg.enMsgId           = ID_CSS_MULTI_BAND_SCAN_REQ;

    pstCssControl->stCommMsg.enBandScanType    = pstBandScanReq->enBandScanType;
    pstCssControl->stCommMsg.bitOpMcc          = pstBandScanReq->bitOpMcc;
    pstCssControl->stCommMsg.aucMcc[0]         = pstBandScanReq->aucMcc[0];
    pstCssControl->stCommMsg.aucMcc[1]         = pstBandScanReq->aucMcc[1];

    CSS_MEM_CPY(&(pstCssControl->stCommMsg.stRatList), &(pstBandScanReq->stRatList), sizeof(CSS_RAT_LIST));


    return;
}


VOS_VOID CSS_StopBandScanReqMsgSave(const CSS_STOP_BAND_SCAN_REQ_STRU *pstStopBandScanReq)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    CSS_INFO_LOG("CSS_BandScanReqMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(CSS_StopBandScanReqMsgSave_ENUM, LNAS_ENTRY);

    /* 如果之前已经有保存，则直接将原有存储消息覆盖 */
    if (CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg)
    {
        CSS_INFO_LOG("CSS_BandScanReqMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(CSS_StopBandScanReqMsgSave_ENUM, LNAS_BandScanReqMsgSave_Existed);
        CSS_MEM_SET(&(pstCssControl->stCommMsg), 0, sizeof(pstCssControl->stCommMsg));
    }

    /* 保存命令内容 */
    pstCssControl->stCommMsg.bitOpSaveMsg = CSS_OP_TRUE;
    pstCssControl->stCommMsg.ulReceiverPid = pstStopBandScanReq->ulSenderPid;
    pstCssControl->stCommMsg.enMsgId = ID_CSS_STOP_BAND_SCAN_REQ;


    return;
}


VOS_VOID CSS_ProcCommMsgBandScanReq
(
    const CSS_MULTI_BAND_SCAN_REQ_STRU  *pRcvMsg
)
{
    CSS_MAIN_STATE_ENUM_UINT16          enMainState        = CSS_MAIN_STATE_BUTT;    /* 当前处于的主状态 */
    CSS_SUB_STATE_ENUM_UINT16           enSubState         = CSS_SS_STATE_BUTT;      /* 当前处于的子状态 */
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl = CSS_GetControlAddr();
    enMainState = CSS_GetCurMainStatus();
    enSubState  = CSS_GetCurSubStatus();

    #if (VOS_OS_VER != VOS_WIN32)
    NAS_TRACE_HIGH(" CSS_ProcCommMsgBandScanReq pRcvMsg->enBandScanType = %d, %d, %d", pRcvMsg->enBandScanType, enMainState, enSubState);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_BandScanType, pRcvMsg->enBandScanType);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_EMM_MAIN_STATE, enMainState);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_EMM_SUB_STATE, enSubState);
    #endif

    switch(enMainState)
    {
        case CSS_MS_IDLE:
            if (CSS_SS_IDLE == enSubState)
            {
                /*现不支持MCC扫频请求*/
                if (CSS_BAND_SCAN_MCC_BASED == pRcvMsg->enBandScanType)
                {
                    CSS_WARN_LOG1("CSS_ProcCommMsgBandScanReq:not support MCC scan ",CSS_BAND_SCAN_FAIL_REASON_TYPE_NOT_SUPPORT);
                    TLPS_PRINT2LAYER_WARNING1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_FUNCTION_LABEL1, CSS_BAND_SCAN_FAIL_REASON_TYPE_NOT_SUPPORT);
                    CSS_SndCommMsgBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
                    return;
                }

                /* 存储扫频结果的空间释放 */
                CSS_FreeCommScanRsltMemory();

                /* 扫频请求消息保存 */
                CSS_BandScanReqMsgSave(pRcvMsg);

                /* 对扫频请求进行处理:如将BAND频点分段、申请内存空间等 */
                if (CSS_SUCC != CSS_ProcBandScanReqest())
                {
                    CSS_SndCommMsgBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                              pstCssControl->stCommMsg.ulOpid,
                                              CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
                    return;
                }

                /* 将LPHY设置为主模 */
                CSS_StartTimer(&pstCssControl->stSetactiveModeTimer);
                CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF);

                CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_ACTIVE);
            }
            break;

        case CSS_MS_SCAN:
            /* 如果是扫频过程中又收到扫频请求，则直接回复失败，原因值为扫频过程中 */
            CSS_WARN_LOG1("CSS_ProcCommMsgBandScanReq FAIL band scaning ", CSS_BAND_SCAN_FAIL_REASON_SCANING);
            TLPS_PRINT2LAYER_WARNING1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_FUNCTION_LABEL2, CSS_BAND_SCAN_FAIL_REASON_SCANING);
            CSS_SndCommMsgBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_SCANING);
            break;

        case CSS_MS_STOP_SCAN:
            /* 如果是停止扫频过程中收到扫频请求，则直接回复失败 */
            CSS_WARN_LOG1("CSS_ProcCommMsgBandScanReq FAIL stop band scaning ", CSS_BAND_SCAN_FAIL_REASON_STOP_SCANING );
            TLPS_PRINT2LAYER_WARNING1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_FUNCTION_LABEL3, CSS_BAND_SCAN_FAIL_REASON_STOP_SCANING);
            CSS_SndCommMsgBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
            break;

        default:
            CSS_WARN_LOG("CSS_ProcCommMsgBandScanReq FAIL stop band scaning, enMainState= ");
            TLPS_PRINT2LAYER_WARNING(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_FUNCTION_LABEL4);
            break;
    }

    return ;
}
VOS_VOID CSS_ProcCommMsgStopBandScanReq
(
    const CSS_STOP_BAND_SCAN_REQ_STRU *pstStopBandScanReq
)
{
    CSS_MAIN_STATE_ENUM_UINT16  enMainState     = CSS_MAIN_STATE_BUTT;    /* 当前处于的主状态 */
    CSS_SUB_STATE_ENUM_UINT16   enSubState      = CSS_SS_STATE_BUTT;     /* 当前处于的子状态 */
    CSS_CONTROL_STRU                   *pstCssControl;

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();
    pstCssControl = CSS_GetControlAddr();

    #if (VOS_OS_VER != VOS_WIN32)
    NAS_TRACE_HIGH(" CSS_ProcCommMsgStopBandScanReq enMainState = %d, %d", enMainState, enSubState);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgStopBandScanReq_ENUM, LNAS_EMM_MAIN_STATE, enMainState);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgStopBandScanReq_ENUM, LNAS_EMM_SUB_STATE, enSubState);
    #endif

    if (CSS_MS_IDLE == enMainState)
    {
        /* 只有已经开机的状态才处理，未开机不处理 */
        if (CSS_SS_IDLE == enSubState)
        {
            /* 直接回复成功 */
            CSS_SndCommMsgStopBandScanCnf(pstStopBandScanReq->ulSenderPid, CSS_RESULT_SUCC);
        }
    }
    else if (CSS_MS_SCAN == enMainState)
    {
        if (CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF == enSubState)
        {
            /* 如果当前处于等待设置主模回复的状态，直接通知LPHY设置从模 */
            CSS_StopTimer(&pstCssControl->stSetactiveModeTimer);
            CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

            CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

            CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

            CSS_StopBandScanReqMsgSave(pstStopBandScanReq);
        }
        else if (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == enSubState)
        {
            /* 如果当前处于等待设置从模回复的状态，则直接迁移状态到STOP+WAIT_SET_WORK_INACTIVE_MODE_CNF */
            CSS_GetCurMainStatus() = CSS_MS_STOP_SCAN;

            CSS_StopBandScanReqMsgSave(pstStopBandScanReq);
        }
        else if (CSS_SS_WAIT_BAND_SCAN_IND == enSubState)
        {
            /* 如果当前处于等待扫频结果时，需要先通知LPHY停止扫频，迁移状态 */
            CSS_StopTimer(&pstCssControl->stBandScanIndTimer);
            CSS_StartTimer(&pstCssControl->stStopBandScanTimer);

            CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_STOP_SCAN_CNF);

            CSS_SndLphyMsgStopBandScanReq();

            CSS_StopBandScanReqMsgSave(pstStopBandScanReq);
        }
    }
    else
    {
        /* 停止扫频过程中，又收到停止扫频消息，则直接丢弃 */
    }
    return ;
}


VOS_VOID CSS_ProcCommMsg(const VOS_VOID *pRcvMsg)
{

    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_CSS_MULTI_BAND_SCAN_REQ:
            CSS_ProcCommMsgBandScanReq((const CSS_MULTI_BAND_SCAN_REQ_STRU*)pRcvMsg);
            break;

        case ID_CSS_STOP_BAND_SCAN_REQ:
            CSS_ProcCommMsgStopBandScanReq((const CSS_STOP_BAND_SCAN_REQ_STRU *)pRcvMsg);
            break;

        default:
            break;
    }

    return;
}


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaMain.c */



