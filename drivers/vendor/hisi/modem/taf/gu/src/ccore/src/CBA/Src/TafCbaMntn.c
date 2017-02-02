

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaMntn.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_MNTN_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/




VOS_VOID TAF_CBA_SndOmLogInfo(
    TAF_CBA_OM_LOG_ID_ENUM_UINT32       enLogId
)
{
    TAF_CBA_MNTN_INFO_STRU              stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(stMsg));

    /* ��Ϣ��װ */
    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = WUEPS_PID_TAF;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverPid       = WUEPS_PID_TAF;
    stMsg.ulLength            = sizeof(stMsg) - VOS_MSG_HEAD_LENGTH;

    stMsg.enMsgId             = TAF_CBA_OM_MSG_LOG_INFO;

    stMsg.u.stLogInfo.enLogId = enLogId;

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(&stMsg);
}



VOS_VOID TAF_CBA_SndOmDeledRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enType,
    TAF_CBA_OM_DEL_REASON_ENUM_UINT8    enDelReason,
    TAF_CBA_RECORD_STRU                *pstDelRecord
)
{
    TAF_CBA_MNTN_INFO_STRU              stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(stMsg));

    /* ��Ϣ��װ */
    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = WUEPS_PID_TAF;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverPid       = WUEPS_PID_TAF;
    stMsg.ulLength            = sizeof(stMsg) - VOS_MSG_HEAD_LENGTH;

    stMsg.enMsgId             = enType;

    /* ������Ϣ */
    stMsg.u.stDelRecordInfo.enDelReason      = enDelReason;
    stMsg.u.stDelRecordInfo.usMsgID          = pstDelRecord->usMsgID;
    stMsg.u.stDelRecordInfo.usSN             = pstDelRecord->usSN;
    stMsg.u.stDelRecordInfo.ulDupDetcTimeLen = pstDelRecord->ulDupDetcTimeLen;
    stMsg.u.stDelRecordInfo.ulRcvTimeTick    = pstDelRecord->ulRcvTimeTick;
    stMsg.u.stDelRecordInfo.ulCurrTick       = VOS_GetTick();

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(&stMsg);
}
VOS_VOID TAF_CBS_SndOmSavedRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enMsgType,
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType,
    TAF_CBA_RECORD_STRU                *pstNewRecord,
    VOS_UINT16                          usRecordNum
)
{
    TAF_CBA_MNTN_INFO_STRU              stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(stMsg));

    /* ��Ϣ��װ */
    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = WUEPS_PID_TAF;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverPid       = WUEPS_PID_TAF;
    stMsg.ulLength            = sizeof(stMsg) - VOS_MSG_HEAD_LENGTH;

    stMsg.enMsgId             = enMsgType;

    stMsg.u.stSaveRecordInfo.enSaveType       = enSaveType;
    stMsg.u.stSaveRecordInfo.usRecordNum      = usRecordNum;
    stMsg.u.stSaveRecordInfo.ulDupDetcTimeLen = pstNewRecord->ulDupDetcTimeLen;

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(&stMsg);
}



VOS_VOID TAF_CBA_SndOmDupRecordInfo(
    TAF_CBA_OM_MSG_ID_ENUM_UINT32       enMsgType,
    TAF_CBA_RECORD_STRU                *pstOldRecord
)
{
    TAF_CBA_MNTN_INFO_STRU              stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(stMsg));

    /* ��Ϣ��װ */
    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = WUEPS_PID_TAF;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulReceiverPid       = WUEPS_PID_TAF;
    stMsg.ulLength            = sizeof(stMsg) - VOS_MSG_HEAD_LENGTH;

    stMsg.enMsgId             = enMsgType;

    stMsg.u.stDupRecordInfo.usPageBitmap = pstOldRecord->usPageBitmap;
    stMsg.u.stDupRecordInfo.usMsgID      = pstOldRecord->usMsgID;
    stMsg.u.stDupRecordInfo.usSN         = pstOldRecord->usSN;

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(&stMsg);
}


VOS_VOID TAF_CBA_SndOmCbmiDownloadListInfo(VOS_VOID)
{
    TAF_CBA_MNTN_INFO_STRU             *pstMsg;
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU    *pstCbmidList;
    VOS_UINT32                          ulCbmidInx;

    pstMsg = (TAF_CBA_MNTN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_MNTN_INFO_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndOmCbmiDownloadListInfo: MEM ALLOC ERROR");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_CBA_MNTN_INFO_STRU));

    /* ��Ϣ��װ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_CBA_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = TAF_CBA_OM_MSG_CBMI_DOWNLOAD_LIST;

    /* ������ϢID�б� */
    pstCbmidList = TAF_CBA_GetCbmiDownloadList();

    pstMsg->u.stCbmiDownloadList.usCbmidNum = pstCbmidList->usCbmidNum;

    for ( ulCbmidInx = 0; ulCbmidInx < pstCbmidList->usCbmidNum; ulCbmidInx++ )
    {
        pstMsg->u.stCbmiDownloadList.ausMsgId[ulCbmidInx] = pstCbmidList->ausMsgId[ulCbmidInx];
    }

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
}
VOS_VOID TAF_CBA_SndOmCbmiRangeList(VOS_VOID)
{
    TAF_CBA_MNTN_INFO_STRU             *pstMsg;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmirList;
    VOS_UINT32                          ulCbmirInx;

    pstMsg = (TAF_CBA_MNTN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CBA_MNTN_INFO_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndOmCbmiRangeList: MEM ALLOC ERROR");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_CBA_MNTN_INFO_STRU));

    /* ��Ϣ��װ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = sizeof(TAF_CBA_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = TAF_CBA_OM_MSG_CBMI_RANGE_LIST;

    /* ������ϢID�б� */
    pstCbmirList = TAF_CBA_GetCbMiRangeList();

    for ( ulCbmirInx = 0; ulCbmirInx < pstCbmirList->usCbmirNum; ulCbmirInx++ )
    {
        if (TAF_CBA_CBMI_RANGE_RCV_MODE_ACCEPT != pstCbmirList->astCbmiRangeInfo[ulCbmirInx].enRcvMode)
        {
            continue;
        }

        pstMsg->u.stCbmiRangeList.astCbmiRange[ulCbmirInx].usMsgIdFrom =
                                    pstCbmirList->astCbmiRangeInfo[ulCbmirInx].usMsgIdFrom;

        pstMsg->u.stCbmiRangeList.astCbmiRange[ulCbmirInx].usMsgIdTo =
                                    pstCbmirList->astCbmiRangeInfo[ulCbmirInx].usMsgIdTo;

        (pstMsg->u.stCbmiRangeList.usCbmirNum)++;
    }

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstMsg);
}
VOS_VOID TAF_CBA_SndOmNvimInfo(VOS_VOID)
{
    VOS_UINT8                          *pucMsgBuf = VOS_NULL_PTR;
    TAF_CBA_MNTN_INFO_STRU             *pstMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulBufLen;

    ulBufLen = TAF_CBA_MNTN_INFO_HEADER_LEN + sizeof(TAF_CBA_LOG_NVIM_INFO_STRU);

    pucMsgBuf = PS_MEM_ALLOC(WUEPS_PID_TAF, ulBufLen);
    if ( VOS_NULL_PTR == pucMsgBuf )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_SndOmNvimInfo: MEM ALLOC ERROR");
        return;
    }

    PS_MEM_SET(pucMsgBuf, 0x00, ulBufLen);

    pstMsg = (TAF_CBA_MNTN_INFO_STRU*)pucMsgBuf;

    /* ��Ϣ��װ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_TAF;
    pstMsg->ulLength        = ulBufLen - VOS_MSG_HEAD_LENGTH;

    pstMsg->enMsgId         = TAF_CBA_OM_MSG_NVIM_INFO;

    /* ���CBS����״̬���NVֵ */
    pstMsg->u.stCbsNvimInfo.stCbsServiceParam.ucCbStatus     = TAF_CBA_GetCbsStatus();
    pstMsg->u.stCbsNvimInfo.stCbsServiceParam.ucDupDetectCfg = TAF_CBA_GetDupDetectCfg();


    pstMsg->u.stCbsNvimInfo.stCbsServiceParam.ucRptAppFullPageFlg = TAF_CBA_GetRptAppFullPageFlg();

#if (FEATURE_ETWS == FEATURE_ON)
    /* ���ETWS���NVֵ */
    PS_MEM_CPY(&(pstMsg->u.stCbsNvimInfo.stEtwsMsCfg),
               TAF_CBA_GetMsCfgEtwsInfo(),
               sizeof(TAF_CBA_MS_CFG_ETWS_INFO_STRU));
#endif

    /* ������ά�ɲ���Ϣ */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pucMsgBuf);
}

/*lint -restore */


#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
