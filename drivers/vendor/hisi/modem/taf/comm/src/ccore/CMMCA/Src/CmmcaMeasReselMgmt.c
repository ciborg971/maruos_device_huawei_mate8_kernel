
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CmmcaCtx.h"
#include "CmmcaMeasReselMgmt.h"

#include "CbpaPsInterface.h"

#include "CmmcaRcmInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_MEAS_RESEL_MGMT_C

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* ά��CMDID��MSGID(ERRC->CMMCA)֮���ӳ��� */
const CMMCA_CMDID_ERRC_MSGID_MAP_STRU   g_astCmmcaCmdIdToErrcMsgIdMapTbl[] =
{
    {ID_CMMCA_MMC_RAT_IRAT_MEAS_IND,                 CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND},
    {ID_CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP,           CMMCA_LRRC_CDMA_MSG_IRAT_SYSTEM_CHG_RSP},
    {ID_CMMCA_MMC_RAT_IRAT_SIB8_MEAS_IND,            CMMCA_LRRC_CDMA_MSG_IRAT_SIB8_MEAS_IND},
    {ID_CMMCA_MMC_RAT_RAT_MEAS_CMD,                  CMMCA_LRRC_CDMA_MSG_IRAT_SET_PRIINFO_REQ},
    {ID_CMMCA_MMC_RAT_RAT_RESELMEAS_CMD,             CMMCA_LRRC_CDMA_MSG_IRAT_LTEMEAS_REQ},
    {ID_CMMCA_MMC_RAT_STOP_IRAT_RATMEAS_CMD,         CMMCA_LRRC_CDMA_MSG_STOP_IRAT_RATMEAS_REQ},

    {ID_CMMCA_RAT_MMC_IRAT_MEAS_CMD,                 LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ},
    {ID_CMMCA_RAT_MMC_IRAT_SYSTEM_CHG_REQ,           LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_REQ},
    {ID_CMMCA_RAT_MMC_IRAT_SIB8_MEAS_CMD,            LRRC_CMMCA_CDMA_MSG_IRAT_SIB8_MEAS_IND},
    {ID_CMMCA_RAT_MMC_RAT_MEAS_IND,                  LRRC_CMMCA_CDMA_MSG_IRAT_SET_PRIINFO_REQ},
    {ID_CMMCA_RAT_MMC_RAT_RESELMEAS_IND,             LRRC_CMMCA_CDMA_MSG_IRAT_RATMEAS_IND},
    {ID_CMMCA_RAT_MMC_STOP_IRAT_MEAS_CMD,            LRRC_CMMCA_CDMA_MSG_STOP_IRAT_MEAS_REQ},
    {ID_CMMCA_RAT_MMC_SYSTEM_CHG_ABORT_REQ,          LRRC_CMMCA_CDMA_MSG_IRAT_SYSTEM_CHG_ABORT_CMD}

};

/* g_astCmmcaCmdIdToErrcMsgIdMapTbl��Item���� */
const VOS_UINT32 g_ulCmmcaCmdIdToErrcMsgIdMapTblSize  = sizeof(g_astCmmcaCmdIdToErrcMsgIdMapTbl) / sizeof(g_astCmmcaCmdIdToErrcMsgIdMapTbl[0]);

/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_VOID CMMCA_SndMmcResumeInd(
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd
)
{
    CMMCA_MMC_RESUME_IND_STRU              *pstResumeInd = VOS_NULL_PTR;
    VOS_UINT32                              ulMsgLen;

    ulMsgLen = sizeof(CMMCA_MMC_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstResumeInd = (CMMCA_MMC_RESUME_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, ulMsgLen);
    if (VOS_NULL_PTR == pstResumeInd)
    {
        CMMCA_ERROR_LOG("CMMCA_SndMmcResumeInd: Alloc msg fail!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstResumeInd + VOS_MSG_HEAD_LENGTH,0,
                             sizeof(CMMCA_MMC_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ������Ϣ��Mmc */
    pstResumeInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstResumeInd->ulReceiverPid   = WUEPS_PID_MMC;
    pstResumeInd->enMsgId         = ID_CMMCA_MMC_RESUME_IND;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstResumeInd))
    {
        CMMCA_ERROR_LOG("CMMCA_SndMmcResumeInd: Send msg to mmc fail!");
    }

    return;
}
VOS_VOID CMMCA_RcvCmmcMeasReselReq(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_DATA_STRU            *pstCmdData = VOS_NULL_PTR;
    CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU *pstLrrcMsgInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16        enCmdId;
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32         enMsgId;
    VOS_UINT32                              ulMsgLen;
    VOS_UINT8                               ucIndex;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* �����������е�CmdId */
    pstCmdData = (CMMCA_MMC_RAT_CMD_DATA_STRU *)(pstDataInd->aucData);
    enCmdId    = *((CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16 *)pstCmdData);

    enMsgId = LRRC_CMMCA_MSG_TYPE_BUTT;
    /* ���ݽ��������е�CmdId�����g_astCmmcaCmdIdToErrcMsgIdMapTbl��ƥ����Ӧ��MsgId */
    for (ucIndex = 0; ucIndex < g_ulCmmcaCmdIdToErrcMsgIdMapTblSize; ucIndex++)
    {
        if (g_astCmmcaCmdIdToErrcMsgIdMapTbl[ucIndex].enCmdId == enCmdId)
        {
            enMsgId = g_astCmmcaCmdIdToErrcMsgIdMapTbl[ucIndex].enMsgId;
            break;
        }
    }

    if (ucIndex >= g_ulCmmcaCmdIdToErrcMsgIdMapTblSize)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcMeasReselReq: Find CmdId fail!");
        return;
    }

    /* ���췢�͸�Errc����Ϣ�ṹ */
    ulMsgLen = sizeof(CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU) - CMMCA_MSG_DATA_RSV_LEN + pstDataInd->ulDataLen - VOS_MSG_HEAD_LENGTH;

    pstLrrcMsgInd = (CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, ulMsgLen);

    if (VOS_NULL_PTR == pstLrrcMsgInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcMeasReselReq: Alloc msg fail!");
        return;
    }

    /* ������Ϣ��LRRC */
    pstLrrcMsgInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLrrcMsgInd->ulReceiverPid   = PS_PID_ERRC;
    pstLrrcMsgInd->enMsgId         = enMsgId;
    pstLrrcMsgInd->ulLen           = pstDataInd->ulDataLen;
    VOS_MemCpy(pstLrrcMsgInd->aucMsgData, pstDataInd->aucData, pstLrrcMsgInd->ulLen);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstLrrcMsgInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcMeasReselReq: Send msg to Lrrc fail!");
        return;
    }

    return;
}


VOS_VOID CMMCA_RcvCmmcSystemChgRsp(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd = VOS_NULL_PTR;
    CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU *pstLrrcMsgInd = VOS_NULL_PTR;
    VOS_UINT32                              ulMsgLen;
    VOS_UINT32                              ulRslt;
    CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP_STRU  stSystemChgInd;


    VOS_MemSet(&stSystemChgInd, 0, sizeof(CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP_STRU));
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* ���췢�͸�Errc����Ϣ�ṹ */
    ulMsgLen = sizeof(CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU) - CMMCA_MSG_DATA_RSV_LEN + pstDataInd->ulDataLen - VOS_MSG_HEAD_LENGTH;

    pstLrrcMsgInd = (CMMCA_LRRC_CDMA_MSG_IRAT_MEAS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, ulMsgLen);

    if (VOS_NULL_PTR == pstLrrcMsgInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcSystemChgRsp: Alloc msg fail!");
        return;
    }

    /* ������Ϣ��LRRC */
    pstLrrcMsgInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLrrcMsgInd->ulReceiverPid   = PS_PID_ERRC;
    pstLrrcMsgInd->enMsgId         = CMMCA_LRRC_CDMA_MSG_IRAT_SYSTEM_CHG_RSP;
    pstLrrcMsgInd->ulLen           = pstDataInd->ulDataLen;
    VOS_MemCpy(pstLrrcMsgInd->aucMsgData, pstDataInd->aucData, pstLrrcMsgInd->ulLen);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstLrrcMsgInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcSystemChgRsp: Send msg to Lrrc fail!");
        return;
    }

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ */
    ulRslt = CMMCA_ParseSystemChangeRsp((VOS_UINT16)(pstDataInd->ulDataLen),
                                        pstDataInd->aucData,
                                        &stSystemChgInd);

    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcSystemChgRsp: Parse System change rsp fail!");
        return;
    }

    /* ���system change�ظ��ɹ���Ϣ��������Mmc */
    if  ((CMMCA_IRAT_SYSTEM_CHG_SUCCESS      == stSystemChgInd.enResult)
       ||(CMMCA_IRAT_SYSTEM_CHG_HRPD_SUCCESS == stSystemChgInd.enResult))
    {
        /* ����Modem��״̬ΪINACTIVE */
        CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);

        CMMCA_SndMmcResumeInd(pstDataInd);
    }

    return;
}
VOS_UINT32 CMMCA_GetCmdIdFromErrcMsgId(
    LRRC_CMMCA_MSG_TYPE_ENUM_UINT32     enMsgId,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16   *penCmdId
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < g_ulCmmcaCmdIdToErrcMsgIdMapTblSize; ucIndex++)
    {
        if (g_astCmmcaCmdIdToErrcMsgIdMapTbl[ucIndex].enMsgId == enMsgId)
        {
            *penCmdId = g_astCmmcaCmdIdToErrcMsgIdMapTbl[ucIndex].enCmdId;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}


VOS_VOID CMMCA_RcvCmmcOtherRatInfoInd(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd = VOS_NULL_PTR;
    CMMCA_MTC_OTHER_RAT_INFO_IND_STRU  *pstOtherRatInfoInd = VOS_NULL_PTR;
    CMMCA_OTHER_RAT_INFO_IND_STRU       stOtherRatInfoInd;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulMsgLen;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stOtherRatInfoInd, 0, sizeof(CMMCA_OTHER_RAT_INFO_IND_STRU));

    /* ����CMMCA_ParseOtherRatInfoInd�����Բ������н��� */
    ulRslt = CMMCA_ParseOtherRatInfoInd((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stOtherRatInfoInd);

    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcOtherRatInfoReq: Parse Other Rat Info fail!");
        return;
    }

    /* ���췢�͸�MTC����Ϣ�ṹ */
    ulMsgLen = sizeof(CMMCA_MTC_OTHER_RAT_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstOtherRatInfoInd = (CMMCA_MTC_OTHER_RAT_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, ulMsgLen);

    if (VOS_NULL_PTR == pstOtherRatInfoInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcOtherRatInfoReq: Alloc msg fail!");
        return;
    }

    /* ������Ϣ��MTC */
    pstOtherRatInfoInd->ulReceiverPid = UEPS_PID_MTC;
    pstOtherRatInfoInd->enMsgId = ID_CMMCA_MTC_OTHER_RAT_INFO_IND;
    PS_MEM_CPY(&(pstOtherRatInfoInd->stOtherRatInfo), &stOtherRatInfoInd, sizeof(CMMCA_OTHER_RAT_INFO_IND_STRU));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstOtherRatInfoInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCmmcOtherRatInfoReq: Send msg to mtc fail!");
    }

    return;
}
VOS_VOID CMMCA_RcvCdmaConnStateInfoInd(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd          = VOS_NULL_PTR;
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_CDMA_STATE_INFO_STRU        stTafCdmaState;
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucOpid;

    /* ��ʼ�� */
    PS_MEM_SET(&stTafCdmaState, 0x0, sizeof(stTafCdmaState));
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd      = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* ����������ת�� */
    ulRst = CMMCA_ParseStateInfo((VOS_UINT16)(pstDataInd->ulDataLen),
                                 pstDataInd->aucData,
                                 &stTafCdmaState);
    if (VOS_OK != ulRst)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaConnStateInfoInd: Parse Fail!");
        return;
    }

    /* ����OPID */
    ucOpid = 0x0;
    CMMCA_AssignOpid(&ucOpid);

    /* ��д��Ϣ���Ʋ��� */
    TAF_API_CTRL_HEADER(&stCtrl, WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpid);

    /* ����MTC��Ϣ���ͽӿ� */
    ulRst = MTC_SetCdmaServiceConnStateInfo(&stCtrl, &stTafCdmaState);
    if (VOS_OK != ulRst)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaConnStateInfoInd: Send msg to mtc fail!");
    }

    return;
}


VOS_VOID CMMCA_RcvCdmaMeasurementInfoInd(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd              = VOS_NULL_PTR;
    CMMCA_RCM_MEASUREMENT_INFO_IND_STRU    *pstMeasurementInfoInd   = VOS_NULL_PTR;
    VOS_UINT8                              *pucTmpPtr               = VOS_NULL_PTR;
    CMMCA_RCM_MEASUREMENT_INFO_STRU         stMeasureMentInfo;
    VOS_UINT32                              ulRslt;

    /* ��ʼ�� */
    PS_MEM_SET(&stMeasureMentInfo, 0x0, sizeof(stMeasureMentInfo));
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* �������� */
    ulRslt = CMMCA_ParseMeasurementInfo((VOS_UINT16)(pstDataInd->ulDataLen),
                                        pstDataInd->aucData,
                                        &stMeasureMentInfo);
    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaMeasurementInfoInd: Parse Fail!");
        return;
    }

    /* ���췢�͸�RCM����Ϣ�ṹ */
    pstMeasurementInfoInd = (CMMCA_RCM_MEASUREMENT_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, sizeof(CMMCA_RCM_MEASUREMENT_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMeasurementInfoInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaMeasurementInfoInd: Alloc msg fail!");
        return;
    }

    /* ������Ϣ��RCM */
    pstMeasurementInfoInd->ulReceiverPid = DSP_PID_RCM;
    pstMeasurementInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMeasurementInfoInd->enMsgId = ID_CMMCA_RCM_TAS_MEASUREMENT_IND;
    pucTmpPtr = (VOS_UINT8 *)((VOS_UINT32)(&pstMeasurementInfoInd->stMeasurementInfo));
    PS_MEM_CPY(pucTmpPtr, &stMeasureMentInfo, sizeof(CMMCA_RCM_MEASUREMENT_INFO_STRU));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstMeasurementInfoInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaMeasurementInfoInd: Send msg to mtc fail!");
    }

    return;
}


VOS_VOID CMMCA_RcvCdmaEventInfoInd(VOS_VOID *pMsg)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd        = VOS_NULL_PTR;
    CDMA_TAS_EVENT_DATA_INFO_IND_STRU      *pstEventInfoInd   = VOS_NULL_PTR;
    VOS_UINT8                              *pucTmpPtr         = VOS_NULL_PTR;
    CDMA_TAS_EVENT_INFO_STRU                stEventInfo;
    VOS_UINT32                              ulRslt;

    /* ��ʼ�� */
    PS_MEM_SET(&stEventInfo, 0x0, sizeof(stEventInfo));
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* �������� */
    ulRslt = CMMCA_ParseEventInfo((VOS_UINT16)(pstDataInd->ulDataLen),
                                  pstDataInd->aucData,
                                  &stEventInfo);
    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaEventInfoInd: Parse Fail!");
        return;
    }

    /* ���췢�͸�RCM����Ϣ�ṹ */
    pstEventInfoInd = (CDMA_TAS_EVENT_DATA_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_CMMCA, sizeof(CDMA_TAS_EVENT_DATA_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstEventInfoInd)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaEventInfoInd: Alloc msg fail!");
        return;
    }

    /* ������Ϣ��RCM */
    pstEventInfoInd->ulReceiverPid = DSP_PID_RCM;
    pstEventInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstEventInfoInd->enMsgId = ID_CMMCA_RCM_TAS_EVENT_IND;
    pucTmpPtr = (VOS_UINT8 *)((VOS_UINT32)(&pstEventInfoInd->stCdmaEventData));
    PS_MEM_CPY(pucTmpPtr, &stEventInfo, sizeof(stEventInfo));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CMMCA, pstEventInfoInd))
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCdmaEventInfoInd: Send msg to mtc fail!");
    }

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif





