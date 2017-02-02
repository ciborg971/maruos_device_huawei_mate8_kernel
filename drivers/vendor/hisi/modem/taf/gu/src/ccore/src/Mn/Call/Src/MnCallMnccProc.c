

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallMnccProc.h"
#include "NasMncc.h"
#include "MnCallMgmt.h"
#include "MnCallApi.h"
#include "MnComm.h"
#include "NasIeUtil.h"
#include "MnCallFacilityDecode.h"
#include "MnCallFacilityEncode.h"
#include "MnErrorCode.h"
#include "NasMncc.h"
#include "MnCallSendCc.h"
#include "MnCallBcProc.h"
#include "NasOmInterface.h"
#include "VcCallInterface.h"
#include "MnCallCstProc.h"
#include "MnCall.h"
#include "MnCallTimer.h"
#include "MnCallMsgDef.h"
#include "MM_Share_inc.h"
#include "MnMsgTs.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

#include "NVIM_Interface.h"

#include "TafSdcCtx.h"
#include "TafSdcLib.h"
#include "NasUtranCtrlInterface.h"
#include "NasUsimmApi.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "SpmImsaInterface.h"
#endif
#include "MnCallImsaProc.h"
#include "MnCallMgmt.h"


#include "MnCallReqProc.h"
#include "TafStdlib.h"
#include "MnCallSendApp.h"

#include "MnCallCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_MNCC_PROC_C


/* ��ǰTCH�ŵ����� */
LOCAL  MN_CALL_CHANNEL_INFO_STRU        f_stCallTchStatus;

MN_CALL_CHANNEL_INFO_STRU               g_stLastCallTchStatus;


/* ��ǰ�����Ƿ�ȴ�����Alert��Ϣ */
LOCAL  MN_CALL_WAIT_SEND_ALERT_STRU     f_stWaitSendAlert;

/*��ǰChannel�Ƿ�򿪱�־*/
LOCAL  VOS_BOOL                         f_bChannelOpenFlg = VOS_FALSE;

/* ��ǰ���к�����Ϣ */
LOCAL  MN_CALL_INFO_STRU                f_astCallInfos[MN_CALL_MAX_NUM];


/*lint -save -e958 */

/*****************************************************************************
   2 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : CALL_SetChannelOpenFlg
 ��������  : �����ŵ��򿪱�־
 �������  : bChannelOpenFlg - �����ŵ��򿪱�־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SetChannelOpenFlg(
    VOS_BOOL                            bChannelOpenFlg
)
{
    f_bChannelOpenFlg = bChannelOpenFlg;
}

/*****************************************************************************
 �� �� ��  : CALL_GetChannelOpenFlg
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL MN_CALL_GetChannelOpenFlg( VOS_VOID )
{
    return f_bChannelOpenFlg;
}


/*****************************************************************************
 �� �� ��  : CALL_SetWaitSendAlertStatus
 ��������  :
 �������  : bWaitSendAlertStatus   - ҵ���ŵ���״̬
             uccallId               - ����Id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SetWaitSendAlertStatus(
    VOS_BOOL                            bWaitSendAlertStatus,
    VOS_UINT8                           uccallId
)
{
    f_stWaitSendAlert.bWaitSendAlertStatus = bWaitSendAlertStatus;
    f_stWaitSendAlert.ucCallId = uccallId;
}

/*****************************************************************************
 �� �� ��  : CALL_GetWaitSendAlertStatus
 ��������  :
 �������  :
 �������  : pbWaitSendAlertStatus - ��ǰ�Ƿ��ڵȴ�����alerting��Ϣ״̬
              puccallId             - ��Ӧ�ĺ���Id
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_GetWaitSendAlertStatus(
    VOS_BOOL                            *pbWaitSendAlertStatus,
    VOS_UINT8                           *puccallId
)
{
    *pbWaitSendAlertStatus = f_stWaitSendAlert.bWaitSendAlertStatus;
    *puccallId = f_stWaitSendAlert.ucCallId;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_SetTchStatus
 ��������  :
 �������  : bAvailable - ҵ���ŵ���״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SetTchStatus(
    VOS_BOOL                            bAvailable
)
{
    f_stCallTchStatus.bChannelEnable = bAvailable;
}


LOCAL VOS_BOOL MN_CALL_SetTchPara(
    const NAS_CC_SYNC_IND_STRU           *pstTchPara,
    const VOS_UINT8                       ucCallId
)
{
    MN_CALL_RADIO_MODE_ENUM_U8          enMode;
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType;

    switch(pstTchPara->enTchType)
    {
        case NAS_CC_TCH_TYPE_FR:
            enCodecType = MN_CALL_CODEC_TYPE_FR;
            break;

        case NAS_CC_TCH_TYPE_HR:
            enCodecType = MN_CALL_CODEC_TYPE_HR;
            break;

        case NAS_CC_TCH_TYPE_EFR:
            enCodecType = MN_CALL_CODEC_TYPE_EFR;
            break;

        case NAS_CC_TCH_TYPE_AMR:
            enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;

        case NAS_CC_TCH_TYPE_AMR2:
            enCodecType = MN_CALL_CODEC_TYPE_AMR2;
            break;

        case NAS_CC_TCH_TYPE_AMRWB:
            enCodecType = MN_CALL_CODEC_TYPE_AMRWB;
            break;

        case NAS_CC_TCH_TYPE_AHR:
            enCodecType = MN_CALL_CODEC_TYPE_AMR;
            break;

        case NAS_CC_TCH_SINGAL_MOD:
            /* singal mode, ignore */
            return VOS_FALSE;

        case NAS_CC_TCH_CSD_9600:
        case NAS_CC_TCH_CSD_4800:
        case NAS_CC_TCH_CSD_2400:
        case NAS_CC_TCH_CSD_14400:
            /* data mode, ignore */
            return VOS_FALSE;

        default:
            MN_WARN_LOG1("MN_CALL_SetTchPara enTchType is error: ", (VOS_INT32)(pstTchPara->enTchType));
            return VOS_FALSE;
    }

    switch(pstTchPara->enRaMode)
    {
        case NAS_CC_RA_MODE_GSM:
            enMode = MN_CALL_RADIO_MODE_GSM;
            break;

        case NAS_CC_RA_MODE_WCDMA:
            enMode = MN_CALL_RADIO_MODE_WCDMA;
            break;

        default:
            MN_WARN_LOG1("MN_CALL_SetTchPara enRaMode is error: ", (VOS_INT32)(pstTchPara->enRaMode));
            return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        TAF_CALL_SetTchCallType(TAF_CALL_TYPE_ECALL);
    }
    else
#endif
    {
        TAF_CALL_SetTchCallType(TAF_CALL_TYPE_NORMAL_CALL);
    }

    f_stCallTchStatus.stChannelParam.enCodecType = enCodecType;
    f_stCallTchStatus.stChannelParam.enMode = enMode;


    return VOS_TRUE;
}


VOS_BOOL MN_CALL_GetTchStatus( VOS_VOID )
{
    return f_stCallTchStatus.bChannelEnable;
}


VOS_VOID MN_CALL_SetLastCallTchStatus(
    MN_CALL_CHANNEL_INFO_STRU          *pstCallTchStatus
)
{
    PS_MEM_CPY(&g_stLastCallTchStatus,
               pstCallTchStatus,
               sizeof(MN_CALL_CHANNEL_INFO_STRU));
}


MN_CALL_CODEC_TYPE_ENUM_U8 MN_CALL_GetLastCodecType(VOS_VOID)
{
    return g_stLastCallTchStatus.stChannelParam.enCodecType;
}

/* MN_CALL_JudgeMtCallType������MnComm.c�� */

VOS_VOID TAF_CALL_SetTchCallType(TAF_CALL_TYPE_ENUM_UINT16 enCallType)
{
    f_stCallTchStatus.stChannelParam.enCallType = enCallType;
}

/*****************************************************************************
 �� �� ��  : CALL_JudgeMtCallMode
 ��������  : �ж�����ĺ���ģʽ
 �������  : pstBCRepeatInd - IE Repeat indicator
              pstBC1         - IE BC1
              pstBC2         - IE BC2
 �������  : penCallMode    - ����ģʽ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32  MN_CALL_JudgeMtCallMode(
    const NAS_CC_IE_REPEAT_INDICATOR_STRU       *pstBCRepeatInd,
    const NAS_CC_IE_BC_STRU                     *pstBC1,
    const NAS_CC_IE_BC_STRU                     *pstBC2,
    MN_CALL_MODE_ENUM_U8                        *penCallMode
)
{
    MN_CALL_TYPE_ENUM_U8                enCallType1;
    MN_CALL_TYPE_ENUM_U8                enCallType2;

    /* AVF ģʽ�£���������BC������ */
    if ((VOS_TRUE == NAS_IE_IS_PRESENT(pstBC1))
      &&(VOS_TRUE == NAS_IE_IS_PRESENT(pstBC2)))
    {
        if (VOS_OK != MN_CALL_JudgeMtCallType(&pstBC1->Octet3,
                                           &pstBC1->Octet5a,
                                           &enCallType1))
        {
            return VOS_ERR;
        }

        if (VOS_OK != MN_CALL_JudgeMtCallType(&pstBC2->Octet3,
                                           &pstBC2->Octet5a,
                                           &enCallType2))
        {
            return VOS_ERR;
        }

        /* Ŀǰ����ֻд��֧�������ʹ��棬��������£���ʱ��Ϊ�ǲ����� */
        if ((MN_CALL_TYPE_VOICE == enCallType1)
         && (MN_CALL_TYPE_FAX == enCallType2))
        {
            switch(pstBCRepeatInd->RepeatIndication)
            {
            case MN_CALL_REP_IND_ALTER:
            case MN_CALL_REP_IND_ALTER_1_PRFER:
                *penCallMode = MN_CALL_MODE_AVF;
                return VOS_OK;

            case MN_CALL_REP_IND_FALLBACK:
                *penCallMode = MN_CALL_MODE_SINGLE;
                return VOS_OK;

            default:
                MN_WARN_LOG("MN_CALL_JudgeMtCallMode: Repeat Indication err");
                return VOS_ERR;
            }
        }

        MN_WARN_LOG("MN_CALL_JudgeMtCallMode: not support call mode");
        return VOS_ERR;
    }

    /* ��������£�����singleģʽ */
    *penCallMode = MN_CALL_MODE_SINGLE;
    return VOS_OK;
}
LOCAL VOS_UINT32 MN_CALL_ProcNotifyForwardSsCode(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo
)
{
    /*���� 24.082�е��������յ�ssStatus��ʱ�򣬱�ʾ��ҵ�񱻼���*/
    if (pstNotifySs->OP_SsStatus)
    {
        if (TAF_CFU_SS_CODE == pstNotifySs->SsCode)
        {
            pstSsInfo->enCode = MN_CALL_SS_NTFY_UNCOND_FWD_ACTIVE;
        }
        else
        {
            pstSsInfo->enCode = MN_CALL_SS_NTFY_COND_FWD_ACTIVE;
        }
    }

    /*���� 24.082�е��������յ�SsNotification��ʱ�򣬱�ʾ���뱻ǰת*/
    if (pstNotifySs->OP_SsNotification)
    {
        /*����24.080�ж���SsNotification��ֵ�Ķ�����ȷ��ֵ, 24.080 4.4.2*/
        switch(pstNotifySs->SsNotification)
        {
            case TAF_FWDIND_FORWARDED_CALL_INCOM:
            case TAF_FWDIND_INCALL_FORWARDED:
                pstSsInfo->enCode = MN_CALL_SS_NTFY_FORWORDED_CALL;
                break;

            case TAF_FWDIND_OUTCALL_FORWARDED:
                pstSsInfo->enCode = MN_CALL_SS_NTFY_BE_FORWORDED;
                break;

            default:
                MN_WARN_LOG("MN_CALL_ProcNotifySs: Notification value is wrong");
                return VOS_ERR;

        }
    }
    return VOS_OK;
}
LOCAL VOS_VOID MN_CALL_NotifyNtfyOnHoldOrRetrieved(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo
)
{
    if (MN_CALL_ON_HOLD_IND_RETRIEVED == pstNotifySs->CallOnHoldIndicator)
    {
        pstSsInfo->enCode = MN_CALL_SS_NTFY_RETRIEVED;
    }
    else
    {
        pstSsInfo->enCode = MN_CALL_SS_NTFY_ON_HOLD;
    }
    MN_CALL_UpdateSsNotify(ucCallId, pstSsInfo);

    /* �㲥����(INCOMING)�¼� */
    MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
}
LOCAL VOS_VOID MN_CALL_ProcNotifyCcbsSscode(
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo
)
{

    if (TAF_CCBS_A_SS_CODE == pstNotifySs->SsCode)
    {
        /*ͨ��MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY)�ϱ�CCBS�غ��¼�*/
         pstSsInfo->enCode = MN_CALL_SS_NTFY_CCBS_RECALL;
    }
    else if (TAF_CCBS_B_SS_CODE == pstNotifySs->SsCode)
    {
        pstSsInfo->enCode = MN_CALL_SS_NTFY_CCBS_BE_RECALLED;
    }
    else
    {
        ;
    }
}
LOCAL VOS_VOID MN_CALL_SsRegCcEntryProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{

    /*���²���ҵ������Ľ�չ*/
    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                                       enErrcode);
    }

}
LOCAL VOS_VOID MN_CALL_ProcNotifySsCode(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo

)
{
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();

    /*���н�ֹ�����Ϣ*/
    if (TAF_ALL_BARRING_SS_CODE == (pstNotifySs->SsCode & 0xf0))
    {
        switch(pstNotifySs->SsCode)
        {
            case TAF_BAOC_SS_CODE:
            case TAF_BOIC_SS_CODE:
            case TAF_BOICEXHC_SS_CODE:
                pstSsInfo->enCode = MN_CALL_SS_NTFY_OUTGOING_BARRED;
                break;

            case TAF_BAIC_SS_CODE:
            case TAF_BICROAM_SS_CODE:
                pstSsInfo->enCode = MN_CALL_SS_NTFY_INCOMING_BARRED;
                break;

            default:
                MN_WARN_LOG("MN_CALL_ProcNotifySs: Ss Code Error");
                return;
        }
    }

    /*����ǰת�����Ϣ*/
    if (TAF_ALL_FORWARDING_SS_CODE == (pstNotifySs->SsCode & 0xf0))
    {
        if (TAF_CD_SS_CODE != pstNotifySs->SsCode)
        {
            if (VOS_ERR == MN_CALL_ProcNotifyForwardSsCode(ucCallId, pstNotifySs, pstSsInfo))
            {
                return;
            }
        }

    }

    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        MN_CALL_ProcNotifyCcbsSscode(pstNotifySs, pstSsInfo);
    }

    /* �ο��µ����Կ���ԭ��: CDҵ����Ϣ�ϱ�����ҵ�����NV������ */
    if (TAF_CD_SS_CODE == pstNotifySs->SsCode)
    {
        if (TAF_FWDIND_OUTCALL_FORWARDED == pstNotifySs->SsNotification)
        {
            pstSsInfo->enCode = MN_CALL_SS_NTFY_BE_DEFLECTED;
        }
        else
        {
            pstSsInfo->enCode = MN_CALL_SS_NTFY_DEFLECTED_CALL;
        }
    }

    MN_CALL_UpdateSsNotify(ucCallId, pstSsInfo);

    /* �ϱ��¼�*/
    MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    return;
}
LOCAL VOS_VOID MN_CALL_ProcNotifySsEct(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs,
    MN_CALL_SS_NOTIFY_STRU              *pstSsInfo

)
{
    VOS_UINT8                           ucBcdLen;


    ucBcdLen = 0;

    pstSsInfo->enCode = MN_CALL_SS_NTFY_EXPLICIT_CALL_TRANSFER;
    pstSsInfo->stEctIndicator.enEctCallState = pstNotifySs->EctIndicator.EctCallState;

    if (1 == pstNotifySs->EctIndicator.OP_PresentationAllowedAddr)
    {
        pstSsInfo->stEctIndicator.enEctRdnType
                    = MN_CALL_ECT_RDN_PRESENTATION_ALLOWED_ADDR;
        pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr.enNumType
                    = pstNotifySs->EctIndicator.PresentationAllowedAddr.NumType;
        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR*)pstNotifySs->EctIndicator.PresentationAllowedAddr.aucPartyNumber,
                            pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr.aucBcdNum,
                            &ucBcdLen))
        {
            MN_INFO_LOG("MN_CALL_ProcNotifySsEct: TAF_STD_ConvertAsciiNumberToBcd fail");
        }
        pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr.ucNumLen = ucBcdLen;

        /* �ο�22.091 8.1,8.3 */
        MN_CALL_UpdateCallNumber(ucCallId, &(pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr));
    }

    if (1 == pstNotifySs->EctIndicator.OP_PresentationRestricted)
    {
        pstSsInfo->stEctIndicator.enEctRdnType
                    = MN_CALL_ECT_RDN_PRESENTATION_RESTRICTED;
    }

    if (1 == pstNotifySs->EctIndicator.OP_NumNotAvailableDueToInterworking)
    {
        pstSsInfo->stEctIndicator.enEctRdnType
                    = MN_CALL_ECT_RDN_NUM_NOT_AVAILABLE;
    }

    if (1 == pstNotifySs->EctIndicator.OP_PresentationRestrictedAddr)
    {
        pstSsInfo->stEctIndicator.enEctRdnType
                    = MN_CALL_ECT_RDN_PRESENTATION_RESTRICTED_ADDR;
        pstSsInfo->stEctIndicator.rdn.stPresentationRestrictedAddr.enNumType
                    = pstNotifySs->EctIndicator.PresentationRestrictedAddr.NumType;
        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR*)pstNotifySs->EctIndicator.PresentationRestrictedAddr.aucPartyNumber,
                            pstSsInfo->stEctIndicator.rdn.stPresentationRestrictedAddr.aucBcdNum,
                            &ucBcdLen))
        {
            MN_INFO_LOG("MN_CALL_ProcNotifySsEct: TAF_STD_ConvertAsciiNumberToBcd fail");
        }
        pstSsInfo->stEctIndicator.rdn.stPresentationAllowedAddr.ucNumLen = ucBcdLen;
    }

    MN_CALL_UpdateSsNotify(ucCallId, pstSsInfo);

    /* �㲥����(INCOMING)�¼� */
    MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);

}



LOCAL VOS_VOID  MN_CALL_ProcNotifySs(
    VOS_UINT8                           ucCallId,
    const MN_CALL_SS_NOTIFYSS_ARG_STRU  *pstNotifySs
)
{
    MN_CALL_SS_NOTIFY_STRU              stSsInfo;


    PS_MEM_SET(&stSsInfo, 0, sizeof(stSsInfo));

    MN_INFO_LOG1("MN_CALL_ProcNotifySs: callId,", ucCallId);

    /* ��֪���еȴ� */
    if (pstNotifySs->OP_CallWaitingInd)
    {
        stSsInfo.enCode = MN_CALL_SS_NTFY_IS_WAITING;

        MN_CALL_UpdateSsNotify(ucCallId, &stSsInfo);

        /* �㲥����(INCOMING)�¼� */
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    }

    /* ��֪���б����ֻ��߻ָ� */
    if (pstNotifySs->OP_CallOnHoldInd)
    {
        MN_CALL_NotifyNtfyOnHoldOrRetrieved(ucCallId, pstNotifySs, &stSsInfo);
    }

    /* ��֪����MPTY״̬ */
    if (pstNotifySs->OP_MptyIndicator)
    {
        stSsInfo.enCode = MN_CALL_SS_NTFY_ENTER_MPTY;
        MN_CALL_UpdateSsNotify(ucCallId, &stSsInfo);
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    }

    /* ��֪cug�����Ϣ */
    if (pstNotifySs->OP_CugIndex)
    {
        stSsInfo.enCode = MN_CALL_SS_NTFY_MO_CUG_INFO;
        stSsInfo.ulCugIndex = (VOS_UINT32)pstNotifySs->CugIndex;
        MN_CALL_UpdateSsNotify(ucCallId, &stSsInfo);

        /* �㲥����(INCOMING)�¼� */
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    }

    /* ��֪clir�����Ϣ */
    if(pstNotifySs->OP_ClirSuppressionRej)
    {
        stSsInfo.enCode = MN_CALL_SS_NTFY_CLIR_SUPPRESS_REJ;
        MN_CALL_UpdateSsNotify(ucCallId, &stSsInfo);

        /* �㲥����(INCOMING)�¼� */
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_SS_NOTIFY);
    }

    if (pstNotifySs->OP_SsCode)
    {
        MN_CALL_ProcNotifySsCode(ucCallId, pstNotifySs, &stSsInfo);
    }
    /*ECT�����Ϣ*/
    if (pstNotifySs->OP_EctIndicator)
    {
        MN_CALL_ProcNotifySsEct(ucCallId, pstNotifySs, &stSsInfo);
    }

}
LOCAL VOS_UINT32 MN_CALL_Bc1Bc2CompChk(
    MN_CALL_ID_T                        callId,
    NAS_CC_IE_BC_STRU                   *pstBc1Setup,
    NAS_CC_IE_BC_STRU                   *pstBc2Setup,
    NAS_CC_IE_REPEAT_INDICATOR_STRU     *pstRepeatIndSetup
)
{
    VOS_UINT32                          ulBc1ChkRslt;
    VOS_UINT32                          ulBc2ChkRslt;

    /* BC1��BC2�ļ����Լ�� */
    ulBc1ChkRslt = MN_CALL_BcCompChk(pstBc1Setup);
    ulBc2ChkRslt = MN_CALL_BcCompChk(pstBc2Setup);


    /* �˴���Ҫ��CC�Ķ������Ӷ�Ӧ��ö�ٶ��壬��ʱ��1����alternate */
    if ( MN_CALL_REP_IND_ALTER == pstRepeatIndSetup->RepeatIndication )
    {
        MN_INFO_LOG1("MN_CALL_ProcMnccSetupInd ", pstRepeatIndSetup->RepeatIndication );
        /*�����һ��BC��鶼û��ͨ��*/
        if ((VOS_OK != ulBc1ChkRslt) || (VOS_OK != ulBc2ChkRslt))
        {
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: alter mode one bc check no ok" );
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;
        }
    }
    else if ( ( MN_CALL_REP_IND_FALLBACK == pstRepeatIndSetup->RepeatIndication)
           || ( MN_CALL_REP_IND_ALTER_1_PRFER == pstRepeatIndSetup->RepeatIndication ))
    {
        /* ����BC���û��ͨ�� */
        if ( (VOS_OK != ulBc1ChkRslt) && (VOS_OK != ulBc2ChkRslt) )
        {
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: fallback mode two bc check no ok" );
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;
        }
        /*����һ��BC���û��ͨ��*/
        else if (VOS_OK != ulBc1ChkRslt)
        {
            /*�������ͨ����BC, �������ʧ�ܵ�BC(����Я����Call Confirm��)*/
            /* �˴������ʧ�ܵ�BC����Ϊ������ */
            PS_MEM_CPY(pstBc1Setup,
                       pstBc2Setup,
                       sizeof(NAS_CC_IE_BC_STRU));
            NAS_IE_SET_ABSENT(pstBc2Setup);
        }
        else if (VOS_OK != ulBc2ChkRslt)
        {
            NAS_IE_SET_ABSENT(pstBc2Setup);
        }
        else
        {
            MN_NORM_LOG("MN_CALL_ProcMnccSetupInd: fallback mode BC check pass" );
        }
    }
    else
    {
        MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
        MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: other mode BC check pass" );
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return VOS_ERR;
    }
    return VOS_OK;
}
LOCAL VOS_UINT32 MN_CALL_BcChkForCallCnf(
    VOS_VOID                            *pMsg,
    NAS_CC_IE_BC_STRU                   *pstBc1CallCnf,
    NAS_CC_IE_BC_STRU                   *pstBc2CallCnf,
    MN_CALL_REP_IND_ENUM_U8             *penRepeatInd,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    MN_CALL_ID_T                        callId,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
)
{
    VOS_UINT32                          ulCnt;
    NAS_CC_MSG_SETUP_MO_STRU            *pstMoSetup;
    NAS_CC_MSG_SETUP_MT_STRU            *pstMtSetup;
    NAS_CC_IE_BC_STRU                   *pstBc1Setup;
    NAS_CC_IE_BC_STRU                   *pstBc2Setup;
    NAS_CC_IE_REPEAT_INDICATOR_STRU     *pstRepeatIndSetup;
    VOS_UINT8                           ucRatType;


    if (MN_CALL_DIR_CCBS == enCallDir)
    {
        /*CCBS��cc establishment��setup container�д���setup�ṹͬNAS_CC_MSG_SETUP_MO_STRU*/
        pstMoSetup = (NAS_CC_MSG_SETUP_MO_STRU *)pMsg;
        pstBc1Setup = &pstMoSetup->stBC1;
        pstBc2Setup = &pstMoSetup->stBC2;
        pstRepeatIndSetup = &pstMoSetup->stBCRepeatInd;
    }
    else
    {
        pstMtSetup = (NAS_CC_MSG_SETUP_MT_STRU *)pMsg;
        pstBc1Setup =  &pstMtSetup->stBC1;
        pstBc2Setup = &pstMtSetup->stBC2;
        pstRepeatIndSetup = &pstMtSetup->stBCRepeatInd;
    }

    MMC_ComGetRatType(&ucRatType);
    if (MN_CALL_NET_TYPE_GSM == ucRatType)
    {
        /* ��ǰפ��G��*/
        if ((VOS_TRUE == NAS_IE_IS_PRESENT(pstBc1Setup))
         && (MN_CALL_BC_VAL_ITC_SPEECH != pstBc1Setup->Octet3.InfoTransCap)
         && (MN_CALL_BC_VAL_ITC_AUX_SPEECH != pstBc1Setup->Octet3.InfoTransCap))
        {
            /* ��֧�ֵ�ҵ������ֱ�ӻظ�release complete��Ϣ */
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;

        }


        if ((VOS_TRUE == NAS_IE_IS_PRESENT(pstBc2Setup))
         && (MN_CALL_BC_VAL_ITC_SPEECH != pstBc2Setup->Octet3.InfoTransCap)
         && (MN_CALL_BC_VAL_ITC_AUX_SPEECH != pstBc2Setup->Octet3.InfoTransCap))
        {
            /* ��֧�ֵ�ҵ������ֱ�ӻظ�release complete��Ϣ */
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;

        }
    }
    /* �����Ƕ�BC�ļ�� */
    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc1Setup))
    {
        /*�����뷽��, ���ڵĴ�����Ϊ��voice��
           Ϊ�˹�ܱ���澯����MN_CALL_BuildBcForSns�������õ�ʱ��������ĵڶ�������
           pstDataCfgInfo������ǿ��ת����ʵ������������ģ���ΪMN_CALL_CS_DATA_CFG_INFO_STRU�ṹ
           ��MN_CALL_CS_DATA_CFG_STRU�ṹ��Ԫ��enSpeed�ǲ�һ���ġ������޸�CSD��ʱ�����ر��ע��*/
        ulCnt = MN_CALL_BuildBcForSns(MN_CALL_SNS_MODE_VOICE,
                                      pstDataCfgInfo,
                                      pstBc1CallCnf,
                                      pstBc2CallCnf,
                                      penRepeatInd);
        if ( 0 == ulCnt )
        {
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: no bc1 not support" );
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;
        }
        MN_CALL_UpdateCallMode(callId, MN_CALL_MODE_SINGLE);
        MN_CALL_UpdateCallType(callId, MN_CALL_TYPE_VOICE);
    }
    else if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc2Setup))
    {
        /* BC1�ļ����Լ�飬�������ͨ����飬����Release Complete��Ϣ */
        if (VOS_OK != MN_CALL_BcCompChk(pstBc1Setup) )
        {
            MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: bc1 check no ok" );
            MN_CALL_FreeCallId(callId);
            MN_CALL_DeleteCallEntity(callId);
            return VOS_ERR;
        }
    }
    else
    {
        /* BC1��BC2�ļ����Լ�� */
        if (VOS_ERR == MN_CALL_Bc1Bc2CompChk(callId, pstBc1Setup, pstBc2Setup, pstRepeatIndSetup))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : CALL_UpdateCallStateForCallCnf
 ��������  : ��call confirm��Ϣ����ʱ��ˢ�º���״̬��
 �������  : callId - ����ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_UpdateCallStateForCallCnf(
    MN_CALL_ID_T                        callId
)
{
    /* ���ݵ�ǰ�Ƿ����������У����ö�Ӧ�ĺ���״̬ */
    if ( VOS_TRUE == MN_CALL_CheckNotIdleStateExist() )
    {
        MN_CALL_UpdateCallState(callId, MN_CALL_S_WAITING);
    }
    else
    {
        MN_CALL_UpdateCallState(callId, MN_CALL_S_INCOMING);
    }

}

/*****************************************************************************
 �� �� ��  : CALL_GetDataCfgInfoForCallCnf
 ��������  : ��ȡ����ҵ���������Ϣ��
 �������  : pstBc1CallCnf      - call confirm��Ϣ�е�Bc1
              pstBc2CallCnf     - call confirm��Ϣ�е�Bc2
              enCallType        - ��������
              enCallMode        - ����ģʽ
 �������  : pstDataCfgInfo     - ����ҵ���������Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_GetDataCfgInfoForCallCnf(
    NAS_CC_IE_BC_STRU                   *pstBc1CallCnf,
    NAS_CC_IE_BC_STRU                   *pstBc2CallCnf,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
)
{
    /* ��ȡ����ҵ���������Ϣ */
    if ((MN_CALL_TYPE_CS_DATA == enCallType) || (MN_CALL_TYPE_FAX == enCallType))
    {
        MN_CALL_GetDataCfgInfoFromBc(pstBc1CallCnf, pstDataCfgInfo);
    }
    /* ������������棬���BC2�л�ȡ */
    else
    {
        if (( MN_CALL_MODE_AVF == enCallMode )
          &&( VOS_TRUE == NAS_IE_IS_PRESENT(pstBc2CallCnf)))
        {
            MN_CALL_GetDataCfgInfoFromBc(pstBc2CallCnf, pstDataCfgInfo);
        }
    }

}

/*****************************************************************************
 �� �� ��  : CALL_JudgeAllowToSendAlertReq
 ��������  : �ж��Ƿ���Ҫ����Alerting��Ϣ
 �������  : callId   - ����Id
              pstSetup - MT��setup��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 MN_CALL_JudgeAllowToSendAlertReq(
    MN_CALL_ID_T                        callId,
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup
)
{
    /*
    if ҵ���ŵ��ѽ��� �� Setup��Ϣ����signal IE
            ����MNCC_ALERTING_REQԭ��
            if ԭ�﷢��ʧ��
                ���������Ϣ, ����
        else
            ����һ����־�����ú������ȴ�ʱ������Alerting��Ϣ
    */
    if ((VOS_TRUE == MN_CALL_GetTchStatus()) || (VOS_TRUE == NAS_IE_IS_PRESENT(&pstSetup->stSignal)))
    {
        MN_NORM_LOG("MN_CALL_ProcMnccSetupInd: ready send alerting.");
        if (VOS_OK != MN_CALL_SendCcAlertReq(callId))
        {
            MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: Failed to send Message Alert.");
            MN_CALL_DeleteCallEntity(callId);
            MN_CALL_FreeCallId(callId);
            return VOS_ERR;
        }
        else
        {
            NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MT_ALERTING, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
        }
    }
    else
    {
        MN_NORM_LOG("MN_CALL_ProcMnccSetupInd: Not ready send alerting.");
        MN_CALL_SetWaitSendAlertStatus(VOS_TRUE, callId);
    }

    return VOS_OK;
}


LOCAL VOS_VOID MN_CALL_SsCdOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_DEFLECT_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_DEFLECT_REJ,
                                       enErrcode);
    }
}


LOCAL VOS_VOID MN_CALL_SsSplitMptyOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{
    VOS_UINT32                          ulNumOfCalls = 0;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT16                          i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        /*���¸ú��е�MPTY״̬Ϊ����MPTY��*/
        MN_CALL_UpdateMptyState(callId, MN_CALL_NOT_IN_MPTY);
        MN_CALL_UpdateCallState(callId, MN_CALL_S_ACTIVE);

        MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfCalls, aCallIds);
        /*����ǰMPTY�еĺ���״̬��Ϊhold״̬*/
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateCallState(aCallIds[i], MN_CALL_S_HELD);
        }
        /* ��ATģ���ϱ�MN_CALL_EVT_HOLD�¼� */
        MN_CALL_ReportHoldEvent(MN_CLIENT_ALL, (VOS_UINT8)ulNumOfCalls, aCallIds);

        /*���²���ҵ������Ľ�չ*/
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF,
                                       enErrcode);
    }
    else
    {
        /*���²���ҵ������Ľ�չ*/
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,
                                       enErrcode);
    }

}
LOCAL VOS_VOID MN_CALL_SsHoldMptyOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{
    VOS_UINT32                          ulNumOfCalls = 0;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT16                          i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        /*���µ�ǰ������MPTY�еĺ��еĺ���״̬ΪHELD*/
        MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfCalls, aCallIds);
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateCallState(aCallIds[i], MN_CALL_S_HELD);
        }

        /* ��ATģ���ϱ�MN_CALL_EVT_HOLD�¼� */
        MN_CALL_ReportHoldEvent(MN_CLIENT_ALL, (VOS_UINT8)ulNumOfCalls, aCallIds);

        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_ON_HOLD);

        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_HOLD_REJ,
                                       enErrcode);
    }

}


LOCAL VOS_VOID MN_CALL_SsRetrieveMptyOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{
    VOS_UINT32                          ulNumOfCalls = 0;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT16                          i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        /* ���µ�ǰ������MPTY�еĺ��еĺ���״̬ΪACTIVE */
        MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfCalls, aCallIds);
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateCallState(aCallIds[i], MN_CALL_S_ACTIVE);
        }

        /* ��ATģ���ϱ�MN_CALL_EVT_RETRIEVE�¼� */
        MN_CALL_ReportRetrieveEvent(MN_CLIENT_ALL, (VOS_UINT8)ulNumOfCalls, aCallIds);

        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                       enErrcode);
    }
}


LOCAL VOS_VOID MN_CALL_SsBuildMptyOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{
    VOS_UINT32                          ulNumOfCalls = 0;
    VOS_UINT16                          i;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;


    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        /* ���µ�ǰ������MPTY�еĺ��еĺ���״̬ΪMPTY */
        MN_CALL_GetCallInfoList((VOS_UINT8*)&ulNumOfCalls, f_astCallInfos);

        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_GetCallState(f_astCallInfos[i].callId,&enCallState,&enMptyState);

            if (MN_CALL_S_HELD == enCallState)
            {
                /* ��ATģ���ϱ�MN_CALL_EVT_RETRIEVE�¼� */
                MN_CALL_ReportRetrieveEvent(MN_CLIENT_ALL, 1, &f_astCallInfos[i].callId);
            }

            if ((MN_CALL_S_INCOMING != enCallState) && (MN_CALL_S_WAITING != enCallState))
            {
               MN_CALL_UpdateMptyState(f_astCallInfos[i].callId, MN_CALL_IN_MPTY);
               MN_CALL_UpdateCallState(f_astCallInfos[i].callId, MN_CALL_S_ACTIVE);
            }
        }
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,
                                       enErrcode);
    }
}


LOCAL VOS_VOID MN_CALL_SsEctOperationProc(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_COMPONENT_UNION         *punComponent,
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode
)
{

    /*���²���ҵ������Ľ�չ*/
    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_ECT_CNF,
                                       enErrcode);
    }
    else
    {
        MN_CALL_UpdateCallSupsProgress(callId,
                                       MN_CALL_SS_PROG_EVT_ECT_REJ,
                                       enErrcode);
    }
}
LOCAL VOS_VOID MN_CALL_SsGetInvokeId(
    MN_CALL_SS_COMPONENT_UNION          *punComponent,
    VOS_UINT8                           *pucInvokeId
)
{

    if (MN_CALL_SS_RETURN_RESULT_TYPE_TAG == punComponent->ucCompType)
    {
        *pucInvokeId = punComponent->resultComp.ucInvokeId;
    }
    else if (MN_CALL_SS_RETURN_ERROR_TYPE_TAG == punComponent->ucCompType)
    {
        *pucInvokeId = punComponent->errorComp.ucInvokeId;
    }
    else
    {
        *pucInvokeId = punComponent->rejectComp.ucInvokeId;
    }
}


VOS_VOID  MN_CALL_ProcSsFacility(
    MN_CALL_ID_T                        callId,
    const NAS_CC_IE_FACILITY_STRU       *pstFacIe
)
{
    MN_CALL_SS_COMPONENT_UNION          unComponent;
    VOS_UINT8                           ucOpCode;
    VOS_UINT8                           ucInvokeId;
    MN_CALL_SS_ERR_CODE_ENUM_U8         enErrcode;
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();

    PS_MEM_SET(&unComponent, 0, sizeof(MN_CALL_SS_COMPONENT_UNION));


    enErrcode = MN_CALL_ERR_SS_UNSPECIFIC;

    /* �ȶ�facility�����ݽ��н��� */
    if (VOS_OK != MN_CALL_FacilityDecode(pstFacIe, &unComponent))
    {
        MN_WARN_LOG("MN_CALL_ProcSsFacility: Facility Decode failed!" );
        return;
    }

    if ((MN_CALL_SS_RETURN_RESULT_TYPE_TAG == unComponent.ucCompType)
      ||(MN_CALL_SS_RETURN_ERROR_TYPE_TAG == unComponent.ucCompType)
      ||(MN_CALL_SS_REJECT_TYPE_TAG == unComponent.ucCompType))
    {
        MN_CALL_SsGetInvokeId(&unComponent, &ucInvokeId);

        if (VOS_TRUE == g_stCallInvokeIdTable[ucInvokeId].bUsed)
        {
            ucOpCode = g_stCallInvokeIdTable[ucInvokeId].ucOperateCode;
            MN_CALL_InvokeId_Free(ucInvokeId);
        }
        else
        {
            MN_ERR_LOG("MN_CALL_ProcSsFacility: Can not find invoke ID.");
            return;
        }
    }
    else
    {
        /*���������invoke����type�����ÿ����쳣����������쳣����ô
          �ڵ��ú���MN_CALL_FacilityDecode��ʱ���Ѿ������쳣��*/
        ucOpCode = unComponent.invokeComp.ucOperateCode;
    }

    /* �����return error����ô�ж�Ӧ��error code��ʹ�������error code�ϱ�*/
    if (MN_CALL_SS_RETURN_ERROR_TYPE_TAG == unComponent.ucCompType)
    {
        enErrcode = unComponent.errorComp.ucErrorCode;
    }

    /* �����return reject����ôʹ��δ����ķ��ض�error code*/
    if (MN_CALL_SS_REJECT_TYPE_TAG == unComponent.ucCompType)
    {
        enErrcode = MN_CALL_ERR_SS_UNSPECIFIC;
    }

    MN_INFO_LOG1("MN_CALL_ProcSsFacility: Operation Code.", ucOpCode);


    switch (ucOpCode)
    {
        case MN_CALL_SS_NOTIFYSS_OPERATION:
            MN_CALL_ProcNotifySs(callId, &unComponent.invokeComp.unArg.notifySsArg);
            break;

        case MN_CALL_SS_CD_OPERATION:
           if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCallDeflectionSupportFlg )
           {
               /*���²���ҵ������Ľ�չ*/
               MN_CALL_SsCdOperationProc(callId, &unComponent, enErrcode);
           }
           break;

        case MN_CALL_SS_REG_CC_ENTRY_OPERATION:
            /*���²���ҵ������Ľ�չ*/
            if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                MN_CALL_SsRegCcEntryProc(callId, &unComponent, enErrcode);
            }
            break;


        case MN_CALL_SS_SPLITMPTY_OPERATION:
            MN_CALL_SsSplitMptyOperationProc(callId, &unComponent, enErrcode);
            break;

        case MN_CALL_SS_RETRIEVEMPTY_OPERATION:
            MN_CALL_SsRetrieveMptyOperationProc(callId, &unComponent, enErrcode);
            break;

        case MN_CALL_SS_HOLDMPTY_OPERATION:
            MN_CALL_SsHoldMptyOperationProc(callId, &unComponent, enErrcode);
            break;

        case MN_CALL_SS_BUILDMPTY_OPERATION:
            MN_CALL_SsBuildMptyOperationProc(callId, &unComponent, enErrcode);
            break;

        case MN_CALL_SS_AOC_OPERATION:
            /*AOC�Ĵ��������ټ���*/
            break;

        case MN_CALL_SS_ECT_OPERATION:
            /*���²���ҵ������Ľ�չ*/
            MN_CALL_SsEctOperationProc(callId, &unComponent, enErrcode);
            break;

        default:
            MN_WARN_LOG("MN_CALL_ProcSsFacility: Operation Code Error!" );
            break;

    }


}


LOCAL VOS_UINT32 MN_CALL_NegotBc(
    VOS_VOID                            *pMsg,
    MN_CALL_ID_T                        ucCallId,
    NAS_CC_IE_BC_STRU                   *pstBc1CallCnf,
    NAS_CC_IE_BC_STRU                   *pstBc2CallCnf,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{
    MNCC_MSG_EST_STRU                   *pstCcEstInd;
    NAS_CC_MSG_SETUP_MT_STRU            *pstMtSetup;
    NAS_CC_IE_BC_STRU                   *pstBc1;
    NAS_CC_IE_BC_STRU                   *pstBc2;

    /* CCBS����ͨ���У����ݽṹ���岻ͬ������ȡ��BC���Բ�ͬ�����ݽṹ���� */
    if (MN_CALL_DIR_CCBS == enCallDir)
    {
        pstCcEstInd = (MNCC_MSG_EST_STRU *)pMsg;
        pstBc1 = &pstCcEstInd->stSetupContainer.stSetup.stBC1;
        pstBc2 = &pstCcEstInd->stSetupContainer.stSetup.stBC2;
    }
    else
    {
        pstMtSetup = (NAS_CC_MSG_SETUP_MT_STRU *)pMsg;
        pstBc1 = &pstMtSetup->stBC1;
        pstBc2 = &pstMtSetup->stBC2;
    }

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc1))
    {
        if (VOS_TRUE == NAS_IE_IS_PRESENT(pstBc2))
        {
            /* BC1�����ڵ�ʱ��BC2��Э�̽����Ϊcall confirm�е�BC1*/
            if ( VOS_FALSE == MN_CALL_NegotBcForCallConf(pstBc2,pstBc1CallCnf))
            {
                NAS_IE_SET_ABSENT(pstBc1CallCnf);
                NAS_IE_SET_ABSENT(pstBc2CallCnf);
            }
            else
            {
                NAS_IE_SET_PRESENT(pstBc1CallCnf);
            }
        }
    }
    else
    {
        /* ����BC1Э�� */
        if (VOS_FALSE == MN_CALL_NegotBcForCallConf(pstBc1,pstBc1CallCnf))
        {
            NAS_IE_SET_ABSENT(pstBc1CallCnf);
        }

        /* ����BC2Э�� */
        if (VOS_TRUE == NAS_IE_IS_PRESENT(pstBc2))
        {
            if (VOS_FALSE == MN_CALL_NegotBcForCallConf(pstBc2,pstBc2CallCnf))
            {
                NAS_IE_SET_ABSENT(pstBc2CallCnf);
                if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc1CallCnf))
                {
                    /*BC1��BC2Э�̶����ɹ��Ļ����ظ�release complete*/
                    MN_CALL_SendCcRejReq(ucCallId, MN_CALL_INCOMPATIBLE_DESTINATION);
                    MN_WARN_LOG("MN_CALL_NegotBc: negotiation BC fail" );
                    MN_CALL_FreeCallId(ucCallId);
                    MN_CALL_DeleteCallEntity(ucCallId);
                    return VOS_ERR;
                }
            }
            else
            {
                /* BC1�����ڵ�ʱ�򣬽�Э�̳���BC2����BC1��ʹ�� */
                if (VOS_FALSE == NAS_IE_IS_PRESENT(pstBc1CallCnf))
                {

                    PS_MEM_CPY(pstBc1CallCnf, pstBc2CallCnf, sizeof(NAS_CC_IE_BC_STRU));

                    NAS_IE_SET_PRESENT(pstBc1CallCnf);
                }
            }
        }
    }
    return VOS_OK;
}



LOCAL VOS_VOID MN_CALL_ProcMnccDisIndWithCcbs(
    const NAS_CC_MSG_DISCONNECT_MT_STRU    *pstDisc,
    VOS_UINT8                               ucCallId
)
{
    if ((VOS_TRUE == NAS_IE_IS_PRESENT(&pstDisc->stCause))
     && (CCA_SS_DIAG_CCBS_POSSIBLE == (pstDisc->stCause.diagnostic[0] & 0x7))
     && (VOS_TRUE == NAS_IE_IS_PRESENT(&pstDisc->stAllowedAct))
     && (NAS_CCBS_ACTIVATION_POSSIBLE == pstDisc->stAllowedAct.Octet3.CCBSActivation))
    {
        MN_CALL_UpdateCallState(ucCallId, MN_CALL_S_CCBS_WAITING_ACTIVE);
        MN_CALL_ReportEvent(ucCallId,MN_CALL_EVT_CCBS_POSSIBLE);
    }

}



LOCAL VOS_VOID MN_CALL_CcbsProcMnccRelCnf(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT8                           ucCallId
)
{
    if (MN_CALL_S_CCBS_WAITING_ACTIVE == enCallState)
    {
        MN_CALL_UpdateCallSupsProgress(ucCallId,
                                       MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                                       MN_CALL_ERR_SS_UNSPECIFIC);
    }
    else if (MN_CALL_S_CCBS_WAITING_RECALL == enCallState)
    {
        /* �ж��Ƿ��Ѿ������к�����ز���ҵ�� */
        if (VOS_FALSE == MN_CALL_IsCallSupsCmdInProgress())
        {
           MN_CALL_UpdateCcbsSupsProgress(ucCallId,
                                          MN_CALL_ERR_SS_UNSPECIFIC,
                                          MN_CALL_SS_RES_FAIL);
        }
    }
    else
    {
        ;
    }

}
VOS_VOID MN_CALL_ProcMnccEstInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{

    MNCC_MSG_EST_STRU                   *pstCcEstInd;
    MN_CALL_ID_T                        callId;
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd;
    NAS_CC_IE_BC_STRU                   stBc1CcEstCnf;
    NAS_CC_IE_BC_STRU                   stBc2CcEstCnf;
    MN_CALL_CC_CAUSE_ENUM_U8            enCause;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;
    MN_CALL_BCD_NUM_STRU                stNumber;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;

    enCause = MN_CALL_INVALID_CAUSE;
    enCallType = MN_CALL_TYPE_VOICE;
    enCallMode = MN_CALL_MODE_SINGLE;
    pstCcEstInd = VOS_NULL_PTR;


    callId = 0;

    MN_CALL_ASSERT( VOS_TRUE != MN_CALL_TiUsedCheck(pstMsg->ucTi) );

    PS_MEM_SET(&stDataCfgInfo, 0, sizeof(stDataCfgInfo));
    PS_MEM_SET(&stNumber, 0, sizeof(stNumber));
    PS_MEM_SET(&stBc1CcEstCnf, 0, sizeof(stBc1CcEstCnf));
    PS_MEM_SET(&stBc2CcEstCnf, 0, sizeof(stBc2CcEstCnf));

    pstCcEstInd = (MNCC_MSG_EST_STRU*)&(pstMsg->unParam.stEstInd);
    /* ���� Call Id */
    (VOS_VOID)MN_CALL_AllocCallId(&callId);

    /* �½�����ʵ��,��д��ʼ�ĺ�����Ϣ,��Щ��Ϣ����Ĭ��ֵ��������ˢ�� */
    MN_CALL_CreateCallEntity(callId, pstMsg->ucTi, MN_CLIENT_ALL,
                             enCallType, enCallMode,
                             MN_CALL_DIR_CCBS, &stDataCfgInfo,
                             &stNumber);

    MN_NORM_LOG1("MN_CALL_ProcMnccEstInd: call id, ", callId);

    /*��cc establishment��Ϣ�е�BC���м��*/
    if (VOS_OK != MN_CALL_BcChkForCallCnf(&pstCcEstInd->stSetupContainer.stSetup,
                                          &stBc1CcEstCnf,
                                          &stBc2CcEstCnf,
                                          &enRepeatInd,
                                          MN_CALL_DIR_CCBS,
                                          callId,
                                          &stDataCfgInfo))
    {
        return;
    }

    /* �ж��������ͺͺ���ģʽ */
    if (VOS_OK != MN_CALL_JudgeMtCallType(
                        &pstCcEstInd->stSetupContainer.stSetup.stBC1.Octet3,
                        &pstCcEstInd->stSetupContainer.stSetup.stBC1.Octet5a,
                        &enCallType))
    {
        MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return;
    }

    if (VOS_OK != MN_CALL_JudgeMtCallMode(
                        &pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd,
                        &pstCcEstInd->stSetupContainer.stSetup.stBC1,
                        &pstCcEstInd->stSetupContainer.stSetup.stBC2,
                        &enCallMode))
    {
        MN_CALL_SendCcRejReq(callId, MN_CALL_INCOMPATIBLE_DESTINATION);
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return;
    }

    /*����ʵ����֮ǰ��������Ҫˢ�º���ģʽ�ͺ�������*/
    MN_CALL_UpdateCallMode(callId, enCallMode);
    MN_CALL_UpdateCallType(callId, enCallType);

    /*��ͨ������BC����Э��, �õ���ҪЯ����CC establishment confirm��Ϣ�е�BC*/
    /* Ŀǰ��֧�ֵ����뷽������ǰ���Ѿ����أ�����ڴ˴����ݲ�����BC1
           �����ڵ�������Ժ��ٶ� */
    if (VOS_OK != MN_CALL_NegotBc(pstCcEstInd, callId, &stBc1CcEstCnf,
                                  &stBc2CcEstCnf,MN_CALL_DIR_CCBS))
    {
        return;
    }

    /* ��ȡ����ҵ���������Ϣ */
    MN_CALL_GetDataCfgInfoForCallCnf(&stBc1CcEstCnf,&stBc2CcEstCnf,enCallType,
                                     enCallMode,&stDataCfgInfo);

    MN_CALL_UpdateDataCallCfgInfo(callId, &stDataCfgInfo);

    /* ��ǰ������������, causeֵ��Ϊ user busy*/
    if ( VOS_TRUE == MN_CALL_CheckNotIdleStateExist() )
    {
        enCause = MN_CALL_USER_BUSY;
    }

    /* �Իظ���RepeatInd���и�ֵ */
    /*enRepeatInd = (VOS_FALSE == NAS_IE_IS_PRESENT(&pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd))?\
                  (VOS_UINT8)MN_CALL_REP_IND_NULL:pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd.RepeatIndication;*/
    if ((VOS_TRUE == NAS_IE_IS_PRESENT(&stBc1CcEstCnf))
     && (VOS_TRUE == NAS_IE_IS_PRESENT(&stBc2CcEstCnf)))
    {
        enRepeatInd = pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd.RepeatIndication;
    }
    else
    {
        enRepeatInd = MN_CALL_REP_IND_NULL;
    }
    /*�ظ�cc establishment confirm��Ϣ*/
    if ( VOS_OK != MN_CALL_SendCcEstCnfReq(callId, enRepeatInd,
                                           &stBc1CcEstCnf, &stBc2CcEstCnf, enCause))
    {
        MN_WARN_LOG("MN_CALL_SendCcEstCnfReq: Failed to send Message cc Establishment cnf.");
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return;
    }
    PS_MEM_CPY(&pstCcEstInd->stSetupContainer.stSetup.stBC1,
               &stBc1CcEstCnf,
               sizeof(stBc1CcEstCnf));
    PS_MEM_CPY(&pstCcEstInd->stSetupContainer.stSetup.stBC2,
               &stBc2CcEstCnf,
               sizeof(stBc2CcEstCnf));

    if (MN_CALL_REP_IND_NULL != enRepeatInd)
    {
        NAS_IE_SET_PRESENT(&pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd);
        pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd.RepeatIndication
                        = enRepeatInd;
    }
    else
    {
        NAS_IE_SET_ABSENT(&pstCcEstInd->stSetupContainer.stSetup.stBCRepeatInd);
    }
    MN_CALL_UpdateCcbsSetup(&pstCcEstInd->stSetupContainer.stSetup);


    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstCcEstInd->stSetupContainer.stSetup.stFacility))
    {
        /* ���������ز���ҵ�� */
        MN_CALL_ProcSsFacility(callId,
                               (NAS_CC_IE_FACILITY_STRU*)&pstCcEstInd->stSetupContainer.stSetup.stFacility);
    }
}



VOS_VOID  MN_CALL_ProcMnccRecallInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{

    /*����״̬,�Ա��û�ѡ����ܻغ���ܾ��غ���,���Ը���MN_CALL_S_CCBS_WAITING_RECALL�ҵ���Ӧ��CallId*/
    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_CCBS_WAITING_RECALL);

    /* ���������ز���ҵ�� */
    MN_CALL_ProcSsFacility(pstMsg->ucCallId,
                           (NAS_CC_IE_FACILITY_STRU*)&pstMsg->unParam.stRecall.stFacility);

}

VOS_BOOL MN_CALL_CheckNvAllowMtCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_CC_CAUSE_ENUM_U8           *penCause
)
{
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfg = VOS_NULL_PTR;
    VOS_UINT8                            ucTafMultiSimCallStatusControl;
    VOS_UINT8                            enVpNvCfgState;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState;

    pstCustomCfg = MN_CALL_GetCustomCfgInfo();


    /* ɾ����causeֵ��ʼ������ */

    /* VSIM��MODEM��NAS��VSIM���Կ��ش򿪣���ܾ����ܱ���ҵ�� */
    if (VOS_TRUE == NAS_VSIM_IsRequireVsimCtrl())
    {
        *penCause = MN_CALL_USER_BUSY;
        return VOS_FALSE;
    }

    /*�����ж����NV������ں���״̬Ϊincoming�Һ�����״̬Ϊ
      TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK�ĺ����򷵻�VOS_FALSE��
      �������µı��� */
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    enCallSubState = TAF_CALL_GetCallSubState(aCallIds[0]);

    if ((VOS_TRUE == TAF_CALL_GetAtaReportOkAsyncFlag())
     && (0 != ulNumOfCalls)
     && (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == enCallSubState))
    {
        return VOS_FALSE;
    }

    ucTafMultiSimCallStatusControl = TAF_CALL_GetMultiSimCallStatusControl();
    enVpNvCfgState                 = TAF_CALL_GetVpCfgState();
    /* Voice���͵ĺ��У�ʹ�õ���gucTafCallStatusControl��gucTafMultiSimCallStatusControl������NV���ֵ */
    if (MN_CALL_TYPE_VOICE == enCallType)
    {

        if ((VOS_TRUE == TAF_CALL_GetCallStatusControl())
            ||(VOS_TRUE == ucTafMultiSimCallStatusControl))
        {
            return VOS_TRUE;
        }


        *penCause = pstCustomCfg->ucVoiceCallNotSupportedCause;

        return VOS_FALSE;
    }
    else if (MN_CALL_TYPE_VIDEO == enCallType)
    {
        /* ���ӵ绰NV����жϣ��ж�˫���MT���������VOS_TRUE */
        if (( MN_CALL_VP_MO_MT_BOTH == enVpNvCfgState )
         || ( MN_CALL_VP_MT_ONLY == enVpNvCfgState ))
        {
            return VOS_TRUE;
        }

        *penCause = pstCustomCfg->ucVideoCallNotSupportedCause;

        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }


}


VOS_UINT8 TAF_CALL_IsMtCallAllowed(
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup,
    VOS_UINT8                           ucCallId,
    MN_CALL_CC_CAUSE_ENUM_U8           *penCause
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT                            i;
    MN_CALL_TYPE_ENUM_U8                enCallType = MN_CALL_TYPE_VOICE;
    MN_CALL_MODE_ENUM_U8                enCallMode = MN_CALL_MODE_SINGLE;
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8    enCcwaCtrlMode;
    VOS_UINT8                           ucCcwaiFlg;

    enCcwaCtrlMode = TAF_CALL_GetCcwaCtrlMode();
    ucCcwaiFlg     = TAF_CALL_GetCcwaiFlg();

   /*�����Ƿ�������ͨ���ĺ��У���������ڽ��еĿ��ӵ绰�������������һ������*/
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    for (i = 0; i < ulNumOfCalls; i++)
    {
        if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(aCallIds[i]))
        {
            *penCause = MN_CALL_USER_BUSY;

            return VOS_FALSE;
        }
    }

    if ((ulNumOfCalls > 0)
     && (TAF_CALL_CCWA_CTRL_BY_IMS == enCcwaCtrlMode)
     && (VOS_FALSE == ucCcwaiFlg))
    {
        *penCause = MN_CALL_USER_BUSY;

        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsEcallRedialExist())
    {
        *penCause = MN_CALL_USER_BUSY;

        return VOS_FALSE;
    }
#endif

    /* �ж��������ͺͺ���ģʽ */
    if (VOS_OK != MN_CALL_JudgeMtCallType(&pstSetup->stBC1.Octet3,
                                          &pstSetup->stBC1.Octet5a,
                                          &enCallType))
    {
        *penCause = MN_CALL_INCOMPATIBLE_DESTINATION;

        return VOS_FALSE;
    }

    /*�ж��Ƿ�����������*/
    if (VOS_FALSE == MN_CALL_CheckNvAllowMtCall(enCallType, penCause))
    {
        return VOS_FALSE;
    }

    if (VOS_OK != MN_CALL_JudgeMtCallMode(&pstSetup->stBCRepeatInd,
                                          &pstSetup->stBC1,
                                          &pstSetup->stBC2,
                                          &enCallMode))
    {

        *penCause = MN_CALL_INCOMPATIBLE_DESTINATION;

        return VOS_FALSE;
    }

    /*����ʵ����֮ǰ��������Ҫˢ�º���ģʽ�ͺ�������*/
    MN_CALL_UpdateCallMode(ucCallId, enCallMode);
    MN_CALL_UpdateCallType(ucCallId, enCallType);

    return VOS_TRUE;
}


VOS_VOID  MN_CALL_ProcMnccSetupInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    NAS_CC_MSG_SETUP_MT_STRU            *pstSetup = VOS_NULL_PTR;
    MN_CALL_ID_T                        callId;
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd;
    NAS_CC_IE_BC_STRU                   stBc1CallCnf;
    NAS_CC_IE_BC_STRU                   stBc2CallCnf;
    MN_CALL_CC_CAUSE_ENUM_U8            enCause = MN_CALL_INVALID_CAUSE;
    MN_CALL_TYPE_ENUM_U8                enCallType = MN_CALL_TYPE_VOICE;
    MN_CALL_MODE_ENUM_U8                enCallMode = MN_CALL_MODE_SINGLE;
    MN_CALL_BCD_NUM_STRU                stNumber;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_INFO_STRU                   stCallInfo;

    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    VOS_BOOL                            bWaitSendAlertStatus;
    MN_CALL_ID_T                        ucCallId;

    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();


    callId = 0;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    PS_MEM_SET(&stCallInfo, 0x00, sizeof(stCallInfo));

    MN_CALL_ASSERT( VOS_TRUE != MN_CALL_TiUsedCheck(pstMsg->ucTi) );

    PS_MEM_SET(&stDataCfgInfo, 0, sizeof(stDataCfgInfo));
    PS_MEM_SET(&stNumber, 0, sizeof(stNumber));
    PS_MEM_SET(&stBc1CallCnf, 0, sizeof(stBc1CallCnf));
    PS_MEM_SET(&stBc2CallCnf, 0, sizeof(stBc2CallCnf));
    PS_MEM_SET(aCallIds, 0, sizeof(aCallIds));

    pstSetup = (NAS_CC_MSG_SETUP_MT_STRU*)&(pstMsg->unParam.stSetup);

    /* �����ز����洦��MT���м����ɺ� */

    /* ���� Call Id */
    (VOS_VOID)MN_CALL_AllocCallId(&callId);

    /* �½�����ʵ��,��д��ʼ�ĺ�����Ϣ,���տڵĺ���ṹת����APIҪ��Ľṹ����Щ��Ϣ����Ĭ��ֵ��������ˢ�� */
    MN_CALL_CreateMtCallEntity(callId, pstMsg->ucTi, pstSetup);

    MN_NORM_LOG1("MN_CALL_ProcMnccSetupInd: call id, ", callId);

    /*��call confirm��Ϣ�е�BC���м��*/
    if (VOS_OK != MN_CALL_BcChkForCallCnf(pstSetup,
                                      &stBc1CallCnf,
                                      &stBc2CallCnf,
                                      &enRepeatInd,
                                      MN_CALL_DIR_MT,
                                      callId,
                                      &stDataCfgInfo))
    {

#if (FEATURE_ON == FEATURE_PTM)
        /* setup��Ϣ��Э����ʧ�ܵ��쳣��¼ */
        MN_CALL_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_BC_CHECK_FAIL);
#endif

        return;
    }

    if (VOS_FALSE == TAF_CALL_IsMtCallAllowed(pstSetup, callId, &enCause))
    {
        MN_CALL_SendCcRejReq(callId, enCause);
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);

#if (FEATURE_ON == FEATURE_PTM)
        /* setup��Ϣ��Э����ʧ�ܵ��쳣��¼ */
        MN_CALL_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_MT_CALL_NOT_ALLOW);
#endif

        return;
    }

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    /* ��������ط������ʱ�������У����л����mncc rej ind��Ϣ���ϱ�����ʧ�ܣ�
       ���ٽ����ط�����Ӧ����*/
    MN_CALL_GetCallState(pstBufferdMsg->stBufferedSetupMsg.ucCallId, &enCallState, &enMptyState);

    if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(pstBufferdMsg->stBufferedSetupMsg.ucCallId))
     && (MN_CALL_S_DIALING           == enCallState))
    {
        TAF_CALL_StopAllRedialTimers(pstBufferdMsg->stBufferedSetupMsg.ucCallId);

        /* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
        if (VOS_TRUE == pstBufferdMsg->bitOpBufferedRejIndMsg)
        {
            TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg,
                pstBufferdMsg->stBufferedRejIndMsg.unParam.enCause);
        }
        else if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
        {
            TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg,
                TAF_CS_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
        }
        else
        {
            ;
        }
        /* Modified by zwx247453 for CHR optimize, 2015-07-07, end */
    }

    /*��ͨ������BC����Э��, �õ���ҪЯ����Call Confirm��Ϣ�е�BC*/
    /* Ŀǰ��֧�ֵ����뷽������ǰ���Ѿ����أ�����ڴ˴����ݲ�����BC1
       �����ڵ�������Ժ��ٶ� */
    if (VOS_OK != MN_CALL_NegotBc(pstSetup, callId, &stBc1CallCnf,
                                  &stBc2CallCnf,MN_CALL_DIR_MT))
    {
        /*BC1��BC2Э�̾�ʧ��*/

#if (FEATURE_ON == FEATURE_PTM)
        /* setup��Ϣ��Э����ʧ�ܵ��쳣��¼ */
        MN_CALL_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_NE_GET_BC_FAIL);
#endif

        return;
    }

    /* ��ȡ����ҵ���������Ϣ */
    MN_CALL_GetDataCfgInfoForCallCnf(&stBc1CallCnf,&stBc2CallCnf,enCallType,enCallMode,&stDataCfgInfo);

    MN_CALL_UpdateDataCallCfgInfo(callId, &stDataCfgInfo);

    /* ��ǰ������������, causeֵ��Ϊ user busy*/
    if ( VOS_TRUE == MN_CALL_CheckNotIdleStateExist() )
    {
        enCause = MN_CALL_USER_BUSY;
    }

    /* �Իظ���RepeatInd���и�ֵ */
    enRepeatInd = (VOS_FALSE == NAS_IE_IS_PRESENT(&pstSetup->stBCRepeatInd))?\
            (VOS_UINT8)MN_CALL_REP_IND_NULL:pstSetup->stBCRepeatInd.RepeatIndication;



    /* �ظ�call confirm */
    if ( VOS_OK != MN_CALL_SendCcCallConfReq(callId, enRepeatInd,
                                             &stBc1CallCnf, &stBc2CallCnf, enCause))
    {
        MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: Failed to send Message CallConf.");
        MN_CALL_FreeCallId(callId);
        MN_CALL_DeleteCallEntity(callId);
        return;
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MT_ATTEMPT, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    /* �˴��������Ƶ����洦�� */

    /*ˢ�µ�ǰ�ĺ���״̬*/
    MN_CALL_UpdateCallStateForCallCnf(callId);


    /* ���Setup��Ϣ��û�жԷ����룬���º��й���ģ���б����NoCliCause */
    if (VOS_FALSE == NAS_IE_IS_PRESENT(&pstSetup->stCallingNum))
    {
        MN_CALL_UpdateNoCliCause(callId, MN_CALL_NO_CLI_USR_REJ);
    }

    if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {
        /* �㲥����(INCOMING)�¼�,��Ҫ��������·1�����绹����·2������ */
        if ( (VOS_TRUE == NAS_IE_IS_PRESENT(&pstSetup->stBC1))
          && (NAS_CC_ITC_AUXILIARY_SPEECH == pstSetup->stBC1.Octet3.InfoTransCap))
        {
            MN_CALL_UpdateAlsLineNbr(callId, MN_CALL_ALS_LINE_NO_2);
        }
        else
        {
            MN_CALL_UpdateAlsLineNbr(callId, MN_CALL_ALS_LINE_NO_1);
        }

    }


    if (VOS_OK != MN_CALL_JudgeAllowToSendAlertReq(callId, pstSetup))
    {
        return;
    }

    MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &ucCallId);

    if (VOS_FALSE == bWaitSendAlertStatus)
    {
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_INCOMING);

        MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_NOLOOP);
    }

    MN_CALL_SndStkMtCallEvent(callId, pstMsg->ucTi);


    MN_CALL_GetCallInfoByCallId(callId, &stCallInfo);

    /* ��CALL����Alert req������RING��ʱ��, ɾ���˴��߼� */

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstSetup->stFacility))
    {
        /* ���������ز���ҵ�� */
        MN_CALL_ProcSsFacility(callId, (NAS_CC_IE_FACILITY_STRU*)&pstSetup->stFacility);
    }

    /* UUS1����,���ϱ�UUS1��Ϣ */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstSetup->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(callId,NAS_CC_MSG_SETUP,&pstSetup->stUserUser);
        /* UUS1��Ϣ�ϱ� */
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_UUS1_INFO);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
    {
        /* ���T9��ʱ�������У����º�������ΪPSAP�غ�eCall���� */
        MN_CALL_UpdateCallType(callId, MN_CALL_TYPE_PSAP_ECALL);
    }
#endif

}
VOS_VOID  MN_CALL_ProcMnccSetupCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    const NAS_CC_MSG_CONNECT_MT_STRU    *pstConn;
    MN_CALL_BCD_NUM_STRU                stConnNumber;

    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    PS_MEM_SET(&stConnNumber, 0, sizeof(MN_CALL_BCD_NUM_STRU));

    /* ��ȡ��ǰ����״̬*/
    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( (MN_CALL_S_DIALING == enCallState)
              || (MN_CALL_S_ALERTING == enCallState));

    pstConn = &pstMsg->unParam.stConn;

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstConn->stConnectedNum))
    {
        /* ���º�����Ϣ�е�Connect number */
        stConnNumber.ucNumLen =
            (VOS_UINT8)NAS_IE_GET_BLOCK_SIZE(&pstConn->stConnectedNum, BCDNum);
        PS_MEM_CPY(stConnNumber.aucBcdNum,
                   pstConn->stConnectedNum.BCDNum,
                   stConnNumber.ucNumLen);

        stConnNumber.enNumType = *((VOS_UINT8*)&pstConn->stConnectedNum.Octet3);

        MN_CALL_UpdateConnNumber(pstMsg->ucCallId, &stConnNumber);
    }

    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_ACTIVE);

    /* ֪ͨcall status nty */
    TAF_CALL_SendCcCallStatusNty(pstMsg->ucCallId, MNCC_CALL_STATUS_SETUP_SUCC);


    if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
     && (pstMsgBuff->stBufferedSetupMsg.ucCallId == pstMsg->ucCallId))

    {
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
        {
            TAF_CALL_ProcessEcallPeriodTimerLen(pstMsg->ucCallId);
        }
        else
#endif
        {
            MN_CALL_ClearBufferedMsg();
        }

        TAF_CALL_StopAllRedialTimers(pstMsg->ucCallId);
    }

    /*����ǿ��ӵ绰��֪ͨCSTģ�齨��ͨ��*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
    {
        MN_CALL_SendCstSetupReqMsg(pstMsg->ucCallId);
        MN_CALL_StartTimer(MN_CALL_TID_WAIT_CST_SETUP, 0, 0, VOS_RELTIMER_NOLOOP);
    }

    if (VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* ������Ϣ֪ͨVC������ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
            TAF_CALL_SetSrvccLocalAlertedFlagByCallId(pstMsg->ucCallId, VOS_FALSE);
        }
    }
    MN_CALL_StartFluxCalculate(pstMsg->ucCallId);
    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_CONNECT);

    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MO_ANSWERED, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    MN_CALL_UpdateTi(pstMsg->ucCallId, pstMsg->ucTi);

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstConn->stFacility))
    {
        /* ���������ز���ҵ�� */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstConn->stFacility);
    }

    /* UUS1����,���ϱ�UUS1��Ϣ */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstConn->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,NAS_CC_MSG_CONNECT,(NAS_CC_IE_USER_USER_STRU*)&pstConn->stUserUser);
        /* UUS1��Ϣ�ϱ� */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    MN_CALL_SndStkCallConnEvent(pstMsg->ucTi, MN_CALL_DIR_MO);

#if (FEATURE_ON == FEATURE_ECALL)
    /* ����eCall�������*/
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
    {
        /* ����T2��ʱ�� */
        MN_CALL_StartTimer(TAF_CALL_TID_T2, 0, 0, VOS_RELTIMER_NOLOOP);

        /* ����MN_CALL_EVT_CHANNEL_CONNECT֪ͨVC�����Խ���MSD���� */
        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CONNECT);

        if (MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
        {
            /* ���õȴ�MT eCall��־ */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_TRUE);
        }
    }
#endif

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    MN_CALl_VoicePreferJudgeVoiceCallExist();
#endif
}



VOS_VOID MN_CALL_ProcMnccSetupComplInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfCalls;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSysAppConfig;
    VOS_UINT32                          ulLength;

    ulLength               = 0;
    enCallState            = MN_CALL_S_BUTT;
    enMptyState            = MN_CALL_MPYT_STATE_BUTT;
    ulNumOfCalls           = 0;
    stSysAppConfig.usSysAppConfigType = SYSTEM_APP_BUTT;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_ACTIVE);

    /* ֪ͨcall status nty */
    TAF_CALL_SendCcCallStatusNty(pstMsg->ucCallId, MNCC_CALL_STATUS_SETUP_SUCC);


    /* ���incoming״̬�ĺ�����״̬Ϊnull */
    TAF_CALL_SetCallSubState(pstMsg->ucCallId, TAF_CALL_SUB_STATE_NULL);

    if(VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* ������Ϣ֪ͨVC������ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MT_ANSWERED, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* ���²���ҵ������Ľ�չ(CCA_SS_PROG_EVT_SETUP_COMPL) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);
    /*��ȡ��ǰ���ں��еĸ���,����1������²����ϱ�MN_CALL_EVT_CONNECT�¼�*/
    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    if (1 == ulNumOfCalls)
    {
        /*����ǿ��ӵ绰��֪ͨCSTģ�齨��ͨ��*/
        if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
        {
            MN_CALL_SendCstSetupReqMsg(pstMsg->ucCallId);
            MN_CALL_StartTimer(MN_CALL_TID_WAIT_CST_SETUP, 0, 0, VOS_RELTIMER_NOLOOP);
        }
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_CONNECT);
    }
    /* Ϊ�˱���Ӱ��MBB��Ʒ��(����ȷ���Ƿ�Ӱ��)��ֻ�ϱ�һ��^CONN��^CCALLSTATE */
    else
    {
        (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);

        if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                             &stSysAppConfig, ulLength))
        {
            stSysAppConfig.usSysAppConfigType = SYSTEM_APP_MP;
            MN_WARN_LOG("MN_CALL_ProcMnccSetupComplInd():Read en_NV_Item_System_APP_Config Failed!");
        }

        if (SYSTEM_APP_ANDROID == stSysAppConfig.usSysAppConfigType)
        {
            MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_CONNECT);
        }
    }
    MN_CALL_StartFluxCalculate(pstMsg->ucCallId);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    MN_CALl_VoicePreferJudgeVoiceCallExist();
#endif

#if (FEATURE_ON == FEATURE_ECALL)
    /* ����eCall�������*/
    if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
    {
        /* ֹͣT9��ʱ�� */
        MN_CALL_StopTimer(TAF_CALL_TID_T9);

        /* ����T2��ʱ�� */
        MN_CALL_StartTimer(TAF_CALL_TID_T2, 0, 0, VOS_RELTIMER_NOLOOP);

        /* ����CALL_VC_CHANNEL_CONNECT֪ͨVC�����Խ���MSD���� */
        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CONNECT);

        /* ���º�������ΪPSAP�غ� */
        MN_CALL_UpdateCallType(pstMsg->ucCallId, MN_CALL_TYPE_PSAP_ECALL);
    }
#endif
}
VOS_VOID  MN_CALL_ProcMnccCallProcInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    NAS_CC_MSG_CALL_PROC_STRU           *pstCallProc;
    MN_CALL_MODE_ENUM_U8                enCallMode = MN_CALL_MODE_SINGLE;
    MN_CALL_TYPE_ENUM_U8                enCallType = MN_CALL_TYPE_VOICE;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_INFO_STRU                   stCallInfo;

    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;
    PS_MEM_SET(&stCallInfo, 0x00, sizeof(stCallInfo));

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);
    MN_CALL_UpdateTi(pstMsg->ucCallId, pstMsg->ucTi);

    MN_CALL_ASSERT( MN_CALL_S_DIALING == enCallState);

    pstCallProc = (NAS_CC_MSG_CALL_PROC_STRU*)&pstMsg->unParam.stCallProc;

    MN_CALL_GetCallInfoByCallId(pstMsg->ucCallId, &stCallInfo);
    enCallType = stCallInfo.enCallType;
    enCallMode = stCallInfo.enCallMode;

    /* �ж��������ͺͺ���ģʽ������ˢ�� */
    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstCallProc->stBC1))
    {
        if (VOS_OK == MN_CALL_JudgeMtCallType(&pstCallProc->stBC1.Octet3,
                                           &pstCallProc->stBC1.Octet5a,
                                           &enCallType))
        {
            MN_CALL_UpdateCallType(pstMsg->ucCallId, enCallType);
        }
    }

    if (VOS_OK == MN_CALL_JudgeMtCallMode(&pstCallProc->stRepeatInd,
                                       &pstCallProc->stBC1,
                                       &pstCallProc->stBC2,
                                       &enCallMode))
    {
        MN_CALL_UpdateCallMode(pstMsg->ucCallId, enCallMode);
    }


    /*��ȡָ�����е����ݺ���������Ϣ*/
    MN_CALL_GetDataCallCfgInfo(pstMsg->ucCallId, &stDataCfgInfo);
    /* ���ݺ��У���BC1��ȡ�ٶ� */
    if (((MN_CALL_TYPE_CS_DATA == enCallType) || (MN_CALL_TYPE_FAX == enCallType))
      &&(VOS_TRUE == NAS_IE_IS_PRESENT(&pstCallProc->stBC1)))
    {
        MN_CALL_GetDataCfgInfoFromBc(&pstCallProc->stBC1, &stDataCfgInfo);
    }
    /* ������������棬���BC2�л�ȡ */
    else
    {
        if (( MN_CALL_MODE_AVF == enCallMode )
          &&( VOS_TRUE == NAS_IE_IS_PRESENT(&pstCallProc->stBC2)))
        {
            MN_CALL_GetDataCfgInfoFromBc(&pstCallProc->stBC2, &stDataCfgInfo);
        }
    }


    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_CALL_PROC);

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstCallProc->stFacility))
    {
        /* ���������ز���ҵ�� */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstCallProc->stFacility);
    }

    if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
     && (pstMsgBuff->stBufferedSetupMsg.ucCallId == pstMsg->ucCallId))
    {
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
        {
            TAF_CALL_ProcessEcallPeriodTimerLen(pstMsg->ucCallId);
        }
        else
#endif
        {
            MN_CALL_ClearBufferedMsg();
        }

        TAF_CALL_StopAllRedialTimers(pstMsg->ucCallId);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
    {
        if (MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
        {
            /* ���õȴ�MT eCall��־ */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_TRUE);
        }
    }
#endif
}



VOS_VOID  MN_CALL_ProcMnccSyncInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    VOS_BOOL                            bWaitSendAlertStatus;
    VOS_BOOL                            bResult = VOS_FALSE;
    VOS_UINT8                           uccallId;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfCalls;

    PS_MEM_SET(aCallIds, 0, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    if (VOS_TRUE == pstMsg->unParam.stSyncInd.ulTchAvail)
    {
#if (FEATURE_ON == FEATURE_IMS)
        TAF_CALL_ProcSrvccSyncInfo();
#endif

        if (VOS_FALSE == MN_CALL_GetTchStatus())
        {
            /*����ҵ���ŵ�������־*/
            MN_CALL_SetTchStatus(VOS_TRUE);
            (VOS_VOID)MN_CALL_SetTchPara(&(pstMsg->unParam.stSyncInd), pstMsg->ucCallId);
            MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &uccallId);
            if (VOS_TRUE == bWaitSendAlertStatus)
            {
                MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, 0);
                if (VOS_OK != MN_CALL_SendCcAlertReq(uccallId))
                {
                    MN_WARN_LOG("MN_CALL_ProcMnccSetupInd: Failed to send Message Alert.");
                    MN_CALL_FreeCallId(uccallId);
                    return;
                }

                MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_INCOMING);
                /* ����RING��ʱ�� */
                MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_NOLOOP);
            }

            /*��ʱΪGSM����ָ�������޸ģ����������������֮��ҵ���ŵ���׼����*/
            MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

            if (MN_CALL_S_ACTIVE == enCallState)
            {
                if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
                {
                    /* ������Ϣ֪ͨVC������ͨ�� */
                    MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                    /* ������Ϣ֪ͨAT����ͨ��״̬ */
                    MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);

                    MN_CALL_SetChannelOpenFlg(VOS_TRUE);
                }
            }

            if (MN_CALL_S_ALERTING == enCallState)
            {
                if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
                {
                    if (VOS_FALSE == TAF_CALL_GetSrvccLocalAlertedFlagByCallId(pstMsg->ucCallId))
                    {
                        /* ������Ϣ֪ͨVC������ͨ�� */
                        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                        /* ������Ϣ֪ͨAT����ͨ��״̬ */
                        MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);

                        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
                    }
                }
            }

        }
        else
        {
            bResult = MN_CALL_SetTchPara(&(pstMsg->unParam.stSyncInd), pstMsg->ucCallId);

            if ((VOS_TRUE == MN_CALL_GetChannelOpenFlg()) && (VOS_TRUE == bResult))
            {
                /* ������Ϣ֪ͨVC����ͨ�����øı� */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_PARA_CHANGE);
                /* ������Ϣ֪ͨAT����ͨ��״̬ */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_PARA_CHANGE);

                return;
            }
        }
    }
    else
    {
        if (VOS_TRUE == MN_CALL_GetTchStatus())
        {
            if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
            {
                /* ������Ϣ֪ͨVC�ر�����ͨ�� */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
                /* ������Ϣ֪ͨAT����ͨ��״̬ */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
                MN_CALL_SetChannelOpenFlg(VOS_FALSE);
            }

            /* �����ǰ���еȴ��ĺ��У���ʱ�п�����Ҫ�ر�������������ҵ��
               �ŵ���Ȼ���ڣ���Ҫ��ʱ��Ҫ���ҵ���ŵ������ı�־ */
            MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
            if (0 == ulNumOfCalls)
            {
                /* ���ҵ���ŵ�������־ */
                MN_CALL_SetTchStatus(VOS_FALSE);
            }

        }
    }


}
VOS_VOID  MN_CALL_ProcMnccAlertInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    const NAS_CC_MSG_ALERTING_MT_STRU   *pstAlert;

    MN_CALL_CHANNEL_INFO_STRU           stChannelInfo;

    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);
    MN_CALL_UpdateTi(pstMsg->ucCallId, pstMsg->ucTi);

    MN_CALL_ASSERT( MN_CALL_S_DIALING == enCallState);

    pstAlert = &pstMsg->unParam.stAlert;

    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_ALERTING);

    /* ������緢��ALERTING��Ϣ����ʱ����������������緢����Ҫ��A progress indicator
       IE indicates user attachment if it specifies a progress description in the set {1�� 2�� 3}
       or in the set {6�� 7�� 8�� ...�� 20}. ������ʱͨ��^CSCHANNELINFO:0֪ͨAP����б���������� */
    if (VOS_TRUE == TAF_CALL_IsNeedLocalAlerting(&(pstAlert->stProgInd)))
    {
        PS_MEM_SET(&stChannelInfo, 0, sizeof(stChannelInfo));
        MN_CALL_SndAtChannelInfoInd(MN_CALL_EVT_CHANNEL_LOCAL_ALERTING, &stChannelInfo, VOS_TRUE);
    }
    else
    {
        if (VOS_TRUE == MN_CALL_GetTchStatus())
        {
            if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
            {
                /* ������Ϣ֪ͨVC������ͨ�� */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                /* ������Ϣ֪ͨAT����ͨ��״̬ */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            }
            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
        }
    }


    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_ALERTING);

    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MO_ALERTING, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstAlert->stFacility))
    {
        /* ���������ز���ҵ�� */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstAlert->stFacility);
    }

    /* UUS1����,���ϱ�UUS1��Ϣ */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstAlert->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_ALERTING,
                                  (NAS_CC_IE_USER_USER_STRU*)&pstAlert->stUserUser);
        /* UUS1��Ϣ�ϱ� */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
     && (pstMsgBuff->stBufferedSetupMsg.ucCallId == pstMsg->ucCallId))
    {
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
        {
            TAF_CALL_ProcessEcallPeriodTimerLen(pstMsg->ucCallId);
        }
        else
#endif
        {
            MN_CALL_ClearBufferedMsg();
        }

        TAF_CALL_StopAllRedialTimers(pstMsg->ucCallId);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
    {
        if (MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
        {
            /* ���õȴ�MT eCall��־ */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_TRUE);
        }
    }
#endif
}
VOS_VOID  MN_CALL_ProcMnccDiscInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    const NAS_CC_MSG_DISCONNECT_MT_STRU *pstDisc;
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulTchStatus;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_IDLE != enCallState);

    pstDisc = &pstMsg->unParam.stDisc;

    ulTchStatus = MN_CALL_GetTchStatus();

    if ((VOS_TRUE == ulTchStatus)
     && (VOS_TRUE == pstDisc->stProgInd.IsExist)
     && ( ( (pstDisc->stProgInd.Octet4.ProgDesc >= 1)
          && (pstDisc->stProgInd.Octet4.ProgDesc <= 3))
       || ( (pstDisc->stProgInd.Octet4.ProgDesc >= 6)
          && (pstDisc->stProgInd.Octet4.ProgDesc <= 20))))
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* ������Ϣ֪ͨVC������ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    /* �����·�disconnectʱ��cc���ȹ���mncc_sync_ind(ulTchAvail:false), ���ϱ�mncc_disc_ind��CALL,
       CALL���յ�mncc_disc_ind,TCHһ���ǲ����õģ������޷��жϳ�֮ǰTCH�Ƿ���ù����˴�ɾ���ϱ�ԭ��ֵTAF_CS_CAUSE_CC_INTER_ERR_NO_TCH
       ���ܾ�ȷ��:�˴�������Disconnect��Ϣ�����ԭ��ֵ,�������û��ԭ��ֵ��Ĭ��ֵ#16 */
    if (VOS_TRUE    == pstDisc->stCause.IsExist)
    {
        MN_CALL_UpdateCcCause(pstMsg->ucCallId, pstDisc->stCause.Octet4.CauseValue );
    }
    else
    {
        MN_CALL_UpdateCcCause(pstMsg->ucCallId, TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING);
    }

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(pstMsg->ucCallId, VOS_FALSE);

#if (FEATURE_ON == FEATURE_PTM)
    MN_CALL_CsCallDiscInfoRecord(pstMsg->ucCallId, MN_CALL_GetCsCause(pstMsg->ucCallId));
#endif

    /*���޸�״̬����ʱ��Ϊ���ı�״̬�Ļ���������Ӱ��*/

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstDisc->stFacility))
    {
        /* ���������ز���ҵ�� */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId,
                               (NAS_CC_IE_FACILITY_STRU*)&pstDisc->stFacility);
    }

    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        MN_CALL_ProcMnccDisIndWithCcbs(pstDisc, pstMsg->ucCallId);
    }

    /* UUS1����,���ϱ�UUS1��Ϣ */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstDisc->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_DISCONNECT,
                                  (NAS_CC_IE_USER_USER_STRU *)&pstDisc->stUserUser);
        /* UUS1��Ϣ�ϱ� */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    /* �·�CALL DISCONNECT EVENT��USIMģ�� */
    MN_CALL_SndStkCallDiscEvent(pstMsg, pstMsg->enPrimName, VOS_TRUE);

}


VOS_VOID TAF_CALL_ProcCallAllReleased(
    const MNCC_IND_PRIM_MSG_STRU       *pstMsg
)
{
    VOS_UINT8                           ucCallId;
    VOS_BOOL                            bWaitSendAlertStatus;

    if (VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
        {
            /* ������Ϣ֪ͨVC�ر�����ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
        }
        MN_CALL_SetTchStatus(VOS_FALSE);
        MN_CALL_SetChannelOpenFlg(VOS_FALSE);
    }

    MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &ucCallId);

    if ((VOS_TRUE == bWaitSendAlertStatus))
    {
        MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, 0);
    }

    /* �����ǰû�к��У��ϱ����к��ж���RELEASED */
    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_ALL_RELEASED);

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_GetInternalHangUpFlag())
    {
        TAF_CALL_SetInternalHangUpFlag(VOS_FALSE);
        /* client ID��op ID��SPM�в�care, ��д0 */
        TAF_CALL_SendTafRelCallCnf(0, 0, TAF_CS_CAUSE_SUCCESS);
    }
#endif
}


VOS_VOID TAF_CALL_ProcCallCause(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucCauseExistFlag,
    MN_CALL_CC_CAUSE_ENUM_U8            enCallCause
)
{
    /* ���±���ԭ��ֵ */
    if (VOS_TRUE == ucCauseExistFlag)
    {
        /* �ȼ�¼�����쳣��CHR��ԭ��ֵʹ�ñ����쳣��ԭ��ֵ */
#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        if (0 != enCallCause)
        {
            MN_CALL_CsCallErrRecord(ucCallId, enCallCause);
        }
        else
        {
            MN_CALL_CsCallErrRecord(ucCallId, TAF_CS_CAUSE_UNKNOWN);
        }
#endif

        /* ���ԭ�����Ѿ����쳣ԭ���򱾴ε��쳣������ԭ��ֵ */
        if (MN_CALL_INVALID_CAUSE == MN_CALL_GetCsCause(ucCallId))
        {
            MN_CALL_UpdateCcCause(ucCallId, enCallCause);
        }
    }
    else
    {
#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(ucCallId, MN_CALL_GetCsCause(ucCallId));
#endif
    }

}
VOS_VOID TAF_CALL_ProcCallRedialAfterCallRel(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;

    pstMsgBuff = MN_CALL_GetBufferedMsg();

    if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
     && (ucCallId == pstMsgBuff->stBufferedSetupMsg.ucCallId))
    {
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
        {
            TAF_CALL_ProcessEcallPeriodTimerLen(ucCallId);
        }
        else
#endif
        {
            MN_CALL_ClearBufferedMsg();
        }

        TAF_CALL_StopAllRedialTimers(ucCallId);
    }
}



VOS_VOID  MN_CALL_ProcMnccRelInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    const NAS_CC_MSG_RELEASE_MT_STRU   *pstRel;
    VOS_UINT8                           ucNumOfCalls;
#if (FEATURE_ON == FEATURE_ECALL)
    MN_CALL_MGMT_STRU                   stCallEntity;
#endif
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    MN_CALL_ID_T                        ucDtmfCallId;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;

    ucDtmfCallId = 0;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_IDLE != enCallState);

    pstRel = &pstMsg->unParam.stRel;

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstRel->stFacility))
    {
        /* ���������ز���ҵ�� */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstRel->stFacility);
    }

    /*CCBS���ʱ���û�û����Ӧ�����෢release��Ϣ��causeΪ102:recovery on timer expiry,�ϱ�CCBS����ʧ���¼�*/
    if ( (MN_CALL_S_CCBS_WAITING_ACTIVE == enCallState)
       &&(MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg))
    {
        MN_CALL_UpdateCcbsSupsProgress(pstMsg->ucCallId,
                                       MN_CALL_ERR_SS_UNSPECIFIC,
                                       MN_CALL_SS_RES_FAIL);
    }

    /*����ǿ��ӵ绰����CST�ѽ�����ҵ���ŵ���֪ͨCSTģ���ͷ�*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
    {
        if (VOS_TRUE == MN_CALL_GetVideoCallChannelOpenFlg(pstMsg->ucCallId))
        {
            MN_CALL_SendCstRelReqMsg(pstMsg->ucCallId);
        }
    }

    /* ��Ҫ��ͳ��ͨ��ʱ�䣬���ϱ�RELEASED�¼� */
    MN_CALL_StopFluxCalculate(pstMsg->ucCallId);

    /* һ������� RELEASE��Ϣֻ��Я��һ��Causeֵ��ֻ����24.008 5.4.4.1.2.3
    �½���������������Ż������Causeֵ��Ŀǰ��ʱ���������������ֻȡ��һ�� */
    /* �����Ϣ��Я����Cause����ô����Causeֵ */
    /* ����ԭ��ֵ����MN_CALL_EVT_RELEASEDǰ�棬����release�¼������ԭ��ֵ���ܲ��� */
    TAF_CALL_ProcCallCause(pstMsg->ucCallId,
                           NAS_IE_IS_PRESENT(&pstRel->stCause),
                           pstRel->stCause.Octet4.CauseValue);

    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_RELEASED);


    TAF_CALL_ProcCallStatusFail(pstMsg->ucCallId, enCallState);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(pstMsg->ucCallId, VOS_FALSE);


    /* �绰�Ҷ�ʱ������Ӧ���¼������������������ǿ�ָ�룬���ĸ�����������0�������¼�������ȥ */
    enCause = MN_CALL_GetCsCause(pstMsg->ucCallId);

    if(MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(pstMsg->ucCallId))
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }

    /* ���²���ҵ������Ľ�չ(CCA_SS_PROG_EVT_REL) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_REL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    TAF_CALL_ProcRelCallSsKeyEvent(pstMsg->ucCallId);

    TAF_CALL_ProcCallRedialAfterCallRel(pstMsg->ucCallId);

#if (FEATURE_ON == FEATURE_ECALL)
    /* ��call id�ͷ�֮ǰ����ȡ��ǰCALL ID����ʵ����Ϣ������ʹ�� */
    PS_MEM_SET(&stCallEntity, 0, sizeof(MN_CALL_MGMT_STRU));
    (VOS_VOID)MN_CALL_GetSpecificCallInfo(pstMsg->ucCallId, &stCallEntity);
#endif

    MN_CALL_FreeCallId(pstMsg->ucCallId);

    MN_CALL_GetCallInfoList(&ucNumOfCalls, f_astCallInfos);

    if (0 == ucNumOfCalls)
    {
        TAF_CALL_ProcCallAllReleased(pstMsg);
    }

    /* UUS1����,���ϱ�UUS1��Ϣ */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstRel->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_RELEASE,
                                  (NAS_CC_IE_USER_USER_STRU *)&pstRel->stUserUser);
        /* UUS1��Ϣ�ϱ� */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    /* �·�CALL DISCONNECT EVENT��USIMģ�� */
    MN_CALL_SndStkCallDiscEvent(pstMsg, pstMsg->enPrimName, VOS_TRUE);


    enCause = TAF_CALL_GetAllowedDtmfCallId(&ucDtmfCallId);
    if (enCause != TAF_CS_CAUSE_SUCCESS)
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_RELEASE);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    TAF_CALL_ProcEcallRel(&stCallEntity);
#endif

    return;

}



VOS_VOID  MN_CALL_ProcMnccRelCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8                                   enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8                              enMptyState;
    const NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU              *pstRelComp;
    VOS_UINT8                                               ucNumOfCalls;
    MN_CALL_CUSTOM_CFG_INFO_STRU                           *pstCustomCfgAddr;

    MN_CALL_ID_T                                            ucDtmfCallId;
    TAF_CS_CAUSE_ENUM_UINT32                                enCause;
#if (FEATURE_ON == FEATURE_ECALL)
    MN_CALL_MGMT_STRU                                       stCallEntity;
#endif

    ucDtmfCallId = 0;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_IDLE != enCallState);

    pstRelComp = &pstMsg->unParam.stRelComp;

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(pstMsg->ucCallId, VOS_FALSE);

    if (VOS_TRUE == NAS_IE_IS_PRESENT(&pstRelComp->stFacility))
    {
        /* ���������ز���ҵ�� */
        MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstRelComp->stFacility);
    }
    else
    {
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            /*�û�û����Ӧ�����෢release complete��Ϣ��causeΪ102:recovery on timer expiry,�ϱ�CCBS�غ�ʧ���¼�*/
            MN_CALL_CcbsProcMnccRelCnf(enCallState, pstMsg->ucCallId);
        }

    }


    /*����ǿ��ӵ绰��֪ͨCSTģ���ͷ�*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
    {
        if (VOS_TRUE == MN_CALL_GetVideoCallChannelOpenFlg(pstMsg->ucCallId))
        {
            MN_CALL_SendCstRelReqMsg(pstMsg->ucCallId);
        }
    }

    /* ��Ҫ��ͳ��ͨ��ʱ�䣬���ϱ�RELEASED�¼� */
    MN_CALL_StopFluxCalculate(pstMsg->ucCallId);

    /* ����ԭ��ֵ����MN_CALL_EVT_RELEASEDǰ�棬����release�¼������ԭ��ֵ���ܲ��� */
    TAF_CALL_ProcCallCause(pstMsg->ucCallId,
                           NAS_IE_IS_PRESENT(&pstRelComp->stCause),
                           pstRelComp->stCause.Octet4.CauseValue);

    /*�ȴ��������ز���ҵ�����ϱ�release�¼�,ԭ�����Ƿ��ڴ��������ز���ҵ��ǰ���*/
    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_RELEASED);

    TAF_CALL_ProcCallStatusFail(pstMsg->ucCallId, enCallState);

    enCause = MN_CALL_GetCsCause(pstMsg->ucCallId);

    /* �绰�Ҷ�ʱ������Ӧ���¼������������������ǿ�ָ�룬���ĸ�����������0�������¼�������ȥ */
    if(MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(pstMsg->ucCallId))
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }


    /* ���²���ҵ������Ľ�չ(CCA_SS_PROG_EVT_REL) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_REL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    TAF_CALL_ProcRelCallSsKeyEvent(pstMsg->ucCallId);

    /* UUS1����,���ϱ�UUS1��Ϣ */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstRelComp->stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_RELEASE_COMPLETE,
                                  (NAS_CC_IE_USER_USER_STRU*)&pstRelComp->stUserUser);
        /* UUS1��Ϣ�ϱ� */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

    TAF_CALL_ProcCallRedialAfterCallRel(pstMsg->ucCallId);

#if (FEATURE_ON == FEATURE_ECALL)
    /* ��call id�ͷ�֮ǰ����ȡ��ǰCALL ID����ʵ����Ϣ������ʹ�� */
    PS_MEM_SET(&stCallEntity, 0, sizeof(MN_CALL_MGMT_STRU));
    (VOS_VOID)MN_CALL_GetSpecificCallInfo(pstMsg->ucCallId, &stCallEntity);
#endif

    MN_CALL_FreeCallId(pstMsg->ucCallId);

    MN_CALL_GetCallInfoList(&ucNumOfCalls, f_astCallInfos);

    if (0 == ucNumOfCalls)
    {
        TAF_CALL_ProcCallAllReleased(pstMsg);
    }

    /* �·�CALL DISCONNECT EVENT��USIMģ�� */
    MN_CALL_SndStkCallDiscEvent(pstMsg, pstMsg->enPrimName, VOS_TRUE);

    enCause = TAF_CALL_GetAllowedDtmfCallId(&ucDtmfCallId);
    if (enCause != TAF_CS_CAUSE_SUCCESS)
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_RELEASE);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    TAF_CALL_ProcEcallRel(&stCallEntity);
#endif

    return;
}
VOS_VOID  MN_CALL_ProcMnccRejInd(
    MNCC_IND_PRIM_MSG_STRU             *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT8                           ucNumOfCalls;
#if (FEATURE_ON == FEATURE_ECALL)
    MN_CALL_MGMT_STRU                   stCallEntity;
#endif

    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_DIALING == enCallState);

    if (VOS_TRUE == MN_CALL_IsNeedCallRedial(pstMsg->ucCallId, pstMsg->unParam.enCause))
    {
        /* ����mncc rej ind��Ϣ�������ؽ���ʱ�� */
        pstBufferdMsg->bitOpBufferedRejIndMsg = VOS_TRUE;
        PS_MEM_CPY(&pstBufferdMsg->stBufferedRejIndMsg, pstMsg, sizeof(MNCC_IND_PRIM_MSG_STRU));

#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
        {
            MN_CALL_StartTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL, 0, 0, VOS_RELTIMER_NOLOOP);

            /* ��ʼ��MSD����״̬ΪBUTT */
            TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
        }
        else
#endif
        {
            MN_CALL_StartTimer(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL, 0, 0, VOS_RELTIMER_NOLOOP);
        }
        return;
    }

    TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_RELEASE);


    MN_CALL_UpdateCcCause(pstMsg->ucCallId, pstMsg->unParam.enCause);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(pstMsg->ucCallId, VOS_FALSE);

    /*����ǿ��ӵ绰��֪ͨCSTģ���ͷ�*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(pstMsg->ucCallId))
    {
        if (VOS_TRUE == MN_CALL_GetVideoCallChannelOpenFlg(pstMsg->ucCallId))
        {
            MN_CALL_SendCstRelReqMsg(pstMsg->ucCallId);
        }
    }

    /* ��Ҫ��ͳ��ͨ��ʱ�䣬���ϱ�RELEASED�¼� */
    MN_CALL_StopFluxCalculate(pstMsg->ucCallId);

    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_RELEASED);

    TAF_CALL_ProcCallStatusFail(pstMsg->ucCallId, enCallState);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CS�����쳣log */
    MN_CALL_CsCallErrRecord(pstMsg->ucCallId, pstMsg->unParam.enCause);
#endif

    /* �绰�Ҷ�ʱ������Ӧ���¼������������������ǿ�ָ�룬���ĸ�����������0�������¼�������ȥ */
    if(MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(pstMsg->ucCallId))
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &(pstMsg->unParam.enCause),
                        sizeof(MN_CALL_INFO_STRU));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &(pstMsg->unParam.enCause),
                        sizeof(MN_CALL_INFO_STRU));
    }

    /* ���²���ҵ������Ľ�չ(CCA_SS_PROG_EVT_REL) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_REL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    TAF_CALL_ProcRelCallSsKeyEvent(pstMsg->ucCallId);

    TAF_CALL_ProcCallRedialAfterCallRel(pstMsg->ucCallId);

#if (FEATURE_ON == FEATURE_ECALL)
    /* ��call id�ͷ�֮ǰ����ȡ��ǰCALL ID����ʵ����Ϣ������ʹ�� */
    PS_MEM_SET(&stCallEntity, 0, sizeof(MN_CALL_MGMT_STRU));
    (VOS_VOID)MN_CALL_GetSpecificCallInfo(pstMsg->ucCallId, &stCallEntity);
#endif

    MN_CALL_FreeCallId(pstMsg->ucCallId);

    MN_CALL_GetCallInfoList(&ucNumOfCalls, f_astCallInfos);

    if (0 == ucNumOfCalls)
    {
        TAF_CALL_ProcCallAllReleased(pstMsg);
    }

    /* �·�CALL DISCONNECT EVENT��USIMģ�� */
    MN_CALL_SndStkCallDiscEvent(pstMsg, pstMsg->enPrimName, VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
    if (MN_CALL_S_DIALING != enCallState)
    {
        TAF_CALL_ProcEcallRel(&stCallEntity);
    }
#endif
}


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccFacilityInd
 ��������  : ����MNCC_FACILITYS_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccFacilityInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    /* ���������ز���ҵ�� */
    MN_CALL_ProcSsFacility(pstMsg->ucCallId, (NAS_CC_IE_FACILITY_STRU*)&pstMsg->unParam.stFac.stFacility);

}



VOS_VOID  MN_CALL_ProcMnccHoldCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_ACTIVE == enCallState);

    /* ��ATģ���ϱ�MN_CALL_EVT_HOLD�¼� */
    MN_CALL_ReportHoldEvent(MN_CLIENT_ALL, 1, &(pstMsg->ucCallId));

    MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_HELD);

    TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_CALL_ON_HOLD);

    /* ���²���ҵ������Ľ�չ(HOLD_CNF) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

}



VOS_VOID  MN_CALL_ProcMnccHoldRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_ACTIVE == enCallState);

    enCause = MN_CALL_GetCsCause(pstMsg->ucCallId);

    MN_CALL_UpdateCcCause(pstMsg->ucCallId, pstMsg->unParam.enCause);

    /* ���²���ҵ������Ľ�չ(HOLD_REJ) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_HOLD_REJ,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    /* �������DISC(MO/MT)״̬�µ�HOLD REJ���򲻸���ԭ��ֵ */
    if (NAS_CC_CAUSE_CC_INTER_ERR_HOLD_REJ_IN_DISC_STATE == pstMsg->unParam.enCause)
    {
        MN_CALL_UpdateCcCause(pstMsg->ucCallId, enCause);
    }

}



VOS_VOID  MN_CALL_ProcMnccRetrieveCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfActCalls;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_HELD == enCallState);

    /* �����ǰ�Ѿ�����һ������״̬�ĺ��У��򲻴���Retrieve��� */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfActCalls, aCallIds);
    if (0 == ulNumOfActCalls)
    {
        /* ��ATģ���ϱ�MN_CALL_EVT_RETRIEVE�¼� */
        MN_CALL_ReportRetrieveEvent(MN_CLIENT_ALL, 1, &(pstMsg->ucCallId));

        MN_CALL_UpdateCallState(pstMsg->ucCallId, MN_CALL_S_ACTIVE);

        /* ���²���ҵ������Ľ�չ(RETRIEVE_CNF) */
        MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                       MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                       MN_CALL_ERR_SS_UNSPECIFIC);
    }
}
VOS_VOID  MN_CALL_ProcMnccRetrieveRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfHoldCalls;
    VOS_UINT32                          i;

    PS_MEM_SET(aCallIds, 0, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstMsg->ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_HELD == enCallState);

    MN_CALL_UpdateCcCause(pstMsg->ucCallId, pstMsg->unParam.enCause);

    /* retrieve����ʧ�ܣ����Ӵ��������ʱ������hold״̬�ĺ��У���ʱӦ��
       Ҫ������һ������hold״̬�ĺ��л��� */
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfHoldCalls, aCallIds);
    if (2 == ulNumOfHoldCalls)
    {
        for (i = 0; i < ulNumOfHoldCalls; i++)
        {
            if (pstMsg->ucCallId != aCallIds[i])
            {
                MN_CALL_ReportRetrieveEvent(MN_CLIENT_ALL, 1, &aCallIds[i]);
                MN_CALL_UpdateCallState(aCallIds[i], MN_CALL_S_ACTIVE);
                break;
            }
        }
    }

    /* ���²���ҵ������Ľ�չ(RETRIEVE_REJ) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

}

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccFacilityLocalRej
 ��������  : ����MNCC_RETRIEVE_REJԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccFacilityLocalRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    VOS_UINT8                           ucInvokeId;
    VOS_UINT8                           ucOpCode;
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvent;

    /*���Invoke Id�����Ӧ��Operation Code*/
    ucInvokeId = pstMsg->unParam.ucInvokeId;
    if (VOS_FALSE == g_stCallInvokeIdTable[ucInvokeId].bUsed)
    {
        MN_WARN_LOG("MN_CALL_ProcMnccFacilityLocalRej: invalid InvokeId");
        return;
    }
    ucOpCode = g_stCallInvokeIdTable[ucInvokeId].ucOperateCode;
    if (VOS_OK != MN_CALL_SsOpCodeTransToSsEvent(ucOpCode, &enEvent))
    {
        MN_WARN_LOG("MN_CALL_ProcMnccFacilityLocalRej: invalid Operation Code");
        return;
    }

    MN_CALL_InvokeId_Free(ucInvokeId);
    MN_CALL_UpdateCcCause(pstMsg->ucCallId, MN_CALL_INTERWORKING_UNSPECIFIED);

    /* ���²���ҵ������Ľ�չ(RETRIEVE_REJ) */
    MN_CALL_UpdateCallSupsProgress(pstMsg->ucCallId,
                                   enEvent,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

}


VOS_VOID  MN_CALL_SendVcMsg(
    CALL_VC_MSG_ID_ENUM_U16             enEventType
)
{
    CALL_VC_CHANNEL_INFO_MSG_STRU       *pstChannelInfoMsg;

    /* ������Ϣ */
    pstChannelInfoMsg = (CALL_VC_CHANNEL_INFO_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                           sizeof(CALL_VC_CHANNEL_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstChannelInfoMsg)
    {
        MN_ERR_LOG("MN_CALL_SendVcMsg: ALLOC MSG FAIL.");
        return;
    }

    pstChannelInfoMsg->ulReceiverPid = WUEPS_PID_VC;
    pstChannelInfoMsg->enMsgName     = enEventType;
    (VOS_VOID)VOS_MemCpy(&pstChannelInfoMsg->stChannelInfo,
               &f_stCallTchStatus,
               sizeof(MN_CALL_CHANNEL_INFO_STRU));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstChannelInfoMsg))
    {
        MN_ERR_LOG("MN_CALL_SendVcMsg: MSG SEND FAIL.");
    }
}
VOS_VOID  MN_CALL_ReportChannelEvent(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enEventType
)
{

    MN_CALL_CHANNEL_INFO_STRU          *pstChannelInfo = VOS_NULL_PTR;

    pstChannelInfo = &f_stCallTchStatus;

    /* �ŵ�����ʱ��AT�ϱ� CHANNEL ��Ϣ, ����ȫ�ֱ����м�¼��ʱ���ŵ���Ϣ */
    if ((MN_CALL_EVT_CHANNEL_OPEN        == enEventType)
     || (MN_CALL_EVT_CHANNEL_PARA_CHANGE == enEventType))
    {
        MN_CALL_SndAtChannelInfoInd(enEventType, pstChannelInfo, VOS_FALSE);

        /* ��¼��ʱ�ŵ���Ϣ��ȫ�ֱ����� */
        MN_CALL_SetLastCallTchStatus(pstChannelInfo);
    }
}


VOS_VOID  MN_CALL_ProcMnccProgressInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    VOS_UINT32                          ulLocalAlertingFlg;

    ulLocalAlertingFlg = TAF_CALL_IsNeedLocalAlerting(&pstMsg->unParam.stProgressInd.stProgInd);

    if (VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if ((VOS_FALSE == MN_CALL_GetChannelOpenFlg())
         && (VOS_FALSE == ulLocalAlertingFlg))
        {
            /* ������Ϣ֪ͨVC������ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);

            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
        }

    }

    /* UUS1����,���ϱ�UUS1��Ϣ */
    if ( VOS_TRUE == NAS_IE_IS_PRESENT(&pstMsg->unParam.stProgressInd.stUserUser) )
    {
        MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                                  NAS_CC_MSG_PROGRESS,
                                  (NAS_CC_IE_USER_USER_STRU*)&pstMsg->unParam.stProgressInd.stUserUser);
        /* UUS1��Ϣ�ϱ� */
        MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);
    }

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstMsg->ucCallId))
    {
        if (MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
        {
            /* ���õȴ�MT eCall��־ */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_TRUE);
        }
    }
#endif
}


VOS_UINT32 MN_CALL_GetTchParm(
    MN_CALL_CHANNEL_PARAM_STRU          *pstChannParm
)
{
    if ( VOS_FALSE == f_stCallTchStatus.bChannelEnable )
    {
        return VOS_ERR;
    }

    pstChannParm->enCodecType = f_stCallTchStatus.stChannelParam.enCodecType;
    pstChannParm->enMode      = f_stCallTchStatus.stChannelParam.enMode;
    pstChannParm->enCallType  = f_stCallTchStatus.stChannelParam.enCallType;

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCcUus1Info
 ��������  : ����CCģ���к�������UUS1��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_UpdateCcUus1Info(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType;
    VOS_UINT32                          ulRet;
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType;
    NAS_CC_IE_USER_USER_STRU            stUuieInfo;

    /* �Ƚ�����Ϣ����ת��,�û�����ANYʱ,��Ĭ��ΪSetup��Ϣ */
    enMsgType = pstUus1Info->enMsgType;
    if ( MN_CALL_UUS1_MSG_ANY == enMsgType )
    {
        enMsgType = MN_CALL_UUS1_MSG_SETUP;
    }

    /* ��CALL�������Ϣ����ת��ΪCC�������Ϣ���� */
    ulRet = MN_CALL_ConCallMsgTypeToCcMsgType(enMsgType,&enCcMsgType);
    if ( VOS_OK != ulRet )
    {
        return MN_ERR_INVALIDPARM;
    }

    /* �˴�ͨ��APIֱ�Ӹ���CCģ�������ȫ�ֱ���,������CALLģ��,Ŀ������ΪCALL����
    Disconnect����ʱ,�������ַ��͵���Ϣ��Disconnect����Release����
    Release complete, ֻ��CC֪�������Ϣ*/

    if ( MN_CALL_SET_UUS1_ACT == enSetType )
    {
        ulRet = MN_CALL_ConCallUusInfoToCc(enMsgType,pstUus1Info,&stUuieInfo);
        if ( VOS_OK != ulRet )
        {
            return MN_ERR_INVALIDPARM;
        }

        ulRet = NAS_CC_ActUus1Info(enCcMsgType, &stUuieInfo);
    }
    else
    {
        ulRet = NAS_CC_DeactUus1Info(enCcMsgType);
    }

    if ( VOS_OK != ulRet)
    {
        return MN_ERR_INVALIDPARM;
    }


    return MN_ERR_NO_ERROR;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_GetCcUus1Info
 ��������  : ��ȡCC�����UUS1�����Ϣ
 �������  : ��
 �������  : pulActNum      :CC�ܹ��������
             pstUus1Info    :����UUS1����Ϣ
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcUus1Info(
    VOS_UINT32                          *pulActNum,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    VOS_UINT32                          ulActNum;
    NAS_CC_UUS1_INFO_STRU               astUus1Info[NAS_CC_MAX_UUIE_MSG_NUM];
    VOS_UINT32                          i;

    NAS_CC_GetAllUus1Info(&ulActNum,astUus1Info);

    *pulActNum = ulActNum;

    /* ��CC�������Ϣ��ʽת��ΪCALL����Ϣ��ʽ */
    for ( i = 0 ; i < ulActNum ; i++ )
    {
        MN_CALL_ConCcUusInfoToCall(astUus1Info[i].enMsgType,
                                   &astUus1Info[i].stUuieInfo,
                                   pstUus1Info);
        pstUus1Info++;

    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcUusInfoInd
 ��������  : ����տ�User to User Info��Ϣ������������Ϣ��Я������Ϣ
 �������  : pstMsg :��Ϣ��User to User����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��2��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  MN_CALL_ProcUusInfoInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    const NAS_CC_UUS_INFO_IND_STRU            *pstUusInfo;

    pstUusInfo = (NAS_CC_UUS_INFO_IND_STRU *)&(pstMsg->unParam.stUusInfo);

    MN_CALL_UpdateRptUus1Info(pstMsg->ucCallId,
                              pstUusInfo->enCcMsgtype,
                              (NAS_CC_IE_USER_USER_STRU*)&pstUusInfo->stUserInfo.stUserUser);
    /* UUS1��Ϣ�ϱ� */
    MN_CALL_ReportEvent(pstMsg->ucCallId, MN_CALL_EVT_UUS1_INFO);

}
VOS_VOID  MN_CALL_ProcEmergencyListInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    MNCC_EMERGENCY_LIST_IND_STRU        *pstMnccEmcListInd  = VOS_NULL_PTR;

    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfg       = VOS_NULL_PTR;

    pstCustomCfg      = MN_CALL_GetCustomCfgInfo();

    pstMnccEmcListInd = (MNCC_EMERGENCY_LIST_IND_STRU *)&(pstMsg->unParam.stEmcListInd);

    MN_CALL_SetMmEmerNumList(pstMnccEmcListInd);

    /* �������ϱ�����NV���ش򿪣��ϱ����������� */
    if (VOS_TRUE == pstCustomCfg->ucReportEccNumFlg)
    {
        MN_CALL_ReportEccNumList();
    }
}
VOS_VOID MN_CALL_ReportHoldEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId )
{
    MN_CALL_EVT_HOLD_STRU               stEvent;
    VOS_UINT8                           ucLoop;
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stEvent, 0, sizeof(MN_CALL_EVT_HOLD_STRU));
    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stEvent.enEvent     = MN_CALL_EVT_HOLD;
    stEvent.usClientId  = MN_GetRealClientId(usClientId, WUEPS_PID_TAF);
    stEvent.ucCallNum   = ucCallNum;
    PS_MEM_CPY(stEvent.aucCallId, pucCallId, ucCallNum);

    PS_MEM_CPY(stEvent.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                sizeof(stEvent.aucCurcRptCfg));
    PS_MEM_CPY(stEvent.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                sizeof(stEvent.aucUnsolicitedRptCfg));

    /* ������������Ϣ */
    stEvent.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;

    /* ��HOLD�¼����͵�AT */
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE))
    {
        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEvent, sizeof(MN_CALL_EVT_HOLD_STRU));
    }

    /* ��HOLD�¼����͵�OAM */
    for (ucLoop = 0; ucLoop < ucCallNum; ucLoop++)
    {
        MN_CALL_GetCallInfoByCallId(stEvent.aucCallId[ucLoop], &stCallInfo);

        MN_CS_SendMsgToOam(MN_CLIENT_ALL,
                           MN_CALL_EVT_HOLD,
                           MAPS_STK_PID,
                           &stCallInfo);
    }

    return;
}
VOS_VOID MN_CALL_ReportRetrieveEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId )
{
    MN_CALL_EVT_RETRIEVE_STRU           stEvent;
    VOS_UINT8                           ucLoop;
    MN_CALL_INFO_STRU                   stCallInfo;
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU   *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stEvent, 0, sizeof(MN_CALL_EVT_RETRIEVE_STRU));
    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stEvent.enEvent     = MN_CALL_EVT_RETRIEVE;
    stEvent.usClientId  = MN_GetRealClientId(usClientId, WUEPS_PID_TAF);
    stEvent.ucCallNum   = ucCallNum;
    PS_MEM_CPY(stEvent.aucCallId, pucCallId, ucCallNum);

    PS_MEM_CPY(stEvent.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                sizeof(stEvent.aucCurcRptCfg));
    PS_MEM_CPY(stEvent.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                sizeof(stEvent.aucUnsolicitedRptCfg));

    /* ������������Ϣ */
    stEvent.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;

    /* ��RETRIEVE�¼����͵�AT */
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE))
    {
        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEvent, sizeof(MN_CALL_EVT_RETRIEVE_STRU));
    }

    /* ��RETRIEVE�¼����͵�OAM */
    for (ucLoop = 0; ucLoop < ucCallNum; ucLoop++)
    {
        MN_CALL_GetCallInfoByCallId(stEvent.aucCallId[ucLoop], &stCallInfo);

        MN_CS_SendMsgToOam(MN_CLIENT_ALL,
                           MN_CALL_EVT_RETRIEVE,
                           MAPS_STK_PID,
                           &stCallInfo);
    }

    return;
}



/* ɾ��MN_CALL_ReportErrIndEvent */



VOS_VOID  MN_CALL_ProcBufferedCall(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT8                           ucNumOfCalls;
    VOS_BOOL                            bWaitSendAlertStatus;
    VOS_UINT8                           ucTempCallId;
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;
    /* Deleted by zwx247453 for CHR optimize, 2015-07-07 */


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    MN_CALL_GetCallState(ucCallId, &enCallState, &enMptyState);

    MN_CALL_ASSERT( MN_CALL_S_DIALING == enCallState);

    /* ��ʱ��ֹͣ�Ƶ���������ͳһ���� */

    /* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
    MN_CALL_UpdateCcCause(ucCallId, enCause);
    /* Modified by zwx247453 for CHR optimize, 2015-07-07, end */

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(ucCallId, VOS_FALSE);

    /*����ǿ��ӵ绰��֪ͨCSTģ���ͷ�*/
    if (MN_CALL_TYPE_VIDEO == MN_CALL_GetCallType(ucCallId))
    {
        if (VOS_TRUE == MN_CALL_GetVideoCallChannelOpenFlg(ucCallId))
        {
            MN_CALL_SendCstRelReqMsg(ucCallId);
        }
    }

    /* ��Ҫ��ͳ��ͨ��ʱ�䣬���ϱ�RELEASED�¼� */
    MN_CALL_StopFluxCalculate(ucCallId);

    MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_RELEASED);

    TAF_CALL_ProcCallStatusFail(ucCallId, enCallState);

    /* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CS�����쳣log */
    MN_CALL_CsCallErrRecord(ucCallId, enCause);
#endif
    /* Modified by zwx247453 for CHR optimize, 2015-07-07, end */

    /* �绰�Ҷ�ʱ������Ӧ���¼������������������ǿ�ָ�룬���ĸ�����������0�������¼�������ȥ */
    enCause = MN_CALL_INVALID_CAUSE;

    if(MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(ucCallId))
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &enCause,
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }

    /* ���²���ҵ������Ľ�չ(CCA_SS_PROG_EVT_REL) */
    MN_CALL_UpdateCallSupsProgress(ucCallId,
                                   MN_CALL_SS_PROG_EVT_REL,
                                   MN_CALL_ERR_SS_UNSPECIFIC);

    TAF_CALL_ProcRelCallSsKeyEvent(ucCallId);

    MN_CALL_FreeCallId(ucCallId);


    MN_CALL_GetCallInfoList(&ucNumOfCalls, f_astCallInfos);
    if ((VOS_TRUE == MN_CALL_GetTchStatus()) && (0 == ucNumOfCalls))
    {
        if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
        {
            /* ������Ϣ֪ͨVC�ر�����ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);

        }
        MN_CALL_SetTchStatus(VOS_FALSE);
        MN_CALL_SetChannelOpenFlg(VOS_FALSE);
    }

    MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &ucTempCallId) ;
    if ((VOS_TRUE == bWaitSendAlertStatus) && (0 == ucNumOfCalls))
    {
        MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, 0);
    }

    /* �����ǰû�к��У��ϱ����к��ж���RELEASED */
    if (0 == ucNumOfCalls)
    {
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_ALL_RELEASED);
        TAF_CALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);
        
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
        TAF_SendMtcCsSrvInfoInd();
#endif
    }

    if ((VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
     && (ucCallId == pstBufferdMsg->stBufferedSetupMsg.ucCallId))
    {
        MN_CALL_ClearBufferedMsg();
    }

    return;
}


VOS_VOID TAF_CALL_ProcBufferedRedialMessage(
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedRejIndMsg)
    {
        /* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
        MN_CALL_ProcBufferedCall(pstBufferdMsg->stBufferedRejIndMsg.ucCallId, enCause);
        /* Modified by zwx247453 for CHR optimize, 2015-07-07, end */

        /* �·�CALL DISCONNECT EVENT��USIMģ�� */
        MN_CALL_SndStkCallDiscEvent(&(pstBufferdMsg->stBufferedRejIndMsg),
                                    pstBufferdMsg->stBufferedRejIndMsg.enPrimName,
                                    VOS_TRUE);
    }
    else if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
        /* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
        MN_CALL_ProcBufferedCall(pstBufferdMsg->stBufferedSetupMsg.ucCallId, enCause);
        /* Modified by zwx247453 for CHR optimize, 2015-07-07, end */
    }
    else
    {

    }
}


VOS_VOID MN_CALL_SndAtChannelInfoInd(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enChannelEvent,
    MN_CALL_CHANNEL_INFO_STRU          *pstChannelInfo,
    VOS_UINT8                           ucIsLocalAlertingFlag
)
{
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;

    PS_MEM_SET(&stChannelEvt, 0x00, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    stChannelEvt.enEvent        = MN_CALL_EVT_CHANNEL_INFO_IND;

    stChannelEvt.usClientId     = MN_GetRealClientId(MN_CLIENT_ALL, WUEPS_PID_TAF);

    stChannelEvt.ucIsLocalAlertingFlag = ucIsLocalAlertingFlag;

    /* ������������Ϣ */
    stChannelEvt.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;

    stChannelEvt.enCodecType   = pstChannelInfo->stChannelParam.enCodecType;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));
}

/* ɾ���ú���������ʵ���Ƶ�����MN_CALL_ReportChannelEvent�� */

VOS_UINT32 TAF_CALL_IsNeedLocalAlerting(const NAS_CC_IE_PROGRESS_INDICATOR_STRU *pstProgInd)
{
    if (VOS_TRUE == pstProgInd->IsExist)
    {
        if (((pstProgInd->Octet4.ProgDesc >= 1)
          && (pstProgInd->Octet4.ProgDesc <= 3))
         || ((pstProgInd->Octet4.ProgDesc >= 6)
          && (pstProgInd->Octet4.ProgDesc <= 20)))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}



VOS_VOID  TAF_CALL_RcvCcStartDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    MN_CALL_ID_T                        CallId;

    /* �ж�״̬�Ƿ��쳣 */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_WAIT_START_CNF)
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStartDtmfCnf: Dtmf State Error!");
        return;
    }

    /* �ظ�DTMF��ʽ��Ӧ�¼� */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                         pstDtmfCurInfo->opId,
                         MN_CALL_EVT_START_DTMF_RSLT,
                         TAF_CS_CAUSE_SUCCESS);

    /* ����л�����ΪSTOP_DTMF������ֱ�ӷ��� */
    if (TAF_CALL_GetDtmfBufCnt() > 0)
    {
        /* ��ȡ������������DTMF��CallId */
        CallId = 0;
        if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&CallId))
        {
            MN_WARN_LOG("TAF_CALL_RcvCcStartDtmfCnf: Dtmf Not Allowed!");
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        pstListHead = TAF_CALL_GetDtmfListHead();
        /*lint -e961*/
        pstNode     = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/

        if (0 == pstNode->stDtmf.usOnLength)
        {
            *pstDtmfCurInfo = pstNode->stDtmf;

            /* �ӹ��˱���ɾ���ڵ� */
            TAF_CALL_DelDtmfNode(pstNode);

            if (VOS_OK != MN_CALL_SendCcStopDtmfReq(CallId))
            {
                TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
                MN_ERR_LOG("TAF_CALL_RcvCcStartDtmfCnf: Send Stop Dtmf Failed!");
                return;
            }

            /* ���ͳɹ�������DTMF״̬ */
            TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_STOP_CNF);
            return;
        }
    }

    /* û�л��棬�򻺴�ΪSTART_DTMF������������ʱ��������DTMF״̬ */
    MN_CALL_StartTimer(TAF_CALL_TID_DTMF_ON_LENGTH, 0, pstDtmfCurInfo->usOnLength, VOS_RELTIMER_NOLOOP);

    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_ON_LENGTH_TIME_OUT);

    return;
}
VOS_VOID  TAF_CALL_RcvCcStartDtmfRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    MN_CALL_ID_T                        CallId;

    /* �ж�״̬�Ƿ��쳣 */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_WAIT_START_CNF)
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStartDtmfRej: Dtmf State Error!");
        return;
    }

    /* �ظ�DTMF��ʽ��Ӧ�¼� */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                         pstDtmfCurInfo->opId,
                         MN_CALL_EVT_START_DTMF_RSLT,
                         TAF_CS_CAUSE_DTMF_REJ);

    /* ������Ϊ�գ������û��漰DTMF״̬���˳� */
    if (0 == TAF_CALL_GetDtmfBufCnt())
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* �л��棬��ΪSTOP_DTMF������ֱ���ͷŴ˻��棬֮����ΪSTART_DTMF�����򷢳� */
    pstListHead = TAF_CALL_GetDtmfListHead();
    /*lint -e961*/
    pstNode     = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
    /*lint +e961*/

    if (0 == pstNode->stDtmf.usOnLength)
    {
        *pstDtmfCurInfo = pstNode->stDtmf;

        /* �ӹ��˱���ɾ���ڵ� */
        TAF_CALL_DelDtmfNode(pstNode);

        /* �ظ�STOP_DTMF����ʽ��Ӧ */
        TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                             pstDtmfCurInfo->opId,
                             MN_CALL_EVT_STOP_DTMF_RSLT,
                             TAF_CS_CAUSE_DTMF_REJ);

        /* �������Ϊ�գ���ֱ�����û��漰DTMF״̬���˳� */
        if (0 == TAF_CALL_GetDtmfBufCnt())
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        /* ���治Ϊ�գ���ΪSTART_DTMF����׼������ */
        /*lint -e961*/
        pstNode = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/
    }

    /* ��ȡ������������DTMF��CallId����ȡʧ������ջ�������DTMF״̬���˳� */
    CallId = 0;
    if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&CallId))
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStartDtmfRej: Dtmf Not Allowed!");
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* �ӻ�����ȡ���ڵ㣬����START_DTMF���� */
    *pstDtmfCurInfo = pstNode->stDtmf;

    /* �ӹ��˱���ɾ���ڵ� */
    TAF_CALL_DelDtmfNode(pstNode);

    if (VOS_OK != MN_CALL_SendCcStartDtmfReq(CallId, pstDtmfCurInfo->cKey))
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        MN_ERR_LOG("TAF_CALL_RcvCcStartDtmfRej: Send Stop Dtmf Failed!");
        return;
    }

    /* ���ͳɹ�������DTMF״̬ */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);

    return;
}


VOS_VOID  TAF_CALL_RcvCcStopDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
)
{
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    MN_CALL_ID_T                        CallId;
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;

    /* �ж�״̬�Ƿ��쳣 */
    enDtmfState = TAF_CALL_GetDtmfState();
    if ( (enDtmfState != TAF_CALL_DTMF_WAIT_STOP_CNF)
      && (enDtmfState != TAF_CALL_DTMF_WAIT_AUTO_STOP_CNF) )
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStopDtmfCnf: Dtmf State Error!");
        return;
    }

    /* ������û�������STOP_DTMF��Ҫ�ظ���ʽ��Ӧ�¼� */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    if (enDtmfState != TAF_CALL_DTMF_WAIT_AUTO_STOP_CNF)
    {
        TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                             pstDtmfCurInfo->opId,
                             MN_CALL_EVT_STOP_DTMF_RSLT,
                             TAF_CS_CAUSE_SUCCESS);
    }

    /* offlength���Ȳ�Ϊ0ʱ��Ҫ������ʱ������ʱ����ʱ���·���һ��start dtmf req�����offlengthΪ0��ֱ�Ӵ����� */
    if (pstDtmfCurInfo->usOffLength != 0)
    {
       MN_CALL_StartTimer(TAF_CALL_TID_DTMF_OFF_LENGTH, 0, pstDtmfCurInfo->usOffLength, VOS_RELTIMER_NOLOOP);
       TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_OFF_LENGTH_TIME_OUT);
       return;
    }

    /* ������Ϊ�գ������û��漰DTMF״̬���˳� */
    if (0 == TAF_CALL_GetDtmfBufCnt())
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* �л��棬��ΪSTOP_DTMF������ֱ���ͷŴ˻��棬֮����ΪSTART_DTMF�����򷢳� */
    pstListHead = TAF_CALL_GetDtmfListHead();
    /*lint -e961*/
    pstNode     = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
    /*lint +e961*/

    if (0 == pstNode->stDtmf.usOnLength)
    {
        *pstDtmfCurInfo = pstNode->stDtmf;

        /* �ӹ��˱���ɾ���ڵ� */
        TAF_CALL_DelDtmfNode(pstNode);

        /* �ظ�STOP_DTMF����ʽ��Ӧ */
        TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                             pstDtmfCurInfo->opId,
                             MN_CALL_EVT_STOP_DTMF_RSLT,
                             TAF_CS_CAUSE_SUCCESS);

        /* �������Ϊ�գ���ֱ�����û��漰DTMF״̬���˳� */
        if (TAF_CALL_GetDtmfBufCnt() == 0)
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        /* ���治Ϊ�գ���ΪSTART_DTMF����׼������ */
        /*lint -e961*/
        pstNode = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/
    }

    /* ��ȡ������������DTMF��CallId����ȡʧ������ջ�������DTMF״̬���˳� */
    CallId = 0;
    if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&CallId))
    {
        MN_WARN_LOG("TAF_CALL_RcvCcStopDtmfCnf: Dtmf Not Allowed!");
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* �ӻ�����ȡ���ڵ㣬����START_DTMF���� */
    *pstDtmfCurInfo = pstNode->stDtmf;

    /* �ӹ��˱���ɾ���ڵ� */
    TAF_CALL_DelDtmfNode(pstNode);

    if (VOS_OK != MN_CALL_SendCcStartDtmfReq(CallId, pstDtmfCurInfo->cKey))
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        MN_ERR_LOG("TAF_CALL_RcvCcStopDtmfCnf: Send Stop Dtmf Failed!");
        return;
    }

    /* ���ͳɹ�������DTMF״̬ */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);

    return;
}
VOS_VOID  TAF_CALL_DeleteAllCallEntities( VOS_VOID)
{
    MN_CALL_MGMT_STRU                  *pstMnEntity = VOS_NULL_PTR;
    VOS_UINT8                           i;

    /* ��������ʵ��,�������bused��־ΪVOS_TRUE��ʵ����Ϣ */
    pstMnEntity = TAF_CALL_GetCallEntityAddr();

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstMnEntity->bUsed)
        {
            MN_CALL_DeleteCallEntity(pstMnEntity->stCallInfo.callId);
        }

        pstMnEntity++;
    }

    return;
}




#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_CALL_ProcDtmfBuffer(VOS_VOID)
{
    HI_LIST_S                          *pstListHead    = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode        = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo = VOS_NULL_PTR;
    MN_CALL_ID_T                        ucCallId;

    /* �����ǰ�в���ҵ���¼����ڽ��У��ݲ�����DTMF */
    if (VOS_TRUE == MN_CALL_IsCallSupsCmdInProgress())
    {
        return;
    }

    /* ����Ƿ���DTMF���� */
    if (0 == TAF_CALL_GetDtmfBufCnt())
    {
        return;
    }

    /* ��ȡ������������DTMF��CallId */
    ucCallId = 0;
    if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&ucCallId))
    {
        MN_WARN_LOG("TAF_CALL_ProcDtmfBuffer: Dtmf Not Allowed!");
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* ��ȡ������׸�DTMF���� */
    pstListHead     = TAF_CALL_GetDtmfListHead();
    /*lint -e961*/
    pstNode         = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
    /*lint +e961*/

    /* ����ֹͣDTMF���� */
    if (0 == pstNode->stDtmf.usOnLength)
    {
        /* �ӹ��˱���ɾ���ڵ� */
        TAF_CALL_DelDtmfNode(pstNode);

        if (VOS_OK != MN_CALL_SendCcStopDtmfReq(ucCallId))
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            MN_ERR_LOG("TAF_CALL_ProcDtmfBuffer: Send Stop Dtmf Failed!");
            return;
        }

        /* ���ͳɹ�������DTMF״̬ */
        TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_STOP_CNF);
        return;
    }
    /* ��������DTMF���� */
    else
    {
        pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();

        /* �ӻ�����ȡ���ڵ㣬����START_DTMF���� */
        *pstDtmfCurInfo = pstNode->stDtmf;

        /* �ӹ��˱���ɾ���ڵ� */
        TAF_CALL_DelDtmfNode(pstNode);

        if (VOS_OK != MN_CALL_SendCcStartDtmfReq(ucCallId, pstDtmfCurInfo->cKey))
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            MN_ERR_LOG("TAF_CALL_ProcDtmfBuffer: Send Start Dtmf Failed!");
            return;
        }

        /* ���ͳɹ�������DTMF״̬ */
        TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);
    }
}
VOS_VOID TAF_CALL_MapCallStateToCcState(
    MNCC_ENTITY_STATUS_STRU            *pstCcInfo,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    switch (enCallState)
    {
        case MN_CALL_S_ACTIVE:
            pstCcInfo->enCallState    = NAS_CC_CALL_STATE_U10;
            break;

        case MN_CALL_S_HELD:
            pstCcInfo->enCallState    = NAS_CC_CALL_STATE_U10;
            pstCcInfo->enHoldAuxState = NAS_CC_HOLD_AUX_S_CALL_HELD;
            break;

        case MN_CALL_S_ALERTING:
            pstCcInfo->enCallState    = NAS_CC_CALL_STATE_U4;
            break;

        case MN_CALL_S_WAITING_ACCEPT:
        case MN_CALL_S_WAITING:
        case MN_CALL_S_INCOMING:
            pstCcInfo->enCallState    = NAS_CC_CALL_STATE_U7;
            break;

        default:
            /* It been filtered in TAF_CALL_CreateCallEntitiesWithImsCallInfo and should not happen! */
            break;
    }
}
VOS_VOID TAF_CALL_GetInfoTransCap(
    MN_CALL_ID_T                        CallId,
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8   *pEnInfoTransCap1,
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8   *pEnInfoTransCap2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
)
{
    MN_CALL_MGMT_STRU                   stMgmtEntity;
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    pstCustomCfgAddr = VOS_NULL_PTR;

    PS_MEM_SET(&stMgmtEntity, 0, sizeof(MN_CALL_MGMT_STRU));
    MN_CALL_GetMgmtEntityInfoByCallId(CallId, &stMgmtEntity);

    switch (stMgmtEntity.stCallInfo.enCallType)
    {
        case MN_CALL_TYPE_VOICE:
        case MN_CALL_TYPE_EMERGENCY:
            {
                /* ��ȡ���Կ���NV��ַ */
                pstCustomCfgAddr = MN_CALL_GetCustomCfgInfo();

                /* ��дBC������Octet 3*/
                if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
                {

                    if ( ( MN_CALL_ALS_LINE_NO_2 == MN_CALL_GetAlsLineInfo() )
                      && ( MN_CALL_DIR_MT != stMgmtEntity.stCallInfo.enCallDir )
                      && ( MN_CALL_TYPE_EMERGENCY != stMgmtEntity.stCallInfo.enCallType ) )
                    {
                        /*ITC��Ҫ���ݵ�ǰʹ�õ���·�Ž��и�ֵ,��·1ʱITCȡֵspeech,��·2ʱȡ
                          ֵAuxiliary speech*/
                        *pEnInfoTransCap1 = NAS_CC_ITC_AUXILIARY_SPEECH;
                    }
                    else
                    {
                        *pEnInfoTransCap1 = NAS_CC_ITC_SPEECH;
                    }
                }
                else
                {
                    *pEnInfoTransCap1 = NAS_CC_ITC_SPEECH;
                }
            }
            break;

       /*
        * data configure information is not reported by IMSA, it is a problem to create BC
        * parameter for CS data call !!! Don't support it now.
        */
        case MN_CALL_TYPE_VIDEO:
        case MN_CALL_TYPE_FAX:
        case MN_CALL_TYPE_CS_DATA:
        default:
            break;
    }

    *penBcRepeatInd = MN_CALL_REP_IND_NULL;
}


VOS_VOID TAF_CALL_MapCallInfoToCcInfo(
    MNCC_ENTITY_STATUS_STRU            *pstCcInfo,
    VOS_UINT8                          *pucCallNum
)
{
    MN_CALL_MGMT_STRU                  *pstMnEntity = VOS_NULL_PTR;
    VOS_UINT8                           i;
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enInfoTransCap1;
    NAS_CC_INFO_TRANSFER_CAP_ENUM_U8    enInfoTransCap2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;

    enInfoTransCap1 = NAS_CC_ITC_RESERVED;
    enInfoTransCap2 = NAS_CC_ITC_RESERVED;
    pstMnEntity = TAF_CALL_GetCallEntityAddr();

    *pucCallNum = 0;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (VOS_FALSE == pstMnEntity->bUsed)
        {
            pstMnEntity++;
            continue;
        }

        TAF_CALL_MapCallStateToCcState(pstCcInfo, pstMnEntity->stCallInfo.enCallState);

        if (MN_CALL_IN_MPTY == pstMnEntity->stCallInfo.enMptyState)
        {
            pstCcInfo->enMptyAuxState = NAS_CC_MPTY_AUX_S_CALL_IN_MPTY;
        }
        else
        {
            pstCcInfo->enMptyAuxState = NAS_CC_MPTY_AUX_S_IDLE;
        }

        pstCcInfo->ucTi     = (VOS_UINT8)pstMnEntity->ulTi;
        pstCcInfo->ucCallId = pstMnEntity->stCallInfo.callId;

        /*
         * CC only need information Transfer capability, so convert it.
         */
        TAF_CALL_GetInfoTransCap(pstMnEntity->stCallInfo.callId, &enInfoTransCap1, &enInfoTransCap2, &enBcRepeatInd);

        /* set BC1 */
        pstCcInfo->stBC1.IsExist             = VOS_TRUE;
        pstCcInfo->stBC1.Octet3.InfoTransCap = enInfoTransCap1;

        if (MN_CALL_REP_IND_ALTER == enBcRepeatInd)
        {
            /* set BC2 */
            pstCcInfo->stBC2.IsExist             = VOS_TRUE;
            pstCcInfo->stBC2.Octet3.InfoTransCap = enInfoTransCap2;
        }

        pstMnEntity++;
        pstCcInfo++;
        (*pucCallNum)++;
    }

    return;
}

/* ɾ���˺��� */

VOS_VOID  TAF_CALL_ProcMnccSrvccStart(VOS_VOID)
{
    /* ������ʱȦ���������õķ�ʽ��ȡcall��Ϣ */
#if 0
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           ucRealCallNum;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulBeginSlice;
    VOS_UINT32                          ulEndSlice;
    VOS_UINT32                          ulSlice;
    MNCC_ENTITY_STATUS_STRU             astEntitySta[MNCC_MAX_ENTITY_NUM];
    CALL_IMSA_SRVCC_CALL_INFO_STRU     *pstCallInfo = VOS_NULL_PTR;
#endif

    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_START);

#if 0
    /* Ϊ���IMSAͨ���첽�ӿ�֪ͨCALLģ�������Ϣ���µ�ʱ������(SRVCC�ȳɹ�,���յ�IMSA��ͬ��������Ϣָʾ) */
    /* CALL����IMSA��API�ӿ�,IMSA����SDK��API�ӿ� */

    /* �ȷ����ڴ� */
    pstCallInfo = (CALL_IMSA_SRVCC_CALL_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(CALL_IMSA_SRVCC_CALL_INFO_STRU) * CALL_IMSA_MAX_ENTITY_NUM);

    if (VOS_NULL_PTR == pstCallInfo)
    {
        /* �쳣��ӡ */
        MN_ERR_LOG("TAF_CALL_ProcMnccSrvccStart: alloc mem failed!");

        return;
    }

    ucCallNum = 0;

    PS_MEM_SET(pstCallInfo, 0x00, sizeof(CALL_IMSA_SRVCC_CALL_INFO_STRU) * CALL_IMSA_MAX_ENTITY_NUM);

    /* ��������,��ֹ���������ȼ�������ռ,����API�ĵ��ù��̱��ж� */
    VOS_TaskLock();
    ulBeginSlice = VOS_GetSlice();

    ulRslt    = CALL_IMSA_GetSrvccCallInfo(&ucCallNum, pstCallInfo);

    ulEndSlice = VOS_GetSlice();
    VOS_TaskUnlock();

    ulSlice = ulEndSlice - ulBeginSlice;

    vos_printf("TAF_CALL_ProcMnccSrvccStart, call imsa api time length,tick = 0x%x\r\n", ulSlice);

    /* LOG������IMSA��API�ӿڣ����ڿ�ά�ɲ� */
    //TAF_CALL_LogImsaApiGetSrvccCallInfo(ulRslt, ucCallNum, pstCallInfo);

    if (VOS_FALSE == ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstCallInfo);

        return;
    }

    /* ӳ�����ʵ�� */
    TAF_CALL_CreateCallEntitiesWithImsCallInfo(ucCallNum, pstCallInfo);

    /* ��CALLģ��ĺ�����Ϣӳ���CCģ��ĺ�����Ϣ */
    PS_MEM_SET(&astEntitySta[0], 0, sizeof(MNCC_ENTITY_STATUS_STRU) * MNCC_MAX_ENTITY_NUM);

    /* get the actual number of call entity created */
    ucRealCallNum = TAF_CALL_GetCallEntityNum();

    TAF_CALL_MapCallInfoToCcInfo(&astEntitySta[0], ucRealCallNum);

    /* ֪ͨCCģ�������ϢMNCC_SRVCC_CALL_INFO_NOTIFY */
    TAF_CALL_SendCcSrvccCallInfoNtf(ucRealCallNum, astEntitySta);
#endif

    /* ֪ͨIMSAģ��SRVCC״̬��Ϣ */
    TAF_CALL_SendImsaSrvccStatusNtf(CALL_IMSA_SRVCC_STATUS_START);

#if 0
    /* �ͷŷ�����ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstCallInfo);

    return;
#endif
}
VOS_VOID  TAF_CALL_ProcMnccSrvccSucc(VOS_VOID)
{
    VOS_UINT8                           i;
    MN_CALL_MGMT_STRU                  *pstMnEntity = VOS_NULL_PTR;
    MN_CALL_TYPE_ENUM_U8                enCallType = MN_CALL_TYPE_BUTT;

    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_SUCCESS);
    TAF_SDC_SetImsCallExistFlg(VOS_FALSE);
    
    
    TAF_SndMmaImsSrvInfoNotify(VOS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
    TAF_SendMtcCsSrvInfoInd();
#endif

    /* ֪ͨIMSAģ��SRVCC״̬��Ϣ */
    TAF_CALL_SendImsaSrvccStatusNtf(CALL_IMSA_SRVCC_STATUS_SUCCESS);

    pstMnEntity = TAF_CALL_GetCallEntityAddr();
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /* check whether or not call state is incoming when SRVCC success is received.
         * If yes, start ring timer. */
        if (VOS_TRUE == pstMnEntity[i].bUsed)
        {
            if (MN_CALL_S_INCOMING == pstMnEntity[i].stCallInfo.enCallState)
            {
                MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_LOOP);
                break;
            }

            if (MN_CALL_TYPE_EMERGENCY == pstMnEntity[i].stCallInfo.enCallType)
            {
                enCallType = MN_CALL_TYPE_EMERGENCY;
            }
            
            /*****************************************************************************
             from section 12.2.3B.3.1 in 24.237
             If the SC UE:
             1) as received a terminating call which is in the early dialog state according to
                the conditions in subclauses 12.1 and 12.2.3B.1; and
             2) as sent a SIP 200 (OK) response (i.e. user answers the call when in the PS domain)
                prior to successfully performing access transfer to the CS domain;

             then the UE sends a CC CONNECT message and transitions to Active (U10) state
             as described in 3GPP TS 24.008.
             *****************************************************************************/
            if (MN_CALL_S_WAITING_ACCEPT == pstMnEntity[i].stCallInfo.enCallState)
            {
                /* ���˺���״̬��incoming״̬���ȴ�connect ack */
                pstMnEntity[i].stCallInfo.enCallState = MN_CALL_S_INCOMING;

                MN_CALL_CallAnswerReqProc(pstMnEntity[i].stCallInfo.clientId,
                                          pstMnEntity[i].stCallInfo.opId,
                                          pstMnEntity[i].stCallInfo.callId,
                                          VOS_NULL_PTR);

                break;
            }
        }
    }

    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, enCallType);

    /* TCH�ѷ��䣬����DTMF���󣬷������յ�SYNC IND�д������Ϣ */
    if (VOS_TRUE == MN_CALL_GetTchStatus())
    {
        /* ����Ƿ���DTMF������Ҫ���� */
        TAF_CALL_ProcDtmfBuffer();
    }

    return;
}
VOS_VOID  TAF_CALL_ProcMnccSrvccFail(VOS_VOID)
{
    TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_FAIL);

    MN_CALL_SetChannelOpenFlg(VOS_FALSE);

    /* ����IMSAͬ�������ĺ�����Ϣ */
    TAF_CALL_DeleteAllCallEntities();

    /* ���ҵ���ŵ�������־ */
    MN_CALL_SetTchStatus(VOS_FALSE);

    /* ���DTMF��Ϣ */
    TAF_CALL_InitDtmfCtx();

    /* ֪ͨIMSAģ��SRVCC״̬��Ϣ */
    TAF_CALL_SendImsaSrvccStatusNtf(CALL_IMSA_SRVCC_STATUS_FAIL);

    return;
}


VOS_VOID  TAF_CALL_ProcMnccSrvccStatusInd(
    MNCC_SRVCC_STATUS_IND_STRU         *pstSrvccMsg
)
{
    switch (pstSrvccMsg->enSrvccStatus)
    {
        case NAS_MNCC_SRVCC_STATUS_START:

            TAF_CALL_ProcMnccSrvccStart();
            break;

        case NAS_MNCC_SRVCC_STATUS_SUCCESS:

            TAF_CALL_ProcMnccSrvccSucc();
            break;

        case NAS_MNCC_SRVCC_STATUS_FAIL:

            TAF_CALL_ProcMnccSrvccFail();
            break;

        default:

            MN_ERR_LOG("TAF_CALL_ProcMnccSrvccStatusInd: Unexpected srvcc status!");
            break;
    }

    return;
}


VOS_VOID TAF_CALL_ProcSrvccSyncInfo(VOS_VOID)
{
    if (MN_CALL_SRVCC_STATE_SUCCESS == TAF_CALL_GetSrvccState())
    {
        if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
        {
            TAF_CALL_SetSrvccState(MN_CALL_SRVCC_STATE_BUTT);

            MN_CALL_SetTchStatus(VOS_TRUE);

            TAF_CALL_ProcDtmfBuffer();
        }
    }
}
#endif

#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_CALL_ProcessEcallPeriodTimerLen(VOS_UINT8 ucCallId)
{
    VOS_UINT32                          ulEcallPeriodTimerLen;

    /* ���eCall period��ʱ�������У���ȡeCall period��ʱ�� */
    if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD))
    {
        ulEcallPeriodTimerLen = MN_CALL_GetTimerRemainLen(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);

        /* ����eCall period��ʱ��ʣ��ʱ����Ϊ����eCall�ز�ʹ�� */
        TAF_CALL_UpdateEcallPeriodRemainTimerLen(ulEcallPeriodTimerLen);
    }
}


VOS_UINT8 TAF_CALL_IsEcallRedialExist(VOS_VOID)
{
    MN_CALL_MSG_BUFF_STRU              *pstCallMsgBuff    = VOS_NULL_PTR;
    VOS_UINT8                           ucEcallFlag;

    pstCallMsgBuff = MN_CALL_GetBufferedMsg();

    if (VOS_TRUE == pstCallMsgBuff->bitOpBufferedSetupMsg)
    {
        ucEcallFlag = TAF_CALL_IsCallTypeEmgencyCall(pstCallMsgBuff->stBufferedSetupMsg.ucCallId);

        if ((MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
         && (VOS_TRUE                    == ucEcallFlag))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID TAF_CALL_ProcEcallRel(
    MN_CALL_MGMT_STRU                  *pstCallEntity
)
{
    MN_CALL_MGMT_STRU                  *pstCallEntityAddr = VOS_NULL_PTR;
    MN_CALL_MSG_BUFF_STRU              *pstCallMsgBuff    = VOS_NULL_PTR;
    VOS_UINT32                          ulEcallPeriodTimerLen;
    VOS_UINT32                          ulCallRedialIntervalLen;

    /* ����ʵ����Ч */
    if (VOS_FALSE == pstCallEntity->bUsed)
    {
        return;
    }

    /* ��MO eCall���з��� */
    if ((MN_CALL_TYPE_MIEC         != pstCallEntity->stCallInfo.enCallType)
     && (MN_CALL_TYPE_AIEC         != pstCallEntity->stCallInfo.enCallType)
     && (MN_CALL_TYPE_TEST         != pstCallEntity->stCallInfo.enCallType)
     && (MN_CALL_TYPE_RECFGURATION != pstCallEntity->stCallInfo.enCallType)
     && (MN_CALL_TYPE_PSAP_ECALL   != pstCallEntity->stCallInfo.enCallType))
    {
        return;
    }

    /* ���T2��ʱ�������У�ֹͣT2��ʱ�� */
    if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T2))
    {
        /* ֹͣT2��ʱ�� */
        MN_CALL_StopTimer(TAF_CALL_TID_T2);
    }

    /* "�ȴ�MT eCall��־λ"��MO eCall��ͨ�����ã�������MN_CALL_ProcMnccSetupCnf��
     * ��eCall�ͷź�����ñ�־λΪTRUE, �����ȴ�eCallʱ����ʱ��T9����ʱ����ñ�־
     */
    if (VOS_TRUE == TAF_CALL_GetWaitingMtEcallFlag())
    {
        /* ����T9��ʱ�� */
        MN_CALL_StartTimer(TAF_CALL_TID_T9, 0, 0, VOS_RELTIMER_NOLOOP);

        /* ���"�ȴ�mt eCall���б�־λ" */
        TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);
    }

    /* �������ΪMO �Ҷϣ�����ز����� */
    if ((VOS_TRUE == pstCallEntity->stCallInfo.stDiscDir.ucDiscCallFlag)
     && (VOS_TRUE == pstCallEntity->stCallInfo.stDiscDir.ucIsUser))
    {
        MN_CALL_ClearBufferedMsg();

        return;
    }

    pstCallMsgBuff = MN_CALL_GetBufferedMsg();

    /* ��ȡeCallʣ���ز�periodʱ�� */
    ulEcallPeriodTimerLen   = TAF_CALL_GetEcallPeriodRemainTimerLen();
    /* ��ȡeCall�ز����ʱ�� */
    ulCallRedialIntervalLen = MN_CALL_GetTimerLen(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);

    if ((VC_CALL_ECALL_MSD_TRANSMITTING_SUCCESS != TAF_CALL_GetEcallMsdTransStatus())
     && (VOS_TRUE                               == pstCallMsgBuff->bitOpBufferedSetupMsg)
     && (ulCallRedialIntervalLen                <= ulEcallPeriodTimerLen))
    {
        /* �޸ĺ���״̬dialing�����´�������ʵ��, ���ϱ�orig��Ϣ�����������ز���ʼ */
        pstCallEntity->stCallInfo.enCallState              = MN_CALL_S_DIALING;
        pstCallEntity->stCallInfo.stDiscDir.ucDiscCallFlag = VOS_FALSE;

        pstCallEntityAddr = TAF_CALL_GetCallEntityAddr();
        PS_MEM_CPY((pstCallEntityAddr+pstCallEntity->stCallInfo.callId - 1),
                   pstCallEntity,
                   sizeof(MN_CALL_MGMT_STRU));

        /* �ϱ�ORIG�¼� */
        MN_CALL_ReportEvent(pstCallEntity->stCallInfo.callId, MN_CALL_EVT_ORIG);

        /* ��ʣ��ʱ���������ز����Զ�ʱ�� */
        MN_CALL_StartTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD, 0, ulEcallPeriodTimerLen, VOS_RELTIMER_NOLOOP);

        /* �����ز����Լ����ʱ�� */
        MN_CALL_StartTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL, 0, 0, VOS_RELTIMER_NOLOOP);

        /* ��ʼ��MSD����״̬ΪBUTT */
        TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);

        return;
    }

    /* ����ز����� */
    MN_CALL_ClearBufferedMsg();
}
#endif

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
