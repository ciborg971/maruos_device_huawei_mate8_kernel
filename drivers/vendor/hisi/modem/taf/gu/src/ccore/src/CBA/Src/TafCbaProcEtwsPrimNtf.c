

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbsInterface.h"
#include  "TafCbaMntn.h"
#include  "TafCbaProcEtwsPrimNtf.h"
#include  "TafCbaComFunc.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaProcAt.h"

#include  "TafLog.h"
#include  "MnComm.h"
#include  "MnMsgTimerProc.h"
#include  "MnMsgReport.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_ETWS_PRIM_NTF_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

#if (FEATURE_ON == FEATURE_ETWS)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/





VOS_VOID TAF_CBA_RcvAsEtwsPrimNotifyInd(
    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU                    *pstMsg
)
{
    TAF_CBA_RECORD_STRU                                     stNewRecord;

    /* ETWS���Թر��򲻴���ETWS��֪ͨ��Ϣ */
    if (VOS_TRUE != TAF_CBA_GetEtwsEnableFlg())
    {
        /* ��ά�ɲ� */
        TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_RCV_PRIM_NTF_WHEN_ETWS_DISABLE);
        return;
    }

    /* �ж�MSG ID�Ƿ���Ч */
    if (VOS_TRUE != TAF_CBA_IsEtwsPrimNtfMsgIdValid(pstMsg->usMessageId))
    {
        /* ��ά�ɲ� */
        TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_ETWS_PRIM_NTF_MSGID_INVALID);
        return;
    }

    /* ����ɾ���ظ����ʱ����ʱ��ETWS��֪ͨ��¼ */
    TAF_CBA_DelEtwsPrimNtfExpiredRecord();

    /* ������֪ͨ���ݼ�¼ */
    TAF_CBA_BuildEtwsPrimNtfRecord(pstMsg, &stNewRecord);

    /* �ظ����, �����ظ�����Ϣ, ���ñ�����ϱ���AT */
    if ( VOS_TRUE == TAF_CBA_IsDupEtwsPrimNtf(&stNewRecord) )
    {
        return;
    }

    /* ������֪ͨ��¼ */
    TAF_CBA_SaveEtwsPrimNtfRecord(&stNewRecord);

    /* �ϱ���֪ͨ�� AT */
    TAF_CBA_SndAtEtwsPrimNtfMsg(pstMsg);

    /* ��������: �� WģCBSδʹ��ʱ����Ҫ��ʱʹ��CBS����, �Ա����յ�ETWS��֪ͨ */
    TAF_CBA_TemporaryEnableCbs();

}


VOS_UINT32 TAF_CBA_IsMsgIdInEtwsMsgIdList(
    VOS_UINT16                          usMsgId
)
{
    VOS_UINT32                          ulUserEtwsIdx;
    TAF_CBA_ETWS_MSGID_RANGE_STRU      *pstUserSpecEtwsMsgIdList;
    VOS_UINT16                          usTmpMsgIdFrom;
    VOS_UINT16                          usTmpMsgIdTo;

    /* �����ж��Ƿ���Э��涨��ETWS CBS��ϢID��Χ�� */
    if ( (usMsgId >= TAF_CBA_PROTOCOL_ETWS_CBS_MSGID_FROM)
      && (usMsgId <= TAF_CBA_PROTOCOL_ETWS_CBS_MSGID_TO) )
    {
        return VOS_TRUE;
    }

    /* ���ж��Ƿ����û����Ƶ�ETWS ��ϢID��Χ�� */
    pstUserSpecEtwsMsgIdList = TAF_CBA_GetUserSpecEtwsMsgIdList();

    for ( ulUserEtwsIdx = 0; ulUserEtwsIdx < TAF_CBA_NVIM_MAX_USER_SPEC_ETWS_MSGID_RANGE_NUM; ulUserEtwsIdx++ )
    {
        /* ���ڳ�ʼ��ʱû������С���жϴ���������Ҫ������ */
        if ( pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdFrom <=  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdTo)
        {
            usTmpMsgIdFrom =  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdFrom;
            usTmpMsgIdTo   =  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdTo;
        }
        else
        {
            usTmpMsgIdFrom =  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdTo;
            usTmpMsgIdTo   =  pstUserSpecEtwsMsgIdList[ulUserEtwsIdx].usMsgIdFrom;
        }

        if ((usMsgId >= usTmpMsgIdFrom)
         && (usMsgId <= usTmpMsgIdTo))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32  TAF_CBA_IsEtwsPrimNtfMsgIdValid(
    VOS_UINT16                          usMsgId
)
{
    VOS_UINT32                          ulIsInCbsActiveList;
    VOS_UINT32                          ulIsInEtwsList;

    /* �ж�MSG ID �Ƿ���CBS�����б��� */
    ulIsInCbsActiveList = TAF_CBA_IsMsgIdInCbsActiveList(usMsgId);

    /* �ж�MSG ID �Ƿ���ETWS MSG ID ��Χ�� */
    ulIsInEtwsList      = TAF_CBA_IsMsgIdInEtwsMsgIdList(usMsgId);

    if ( (VOS_TRUE == ulIsInCbsActiveList)
      && (VOS_TRUE == ulIsInEtwsList) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_CBA_GetEtwsDupDetcTimeLen(
    TAF_CBA_PLMN_ID_STRU                                   *pstPlmn
)
{
    TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU               *pstEnhDupDetcTimeLenCfg;
    VOS_UINT8                                               ucEnhDupDetcFlg;
    VOS_UINT32                                              ulIndex;

    ucEnhDupDetcFlg         = TAF_CBA_GetEnhDupDetcFlg();

    pstEnhDupDetcTimeLenCfg = TAF_CBA_GetEnhDupDetcTimeLenCfg();

    /*  CHANGE REQUEST 23.041   CR  0083
        8.2 Duplication Detection Function
        Upon reception of a new message, the MS/UE shall perform duplication detection on the messages.
        Those messages that are received from the same PLMN in the certain time period specified
        by the Duplication Detection Time are subject to duplication detection.
        The value of Duplication Detection Time to be used by the MS/UE shall be derived from the
        MCC of the current PLMN as follows:
        -   If MCC = 440 or MCC = 441 (Japan), Duplication Detection Time shall be 1 hour;
        -   For all other MCCs, Duplication Detection Time shall be 24 hours.
    */

    /* ��ǿ���ظ���ⶨ������δ����ʱ����Чʱ��ȡֵ */
    if (VOS_TRUE != ucEnhDupDetcFlg)
    {
        return TAF_CBA_GetNormalDupDetcTimeLen();
    }

    /* ��ǿ���ظ���ⶨ�����Կ���ʱ��ȡֵ, ��ǰPLMN��MCC�ڶ���MCC��Χ��Ͷ���MCC��ȡֵ��ͬ */
    for ( ulIndex = 0; ulIndex < TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM; ulIndex++ )
    {
        if (pstPlmn->ulMcc == pstEnhDupDetcTimeLenCfg->aulSpecMcc[ulIndex])
        {
            return pstEnhDupDetcTimeLenCfg->ulSpecMccTimeLen;
        }
    }

    return pstEnhDupDetcTimeLenCfg->ulOtherMccTimeLen;
}



VOS_VOID TAF_CBA_BuildEtwsPrimNtfRecord(
    RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU                    *pstMsg,
    TAF_CBA_RECORD_STRU                                    *pstNewRecord
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    
    if ( (VOS_NULL == pstMsg)
      || (VOS_NULL == pstNewRecord) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_BuildEtwsPrimNtfRecord: ERR:pstMsg NULL Ptr!");
        return;
    }

    enRatType = TAF_CBA_GetRatTypeBySenderPid(pstMsg->ulSenderPid);

    PS_MEM_SET(pstNewRecord, 0x00, sizeof(TAF_CBA_RECORD_STRU));

    pstNewRecord->enNetMode        = enRatType;
    pstNewRecord->ucTotalPage      = 0;
    pstNewRecord->usPageBitmap     = 0;
    pstNewRecord->usMsgID          = pstMsg->usMessageId;
    pstNewRecord->usSN             = pstMsg->usSerialNumber;
    pstNewRecord->stPlmn.ulMcc     = pstMsg->stCurrNetworkInfo.stCurPlmn.ulMcc;
    pstNewRecord->stPlmn.ulMnc     = pstMsg->stCurrNetworkInfo.stCurPlmn.ulMnc;
    pstNewRecord->ulDupDetcTimeLen = TAF_CBA_GetEtwsDupDetcTimeLen(&(pstNewRecord->stPlmn));
    pstNewRecord->ulRcvTimeTick    = VOS_GetTick();
}


VOS_VOID TAF_CBA_SaveEtwsPrimNtfRecord (
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    TAF_CBA_RECORD_STRU                *pstPrimNtfList;
    VOS_UINT16                          usPrimNtfNum;
    VOS_UINT32                          ulSameMsgIdCodeInx;
    VOS_UINT32                          ulAppendInx;
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType;

    ulSameMsgIdCodeInx   = 0;
    ulAppendInx          = 0;
    pstPrimNtfList       = TAF_CBA_GetRcvEtwsPrimNtfList();
    usPrimNtfNum         = TAF_CBA_GetRcvEtwsPrimNtfNum();

    /* ��¼���д��ں��յ���Ϣ��MSG ID��MSG CODE��ͬ�ļ�¼��, �򸲸�ԭ��¼�� */
    if (VOS_TRUE == TAF_CBA_GetEtwsPrimNtfRecordInxByMsgIdCode(pstNewRecord, &ulSameMsgIdCodeInx))
    {
        /* ��ά�ɲ� */
        TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_ETWS_PRIM_NTF_RECORD,
                                     TAF_CBA_OM_SAVE_TYPE_REPLACE_RECORD,
                                     pstNewRecord,
                                     usPrimNtfNum);

        /* �����¼�� */
        pstPrimNtfList[ulSameMsgIdCodeInx] = (*pstNewRecord);

        return;
    }

    /*  ������������һ����¼�� */
    if ( TAF_CBA_MAX_ETWS_PRIM_NTF_RECORD_NUM == usPrimNtfNum )
    {
        /* �б��������ȡ����ļ�¼���index, ����֮ */
        ulAppendInx = TAF_CBA_GetEarliestEtwsPrimNtfRecordInx();

        /* �����¼�Ŀ�ά�ɲ���Ϣ */
        TAF_CBA_SndOmDeledRecordInfo(TAF_CBA_OM_MSG_DEL_ETWS_PRIM_RECORD,
                                     TAF_CBA_OM_DEL_REASON_LIST_FULL,
                                     &pstPrimNtfList[ulAppendInx]);

        /* �����¼�� */
        pstPrimNtfList[ulAppendInx] = (*pstNewRecord);

        /* ��¼���������, ���ڿ�ά�ɲ� */
        enSaveType = TAF_CBA_OM_SAVE_TYPE_RECORD_FULL;
    }
    else
    {
        /* �б�δ���������������һ����¼ */
        ulAppendInx = usPrimNtfNum;

        /* ������֪ͨ��¼�� */
        pstPrimNtfList[ulAppendInx] = (*pstNewRecord);

        /* ������֪ͨ��¼���� */
        usPrimNtfNum++;
        TAF_CBA_SetRcvEtwsPrimNtfNum(usPrimNtfNum);

        /* ��¼���������, ���ڿ�ά�ɲ� */
        enSaveType = TAF_CBA_OM_SAVE_TYPE_APPEND_RECORD;
    }

    /* ��ά�ɲ� */
    TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_ETWS_PRIM_NTF_RECORD,
                                 enSaveType,
                                 pstNewRecord,
                                 usPrimNtfNum);
}
VOS_UINT32  TAF_CBA_GetEarliestEtwsPrimNtfRecordInx(VOS_VOID)
{
    TAF_CBA_RECORD_STRU                *pstRecordList;
    VOS_UINT32                          ulRcvPrimNtfNum;
    VOS_UINT32                          ulEarliestInx;
    VOS_UINT32                          ulEarliestTick;
    VOS_UINT32                          ulInx;

    pstRecordList   = TAF_CBA_GetRcvEtwsPrimNtfList();
    ulRcvPrimNtfNum = TAF_CBA_GetRcvEtwsPrimNtfNum();

    ulEarliestInx   = 0;
    ulEarliestTick  = pstRecordList[0].ulRcvTimeTick;

    for ( ulInx = 1; ulInx < ulRcvPrimNtfNum; ulInx++ )
    {
        if ( pstRecordList[ulInx].ulRcvTimeTick < ulEarliestTick )
        {
            ulEarliestInx  = ulInx;
            ulEarliestTick = pstRecordList[ulInx].ulRcvTimeTick;
        }
    }

    return ulEarliestInx;

}


VOS_UINT32 TAF_CBA_IsNeedDupDetectEtwsPrimNtf(VOS_VOID)
{
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enDupDetectCfg;

    enDupDetectCfg = TAF_CBA_GetDupDetectCfg();
    
    if ( TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE == enDupDetectCfg )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 TAF_CBA_IsDupEtwsPrimNtf(
    TAF_CBA_RECORD_STRU                *pstRecord
)
{
    TAF_CBA_RECORD_STRU                *pstPrimNtfList;
    VOS_UINT8                           ucEnhDupDetcFlg;
    VOS_UINT16                          ulPrimNotifyNum;
    VOS_UINT32                          ulInx;


    if ( VOS_TRUE != TAF_CBA_IsNeedDupDetectEtwsPrimNtf() )
    {
        /* ����Ҫ���ظ���������Ϊ �����ظ��ļ�¼�� */        
        return VOS_FALSE;
    }

    ucEnhDupDetcFlg = TAF_CBA_GetEnhDupDetcFlg();

    pstPrimNtfList  = TAF_CBA_GetRcvEtwsPrimNtfList();
    ulPrimNotifyNum = TAF_CBA_GetRcvEtwsPrimNtfNum();

    for ( ulInx = 0; ulInx < ulPrimNotifyNum; ulInx++ )
    {
        /* �жϽ���ģʽ */
        if (pstRecord->enNetMode != pstPrimNtfList[ulInx].enNetMode)
        {
            continue;
        }

        /* DoCoMo��ETWS����ǿ���ظ���ⶨ�����Լ���ʱ, ��Ҫ�ж�PLMN */
        if (VOS_TRUE == ucEnhDupDetcFlg)
        {
            /* �ж�PLMN */
            if ( (pstRecord->stPlmn.ulMcc != pstPrimNtfList[ulInx].stPlmn.ulMcc)
              || (pstRecord->stPlmn.ulMnc != pstPrimNtfList[ulInx].stPlmn.ulMnc) )
            {
                continue;
            }
        }

        /* �ж� MSG ID */
        if (pstRecord->usMsgID != pstPrimNtfList[ulInx].usMsgID)
        {
            continue;
        }

        /* �Ƚ�����SN, Ŀǰ����ֱ��ж� MSG CODE, GS �� UPDATE NUMBER */
        if (pstRecord->usSN == pstPrimNtfList[ulInx].usSN)
        {
            /* ��ά�ɲ� */
            TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_ETWS_PRIM_NTF_RECORD,
                                       &(pstPrimNtfList[ulInx]));

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_CBA_GetEtwsPrimNtfRecordInxByMsgIdCode(
    TAF_CBA_RECORD_STRU                *pstRecord,
    VOS_UINT32                         *pstIndex
)
{
    TAF_CBA_RECORD_STRU                *pstPrimNtfList;
    VOS_UINT16                          ulPrimNtfNum;
    VOS_UINT32                          ulInx;

    pstPrimNtfList = TAF_CBA_GetRcvEtwsPrimNtfList();
    ulPrimNtfNum   = TAF_CBA_GetRcvEtwsPrimNtfNum();

    for ( ulInx = 0; ulInx < ulPrimNtfNum; ulInx++ )
    {
        /* �жϽ���ģʽ */
        if (pstRecord->enNetMode != pstPrimNtfList[ulInx].enNetMode)
        {
            continue;
        }

        /* �ж�PLMN */
        if ( (pstRecord->stPlmn.ulMcc != pstPrimNtfList[ulInx].stPlmn.ulMcc)
          || (pstRecord->stPlmn.ulMnc != pstPrimNtfList[ulInx].stPlmn.ulMnc) )
        {
            continue;
        }

        /* �ж� MSG ID �� MSG CODE */
        if ( (VOS_TRUE == TAF_CBA_IsSameMsgCode(pstRecord->usSN, pstPrimNtfList[ulInx].usSN))
          && (pstRecord->usMsgID == pstPrimNtfList[ulInx].usMsgID) )
        {
            *pstIndex = ulInx;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_VOID TAF_CBA_TemporaryEnableCbs(VOS_VOID)
{
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus;
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;

    /* ���CBS�����Ƿ��ڿ���״̬, �Ѵ��ڿ���״̬����Ҫ����ʱʹ��CBS���� */
    enCbsStatus = TAF_CBA_GetCbsStatus();
    if ( (TAF_CBA_CBSTATUS_W_ENABLE  == enCbsStatus)
      || (TAF_CBA_CBSTATUS_WG_ENABLE == enCbsStatus) )
    {
        /* ��ǰWģ��CBS���ڿ�������������T��ʱ�� */
        /* todo:���G֧��ETWS��������Ҫ�޸� */
        return;
    }

    if (VOS_TRUE == MN_MSG_IsTimerStarting(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS))
    {
        /* T��ʱ����������������֮ */
        MN_MSG_StopTimer(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS);
        MN_MSG_StartTimer(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS, 0);
    }
    else
    {
        /* T��ʱ��δ����������֮����֪ͨBMCʹ��CBS, ��ʹ֮���յ�ETWS��֪ͨ */
        MN_MSG_StartTimer(TI_TAF_CBA_RCV_ETWS_TEMP_ENABLE_CBS, 0);

        /* Wģ�����������Ĵ���,
           LģҲ������ʱ������Ϊ�˵�Lģ�л���Wģ�����ͨ���ö�ʱ����״̬�����Ƿ񼤻�W��CBS���� */
        enNetMode = TAF_CBA_GetNetRatType();
        if ((VOS_FALSE == TAF_CBA_IsCbsActiveListEmpty())
         && (TAF_CBA_NET_RAT_TYPE_WCDMA == enNetMode))      
        {
            TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
        }
    }
}
/*lint -restore */

#endif  /* (FEATURE_ON == FEATURE_ETWS) */

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
