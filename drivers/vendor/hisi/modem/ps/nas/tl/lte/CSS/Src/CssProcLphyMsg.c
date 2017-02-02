

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

    /*��ȡ��ǰ���OPID*/
    usOpid = (VOS_UINT16)CSS_GetLphyCurOpid();

    /*�����δ�����ֵ��ֱ�Ӽ�1*/
    if( usOpid < CSS_MAX_OPID)
    {
        *pusOpid = usOpid + 1;
    }
    else/*����Ѿ������ֵ���ӳ�ֵ��ʼ����*/
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

    /* ���������MCCɨƵ Ŀǰ������ */
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

    /*������Ϣ�ռ�*/
    pstCssStopBandScanReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_STOP_BAND_SCAN_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssStopBandScanReq)
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET( CSS_GET_MSG_ENTITY(pstCssStopBandScanReq), 0, CSS_GET_MSG_LENGTH(pstCssStopBandScanReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssStopBandScanReq,ID_CSS_LPHY_STOP_BAND_SCAN_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssStopBandScanReq->usOpId = usOpid;

    /*������Ϣ���ͺ��� */
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

    /*������Ϣ�ռ�*/
    pstCssSetModeInactive = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_SET_WORK_MODE_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssSetModeInactive)
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET( CSS_GET_MSG_ENTITY(pstCssSetModeInactive), 0, CSS_GET_MSG_LENGTH(pstCssSetModeInactive));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssSetModeInactive,ID_CSS_LPHY_SET_WORK_MODE_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssSetModeInactive->usOpId = usOpid;
    pstCssSetModeInactive->enWorkModeType = enWorkModeType;

    /*������Ϣ���ͺ��� */
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
        /*��ӡ�쳣��Ϣ*/
        CSS_WARN_LOG("CSS_SndLphyMsgBandScanReq:BAND NODE is NULL!");
        TLPS_PRINT2LAYER_WARNING(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_BandNodeIsNULL);
        return ;
    }

    /*������Ϣ�ռ�*/
    pstCssBandScanReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_BAND_SCAN_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssBandScanReq)
    {
        /*��ӡ�쳣��Ϣ*/
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

    /*������Ϣ���ͺ��� */
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

    /* ���OPID��ƥ�䣬��ֱ���˳� */
    if (pstCssControl->ulCssLphyOpid != pRcvMsg->usOpId)
    {
        /*��ӡ������Ϣ*/
        CSS_WARN_LOG("CSS_ProcLphyMsgScanInd: opid mismatch!");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_OpidMismatch);
        return;
    }

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (CSS_MS_SCAN != CSS_GetCurMainStatus() || CSS_SS_WAIT_BAND_SCAN_IND != CSS_GetCurSubStatus())
    {
        /*��ӡ������Ϣ*/
        CSS_WARN_LOG("CSS_ProcLphyMsgScanInd: STATE ERR!");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_STATE_ERR);
        return;
    }

    /*����ϱ���BAND�Ƿ�͵�ǰ���ڴ����BAND�Ƿ�һ��*/
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

    /*��������쳣�����򷵻�*/
    if (CSS_CAUSE_NULL_PTR == CSS_ProcLphyBandScanRslt(&(pRcvMsg->stBandScanResult)))
    {
        return;
    }

    /*�ж��Ƿ���Ҫ������һ��ɨƵ*/
    if (CSS_TRUE == CSS_IsNeedSndLphyNextBandScanReq())
    {
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);
        CSS_SndLphyMsgCommBandScanReq(CSS_GetCommScanBandListCurrNode(),
                                          CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                          CSS_GetCommScanCurFreqRangeIdx());
    }
    /*���е�Ƶ�㶼ɨ���ˣ��˴��к�������ת״̬����������*/
    else
    {
        /* ��LPHY����Ϊ��ģ */
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

    /* ���OPIDƥ�䲻�ɹ�����ֱ�Ӷ��� */
    if (CSS_GetLphyCurOpid() != pRcvMsg->usOpId)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgStopScanCnf opid mismatch ");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgStopScanCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* ֹͣ��ʱ�� */
    CSS_StopTimer(&pstCssControl->stStopBandScanTimer);

    /* ���ֹͣɨƵʧ�ܣ���ֱ�ӵ��õ���ӿڸ�λ */
    if(CSS_LPHY_RESULT_FAIL == pRcvMsg->enStopBandScanRslt)
    {
        CSS_ClearLocalResource();

        /* ���ô�ģʧ�ܣ����õ���ӿڣ�ֱ�Ӹ�λ */
        (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_STOP_SCAN_FAIL, (__LINE__), (THIS_FILE_ID) );

        return ;
    }

    /* ���OPIDƥ��ɹ�����״̬ΪSTOP_SCAN+CSS_SS_WAIT_STOP_SCAN_CNF,����Ҫ��LPHY����Ϊ��ģ */
    if ((CSS_MS_STOP_SCAN == CSS_GetCurMainStatus()) && (CSS_SS_WAIT_STOP_SCAN_CNF == CSS_GetCurSubStatus()))
    {

        /* �յ�LPHY��ֹͣɨƵ��Ϣ�󣬽�LPHY����Ϊ��ģ */
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
            /* �洢ɨƵ����Ŀռ��ͷ� */
            CSS_FreeCommScanRsltMemory();
            /* ת״̬ */
            CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

            /* ���������ģʧ�ܣ���֪ͨɨƵʧ�ܣ�ֹͣ��ʱ����Ǩ��״̬ */
            CSS_SndCommMsgBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                      pstCssControl->stCommMsg.ulOpid,
                                      CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);

        }
    }
    else if (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == CSS_GetCurSubStatus())
    {
        CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);

        /* �����ɨƵ�������յ����ô�ģ�Ļظ�����Ҫ��GUNAS/AS����ɨƵ��� */
        /* ������ô�ģʧ�ܣ���ֱ�Ӹ�λ */
        if (CSS_LPHY_RESULT_FAIL == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_ClearLocalResource();

            /* ���ô�ģʧ�ܣ����õ���ӿڣ�ֱ�Ӹ�λ */
            (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL, (__LINE__), (THIS_FILE_ID) );

            return;
        }

        /* ��GUNSA/AS����ɨƵ��� */
        CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);
        CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc();

        /* �����ر����ɨƵ�������HIDS�� */
        CSS_SendOmBandScanResultInfoInd();
    }
}

VOS_VOID CSS_ProcLphyMsgSetModeCnf
(
    const CSS_LPHY_SET_WORK_MODE_CNF_STRU   *pstSetModeCnf
)
{
    CSS_MAIN_STATE_ENUM_UINT16  enMainState;    /* ��ǰ���ڵ���״̬ */
    CSS_SUB_STATE_ENUM_UINT16   enSubState;     /* ��ǰ���ڵ���״̬ */
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();

    /* ���OPIDƥ�䲻�ɹ�����ֱ�Ӷ��� */
    if (CSS_GetLphyCurOpid() != pstSetModeCnf->usOpId)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgSetModeCnf opid mismatch");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgSetModeCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* �����״̬��ɨƵ����������ģ�ɹ������LPHY����ɨƵ���� */
    if (CSS_MS_SCAN == enMainState)
    {
        CSS_MsScanProcLphyMsgSetModeCnf(pstSetModeCnf);
    }
    else if ((CSS_MS_STOP_SCAN == enMainState) && (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == enSubState))
    {
        /* ֹͣ��ʱ�� */
        CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);

        /* ������ô�ģʧ�ܣ���ֱ�Ӹ�λ */
        if (CSS_LPHY_RESULT_FAIL == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_ClearLocalResource();

            /* ���ô�ģʧ�ܣ����õ���ӿڣ�ֱ�Ӹ�λ */
            (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL, (__LINE__), (THIS_FILE_ID) );

            return;
        }

        /* �����״̬���������: GUNAS/AS֪ͨCSSģ��ֹͣɨƵ��������ɨƵ�����У������쳣��CSSģ������֪ͨLPHYֹͣɨƵ */
        /* ����������Ϣ��ֹͣɨƵ����ֱ�ӻظ�ֹͣɨƵ�ɹ� */
        if ((CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg) &&
            (ID_CSS_STOP_BAND_SCAN_REQ == pstCssControl->stCommMsg.enMsgId))
        {
            CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

            CSS_SndCommMsgStopBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                           CSS_RESULT_SUCC );


        }

        /* �����ɨƵ�����г����쳣����ظ�ɨƵʧ�� */
        if ((CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg) &&
            (ID_CSS_MULTI_BAND_SCAN_REQ == pstCssControl->stCommMsg.enMsgId))
        {
            CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

            CSS_SndCommMsgBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                      pstCssControl->stCommMsg.ulOpid,
                                      CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
        }

        /* ֹͣɨƵ����ɨƵ�������쳣����Ҫ���洢ɨƵ����Ŀռ��ͷ� */
        CSS_FreeCommScanRsltMemory();
    }

    return ;
}
VOS_VOID CSS_ProcLphyMsg(const VOS_VOID *pRcvMsg )
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
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




