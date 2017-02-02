



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasCommPrint.h"
#include "CssPublic.h"
#include "CssOmInterface.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPUBLIC_C

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
CSS_LPHY_FREQ_RANGE_INFO_STRU    g_ausCssLteBandFreq[] =
{{21100,21700}, {19300,19900}, {18050,18800}, {21100,21550}, {8690,8940},       /* Band1 ~Band5  */
 {8750,8850},   {26200,26900}, {9250,9600},   {18449,18799}, {21100,21700},     /* Band6 ~Band10 */
 {14759,14959}, {7290,7460},   {7460,7560},   {7580,7680},   {65535,65535},     /* Band11~Band15 */
 {65535,65535}, {7340,7460},   {8600,8750},   {8750,8900},   {7910,8210},       /* Band16~Band20 */
 {14959,15109}, {35100,35900}, {21800,22000}, {15250,15590}, {19300,19950},     /* Band21~Band25 */
 {8590,8940},   {8520,8690},   {7580,8030},   {7170,7280},   {23500,23600},     /* Band26~Band30 */
 {4625,4675},   {65535,65535}, {19000,19200}, {20100,20250}, {18500,19100},     /* Band31~Band35 */
 {19300,19900}, {19100,19300}, {25700,26200}, {18800,19200}, {23000,24000},     /* Band36~Band40 */
 {24960,26900}, {34000,36000}, {36000,38000}, {7030,8030}                       /* Band41~Band44 */
};


CSS_OVERLAP_BAND_STRU            g_aucOverLapBand[] =
{
 {1,4},{1,10},{2,25},{2,36},{3,9},
 {3,35},{4,10},{5,6},{5,18},{5,19},
 {5,26},{6,19},{6,26},{7,41},{9,35},
 {12,17},{13,44},{14,28},{14,44},{17,44},
 {18,26},{18,27},{19,26},{20,28},{20,44},
 {25,36},{26,27},{28,44},{29,44},{30,40},
 {33,35},{33,39},{33,37},{35,39},{37,39},
 {38,41}
};
const VOS_UINT32 g_aucOverLapBandSize = (sizeof(g_aucOverLapBand)/sizeof(CSS_OVERLAP_BAND_STRU));


CSS_LPHY_FREQ_RANGE_INFO_STRU    g_ausCssWcdmaBandFreq[] =
{{21124,21676}, {19324,19876}, {18074,18776}, {21124,21526}, {8714,8916},            /* Band1 ~Band5  */
 {8774,8826}, {26224,26876}, {9274,9576}, {18474,18774}, {21124,21676},              /* Band6 ~Band10 */
 {14784,14934}, {7314,7436}, {7484,7536}, {7604,7656}, {65535,65535},                /* Band11 ~Band15 */
 {65535,65535}, {65535,65535}, {65535,65535}, {8774,8876}, {7934,8186},              /* Band16 ~Band20 */
 {14984,15084} , {35124,35876}, {65535,65535} , {65535,65535}, {19324,19926},        /* Band21 ~Band25 */
 {8614,8916}                                                                         /* Band26*/
};

CSS_LPHY_FREQ_RANGE_INFO_STRU    g_ausCssGsmBandFreq[] =
{{65535,65535}, {19302,19898}, {18052,18798}, {65535,65535}, {8692,8938},       /* Band1 ~Band5  */
 {65535,65535}, {65535,65535}, {9212,9598}                                      /* Band6 ~Band8 */
};










VOS_CHAR                                g_acCssPrintBuf[CSS_PRINT_BUFF_LEN] = "";

NAS_COMM_PRINT_LIST_STRU g_astCssCommMsgIdArray[] =
{
    {   ID_CSS_MULTI_BAND_SCAN_REQ                 ,
            "MSG:  ID_CSS_MULTI_BAND_SCAN_REQ                           ",
        VOS_NULL_PTR},
    {   ID_CSS_STOP_BAND_SCAN_REQ                  ,
            "MSG:  ID_CSS_STOP_BAND_SCAN_REQ                            ",
        VOS_NULL_PTR},
    {   ID_CSS_MULTI_BAND_SCAN_CNF                    ,
            "MSG:  ID_CSS_MULTI_BAND_SCAN_CNF                              ",
        VOS_NULL_PTR},
    {   ID_CSS_STOP_BAND_SCAN_CNF                    ,
            "MSG:  ID_CSS_STOP_BAND_SCAN_CNF                              ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_LIST_STRU g_astCssLphyMsgIdArray[] =
{
    {   ID_CSS_LPHY_BAND_SCAN_REQ                 ,
            "MSG:  ID_CSS_LPHY_BAND_SCAN_REQ                           ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_STOP_BAND_SCAN_REQ                  ,
            "MSG:  ID_CSS_LPHY_STOP_BAND_SCAN_REQ                            ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_SET_WORK_MODE_REQ                    ,
            "MSG:  ID_CSS_LPHY_SET_WORK_MODE_REQ                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_BAND_SCAN_IND                    ,
            "MSG:  ID_CSS_LPHY_BAND_SCAN_IND                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_STOP_BAND_SCAN_CNF                    ,
            "MSG:  ID_CSS_LPHY_STOP_BAND_SCAN_CNF                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_SET_WORK_MODE_CNF                    ,
            "MSG:  ID_CSS_LPHY_SET_WORK_MODE_CNF                              ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_LIST_STRU g_astCssLmmMsgIdArray[] =
{
    {   ID_LMM_CSS_START_IND                 ,
            "MSG:  ID_LMM_CSS_START_IND                           ",
        VOS_NULL_PTR},
    {   ID_LMM_CSS_STOP_IND                  ,
            "MSG:  ID_LMM_CSS_STOP_IND                            ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astCssTimerArray[] =
{
    {   TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF,
            "STATE TI:  TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF           "},
    {   TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF     ,
            "STATE TI:  TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF                  "},
    {   TI_CSS_WAIT_FOR_SCAN_IND     ,
            "STATE TI:  TI_CSS_WAIT_FOR_SCAN_IND                  "},
    {   TI_CSS_WAIT_FOR_STOP_SCAN_CNF               ,
            "STATE TI:  TI_CSS_WAIT_FOR_STOP_SCAN_CNF                  "},
};


/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID  CSS_SndOmTimerStatus(
    CSS_TIMER_RUN_STA_ENUM_UINT32          enTimerStatus,
    VOS_UINT16                          enTimerId,
    VOS_UINT32                          ulTimerRemainLen
)
{
    CSS_TIMER_INFO_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CSS_TIMER_INFO_STRU*)CSS_ALLOC_MSG(sizeof(CSS_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CSS_ERR_LOG("CSS_SndOmTimerStatus: mem alloc fail!.");
        return;
    }

    CSS_WRITE_OM_MSG_HEAD(  pstMsg, (enTimerId + CSS_TIMER_ID_TO_MSG_ID_BASE));

    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->usTimerId                   = enTimerId;
    pstMsg->usRsv                       = 0;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    CSS_FREE_MSG(pstMsg);

}


VOS_VOID  CSS_SndOmBandScanAbnormalInfo
(
    VOS_UINT32 ulFileName,
    VOS_UINT32 ulLineNo,
    CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8 enBandScanFailReason,
    VOS_UINT8 ucPara1,
    VOS_UINT8 ucPara2
)
{
    CSS_BAND_SCAN_ABNORMAL_INFO_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CSS_BAND_SCAN_ABNORMAL_INFO_IND_STRU*)CSS_ALLOC_MSG(sizeof(CSS_BAND_SCAN_ABNORMAL_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CSS_ERR_LOG("CSS_SndOmBandScanAbnormalInfo: mem alloc fail!.");
        return;
    }

    CSS_WRITE_OM_MSG_HEAD(  pstMsg, ID_CSS_BAND_SCAN_ABNORMAL_INFO_IND);

    pstMsg->enCurMainState              = CSS_GetCurMainStatus();
    pstMsg->enCurSubState               = CSS_GetCurSubStatus();
    pstMsg->enBandScanFailReason        = enBandScanFailReason;
    pstMsg->ucPara1                     = ucPara1;
    pstMsg->ucPara2                     = ucPara2;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    CSS_FREE_MSG(pstMsg);

}



VOS_VOID  CSS_SendOmStateChangeInd
(
    CSS_MAIN_STATE_ENUM_UINT16                      enPreMainState,
    CSS_SUB_STATE_ENUM_UINT16                       enPreSubState,
    CSS_MAIN_STATE_ENUM_UINT16                      enCurMainState,
    CSS_SUB_STATE_ENUM_UINT16                       enCurSubState
)
{
    CSS_STATE_CHANGE_IND_STRU           *pstStateChangeInd;


    /*����ռ䲢��������Ƿ�ɹ�*/
    pstStateChangeInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_STATE_CHANGE_IND_STRU));

    if ( VOS_NULL_PTR == pstStateChangeInd )
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SendOmStateChangeInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    CSS_MEM_SET(CSS_GET_MSG_ENTITY(pstStateChangeInd), 0, \
               CSS_GET_MSG_LENGTH(pstStateChangeInd));

    /*��д��Ϣͷ*/
    CSS_WRITE_OM_MSG_HEAD(pstStateChangeInd,ID_CSS_STATE_CHANGE_IND);

    pstStateChangeInd->enPreMainState = enPreMainState;
    pstStateChangeInd->enPreSubState = enPreSubState;
    pstStateChangeInd->enCurMainState = enCurMainState;
    pstStateChangeInd->enCurSubState = enCurSubState;


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    CSS_SND_MSG(pstStateChangeInd);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstStateChangeInd);

    /*�ͷ���Ϣ�ռ�*/
    CSS_FREE_MSG(pstStateChangeInd);

#endif

    return;
}
VOS_VOID  CSS_SendOmCommBandInfoInd
(
    CSS_COMM_BAND_INFO_STRU  *pstCssCommBandConfig
)
{
    CSS_COMM_BAND_NV_INFO_IND_STRU           *pstCommBandInfoInd;


    /*����ռ䲢��������Ƿ�ɹ�*/
    pstCommBandInfoInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_COMM_BAND_NV_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstCommBandInfoInd )
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SendOmCommBandInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    CSS_MEM_SET(CSS_GET_MSG_ENTITY(pstCommBandInfoInd), 0, \
               CSS_GET_MSG_LENGTH(pstCommBandInfoInd));

    /*��д��Ϣͷ*/
    CSS_WRITE_OM_MSG_HEAD(pstCommBandInfoInd,ID_CSS_COMM_BAND_NV_INFO_IND);

    CSS_MEM_CPY(&pstCommBandInfoInd->stCommBandInfo, pstCssCommBandConfig, sizeof(CSS_COMM_BAND_INFO_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    CSS_SND_MSG(pstCommBandInfoInd);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstCommBandInfoInd);

    /*�ͷ���Ϣ�ռ�*/
    CSS_FREE_MSG(pstCommBandInfoInd);

#endif

    return;
}
VOS_VOID  CSS_SendOmRatThresholdInfoInd
(
    CSS_RSSI_THRESHOLD_STRU  *pstCssRatThresholdConfig
)
{
    CSS_RAT_THRESHOLD_INFO_IND_STRU           *pstCssRatThresholdInfoInd;


    /*����ռ䲢��������Ƿ�ɹ�*/
    pstCssRatThresholdInfoInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_RAT_THRESHOLD_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstCssRatThresholdInfoInd )
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SendOmRatThresholdInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    CSS_MEM_SET(CSS_GET_MSG_ENTITY(pstCssRatThresholdInfoInd), 0, \
               CSS_GET_MSG_LENGTH(pstCssRatThresholdInfoInd));

    /*��д��Ϣͷ*/
    CSS_WRITE_OM_MSG_HEAD(pstCssRatThresholdInfoInd,ID_CSS_RAT_THRESHOLD_INFO_IND);

    CSS_MEM_CPY(&pstCssRatThresholdInfoInd->stBandThresholdInfo, pstCssRatThresholdConfig, sizeof(CSS_RSSI_THRESHOLD_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    CSS_SND_MSG(pstCssRatThresholdInfoInd);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstCssRatThresholdInfoInd);

    /*�ͷ���Ϣ�ռ�*/
    CSS_FREE_MSG(pstCssRatThresholdInfoInd);

#endif

    return;
}
VOS_VOID  CSS_SendOmBandScanResultInfoInd
(
    VOS_VOID
)
{
    CSS_BAND_SCAN_RESULT_IND_STRU           *pstCssBandScanResultInd;
    VOS_UINT8                                ucBandNum     = 0;
    VOS_UINT8                                ucBandNodeNum = 0;
    CSS_COMM_SCAN_BAND_NODE_STRU            *pBandNode;
    VOS_UINT16                               usMemSize = 0;

    pBandNode   = CSS_GetCommScanBandListHeadNode();


    /*����ռ䲢��������Ƿ�ɹ�*/
    pstCssBandScanResultInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_BAND_SCAN_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstCssBandScanResultInd )
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SendOmBandScanResultInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    CSS_MEM_SET(CSS_GET_MSG_ENTITY(pstCssBandScanResultInd), 0, \
               CSS_GET_MSG_LENGTH(pstCssBandScanResultInd));

    /*��д��Ϣͷ*/
    CSS_WRITE_OM_MSG_HEAD(pstCssBandScanResultInd,ID_CSS_BAND_SCAN_RESULT_IND);

    /* ���ɨƵ��� */
    while (CSS_NULL_PTR != pBandNode && ucBandNodeNum < CSS_GetCommScanBandListAddr()->ucBandCount)
    {
        pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].enBandInd          = pBandNode->stBandInfo.ucBandInd;
        pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucFreqNum          = pBandNode->stBandInfo.ucScanRsltArrayCount;
        CSS_MEM_CPY(pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].astFreqScanResult,
                    pBandNode->stBandInfo.pstScanRsltArray,
                    sizeof(CSS_FREQ_RANGE_STRU)*(pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucFreqNum));

        /*lint -e734*/
        pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucDynMemSize = sizeof(CSS_FREQ_RANGE_STRU)*(pBandNode->stBandInfo.ucScanRsltArrayCount)
                                                                                         + sizeof(CSS_LPHY_FREQ_RANGE_INFO_STRU)*(pBandNode->stBandInfo.ucScanReqCount);
        /*lint +e734*/
        usMemSize += (pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucDynMemSize + sizeof(CSS_COMM_SCAN_BAND_NODE_STRU));

        ucBandNum ++;

        pBandNode       = pBandNode->pstNext;
        ucBandNodeNum  += 1;
    }

    pstCssBandScanResultInd->stBandScanResult.ucBandNum = ucBandNum;

    pstCssBandScanResultInd->stBandScanResult.usDynMemSize = usMemSize;

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    CSS_SND_MSG(pstCssBandScanResultInd);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstCssBandScanResultInd);

    /*�ͷ���Ϣ�ռ�*/
    CSS_FREE_MSG(pstCssBandScanResultInd);

#endif

    return;
}


VOS_VOID  CSS_SendOmBandApiInfoInd
(
    CSS_RAT_COVERAGE_STRU                           *pstRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU                    *pstBandScanResult
)
{
    CSS_BAND_SCAN_API_INFO_IND_STRU           *pstCssBandApiInfoInd;


    /*����ռ䲢��������Ƿ�ɹ�*/
    pstCssBandApiInfoInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_BAND_SCAN_API_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstCssBandApiInfoInd )
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SendOmBandApiInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    CSS_MEM_SET(CSS_GET_MSG_ENTITY(pstCssBandApiInfoInd), 0, \
               CSS_GET_MSG_LENGTH(pstCssBandApiInfoInd));

    /*��д��Ϣͷ*/
    CSS_WRITE_OM_MSG_HEAD(pstCssBandApiInfoInd,ID_CSS_BAND_SCAN_API_INFO_IND);

    CSS_MEM_CPY(&pstCssBandApiInfoInd->stRatCoverage, pstRatCoverage, sizeof(CSS_RAT_COVERAGE_STRU));
    CSS_MEM_CPY(&pstCssBandApiInfoInd->stBandScanResult, pstBandScanResult, sizeof(CSS_BAND_SCAN_LIST_INFO_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    CSS_SND_MSG(pstCssBandApiInfoInd);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstCssBandApiInfoInd);

    /*�ͷ���Ϣ�ռ�*/
    CSS_FREE_MSG(pstCssBandApiInfoInd);

#endif

    return;
}
VOS_VOID  CSS_SendOmMmlUeSupportBandInfoInd
(
    NAS_MML_MS_BAND_INFO_STRU   *pstUeSupportBand
)
{
    CSS_UE_SUPPORT_BAND_INFO_IND_STRU   *pstUeSupportBandInfoInd = CSS_NULL_PTR;


    /*����ռ䲢��������Ƿ�ɹ�*/
    pstUeSupportBandInfoInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_BAND_SCAN_API_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstUeSupportBandInfoInd )
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SendOmMmlUeSupportBandInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    CSS_MEM_SET(CSS_GET_MSG_ENTITY(pstUeSupportBandInfoInd), 0, \
               CSS_GET_MSG_LENGTH(pstUeSupportBandInfoInd));

    /*��д��Ϣͷ*/
    CSS_WRITE_OM_MSG_HEAD(pstUeSupportBandInfoInd,ID_CSS_UE_SUPORT_BAND_INFO_IND);

    CSS_MEM_CPY(&pstUeSupportBandInfoInd->stUeSupportBand, (CSS_UE_SUPPORT_FREQ_BAND_STRU*)pstUeSupportBand, sizeof(CSS_UE_SUPPORT_FREQ_BAND_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    CSS_SND_MSG(pstUeSupportBandInfoInd);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstUeSupportBandInfoInd);

    /*�ͷ���Ϣ�ռ�*/
    CSS_FREE_MSG(pstUeSupportBandInfoInd);

#endif

    return;
}
VOS_UINT32  CSS_ReadNvCommBandConfig
(
    CSS_NV_COMM_BAND_CONFIG_STRU  *pstCssCommBandConfig
)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = CSS_FAIL;

    /* ��NV */
    ulDataLen = sizeof(CSS_NV_COMM_BAND_CONFIG_STRU);
    ulRslt = CSS_NV_Read(EN_NV_ID_PS_COMM_BAND_CONFIG,
                              (VOS_VOID *)pstCssCommBandConfig,
                              ulDataLen);

    if(CSS_RESULT_FAIL == ulRslt)
    {
        CSS_WARN_LOG("CSS_ReadNvCommBandConfig: read NV Fail.");
        TLPS_PRINT2LAYER_WARNING(CSS_ReadNvCommBandConfig_ENUM, LNAS_ReadNvFail);
        return CSS_FAIL;
    }


    return CSS_SUCC;
}
VOS_UINT32  CSS_ReadNvRssiThreshold
(
    CSS_NV_RAT_RSSI_THRESHOLD_STRU  *pstCssRssiTH
)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = CSS_FAIL;

    /* ��NV */
    ulDataLen = sizeof(CSS_NV_RAT_RSSI_THRESHOLD_STRU);
    ulRslt = CSS_NV_Read(EN_NV_ID_PS_RAT_RSSI_THRESHOLD,
                              (VOS_VOID *)pstCssRssiTH,
                              ulDataLen);

    if(CSS_RESULT_FAIL == ulRslt)
    {
        CSS_WARN_LOG("CSS_ReadNvRssiThreshold: read NV Fail.");
        TLPS_PRINT2LAYER_WARNING(CSS_ReadNvRssiThreshold_ENUM, LNAS_ReadNvFail);

        return CSS_FAIL;
    }

    /* zhaochen 00308719 PCLINT��Ϊ����64����ܵ��¾��ȶ�ʧ��ʵ������ֵ������ô�󣬹����� begin 2015-06-29 */
    /*lint -e734*/
    pstCssRssiTH->sGHighRssiThresHold = pstCssRssiTH->sGHighRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sGLowRssiThresHold = pstCssRssiTH->sGLowRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sWHighRssiThresHold = pstCssRssiTH->sWHighRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sWLowRssiThresHold = pstCssRssiTH->sWLowRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sLHighRssiThresHold = pstCssRssiTH->sLHighRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sLLowRssiThresHold = pstCssRssiTH->sLLowRssiThresHold * CSS_RSSI_64DB;
    /*lint +e734*/
    /* zhaochen 00308719 end 2015-06-29 */

    return CSS_SUCC;
}
VOS_VOID   CSS_FSMTranState
(
    CSS_MAIN_STATE_ENUM_UINT16  enMainState,
    CSS_SUB_STATE_ENUM_UINT16   enSubState
)
{
    /* ��ת״̬ǰ��״̬��ת״̬��Ĺ���HIDS�� */
    CSS_SendOmStateChangeInd(CSS_GetCurMainStatus(),
                            CSS_GetCurSubStatus(),
                            enMainState,
                            enSubState);

    #if (VOS_OS_VER != VOS_WIN32)
    NAS_TRACE_HIGH(" CSS_FSMTranState CSS_GetCurMainStatus = %d, CSS_GetCurSubStatus = %d",
                    CSS_GetCurMainStatus(), CSS_GetCurSubStatus());
    TLPS_PRINT2LAYER_INFO1(CSS_FSMTranState_ENUM, LNAS_CSS_GetCurMainStatus, CSS_GetCurMainStatus());
    TLPS_PRINT2LAYER_INFO1(CSS_FSMTranState_ENUM, LNAS_CSS_GetCurSubStatus, CSS_GetCurSubStatus());

    NAS_TRACE_HIGH(" CSS_FSMTranState CSS_GetDstMainStatus = %d, CSS_GetstSubStatus = %d",
                    enMainState, enSubState);
    TLPS_PRINT2LAYER_INFO1(CSS_FSMTranState_ENUM, LNAS_CSS_GetDstMainStatus, enMainState);
    TLPS_PRINT2LAYER_INFO1(CSS_FSMTranState_ENUM, LNAS_CSS_GetstSubStatus, enSubState);
    #endif

    CSS_GetCurMainStatus()               = enMainState;
    CSS_GetCurSubStatus()                = enSubState;

    return;
}
VOS_UINT32 CSS_GetTimerLen
(
    CSS_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    if (TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF == enTimerId)
    {
        return TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF_LEN;
    }

    if (TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF == enTimerId)
    {
        return TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF_LEN;
    }

    if (TI_CSS_WAIT_FOR_SCAN_IND == enTimerId)
    {
        return TI_CSS_WAIT_FOR_SCAN_IND_LEN;
    }

    if (TI_CSS_WAIT_FOR_STOP_SCAN_CNF == enTimerId)
    {
        return TI_CSS_WAIT_FOR_STOP_SCAN_CNF_LEN;
    }

    return 0;
}


VOS_VOID CSS_StartTimer(CSS_TIMER_STRU *pstTimer)
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
            CSS_WARN_LOG("CSS_StartTimer:WARN: stop timer error!");
            TLPS_PRINT2LAYER_WARNING(CSS_StartTimer_ENUM, LNAS_StopTimerErr);
            return;
        }

        /*��ӡ�쳣��Ϣ*/
        CSS_WARN_LOG1("(TimerType) Timer not close!",pstTimer->usName);
        TLPS_PRINT2LAYER_WARNING2(CSS_StartTimer_ENUM, LNAS_TimerNotClose,pstTimer->usName,1);
    }

    if (pstTimer->ulTimerLen == 0)
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_StartTimer:ERROR: start unreasonable timer.");
        TLPS_PRINT2LAYER_WARNING(CSS_StartTimer_ENUM, LNAS_StartUnreasonableTimer);
        return;
    }

    /*�趨��ʱ��NAME����ʧ���򱨾�����*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimer->phTimer),PS_PID_CSS,\
                                pstTimer->ulTimerLen,(VOS_UINT32)pstTimer->usName,\
                                pstTimer->usPara,pstTimer->ucMode))
    {
          /*��ӡ�쳣��Ϣ*/
          CSS_WARN_LOG("CSS_StartTimer:WARN: start timer error!");
          TLPS_PRINT2LAYER_WARNING1(CSS_StartTimer_ENUM, LNAS_StopTimerErr,1);
          return;
    }

    CSS_SndOmTimerStatus(CSS_TIMER_RUNNING, pstTimer->usName, pstTimer->ulTimerLen);

}
VOS_VOID CSS_StopTimer(CSS_TIMER_STRU *pstTimer)
{
    VOS_UINT32                          ulTimerRemainLen    =    0;

    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimer->phTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            CSS_WARN_LOG("CSS_StopTimer:WARN: stop timer error!");
            TLPS_PRINT2LAYER_WARNING(CSS_StopTimer_ENUM, LNAS_StopTimerErr);
            return;
        }

        pstTimer->phTimer = VOS_NULL_PTR;

        CSS_INFO_LOG1("(TimerType) Timer closed!",pstTimer->usName);
        TLPS_PRINT2LAYER_WARNING1(CSS_StopTimer_ENUM, LNAS_TimerClosed,pstTimer->usName);
    }

    CSS_SndOmTimerStatus(CSS_TIMER_STOPED, pstTimer->usName, ulTimerRemainLen);

}

VOS_VOID CSS_FreeCommScanRsltMemory(VOS_VOID)
{
    CSS_COMM_SCAN_BAND_LIST_STRU         *pRsltList     = CSS_GetCommScanBandListAddr();

    CSS_COMM_SCAN_BAND_NODE_STRU         *pBandNode     = CSS_GetCommScanBandListHeadNode();
    CSS_COMM_SCAN_BAND_NODE_STRU         *ptmpNode;
    VOS_UINT8                             ucNum         = 0;

    while ((CSS_NULL_PTR != pBandNode) && (ucNum < pRsltList->ucBandCount))
    {
        ptmpNode = pBandNode->pstNext;

        if (CSS_NULL_PTR != pBandNode->stBandInfo.pstScanReqArray)
        {
            (VOS_VOID)CSS_MEM_FREE(pBandNode->stBandInfo.pstScanReqArray);
            pBandNode->stBandInfo.pstScanReqArray = CSS_NULL_PTR;
        }
        if (CSS_NULL_PTR != pBandNode->stBandInfo.pstScanRsltArray)
        {
            (VOS_VOID)CSS_MEM_FREE(pBandNode->stBandInfo.pstScanRsltArray);
            pBandNode->stBandInfo.pstScanRsltArray = CSS_NULL_PTR;
        }

        (VOS_VOID)CSS_MEM_FREE(pBandNode);
        pBandNode = CSS_NULL_PTR;

        ucNum += 1;

        pBandNode = ptmpNode;
    }

    pRsltList->ucBandCount           = 0;
    pRsltList->ucCurFreqRangeIdx     = 0;
    pRsltList->pstCurr               = CSS_NULL_PTR;
    pRsltList->pstHead               = CSS_NULL_PTR;
    pRsltList->pstTail               = CSS_NULL_PTR;
}



VOS_INT32  CSS_PrintCommMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulAtImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulAtImsaMsgNum = sizeof(g_astCssCommMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulAtImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astCssCommMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulAtImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astCssCommMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astCssCommMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astCssCommMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        CSS_WARN_LOG1("IMSA_PrintAtMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(CSS_PrintCommMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  CSS_PrintLphyMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulAtImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulAtImsaMsgNum = sizeof(g_astCssLphyMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulAtImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astCssLphyMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulAtImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astCssLphyMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astCssLphyMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astCssLphyMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        CSS_WARN_LOG1("CSS_PrintLphyMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(CSS_PrintLphyMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  CSS_PrintLmmMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulAtImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulAtImsaMsgNum = sizeof(g_astCssLmmMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulAtImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astCssLmmMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulAtImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astCssLmmMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astCssLmmMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astCssLmmMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        CSS_WARN_LOG1("CSS_PrintLmmMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(CSS_PrintLmmMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  CSS_PrintTimerMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulTimerType,
    VOS_UINT32                          ulTimerPara
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulCssTimerNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulCssTimerNum = sizeof(g_astCssTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulCssTimerNum; ulLoop++)
    {
        if (g_astCssTimerArray[ulLoop].ulId == ulTimerType)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulCssTimerNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astCssTimerArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        /* ��ӡ��Ϣ��ÿ������*/
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " ulPara = %d \r\n",
                           ulTimerPara,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        CSS_WARN_LOG1("CSS_PrintTimerMsg, Invalid Timer Type: ",ulTimerType);
        TLPS_PRINT2LAYER_WARNING1(CSS_PrintTimerMsg_ENUM, LNAS_InvalidTimerType, ulTimerType);
    }

    return (usTotalLen - usOffset);

}
VOS_VOID CSS_PrintCssRevMsg
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
                     "CSS Receive Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        CSS_WARN_LOG("CSS_PrintCssRevMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(CSS_PrintCssRevMsg_ENUM, LNAS_FUNCTION_LABEL1);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ����PID����Ϣ */
    switch ( pstMsg->ulSenderPid )
    {
        case PS_PID_HPA:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "LPHY-->CSS\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintLphyMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "LMM-->CSS\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintLmmMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case WUEPS_PID_MMC:
        case PS_PID_ERRC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "COMM-->CSS\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintCommMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case VOS_PID_TIMER:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TIMER-->IMSA\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintTimerMsg(pcBuff,
                                            usTotalLen,
                                            ((REL_TIMER_MSG *)(VOS_VOID *)pstMsg)->ulName,
                                            ((REL_TIMER_MSG *)(VOS_VOID *)pstMsg)->ulPara);
            break;

        default:
            CSS_WARN_LOG2("CSS_PrintCssRevMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulSenderPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_WARNING2(CSS_PrintCssRevMsg_ENUM, LNAS_InvalidPid, pstMsg->ulSenderPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        CSS_WARN_LOG2("CSS_PrintCssRevMsg, print return zero length.SenderPid, MsgId: ",
                      pstMsg->ulSenderPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING2(CSS_PrintCssRevMsg_ENUM, LNAS_FUNCTION_LABEL2, pstMsg->ulSenderPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}
VOS_VOID CSS_PrintCssSendMsg
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
                     "CSS SEND Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        CSS_WARN_LOG("CSS_PrintCssSendMsg, Print send msg header exception.");
        TLPS_PRINT2LAYER_WARNING(CSS_PrintCssSendMsg_ENUM, LNAS_FUNCTION_LABEL1);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ����PID����Ϣ */
    switch ( pstMsg->ulReceiverPid )
    {
        case PS_PID_HPA:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "CSS-->LPHY\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintLphyMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "CSS-->LMM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintLmmMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case WUEPS_PID_MMC:
        case PS_PID_ERRC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "CSS-->COMM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintCommMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        default:
            CSS_WARN_LOG2("CSS_PrintCssRevMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulReceiverPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_WARNING2(CSS_PrintCssSendMsg_ENUM, LNAS_InvalidPid, pstMsg->ulReceiverPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        CSS_WARN_LOG2("CSS_PrintCssRevMsg, print return zero length.ReceiverPid, MsgId: ",
                      pstMsg->ulReceiverPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING2(CSS_PrintCssSendMsg_ENUM, LNAS_FUNCTION_LABEL2, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}
VOS_VOID CSS_ClearLocalResource(VOS_VOID)
{

    /* �洢ɨƵ����Ŀռ��ͷ� */
    CSS_FreeCommScanRsltMemory();

    /* ȫ�ֱ�����ʼ�� */
    CSS_MEM_SET(&g_stCssControl, 0, sizeof(CSS_CONTROL_STRU));
}

VOS_VOID CSS_Send_Msg(VOS_VOID* pMsg)
{
    CSS_PrintCssSendMsg((const PS_MSG_HEADER_STRU *)pMsg,CSS_GET_CSS_PRINT_BUF());
    if(VOS_OK != PS_SND_MSG_ALL_CHECK(PS_PID_CSS , pMsg))
    {
        CSS_ERR_LOG("CSS_Send_Msg:Msg Snd Err!");
        TLPS_PRINT2LAYER_ERROR(CSS_Send_Msg_ENUM, LNAS_MsgSndErr);
    }

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



