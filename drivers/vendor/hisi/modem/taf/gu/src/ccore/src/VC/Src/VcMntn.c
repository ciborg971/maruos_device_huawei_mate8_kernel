

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "VcCtx.h"
#include "VcMntn.h"
#include "NasComm.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_VC_MNTN_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/


/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID VC_MNTN_TraceEvent(VOS_VOID *pMsg)
{

    DIAG_TraceReport(pMsg);

    return;
}


VOS_VOID VC_MNTN_TraceCtxInfo(VOS_VOID)
{
    VC_MNTN_STATE_MGMT_STRU             stMntnStateMgmt;
    APP_VC_STATE_MGMT_STRU             *pstStateMgmt;

    pstStateMgmt = APP_VC_GetVcStateMgmtAddr();

    /* ��д��Ϣͷ */
    VC_MNTN_CFG_MSG_HDR(&stMntnStateMgmt, ID_VC_MNTN_HOOK_MSG_STATE_MGMT, (sizeof(VC_MNTN_STATE_MGMT_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    PS_MEM_CPY(&stMntnStateMgmt.stVcCtxInfo.stVcEcallCtx, &pstStateMgmt->stEcallCtx, sizeof(VC_MNTN_ECALL_CTX_STRU));

    stMntnStateMgmt.stVcCtxInfo.ulInCall        = pstStateMgmt->bInCall;
    stMntnStateMgmt.stVcCtxInfo.ulVoiceTestFlag = pstStateMgmt->ulVoiceTestFlag;

    /* ������Ϣ */
    VC_MNTN_TraceEvent(&stMntnStateMgmt);

    return;
}

/* ��VcMain.c�ƹ����� */

VOS_VOID NAS_MNTN_FailtoOpenCsChannel(
    VOS_UINT16                          usPort,
    VOS_UINT32                          ulOmOperResult
)
{
    VOS_UINT32                                      ulRet;
    NAS_MNTN_CS_CHANNEL_OPEN_FAILURE_EVENT_STRU     stChannelOpenFailure;

    /* 1����OM������ͨ����ʧ���¼���� */
    /* 1��1����ʼ����־�¼��ֲ����� */
    PS_MEM_SET(&stChannelOpenFailure, 0x00, sizeof(stChannelOpenFailure));

    /* 1��2����ȡNAS���ĵ�SIM����Ϣ�� */
    NAS_MMA_OutputUsimInfo(&stChannelOpenFailure.stUsimInfo);

    /* 1��3����¼Ҫ�򿪵�����ͨ���˿ں�OMִ�н���� */
    stChannelOpenFailure.usPort         = usPort;
    stChannelOpenFailure.ulOmOperResult = ulOmOperResult;

    /* 2�������OM������ͨ����ʧ���¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_VC,MNTN_NAS_ERRORLOG_CS_CHANNEL_OPEN_FAILURE),
                                &stChannelOpenFailure,
                                sizeof(stChannelOpenFailure));
    if (VOS_OK != ulRet)
    {
        VC_WARN_LOG("NAS_MNTN_FailtoOpenCsChannel: MNTN_RecordErrorLog fail.");
        (VOS_VOID)vos_printf("NAS_MNTN_FailtoOpenCsChannel: MNTN_RecordErrorLog fail.\n");
    }

    return;
}
VOS_VOID NAS_MNTN_CsMedTimeOut(VOS_UINT32                          ulTimerId)
{
    VOS_UINT32                          ulRet;
    NAS_MNTN_CS_MED_TIMEOUT_EVENT_STRU  stCsMedTimeOut;

    /* ���˲����ĵĶ�ʱ����ʱ�¼�������ʱ����ʱ�¼�����Ϊ APP_VC_TIMER_START��
    APP_VC_TIMER_SET_DEV��APP_VC_TIMER_SET_CODEC��APP_VC_TIMER_STOP��
    ����ERROR LOG�ӿ��������־ */
    if ((APP_VC_TIMER_START     != ulTimerId)
     && (APP_VC_TIMER_SET_DEV   != ulTimerId)
     && (APP_VC_TIMER_SET_CODEC != ulTimerId)
     && (APP_VC_TIMER_STOP      != ulTimerId))
    {
        return;
    }

    /* 1��MED���ֳ�ʱ�¼���� */
    /* 1��1����ʼ����־�¼��ֲ����� */
    PS_MEM_SET(&stCsMedTimeOut, 0x00, sizeof(stCsMedTimeOut));

    /* 1��2����ȡNAS���ĵ�SIM����Ϣ�� */
    NAS_MMA_OutputUsimInfo(&stCsMedTimeOut.stUsimInfo);

    /* 1��3����¼��ʱ����ʱ�¼��� */
    stCsMedTimeOut.ulTimerId = ulTimerId;

    /* 2�������OM������ͨ����ʧ���¼���Ϣ */
    ulRet = MNTN_RecordErrorLog(NAS_EVT_TYPE_DEF(WUEPS_PID_VC,MNTN_NAS_ERRORLOG_CS_MED_TIMEOUT),
                                &stCsMedTimeOut,
                                sizeof(stCsMedTimeOut));
    if (VOS_OK != ulRet)
    {
        VC_WARN_LOG("NAS_MNTN_CsMedTimeOut: MNTN_RecordErrorLog fail.");
        (VOS_VOID)vos_printf("NAS_MNTN_CsMedTimeOut: MNTN_RecordErrorLog fail.\n");
    }
    return;
}
#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID VC_MNTN_ShowAlAckInfo(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VC_AL_ACK_REPORT_INFO_STRU         *pstAlAckInfo = VOS_NULL_PTR;

    pstAlAckInfo = APP_VC_GetAlAckInfoAddr();

    (VOS_VOID)vos_printf("AlAck Info:\r\n");
    for (ulIndex = 0; ulIndex < VC_MAX_AL_ACK_NUM; ulIndex++)
    {
        (VOS_VOID)vos_printf("ALACK[%d]: TimeStamp[0x%x], Value[%d]\r\n", ulIndex,
                                pstAlAckInfo->astAlAckInfo[ulIndex].ulTimeStamp,
                                pstAlAckInfo->astAlAckInfo[ulIndex].ucAlAckValue);
    }

}

#endif


/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




