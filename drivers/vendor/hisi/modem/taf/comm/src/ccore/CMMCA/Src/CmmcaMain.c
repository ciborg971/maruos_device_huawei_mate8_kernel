
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CmmcaMain.h"
#include "CmmcaCtx.h"
#include "CmmcaMeasReselMgmt.h"
#include "CmmcaPktMgmt.h"
#include "CmmcaRegMgmt.h"
#include "CbpaPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_MAIN_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/* ����Cmmc������Cmd�Ҷ�Ӧ�Ĵ����� */
const CMMCA_CBPCA_MSG_PROC_STRU         g_astCmmcaMsgProcCbpcaTab[] =
{
    /* Packet Data */
    {ID_CMMCA_MMC_RAT_PDN_TABLE_SETUP_REQ,                  CMMCA_PKT_RcvCmmcSetPdnTabReq},
    {ID_CMMCA_MMC_RAT_DEFAULT_BEARER_REQ,                   CMMCA_PKT_RcvCmmcDefaultBearConnReq},
    {ID_CMMCA_MMC_RAT_BEARER_DISCONNECT_REQ,                CMMCA_PKT_RcvCmmcBearDiscReq},

    /* reg�����Ϣ������cmmca */
    {ID_CMMCA_MMC_RAT_RAT_MODE_REQ,                         CMMCA_REG_RcvRatModeReq},
    {ID_CMMCA_MMC_RAT_POWERUP_REQ,                          CMMCA_REG_RcvPowerUpReq},
    {ID_CMMCA_MMC_RAT_POWERDOWN_REQ,                        CMMCA_REG_RcvPowerDownReq},
    {ID_CMMCA_MMC_RAT_MCC_SEARCH_REQ,                       CMMCA_REG_RcvMccSearchReq},
    {ID_CMMCA_MMC_RAT_ACQ_REQ,                              CMMCA_REG_RcvRatAcqReq},
    {ID_CMMCA_MMC_RAT_PS_REG_REQ,                           CMMCA_REG_RcvPsRegReq},
    {ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ,                 CMMCA_REG_RcvCellInfoPsRegReq},
    {ID_CMMCA_MMC_RAT_NO_SERVICE_REQ,                       CMMCA_REG_RcvNoServiceReq},
    {ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ,               CMMCA_REG_RcvPktDataCmdReq},
    {ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ,                    CMMCA_REG_RcvBearDetachReq},

    /* ��Ȩ�����Ϣ */
    {ID_CMMCA_MMC_API_SET_PDN_PCO_AUTH_REQ,                 CMMCA_PKT_RcvCmmcSetPdnPcoAuthReq},

    /* Meas and Resel:ֱ��͸����ERRC����MMC */
    {ID_CMMCA_MMC_RAT_IRAT_MEAS_IND,                        CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_IRAT_SYSTEM_CHG_RSP,                  CMMCA_RcvCmmcSystemChgRsp},
    {ID_CMMCA_MMC_RAT_IRAT_SIB8_MEAS_IND,                   CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_RAT_MEAS_CMD,                         CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_RAT_RESELMEAS_CMD,                    CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_STOP_IRAT_RATMEAS_CMD,                CMMCA_RcvCmmcMeasReselReq},

    {ID_CMMCA_MMC_RAT_IRAT_RESELMEAS_IND,                   CMMCA_RcvCmmcMeasReselReq},
    {ID_CMMCA_MMC_RAT_SET_IDLEMODEMOBILITYINFO,             CMMCA_RcvCmmcMeasReselReq},

    /* ͸����MTC */
    {ID_CMMCA_MMC_RAT_OTHER_RAT_INFO_IND,                   CMMCA_RcvCmmcOtherRatInfoInd},
    {ID_CMMCA_MTC_CONN_STATE_INFO_IND,                      CMMCA_RcvCdmaConnStateInfoInd},     /* ���CDMA״̬�ϱ� */

    /* ͸����RCM */
    {ID_CMMCA_RCM_TAS_CDMA_MEASUREMENT_IND,                 CMMCA_RcvCdmaMeasurementInfoInd},   /* ���CDMA�����ϱ� */
    {ID_CMMCA_RCM_TAS_CDMA_EVENT_IND,                       CMMCA_RcvCdmaEventInfoInd}         /* ���CDMA�¼��ϱ� */

};


/* g_astCmmcaMsgProcCbpcaTab��Item���� */
const VOS_UINT32 g_ulCmmcaMsgProcCbpcaTabSize  = sizeof(g_astCmmcaMsgProcCbpcaTab) / sizeof(g_astCmmcaMsgProcCbpcaTab[0]);


/* ����TimerId�Ҷ�Ӧ�Ĵ����� */
const CMMCA_TIMER_MSG_PROC_STRU         g_astCmmcaMsgProcTimerTab[] =
{
    {TI_CMMCA_WAIT_IPV6_RA_INFO,                            CMMCA_PKT_RcvTiWaitIpv6RaExp}
};

/* g_astCmmcaMsgProcTimerTab��Item���� */
const VOS_UINT32 g_ulCmmcaMsgProcTimerTabSize  = sizeof(g_astCmmcaMsgProcTimerTab) / sizeof(g_astCmmcaMsgProcTimerTab[0]);

/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_VOID CMMCA_RcvCbpcaMsg(struct MsgCB *pstMsg)
{
    /* ������Ϣͷָ��*/
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_DATA_STRU        *pstCmdData = VOS_NULL_PTR;
    CMMCA_CBPCA_MSG_PROC_FUNC           pProcMsgFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* ��ȡ��Ϣͷָ��*/
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pstMsg;

    if (CBPCA_CMMCA_DATA_IND != pstDataInd->enMsgType)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCbpcaMsg: not data ind");

        return;
    }

    pstCmdData = (CMMCA_MMC_RAT_CMD_DATA_STRU *)(pstDataInd->aucData);

    /* ���g_astCmmcaMsgProcCbpcaTab��pstCmdData->enCmdId��Ӧ�Ĵ���������������ΪCMMCA_MMC_RAT_CMD_DATA_STRU */
    for (ulIndex = 0; ulIndex < g_ulCmmcaMsgProcCbpcaTabSize; ulIndex++)
    {
        if (g_astCmmcaMsgProcCbpcaTab[ulIndex].ulCmdId == pstCmdData->enCmdId)
        {
            /* Cmd Id ƥ�� */
            pProcMsgFunc = g_astCmmcaMsgProcCbpcaTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        pProcMsgFunc(pstDataInd);
    }
    else
    {
        CMMCA_ERROR_LOG("CMMCA_RcvCbpcaMsg: proc msg func is null");
    }

    return;
}
VOS_VOID CMMCA_RcvTafMsg(struct MsgCB *pstMsg)
{
    /* ������Ϣͷָ��*/
    MSG_HEADER_STRU                     *pstHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pstHeader = (MSG_HEADER_STRU *)pstMsg;

    /* APS��Ϣ */
    if(MN_CALLBACK_PS_CALL == pstHeader->ulMsgName)
    {
        CMMCA_PKT_RcvTafPsEvt((TAF_PS_EVT_STRU*)pstMsg);
    }

    return;
}
VOS_VOID CMMCA_RcvErrcMsg(struct MsgCB *pstMsg)
{
    LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU  *pstIratMeasReq = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16         enCmdIdFromMsgId;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16         enCmdIdInData;
    VOS_UINT32                               ulRslt;

    enCmdIdFromMsgId = ID_CMMCA_RAT_MMC_CMD_MAX;

    /* ERRC�ظ���CMMCA����ϢpstMsg,��ṹ��ΪLRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU */
    pstIratMeasReq         = (LRRC_CMMCA_CDMA_MSG_IRAT_MEAS_REQ_STRU *)pstMsg;

    ulRslt = CMMCA_GetCmdIdFromErrcMsgId(pstIratMeasReq->enMsgId, &enCmdIdFromMsgId);

    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvErrcMsg: Not find Cmd Id ");
        return;
    }

    enCmdIdInData = *((CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16 *)(pstIratMeasReq->aucMsgData));

    /* ������MsgId���������CmdId��Errcʵ�ʴ�����CmdId�Ƿ�һ�� */
    if (enCmdIdFromMsgId != enCmdIdInData)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvErrcMsg: MsgId and CmdId don't match ");
        return;
    }

    /* ����CBPCAģ��ӿڽ����ݷ��͵�CBPCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA,
                                  CMMCA_CBPCA_DATA_REQ,
                                  (VOS_UINT8 *)(pstIratMeasReq->aucMsgData),
                                  pstIratMeasReq->ulLen);

    if (VOS_OK != ulRslt)
    {
        CMMCA_ERROR_LOG("CMMCA_RcvErrcMsg: send Msg to Cbpca fail");
    }

    return;
}
VOS_VOID CMMCA_RcvTimerMsg(struct MsgCB *pstMsg)
{
    /* ������Ϣͷָ��*/
    REL_TIMER_MSG                      *pstTiMsg = VOS_NULL_PTR;
    CMMCA_TIMER_MSG_PROC_FUNC           pProcMsgFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* ��ȡ��Ϣͷָ��*/
    pstTiMsg = (REL_TIMER_MSG *)pstMsg;

    /* ֹͣ��ʱ�� */
    CMMCA_StopTimer(WUEPS_PID_CMMCA, pstTiMsg->ulName);

    /* ���g_astCmmcaMsgProcTimerTab */
    for (ulIndex = 0; ulIndex < g_ulCmmcaMsgProcTimerTabSize; ulIndex++)
    {
        if (g_astCmmcaMsgProcTimerTab[ulIndex].enTimerId == pstTiMsg->ulName)
        {
            /* Timer Id ƥ�� */
            pProcMsgFunc = g_astCmmcaMsgProcTimerTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        pProcMsgFunc(pstTiMsg);
    }
    else
    {
        CMMCA_ERROR_LOG("CMMCA_RcvTimerMsg: proc msg func is null");
    }


    return;
}


VOS_VOID CMMCA_ProcMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pstMsgHeader = (MSG_HEADER_STRU*)pMsg;
    CMMCA_DEBUG_RecordMsgInfo(pMsg->ulSenderPid, pstMsgHeader->ulMsgName);

    switch (pMsg->ulSenderPid)
    {
        case WUEPS_PID_CBPCA:
            CMMCA_RcvCbpcaMsg(pMsg);
            break;

        case WUEPS_PID_TAF:
            CMMCA_RcvTafMsg(pMsg);
            break;

        case PS_PID_ERRC:
            CMMCA_RcvErrcMsg(pMsg);
            break;

        case VOS_PID_TIMER:
            CMMCA_RcvTimerMsg(pMsg);
            break;

        case WUEPS_PID_MMA:
            CMMCA_REG_RcvMmaMsg(pMsg);
            break;
        default:
            CMMCA_WARNING_LOG("CMMCA_PidMsgProc: Abnormal PID.");
            break;

    }

    return;
}

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif





