
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcIntrusion.h"
#include "MtcDebug.h"

#include "MtcComm.h"

#include "UsimPsInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_MTC_INTRUSION_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* ���ſ��Ʋ��Բ�ѯ�� */
const MTC_INTRUSION_RULING_STRATEGY_STRU g_astMtcIntrusionRulingStrategyTbl[] =
{
    {MTC_INTRUSION_GSM_BAND_NONE,       MTC_INTRUSION_TL_BAND_NONE,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB3B39},

    {MTC_INTRUSION_GSM_BAND_B31,        MTC_INTRUSION_TL_BAND_NONE,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB39},

    {MTC_INTRUSION_GSM_BAND_B31_OTHER,  MTC_INTRUSION_TL_BAND_NONE,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB39},

    {MTC_INTRUSION_GSM_BAND_B32_OTHER,  MTC_INTRUSION_TL_BAND_NONE,
     MTC_CS_NO_SERVICE,                 MTC_IntrusionEnableB39},

    {MTC_INTRUSION_GSM_BAND_B3_OTHER,   MTC_INTRUSION_TL_BAND_NONE,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB39},

    {MTC_INTRUSION_GSM_BAND_OTHER,      MTC_INTRUSION_TL_BAND_NONE,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB3B39},

    {MTC_INTRUSION_GSM_BAND_NONE,       MTC_INTRUSION_TL_BAND_WITH_B39,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB3},

    {MTC_INTRUSION_GSM_BAND_B32,        MTC_INTRUSION_TL_BAND_WITH_B39,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionDisableB39},

    {MTC_INTRUSION_GSM_BAND_B3,         MTC_INTRUSION_TL_BAND_WITH_B39,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionDisableB39},

    {MTC_INTRUSION_GSM_BAND_B32_OTHER,  MTC_INTRUSION_TL_BAND_WITH_B39,
     MTC_CS_IN_SERVICE,                 MTC_IntrusionDisableB39},

    {MTC_INTRUSION_GSM_BAND_B32_OTHER,  MTC_INTRUSION_TL_BAND_WITH_B39,
     MTC_CS_NO_SERVICE,                 MTC_IntrusionDisableB3},

    {MTC_INTRUSION_GSM_BAND_B3_OTHER,   MTC_INTRUSION_TL_BAND_WITH_B39,
     MTC_CS_IN_SERVICE,                 MTC_IntrusionDisableB39},

    {MTC_INTRUSION_GSM_BAND_B3_OTHER,   MTC_INTRUSION_TL_BAND_WITH_B39,
     MTC_CS_NO_SERVICE,                 MTC_IntrusionDisableB3},

    {MTC_INTRUSION_GSM_BAND_NONE,       MTC_INTRUSION_TL_BAND_WITHOUT_B39,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB3B39},

    {MTC_INTRUSION_GSM_BAND_B31,        MTC_INTRUSION_TL_BAND_WITHOUT_B39,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB39},

    {MTC_INTRUSION_GSM_BAND_B31_OTHER,  MTC_INTRUSION_TL_BAND_WITHOUT_B39,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB39},

    {MTC_INTRUSION_GSM_BAND_B32_OTHER,  MTC_INTRUSION_TL_BAND_WITHOUT_B39,
     MTC_CS_NO_SERVICE,                 MTC_IntrusionEnableB39},

    {MTC_INTRUSION_GSM_BAND_B3_OTHER,   MTC_INTRUSION_TL_BAND_WITHOUT_B39,
     MTC_CS_NO_SERVICE,                 MTC_IntrusionEnableB39},

    {MTC_INTRUSION_GSM_BAND_OTHER,      MTC_INTRUSION_TL_BAND_WITHOUT_B39,
     MTC_CS_SERVICE_STATE_BUTT,         MTC_IntrusionEnableB3B39},
};

/* ����GSM��Ƶ����Ϣ����ѯ��Ӧ��Ƶ��״̬ */
const MTC_INTRUSION_GSM_BAND_STATE_STRU g_stMtcIntrusionGsmBandStateTbl[] =
{
    {VOS_FALSE, VOS_FALSE, VOS_FALSE, MTC_INTRUSION_GSM_BAND_NONE},
    {VOS_TRUE,  VOS_FALSE, VOS_FALSE, MTC_INTRUSION_GSM_BAND_B31},
    {VOS_FALSE, VOS_TRUE,  VOS_FALSE, MTC_INTRUSION_GSM_BAND_B32},
    {VOS_FALSE, VOS_FALSE, VOS_TRUE,  MTC_INTRUSION_GSM_BAND_OTHER},
    {VOS_TRUE,  VOS_TRUE,  VOS_FALSE, MTC_INTRUSION_GSM_BAND_B3},
    {VOS_TRUE,  VOS_FALSE, VOS_TRUE,  MTC_INTRUSION_GSM_BAND_B31_OTHER},
    {VOS_FALSE, VOS_TRUE,  VOS_TRUE,  MTC_INTRUSION_GSM_BAND_B32_OTHER},
    {VOS_TRUE,  VOS_TRUE,  VOS_TRUE,  MTC_INTRUSION_GSM_BAND_B3_OTHER},
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID MTC_SndRrcIntrusionActionSetReq(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
)
{
    VOS_UINT16                          ulLenth;
    MTC_RRC_INTRUSION_ACTION_SET_REQ_STRU   *pstMtcRrcActionReq = VOS_NULL_PTR;

    ulLenth             = sizeof(MTC_RRC_INTRUSION_ACTION_SET_REQ_STRU)
                            - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstMtcRrcActionReq  = (MTC_RRC_INTRUSION_ACTION_SET_REQ_STRU *)PS_ALLOC_MSG(
                                    UEPS_PID_MTC,
                                    ulLenth);

    if (VOS_NULL_PTR == pstMtcRrcActionReq)
    {
        MTC_ERROR_LOG("MTC_SndRrcIntrusionActionSetReq: alloc msg fail.");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstMtcRrcActionReq + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstMtcRrcActionReq->stMsgHeader.ulReceiverPid   = ulRecvPid;
    pstMtcRrcActionReq->stMsgHeader.ulMsgName       = ID_MTC_RRC_INTRUSION_ACTION_SET_REQ;
    pstMtcRrcActionReq->enActionFlag                = enEnableFlag;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstMtcRrcActionReq))
    {
        MTC_ERROR1_LOG("MTC_SndRrcIntrusionActionSetReq: Snd Msg err. Rec Pid ", ulRecvPid);
        return;
    }

    MTC_DEBUG_IntrusionSendActionReq(ulRecvPid);

    return;
}


VOS_VOID MTC_SndIntrusionActionSetReq(
    MODEM_ID_ENUM_UINT16                enModemId,
    PS_BOOL_ENUM_UINT8                  enEnableFlg
)
{
    if (MODEM_ID_0 == enModemId)
    {
        /* ��Modem0�Ľ���㷢����Ϣ*/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        /* �жϵ�ǰ���뼼���Ƿ�֧��TDS */
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_TDS))
        {
            MTC_SndRrcIntrusionActionSetReq(TPS_PID_RRC, enEnableFlg);
        }
#endif
#if (FEATURE_ON == FEATURE_LTE)
        /* �жϵ�ǰ���뼼���Ƿ�֧��LTE */
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_LTE))
        {
            MTC_SndRrcIntrusionActionSetReq(PS_PID_ERRC, enEnableFlg);
        }
#endif
    }
    else if (MODEM_ID_1 == enModemId)
    {
        /* �жϵ�ǰ���뼼���Ƿ�֧��Gģ*/
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_1, MTC_RATMODE_GSM))
        {
            /* ��Modem1 GAS������Ϣ*/
            MTC_SndRrcIntrusionActionSetReq(I1_UEPS_PID_GAS, enEnableFlg);
        }
    }
    else
    {
        MTC_ERROR_LOG("MTC_SndIntrusionActionSetReq: Modem ID Err.");
    }

    return;

}
VOS_VOID MTC_SndRrcIntrusionBandSetReq(
    VOS_UINT32                          ulRecvPid,
    RRC_MTC_MS_BAND_INFO_STRU          *pstForbiddenBandInfo
)
{
    VOS_UINT16                              ulLenth;
    MODEM_ID_ENUM_UINT16                    enModemId;
    MTC_RRC_INTRUSION_BAND_SET_REQ_STRU    *pstBandSetReq = VOS_NULL_PTR;

    enModemId = VOS_GetModemIDFromPid(ulRecvPid);
    if (enModemId >= MODEM_ID_BUTT)
    {
        return;
    }

    /* �����ǰ�Ѿ��ػ�����ֹͣ������Ϣ */
    if (MTC_MODEM_POWER_OFF == MTC_GetModemPowerState(enModemId))
    {
        return;
    }

    /* ������Ϣ�ռ� */
    ulLenth         = sizeof(MTC_RRC_INTRUSION_BAND_SET_REQ_STRU);
    pstBandSetReq   = (MTC_RRC_INTRUSION_BAND_SET_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                UEPS_PID_MTC,
                                                                ulLenth);

    if (VOS_NULL_PTR == pstBandSetReq)
    {
        MTC_ERROR_LOG("MTC_SndRrcIntrusionActionSetReq: Alloc Msg Fail!");
        return;
    }

    /* �����Ϣ */
    pstBandSetReq->stMsgHeader.ulReceiverPid    = ulRecvPid;
    pstBandSetReq->stMsgHeader.ulMsgName        = ID_MTC_RRC_INTRUSION_BAND_SET_REQ;

    PS_MEM_CPY(&pstBandSetReq->stForbiddenBandInfo,
               pstForbiddenBandInfo,
               sizeof(RRC_MTC_MS_BAND_INFO_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstBandSetReq))
    {
        MTC_ERROR1_LOG("MTC_SndRrcIntrusionActionSetReq: Snd Msg Err. ReceiverPid: ", ulRecvPid);
        return;
    }

    /* ��¼��ά�ɲ� */
    MTC_DEBUG_IntrusionSendSetBandReq(ulRecvPid);

    return;

}
VOS_VOID MTC_SndTdsLteIntrusionBandSetReq(
    RRC_MTC_MS_BAND_INFO_STRU          *pstForbiddenBandInfo
)
{
    /* �жϵ�ǰ��ģ״̬, ���ֱ��TDS��LTE����㷢�ͽ���B39ָʾ */
    if (MTC_RATMODE_LTE == MTC_GetModemRatMode(MODEM_ID_0))
    {
#if (FEATURE_ON == FEATURE_LTE)
        /* �жϵ�ǰ���뼼���Ƿ�֧��LTE */
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_LTE))
        {
            MTC_SndRrcIntrusionBandSetReq(PS_PID_ERRC, pstForbiddenBandInfo);
        }
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        /* �жϵ�ǰ���뼼���Ƿ�֧��TDS */
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_TDS))
        {
            MTC_SndRrcIntrusionBandSetReq(TPS_PID_RRC, pstForbiddenBandInfo);
        }
#endif
    }
    else
    {
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        /* �жϵ�ǰ���뼼���Ƿ�֧��TDS */
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_TDS))
        {
            MTC_SndRrcIntrusionBandSetReq(TPS_PID_RRC, pstForbiddenBandInfo);
        }
#endif
#if (FEATURE_ON == FEATURE_LTE)
        /* �жϵ�ǰ���뼼���Ƿ�֧��LTE */
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_LTE))
        {
            MTC_SndRrcIntrusionBandSetReq(PS_PID_ERRC, pstForbiddenBandInfo);
        }
#endif
    }

    return;
}
VOS_VOID MTC_IntrusionDisableB39(VOS_VOID)
{
    RRC_MTC_MS_BAND_INFO_STRU           stForbiddenBandInfo;

    PS_MEM_SET(&stForbiddenBandInfo, 0, sizeof(stForbiddenBandInfo));

    stForbiddenBandInfo.aulBandInfo[1] |= 1 << MTC_BAND_B39_BIT;

    MTC_SndTdsLteIntrusionBandSetReq(&stForbiddenBandInfo);

    return;
}


VOS_VOID MTC_IntrusionDisableB3(VOS_VOID)
{
    RRC_MTC_MS_BAND_INFO_STRU           stForbiddenBandInfo;

    PS_MEM_SET(&stForbiddenBandInfo, 0, sizeof(stForbiddenBandInfo));

    stForbiddenBandInfo.aulBandInfo[0] |= 1 << MTC_BAND_B3_BIT;

    /* ��GAS����㷢�ͽ���B3ָʾ */
    if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_1, MTC_RATMODE_GSM))
    {
        MTC_SndRrcIntrusionBandSetReq(I1_UEPS_PID_GAS, &stForbiddenBandInfo);
    }

    return;
}
VOS_VOID MTC_IntrusionEnableB39(VOS_VOID)
{
    RRC_MTC_MS_BAND_INFO_STRU           stForbiddenBandInfo;

    PS_MEM_SET(&stForbiddenBandInfo, 0, sizeof(stForbiddenBandInfo));

    MTC_SndTdsLteIntrusionBandSetReq(&stForbiddenBandInfo);

    return;
}


VOS_VOID MTC_IntrusionEnableB3(VOS_VOID)
{
    RRC_MTC_MS_BAND_INFO_STRU           stForbiddenBandInfo;

    PS_MEM_SET(&stForbiddenBandInfo, 0, sizeof(stForbiddenBandInfo));

    /* ��GAS����㷢������B3ָʾ */
    if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_1, MTC_RATMODE_GSM))
    {
        MTC_SndRrcIntrusionBandSetReq(I1_UEPS_PID_GAS, &stForbiddenBandInfo);
    }

    return;
}
VOS_VOID MTC_IntrusionEnableB3B39(VOS_VOID)
{
    /* ��������B3���� */
    MTC_IntrusionEnableB3();

    /* ��������B39���� */
    MTC_IntrusionEnableB39();

    return;
}


VOS_VOID MTC_ProcIntrusionStrategy(VOS_VOID)
{
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enModem0PowerState;
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enModem1PowerState;
    VOS_UINT32                              ulLoop;
    VOS_UINT32                              ulLineNum;
    MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8 enGsmBandState;
    MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8  enTLBandState;
    MTC_CS_SERVICE_STATE_ENUM_UINT8         enCsSrvState;
    FUNC_VOID                               pFunc           = VOS_NULL_PTR;

    /* ��ȡModem0��Modem1�Ŀ���״̬��ֻ����ͬʱ����������²Ž��вþ� */
    enModem0PowerState  = MTC_GetModemPowerState(MODEM_ID_0);
    enModem1PowerState  = MTC_GetModemPowerState(MODEM_ID_1);
    if ( (MTC_MODEM_POWER_ON != enModem0PowerState)
      || (MTC_MODEM_POWER_ON != enModem1PowerState) )
    {
        return;
    }

    /* ��ȡ���ش洢��Ƶ����Ϣ����ѯ�þ����Ա�ִ�ж�Ӧ���� */
    ulLineNum       = sizeof(g_astMtcIntrusionRulingStrategyTbl) / sizeof(MTC_INTRUSION_RULING_STRATEGY_STRU);
    enGsmBandState  = MTC_GetModem1GsmBandState();
    enTLBandState   = MTC_GetModem0TLBandState();
    enCsSrvState    = MTC_GetModemCsSrvExistFlg(MODEM_ID_1);

    for (ulLoop = 0; ulLoop < ulLineNum; ulLoop++)
    {
        if (g_astMtcIntrusionRulingStrategyTbl[ulLoop].enGsmBandState != enGsmBandState)
        {
            continue;
        }

        if (g_astMtcIntrusionRulingStrategyTbl[ulLoop].enTLBandState != enTLBandState)
        {
            continue;
        }

        if (MTC_CS_SERVICE_STATE_BUTT != g_astMtcIntrusionRulingStrategyTbl[ulLoop].enCsSrvState)
        {
            if (enCsSrvState != g_astMtcIntrusionRulingStrategyTbl[ulLoop].enCsSrvState)
            {
                continue;
            }
        }

        pFunc = g_astMtcIntrusionRulingStrategyTbl[ulLoop].pFunc;

        break;
    }

    if (VOS_NULL_PTR != pFunc)
    {
        pFunc();
    }

    return;
}


VOS_VOID MTC_IntrusionModemPowerStateChange(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState
)
{
    if (MTC_MODEM_POWER_OFF == enPowerState)
    {
        if (MODEM_ID_0 == enModemId)
        {
            if (MTC_MODEM_POWER_ON == MTC_GetModemPowerState(MODEM_ID_1))
            {
                /* ��Modem1��GAS��������B3ָʾ */
                MTC_IntrusionEnableB3();
            }
        }
        else
        {
            if (MTC_MODEM_POWER_ON == MTC_GetModemPowerState(MODEM_ID_0))
            {
                /* ��Modem0��TD&LTE��������B39ָʾ */
                MTC_IntrusionEnableB39();
            }
        }
    }

    return;
}


MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8 MTC_GetModem1GsmBandState(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLineNum;
    VOS_UINT8                           ucBand31;
    VOS_UINT8                           ucBand32;
    VOS_UINT8                           ucBandOther;
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo = VOS_NULL_PTR;
    MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8 enGsmBandState;

    pulBandInfo = MTC_GetModemCurBandInfo(MODEM_ID_1);

    /* ͨ����ȡBitλ��ȡ��ǰBand״̬ */
    if (0 != (pulBandInfo->aulBandInfo[0] & (1 << MTC_BAND_B31_BIT)))
    {
        ucBand31 = VOS_TRUE;
    }
    else
    {
        ucBand31 = VOS_FALSE;
    }

    if (0 != (pulBandInfo->aulBandInfo[0] & ((VOS_UINT32)1 << MTC_BAND_B32_BIT)))
    {
        ucBand32 = VOS_TRUE;
    }
    else
    {
        ucBand32 = VOS_FALSE;
    }

    if ( (0 != (pulBandInfo->aulBandInfo[0] & MTC_BAND_WITHOUT_B3))
      || (0 != pulBandInfo->aulBandInfo[1]) )
    {
        ucBandOther = VOS_TRUE;
    }
    else
    {
        ucBandOther = VOS_FALSE;
    }

    /* ͨ������ȡ��ǰGSMƵ��״̬ */
    enGsmBandState  = MTC_INTRUSION_GSM_BAND_STATE_BUTT;
    ulLineNum       = sizeof(g_stMtcIntrusionGsmBandStateTbl) / sizeof(MTC_INTRUSION_GSM_BAND_STATE_STRU);

    for (ulLoop = 0; ulLoop < ulLineNum; ulLoop++)
    {
        if (g_stMtcIntrusionGsmBandStateTbl[ulLoop].ucBand31 != ucBand31)
        {
            continue;
        }

        if (g_stMtcIntrusionGsmBandStateTbl[ulLoop].ucBand32 != ucBand32)
        {
            continue;
        }

        if (g_stMtcIntrusionGsmBandStateTbl[ulLoop].ucBandOther != ucBandOther)
        {
            continue;
        }

        enGsmBandState = g_stMtcIntrusionGsmBandStateTbl[ulLoop].enGsmBandState;

        break;
    }

    return enGsmBandState;
}


MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8 MTC_GetModem0TLBandState(VOS_VOID)
{
    RRC_MTC_MS_BAND_INFO_STRU          *pstBandInfo = VOS_NULL_PTR;

    pstBandInfo = MTC_GetModemCurBandInfo(MODEM_ID_0);

    /* ͨ����ȡBitλ��ȡ��ǰBand״̬ */
    if ( (0 == pstBandInfo->aulBandInfo[0])
      && (0 == pstBandInfo->aulBandInfo[1]) )
    {
        return MTC_INTRUSION_TL_BAND_NONE;
    }
    else if (0 != (pstBandInfo->aulBandInfo[1] & (1 << MTC_BAND_B39_BIT)))
    {
        return MTC_INTRUSION_TL_BAND_WITH_B39;
    }
    else
    {
        return MTC_INTRUSION_TL_BAND_WITHOUT_B39;
    }

}
MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8 MTC_GetModem0NCellTLBandState(VOS_VOID)
{
    RRC_MTC_MS_BAND_INFO_STRU          *pstBandInfo = VOS_NULL_PTR;

    pstBandInfo = MTC_GetModemNCellBandInfo(MODEM_ID_0);

    /* ͨ����ȡBitλ��ȡ��ǰBand״̬ */
    if ( (0 == pstBandInfo->aulBandInfo[0])
      && (0 == pstBandInfo->aulBandInfo[1]) )
    {
        return MTC_INTRUSION_TL_BAND_NONE;
    }
    else if (0 != (pstBandInfo->aulBandInfo[1] & (1 << MTC_BAND_B39_BIT)))
    {
        return MTC_INTRUSION_TL_BAND_WITH_B39;
    }
    else
    {
        return MTC_INTRUSION_TL_BAND_WITHOUT_B39;
    }

}



VOS_VOID MTC_RcvIntrusionActionSetCnf(VOS_VOID * pMsg)
{
    RRC_MTC_RESULT_CNF_STRU            *pstResultCnf;
    VOS_UINT32                          ulSendPid;

    pstResultCnf = (RRC_MTC_RESULT_CNF_STRU*)pMsg;
    ulSendPid    = pstResultCnf->stMsgHeader.ulSenderPid;

    /* ����ظ�ʧ�ܣ���ӡ��ʾ */
    if (MTC_RRC_RESULT_NO_ERROR != pstResultCnf->enResult)
    {
        MTC_ERROR2_LOG("MTC_RcvModem1GasIntrusionActionSetCnf: Action fail.", ulSendPid, pstResultCnf->enResult);
    }

    MTC_DEBUG_IntrusionRcvActionCnf(ulSendPid);

    return;
}
VOS_VOID MTC_RcvIntrusionBandSetCnf(VOS_VOID * pMsg)
{
    RRC_MTC_RESULT_CNF_STRU            *pstResultCnf;
    VOS_UINT32                          ulSendPid;

    pstResultCnf = (RRC_MTC_RESULT_CNF_STRU*)pMsg;
    ulSendPid    = pstResultCnf->stMsgHeader.ulSenderPid;

    /* ����ظ�ʧ�ܣ���ӡ��ʾ */
    if (MTC_RRC_RESULT_NO_ERROR != pstResultCnf->enResult)
    {
        MTC_ERROR2_LOG("MTC_RcvIntrusionBandSetCnf: Set Band fail.", ulSendPid, pstResultCnf->enResult);
    }

    MTC_DEBUG_IntrusionRcvSetBandCnf(ulSendPid);

    return;
}
VOS_VOID MTC_RcvIntrusionBandInfoInd(VOS_VOID * pMsg)
{
    MTC_MODEM_INFO_STRU                    *pstModemInfo = VOS_NULL_PTR;
    RRC_MTC_INTRUSION_BAND_INFO_IND_STRU   *pstModemBandInfo = VOS_NULL_PTR;
    MTC_MSG_BUF_STRU                       *pstBufAddr = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;
    MTC_CFG_ENUM_UINT8                      enIntrusionCfg;
    MTC_CFG_ENUM_UINT8                      enNotchCfg;

#if 0
    MTC_CFG_ENUM_UINT8                      enNarrowDcsCfg;
#endif
    pstModemBandInfo    = (RRC_MTC_INTRUSION_BAND_INFO_IND_STRU*)pMsg;
    enModemId           = VOS_GetModemIDFromPid(pstModemBandInfo->stMsgHeader.ulSenderPid);

    /* ���ModemID��Ч�ԣ������±���ȫ�ֱ��� */
    if (enModemId >= MODEM_ID_BUTT)
    {
        MTC_ERROR1_LOG("MTC_RcvIntrusionBandInfoInd: Err ModemId ", enModemId);
        return;
    }

    pstModemInfo    = MTC_GetModemCtxAddr(enModemId);
    pstBufAddr      = MTC_GetBufAddr(enModemId);

    if ( (PS_TRUE == MTC_IsNeedBufModem0Msg(pstModemBandInfo->stMsgHeader.ulSenderPid))
      && (MODEM_ID_0 == enModemId) )
    {
        PS_MEM_SET(&pstBufAddr->stBufBandInfoMsg, 0x0, sizeof(MTC_BAND_INFO_MSG_BUF_STRU));
        PS_MEM_CPY(&pstBufAddr->stBufBandInfoMsg.stIntrusionBandInfoMsg, pstModemBandInfo, sizeof(RRC_MTC_INTRUSION_BAND_INFO_IND_STRU));
        pstBufAddr->stBufBandInfoMsg.enExitBufMsgFlag = PS_TRUE;

        /* ��ȡ��ά�ɲ� */
        MTC_DEBUG_TraceNotchInfo();

        /* ��Ϣ��������ģʽ��Ӧʱ������һ��������� */
        return;
    }

    PS_MEM_CPY(&pstModemInfo->stCurBandInfo,
               &pstModemBandInfo->stCurBandInfo,
               sizeof(RRC_MTC_MS_BAND_INFO_STRU));

    /* ������� */
    pstBufAddr->stBufBandInfoMsg.enExitBufMsgFlag = PS_FALSE;

    PS_MEM_CPY(&pstModemInfo->stSerCellBandInfo,
               &pstModemBandInfo->stSerCellBandInfo,
               sizeof(RRC_MTC_MS_BAND_INFO_STRU));

    enIntrusionCfg  = MTC_GetIntrusionCfg();
    enNotchCfg      = MTC_GetNotchCfg();

    /* ����ǰMTC�������ϱ���SDT */
    MTC_DEBUG_TraceCtxInfo();

    if (MTC_CFG_ENABLE == enIntrusionCfg)
    {
        /* ����Ƶ����Ϣ�󣬴������ſ��Ʋþ� */
        MTC_ProcIntrusionStrategy();
    }

    /* ����ID_RRC_MTC_INTRUSION_BAND_INFO_IND��Ϣֻ����Modem0 ΪTL����ģʽʱ
       ��Modem1�ϱ���modem0ΪGUʱ��������������� */
    if (MTC_CFG_ENABLE == enNotchCfg)
    {
        /* ����Ƶ����Ϣ�󣬴���notch���Ʋþ� */
        MTC_ProcNotchStrategy();
    }
#if 0
    /* �ж�Narrow band dcs�þ��Ƿ�ʹ�� */
    enNarrowDcsCfg = MTC_GetNarrowBandDcsCfg();
    if (MTC_CFG_ENABLE == enNarrowDcsCfg)
    {
        /* ִ��Narrow band dcs�þ� */
        MTC_ProcNarrowDcsStrategy();
    }
#endif
    /* TL��Ƶ���ƿ��ؿ���ʱ, �������ſ��Ʋþ� */
    if ( (MTC_CFG_ENABLE == MTC_GetTlRfCtrlCfg())
      && (MODEM_ID_0 == enModemId) )
    {
        MTC_ProcB39B32Intrusion();
    }

    return;
}


PS_BOOL_ENUM_UINT8 MTC_CheckGsmWithB3(
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo
)
{
    /* ͨ����ȡBitλ��ȡ��ǰBand״̬ */
    if ((0 != (pulBandInfo->aulBandInfo[0] & (VOS_UINT32)(1 << MTC_BAND_B31_BIT)))
     || (0 != (pulBandInfo->aulBandInfo[0] & (VOS_UINT32)((VOS_UINT32)1 << MTC_BAND_B32_BIT))))
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}
PS_BOOL_ENUM_UINT8 MTC_CheckTLWithB34B39(
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo
)
{
    if ((0 != (pulBandInfo->aulBandInfo[1] & (VOS_UINT32)(1 << MTC_BAND_B34_BIT)))
     || (0 != (pulBandInfo->aulBandInfo[1] & (VOS_UINT32)(1 << MTC_BAND_B39_BIT))))
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}


VOS_VOID MTC_ProcNotchStrategy(VOS_VOID)
{
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enModem0PowerState;
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enModem1PowerState;
    MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8 enGsmBandState;
    MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8  enTLBandState;
    PS_BOOL_ENUM_UINT8                      enWithB3Flag;
    PS_BOOL_ENUM_UINT8                      enWithB34B39Flag;
    MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8  enNCellTLBandState;
    MTC_RATMODE_ENUM_UINT8                  enRatMode;
    PS_BOOL_ENUM_UINT8                      enNCellWithB34B39Flag;

    /* ��ȡ��ά�ɲ� */
    MTC_DEBUG_TraceNotchInfo();

    /* ��ȡModem0��Modem1�Ŀ���״̬ */
    enModem0PowerState  = MTC_GetModemPowerState(MODEM_ID_0);
    enModem1PowerState  = MTC_GetModemPowerState(MODEM_ID_1);
    if ( (MTC_MODEM_POWER_ON != enModem0PowerState)
      || (MTC_MODEM_POWER_ON != enModem1PowerState) )
    {
        /* ����Modemδͬʱ����ʱ��Ҫ��λNotch���� */
        MTC_ChangeNotchState(PS_FALSE);
        return;
    }

    enGsmBandState          = MTC_GetModem1GsmBandState();
    enTLBandState           = MTC_GetModem0TLBandState();
    enNCellTLBandState      = MTC_GetModem0NCellTLBandState();
    enRatMode               = MTC_GetModemRatMode(MODEM_ID_0);
    enWithB3Flag            = MTC_CheckGsmWithB3(MTC_GetModemCurBandInfo(MODEM_ID_1));
    enWithB34B39Flag        = MTC_CheckTLWithB34B39(MTC_GetModemCurBandInfo(MODEM_ID_0));
    enNCellWithB34B39Flag   = MTC_CheckTLWithB34B39(MTC_GetModemNCellBandInfo(MODEM_ID_0));

    /* ����Modemͬʱ������������һ��������Modem�������κ�Ƶ�Σ���Ҫʹ��Notch */
    /* ���ж�modem0�������ų���GU����Ƶ����Ϣ����� */
     /* ��GU��û��TL��band��Ϣ������Ҫ�ر� Notch */
    if ( (MTC_RATMODE_GSM == enRatMode)
      || (MTC_RATMODE_WCDMA == enRatMode) )
    {
        if (MTC_INTRUSION_TL_BAND_NONE == enNCellTLBandState)
        {
            MTC_ChangeNotchState(PS_FALSE);
            return;
        }
    }
    else
    {
        /* TL��ģʱ����bandû��band��Ϣ����bandû�У������϶�û�� */
        if (MTC_INTRUSION_TL_BAND_NONE == enTLBandState)
        {
            /* ������B3,���߸���û���ѵ���*/
            if ( (PS_TRUE == enWithB3Flag)
              || (MTC_INTRUSION_GSM_BAND_NONE == enGsmBandState) )
            {
                MTC_ChangeNotchState(PS_TRUE);
            }
            else
            {
                MTC_ChangeNotchState(PS_FALSE);
            }
            return;
        }
    }

    /* ����û���ѵ��� */
    if (MTC_INTRUSION_GSM_BAND_NONE == enGsmBandState)
    {
        /* ������Band34����Band39 */
        if (PS_TRUE == enWithB34B39Flag)
        {
            MTC_ChangeNotchState(PS_TRUE);
        }
        else
        {
            MTC_ChangeNotchState(PS_FALSE);
        }
        return;
    }

    /* GSM B3��TL B34/B39ͬʱ����ʱ��Ҫʹ��Notch������λNotch */
    if ( (PS_TRUE == (enWithB3Flag & enWithB34B39Flag))
      || (PS_TRUE == (enWithB3Flag & enNCellWithB34B39Flag)) )
    {
        MTC_ChangeNotchState(PS_TRUE);
    }
    else
    {
        MTC_ChangeNotchState(PS_FALSE);
    }

    return;
}
VOS_VOID MTC_ChangeNotchState(
    PS_BOOL_ENUM_UINT8                  enEnableFlag
)
{
    /* ����뵱ǰ״̬һ����ֱ�ӷ��� */
    if (MTC_GetNotchEnalbeFlag() == enEnableFlag)
    {
        return;
    }

    /* ֻ���ڸ�Modem����ʱ���·��þ�ָʾ */
    if (MTC_MODEM_POWER_ON == MTC_GetModemPowerState(MODEM_ID_1))
    {
        /* ������GAS�·�NOTCH�þ� */
        MTC_SndRrcNotchChannelInd(I1_UEPS_PID_GAS, enEnableFlag);
    }

    if (MTC_MODEM_POWER_ON == MTC_GetModemPowerState(MODEM_ID_0))
    {
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        /* �жϵ�ǰ���뼼���Ƿ�֧��TDS */
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_TDS))
        {
            /* ���֧��TDSģʽ��������TDS RRC�·�NOTCH�þ� */
            MTC_SndRrcNotchChannelInd(TPS_PID_RRC, enEnableFlag);
        }
#endif
#if (FEATURE_ON == FEATURE_LTE)
        /* �жϵ�ǰ���뼼���Ƿ�֧��LTE */
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_0, MTC_RATMODE_LTE))
        {
            /* ���֧��LTEģʽ��������LTE RRC�·�NOTCH�þ� */
            MTC_SndRrcNotchChannelInd(PS_PID_ERRC, enEnableFlag);
        }
#endif
    }

    /* ��¼Notch��־ */
    MTC_SetNotchEnalbeFlag(enEnableFlag);

    return;
}


VOS_VOID MTC_SndRrcNotchChannelInd(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
)
{
    VOS_UINT16                          ulLenth;
    MTC_RRC_NOTCH_CHANNEL_IND_STRU     *pstNotchChannelInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_RRC_NOTCH_CHANNEL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstNotchChannelInd  = (MTC_RRC_NOTCH_CHANNEL_IND_STRU *)PS_ALLOC_MSG(
                                    UEPS_PID_MTC,
                                    ulLenth);

    if (VOS_NULL_PTR == pstNotchChannelInd)
    {
        MTC_ERROR_LOG("MTC_SndRrcNotchChannelInd: alloc msg fail.");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstNotchChannelInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstNotchChannelInd->stMsgHeader.ulReceiverPid   = ulRecvPid;
    pstNotchChannelInd->stMsgHeader.ulMsgName       = ID_MTC_RRC_NOTCH_CHANNEL_IND;
    pstNotchChannelInd->enStartFlag                 = enEnableFlag;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstNotchChannelInd))
    {
        MTC_ERROR1_LOG("MTC_SndRrcNotchChannelInd: Snd Msg err. Rec Pid ", ulRecvPid);
        return;
    }

    return;
}






PS_BOOL_ENUM_UINT8 MTC_CheckGsmWithB31(
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo
)
{
    /* ͨ����ȡBitλ��ȡ��ǰBand״̬ */
    if (0 != (pulBandInfo->aulBandInfo[0] & (VOS_UINT32)((VOS_UINT32)1 << MTC_BAND_B31_BIT)))
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}
PS_BOOL_ENUM_UINT8 MTC_CheckGsmWithB32(
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo
)
{
    /* ͨ����ȡBitλ��ȡ��ǰBand״̬ */
    if (0 != (pulBandInfo->aulBandInfo[0] & (VOS_UINT32)((VOS_UINT32)1 << MTC_BAND_B32_BIT)))
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}
VOS_VOID MTC_SndRrcBandCfgInd(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
)
{
    VOS_UINT32                          ulLenth;
    MTC_RRC_BAND_CFG_IND_STRU          *pstBandCfgInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_RRC_BAND_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstBandCfgInd  = (MTC_RRC_BAND_CFG_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstBandCfgInd)
    {
        MTC_ERROR_LOG("MTC_SndRrcBandCfgInd: alloc msg fail.");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstBandCfgInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstBandCfgInd->stMsgHeader.ulReceiverPid   = ulRecvPid;
    pstBandCfgInd->stMsgHeader.ulMsgName       = ID_MTC_RRC_BAND_CFG_IND;
    pstBandCfgInd->enNarrowDcsFlag             = enEnableFlag;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstBandCfgInd))
    {
        MTC_ERROR1_LOG("MTC_SndRrcBandCfgInd: Snd Msg err. Rec Pid ", ulRecvPid);
        return;
    }

    return;
}


VOS_VOID MTC_ChangeNarrowBandDcsState(
    PS_BOOL_ENUM_UINT8                  enEnableFlag
)
{
    /* ����뵱ǰ״̬һ����ֱ�ӷ��� */
    if (MTC_GetNarrowDcsEnalbeFlag() == enEnableFlag)
    {
        return;
    }

    /* ֻ���ڸ�Modem����ʱ���·��þ�ָʾ */
    if (MTC_MODEM_POWER_ON == MTC_GetModemPowerState(MODEM_ID_1))
    {
        /* �жϵ�ǰ���뼼���Ƿ�֧��Gģ*/
        if (VOS_TRUE == MTC_IsSupportRatType(MODEM_ID_1, MTC_RATMODE_GSM))
        {
            /* ������GAS�·�Narrow Band dcs �þ� */
            MTC_SndRrcBandCfgInd(I1_UEPS_PID_GAS, enEnableFlag);
        }
    }

    /* ��¼Notch��־ */
    MTC_SetNarrowDcsEnalbeFlag(enEnableFlag);

    return;
}
VOS_VOID MTC_ProcNarrowDcsStrategy(VOS_VOID)
{
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enGModemPowerState;
#if 0
    MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8 enGsmBandState;
    PS_BOOL_ENUM_UINT8                      enWithB31Flag;
    PS_BOOL_ENUM_UINT8                      enWithB32Flag;
#endif
    enGModemPowerState  = MTC_GetModemPowerState(MODEM_ID_1);

    /* G modemδ����ʱ */
    if (MTC_MODEM_POWER_ON != enGModemPowerState)
    {
        /* ȥʹ��Narrow band dcs */
        MTC_ChangeNarrowBandDcsState(PS_FALSE);
        return;
    }
    else
    {
        MTC_ChangeNarrowBandDcsState(PS_TRUE);
        return;
    }
#if 0
    /* ��ȡG modem��Ƶ��״̬ */
    enGsmBandState      = MTC_GetModem1GsmBandState();

    /* �������κ�Ƶ�� */
    if (MTC_INTRUSION_GSM_BAND_NONE == enGsmBandState)
    {
        /* ȥʹ��Narrow band dcs */
        MTC_ChangeNarrowBandDcsState(PS_FALSE);
        return;
    }

    /* 1. ������Ƶ��B31����ҪNarrow Band Dcs
       2. ����Ƶ��B31�Լ�����Ƶ�Σ���ҪNarrow Band Dcs
     */
    enWithB31Flag = MTC_CheckGsmWithB31(MTC_GetModemCurBandInfo(MODEM_ID_1));
    enWithB32Flag = MTC_CheckGsmWithB32(MTC_GetModemCurBandInfo(MODEM_ID_1));

    /* ����B31�Ҳ�����B32�ĳ����£���ҪNarrow Band Dcs */
    if ((PS_TRUE  == enWithB31Flag)
     && (PS_FALSE == enWithB32Flag))
    {
        /* ʹ��Narrow band dcs */
        MTC_ChangeNarrowBandDcsState(PS_TRUE);
    }
    else
    {
        /* ȥʹ��Narrow band dcs */
        MTC_ChangeNarrowBandDcsState(PS_FALSE);
    }
    return;
#endif
}
VOS_VOID MTC_SndI1GasRrcTdsLteRfCtrlInd(PS_BOOL_ENUM_UINT8 enUplinkCloseFlag)
{
    MTC_RRC_TDS_LTE_RF_CONTROL_IND_STRU    *pstMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstMsg = (MTC_RRC_TDS_LTE_RF_CONTROL_IND_STRU *)MTC_ALLOC_MSG_WITH_HDR(
                            sizeof(MTC_RRC_TDS_LTE_RF_CONTROL_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        MTC_ERROR_LOG("MTC_SndI1GasRrcTdsLteRfCtrlInd: Alloc msg fail.");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(MTC_GET_MSG_ENTITY(pstMsg), 0x00, MTC_GET_MSG_LENGTH(pstMsg));

    /* ��д��Ϣͷ */
    MTC_CFG_I1_GAS_MSG_HDR(pstMsg, ID_MTC_RRC_TDS_LTE_RF_CONTROL_IND);

    /* ��д��Ϣ���� */
    pstMsg->enUplinkCloseFlag = enUplinkCloseFlag;

    /* ������Ϣ */
    MTC_SEND_MSG(pstMsg);
    return;
}
#if 0
PS_BOOL_ENUM_UINT8 MTC_ProcB39B32IntrusionStrategy(VOS_VOID)
{
    RRC_MTC_MS_BAND_INFO_STRU          *pstSerCellBandInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulB39Ret;
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enModem0PsState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enModem1PsState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enModem1CsSrvStatus;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enModem0CsSrvStatus;

    /* ��ʼ�� */
    enModem0CsSrvStatus = TAF_MTC_SRV_NO_EXIST;
    enModem1CsSrvStatus = TAF_MTC_SRV_NO_EXIST;
    enModem0PsState     = TAF_MTC_SRV_CONN_STATE_BUTT;
    enModem1PsState     = TAF_MTC_SRV_CONN_STATE_BUTT;
    ulB39Ret            = PS_FALSE;
    enModem1PowerState  = MTC_MODEM_POWER_STATE_BUTT;

    /* �ж�modem1�Ƿ񿪻� */
    enModem1PowerState =  MTC_GetModemPowerState(MODEM_ID_1);
    if (MTC_MODEM_POWER_OFF == enModem1PowerState)
    {
        /* ��׷�������Ч */
        return PS_FALSE;
    }

    /* �ж������Ƿ����B39 */
    pstSerCellBandInfo  = MTC_GetModemSerCellBandInfo(MODEM_ID_0);
    ulB39Ret            = MTC_BAND_CHECK64(*((VOS_UINT64 *)&(pstSerCellBandInfo->aulBandInfo[0])), MTC_BAND_MASK_B39);
    if (VOS_FALSE == ulB39Ret)
    {
        /* ��׷�������Ч */
        return PS_FALSE;
    }

    /* �ж���������ҵ��״̬ */
    enModem0PsState         = MTC_GetPsSrvState(MODEM_ID_0);
    enModem1PsState         = MTC_GetPsSrvState(MODEM_ID_1);
    enModem1CsSrvStatus     = MTC_GetCsSrvState(MODEM_ID_1);
    enModem0CsSrvStatus     = MTC_GetCsSrvState(MODEM_ID_0);

    /* ��������CS,���׷�������Ч */
    if (TAF_MTC_SRV_EXIST == enModem0CsSrvStatus)
    {
        return PS_FALSE;
    }

    /* ����CS, ���׷�����Ч */
    if (TAF_MTC_SRV_EXIST == enModem1CsSrvStatus)
    {
        return PS_TRUE;
    }

    /* ����PS,����IDLE, ���׷�����Ч */
    if ( (TAF_MTC_SRV_EXIST == enModem0PsState)
      && (TAF_MTC_SRV_EXIST != enModem1PsState) )
    {
        return PS_TRUE;
    }

    /* ���������׷�����Ч */
    return PS_FALSE;
}
#endif

PS_BOOL_ENUM_UINT8 MTC_ProcB39B32IntrusionStrategy(VOS_VOID)
{
    RRC_MTC_MS_BAND_INFO_STRU          *pstSerCellBandInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulB39Ret;
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enModem0CsSrvStatus;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enModem0PsSrvStatus;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enModem1CsSrvStatus;

    /* ��ʼ�� */
    enModem0CsSrvStatus             = TAF_MTC_SRV_NO_EXIST;
    enModem0PsSrvStatus             = TAF_MTC_SRV_CONN_STATE_BUTT;
    ulB39Ret                        = PS_FALSE;
    enModem1PowerState              = MTC_MODEM_POWER_STATE_BUTT;

    /* �ж�modem1�Ƿ񿪻� */
    enModem1PowerState =  MTC_GetModemPowerState(MODEM_ID_1);
    if (MTC_MODEM_POWER_OFF == enModem1PowerState)
    {
        /* ��׷�������Ч */
        return PS_FALSE;
    }

    /* �ж������Ƿ����B39 */
    pstSerCellBandInfo  = MTC_GetModemSerCellBandInfo(MODEM_ID_0);
    ulB39Ret            = MTC_BAND_CHECK64(*((VOS_UINT64 *)&(pstSerCellBandInfo->aulBandInfo[0])), MTC_BAND_MASK_B39);
    if (VOS_FALSE == ulB39Ret)
    {
        /* ��׷�������Ч */
        return PS_FALSE;
    }

    /* �ж���������ҵ��״̬ */
    enModem0CsSrvStatus         = MTC_GetCsSrvState(MODEM_ID_0);
    enModem0PsSrvStatus         = MTC_GetPsSrvState(MODEM_ID_0);
    enModem1CsSrvStatus         = MTC_GetCsSrvState(MODEM_ID_1);

    /* ������CSҵ�񣬴�ײ���Ч */
    if (TAF_MTC_SRV_EXIST == enModem0CsSrvStatus)
    {
        /* ��׷�������Ч */
        return PS_FALSE;
    }

    /* ����ֻ����PS, ��������CSʱ��Notch��Ч */
    if ( (TAF_MTC_SRV_EXIST == enModem0PsSrvStatus)
      && (enModem1CsSrvStatus == TAF_MTC_SRV_EXIST))
    {
        /* ��׷�����Ч */
        return PS_TRUE;
    }

    return PS_FALSE;

}

VOS_VOID MTC_ProcB39B32Intrusion(VOS_VOID)
{
    PS_BOOL_ENUM_UINT8                  ulStrategyRet;
    PS_BOOL_ENUM_UINT8                  enEnableFlag;

    /* �жϲþ������֮ǰ�Ƿ�һ�£����һ�������ٷ�����Ϣ */
    enEnableFlag    = MTC_GetTlRfCtrlEnalbeFlag();
    ulStrategyRet   = MTC_ProcB39B32IntrusionStrategy();
    if (enEnableFlag == ulStrategyRet)
    {
        return;
    }

    MTC_SetTlRfCtrlEnalbeFlag(ulStrategyRet);
    MTC_SndI1GasRrcTdsLteRfCtrlInd(ulStrategyRet);

    return;
}
VOS_VOID MTC_SndRrcRseCfgInd(
    VOS_UINT32                          ulRcvPid,
    PS_BOOL_ENUM_UINT8                  enRseOnFlag
)
{
    MTC_RRC_RSE_CFG_IND_STRU           *pstRseCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = sizeof(MTC_RRC_RSE_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstRseCfg = (MTC_RRC_RSE_CFG_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MTC, ulLength);
    if (VOS_NULL_PTR == pstRseCfg)
    {
        MTC_ERROR_LOG("MTC_SndRrcRseCfgInd: alloc mem fail.");
        return;
    }

    /* ��д��Ϣ���� */
    pstRseCfg->stMsgHeader.ulReceiverPid    = ulRcvPid;
    pstRseCfg->stMsgHeader.ulMsgName        = ID_MTC_RRC_RSE_CFG_IND;
    pstRseCfg->enRseOnFlag                  = enRseOnFlag;
    pstRseCfg->aucRsv[0]                    = 0;
    pstRseCfg->aucRsv[1]                    = 0;
    pstRseCfg->aucRsv[2]                    = 0;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstRseCfg))
    {
        MTC_ERROR_LOG("MTC_SndRrcRseCfgInd: Snd Msg err.");
        return;
    }

    /* ���ϱ�������浽�������� */
    MTC_SetRseCfgValue(enRseOnFlag);

    return;
}


VOS_VOID MTC_ProcRseStrategy(VOS_VOID)
{
    PS_BOOL_ENUM_UINT8                  enRseOnFlag;
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem0PowerState;
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;

    /* �жϵ�ǰ�Ƿ�֧��RSE���� */
    if (MTC_CFG_DISABLE == MTC_GetRseSupportCfg())
    {
        return;
    }

    /* �ж��Ƿ��ǲ��Կ� */
    if (VOS_FALSE == USIMM_IsTestCard_Instance(MODEM_ID_1))
    {
        return;
    }

    /* ��ʼ�� */
    enRseOnFlag        = PS_FALSE;
    enModem0PowerState = MTC_GetModemPowerState(MODEM_ID_0);
    enModem1PowerState = MTC_GetModemPowerState(MODEM_ID_1);

    /* ��modem0�ػ� modem1����������ҪRSE ON */
    if ((MTC_MODEM_POWER_OFF == enModem0PowerState )
      &&(MTC_MODEM_POWER_ON  == enModem1PowerState))
    {
        enRseOnFlag = PS_TRUE;
    }

    /* ����֮ǰ��ֵ��ͬ�������·���Ϣ */
    if (enRseOnFlag == MTC_GetRseCfgValue())
    {
        return ;
    }

    /* ��modem1����RSE������Ϣ */
    MTC_SndRrcRseCfgInd(I1_UEPS_PID_GAS, enRseOnFlag);

}

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


