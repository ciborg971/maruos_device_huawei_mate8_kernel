

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "ImsaProcAtMsg.h"
#include    "ImsaEntity.h"
#include    "ImsaPublic.h"
#include    "ImsaServiceManagement.h"
#include    "ImsaConnManagement.h"
#include    "ImsaImsAdaption.h"
#include    "ImsaProcOmMsg.h"
#include    "omnvinterface.h"
#include    "SysNvId.h"
/*lint -e767*/
#define    THIS_FILE_ID    PS_FILE_ID_IMSAPROCOMMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
#if (FEATURE_ON == FEATURE_PTM)

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/



VOS_VOID IMSA_RcvAcpuOmErrLogCtrlInd
(
    VOS_VOID                           *pMsg
)
{
    OM_ERROR_LOG_CTRL_IND_STRU         *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (OM_ERROR_LOG_CTRL_IND_STRU*)pMsg;

    /* ����ERRLOG���Ʊ�ʶ */
    if ((VOS_FALSE != pstRcvMsg->ucAlmStatus)
     && (VOS_TRUE  != pstRcvMsg->ucAlmStatus))
    {
        return;
    }

    IMSA_SetErrlogCtrlFlag(pstRcvMsg->ucAlmStatus);

    if ((pstRcvMsg->ucAlmLevel >= IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstRcvMsg->ucAlmLevel <= IMSA_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        IMSA_SetErrlogAlmLevel(pstRcvMsg->ucAlmLevel);
    }

    return;
}
VOS_VOID IMSA_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stErrorLogCtrlInfo;

    IMSA_MEM_SET(&stErrorLogCtrlInfo, 0x00, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));

    ulResult = IMSA_NV_Read(en_NV_Item_ErrLogCtrlInfo,
                           &stErrorLogCtrlInfo,
                           sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));

    if (ulResult == VOS_OK)
    {
        IMSA_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        IMSA_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);
    }
    else
    {
        IMSA_SetErrlogCtrlFlag(VOS_FALSE);
        IMSA_SetErrlogAlmLevel(IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL);
        IMSA_ERR_LOG("IMSA_ReadErrlogCtrlInfoNvim:read en_NV_Item_ErrLogCtrlInfo failed");
        TLPS_PRINT2LAYER_ERROR(IMSA_ReadErrlogCtrlInfoNvim_ENUM, LNAS_FAIL);
    }

    return;
}


VOS_VOID IMSA_SndAcpuOmErrLogRptCnf
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
)
{
    IMSA_ERR_LOG_REPORT_CNF_STRU         *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* �ϱ�����Ϣ�ܳ��� */
    ulMsgLen  = (sizeof(IMSA_ERR_LOG_REPORT_CNF_STRU) - 4) + ulBufUseLen;

    /* ��Ϣ�ռ����� */
    pstQryCnf = (IMSA_ERR_LOG_REPORT_CNF_STRU *)IMSA_ALLOC_MSG(ulMsgLen);
    if (VOS_NULL_PTR == pstQryCnf)
    {
        IMSA_ERR_LOG("IMSA_SndAcpuOmErrLogRptCnf: alloc msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndAcpuOmErrLogRptCnf_ENUM, LNAS_NULL_PTR);
        return;
    }

    pstQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstQryCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstQryCnf->ulSenderPid      = PS_PID_IMSA;
    pstQryCnf->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstQryCnf->ulMsgType        = IMSA_ERR_LOG_MSG_ERR_REPORT;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptlen         = ulBufUseLen;

    /* buffer��Ϊ��ʱ��lenҲ�ǲ���Ϊ�յ� */
    if (VOS_NULL_PTR != pbuffer)
    {
        IMSA_MEM_CPY(pstQryCnf->aucContent, pbuffer, ulBufUseLen);
    }

    IMSA_SND_MSG(pstQryCnf);

    return;

}
VOS_VOID IMSA_RcvAcpuOmErrLogRptReq
(
    VOS_VOID                           *pMsg
)
{
    VOS_CHAR                           *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                          ulBufUseLen;
    VOS_UINT32                          ulRealLen;
    VOS_UINT32                          ulTotalLen;
    IMSA_ERR_LOG_MNTN_EVENT_STRU        stNasErrLogMntnEvent;

    /* ��ѯһ��RING BUFFER���ж������ݣ��Ա�����ڴ� */
    ulBufUseLen = IMSA_GetErrLogRingBufferUseBytes();
    ulTotalLen = ulBufUseLen + sizeof(IMSA_ERR_LOG_MNTN_EVENT_STRU);

    pbuffer = (VOS_CHAR *)IMSA_MEM_ALLOC(ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        IMSA_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        return;
    }

    IMSA_MEM_SET(pbuffer, 0, ulTotalLen);

    /* ��ȡRING BUFFER������ */
    ulRealLen = IMSA_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        IMSA_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        IMSA_MEM_FREE(pbuffer);
        return;
    }

    /* �����������������Ϣ׷����RingBuf���� */
    IMSA_WRITE_ERRLOG_HEADER_INFO(&stNasErrLogMntnEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_MNTN,
                                  IMSA_ERR_LOG_CTRL_LEVEL_MAJOR,
                                  VOS_GetSlice(),
                                  (sizeof(IMSA_ERR_LOG_MNTN_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNasErrLogMntnEvent.ulCount = IMSA_GetErrlogOverflowCnt();

    IMSA_MEM_CPY(pbuffer + ulBufUseLen, &stNasErrLogMntnEvent, sizeof(stNasErrLogMntnEvent));

    /* ��ȡ���˺���Ҫ��RINGBUFFER��� */
    IMSA_CleanErrLogRingBuf();

    /* ����������� */
    IMSA_SetErrlogOverflowCnt(0);

    /* ��ά�ɲ�BUF����Ĺ��� */
    /*NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MNTN,
                           UEPS_PID_MTA,
                           (VOS_UINT8 *)&stNasErrLogMntnEvent,
                           sizeof(stNasErrLogMntnEvent));*/

    /* ����ID_OM_ERR_LOG_REPORT_CNF��Ϣ��ACPU OM */
    IMSA_SndAcpuOmErrLogRptCnf(pbuffer, ulTotalLen);

    IMSA_MEM_FREE(pbuffer);

    return;
}

#endif
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcAtMsg.c */





