

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbsInterface.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaComFunc.h"
#include  "TafCbaProcEtwsPrimNtf.h"
#include  "TafCbaProcNvim.h"
#include  "TafCbaMntn.h"
#include  "TafCbaProcUsim.h"
#include  "TafCbaProcAt.h"

#include  "MnComm.h"
#include  "mnmsgcbencdec.h"
#include  "MnMsgReport.h"
#include  "MnMsgTimerProc.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_AS_C


#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/



VOS_VOID TAF_CBA_ProcGasMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_CBS_MSG_DATA                   *pstMsgData;

    pstMsgData = (TAF_CBS_MSG_DATA *)pstMsg;
    switch (pstMsgData->enMsgID)
    {
        case ID_GAS_CBS_CFG_CNF:
            TAF_CBA_RcvAsCbsCfgCnf((BMC_CBS_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_GAS_CBS_DATA_IND :
            TAF_CBA_RcvGasCbsDataInd((GAS_CBS_DATA_IND_STRU *)pstMsg);
            break;

        case ID_RR_CBS_GS_STATUS_CHANGE_IND:
            TAF_CBA_RcvAsGsStatusChangeInd((RR_CBS_GS_STATUS_CHANGE_IND_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcGasMsg:Invalid Msg");
            break;
    }
}



VOS_VOID TAF_CBA_ProcWrrMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_CBS_MSG_DATA                   *pstMsgData;

    pstMsgData = (TAF_CBS_MSG_DATA *)pstMsg;
    switch (pstMsgData->enMsgID)
    {
#if (FEATURE_ETWS == FEATURE_ON)
        case ID_RR_CBS_ETWS_PRIMARY_NOTIFY_IND:
            TAF_CBA_RcvAsEtwsPrimNotifyInd((RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU *)pstMsg);
            break;
#endif
        case ID_RR_CBS_GS_STATUS_CHANGE_IND:
            TAF_CBA_RcvAsGsStatusChangeInd((RR_CBS_GS_STATUS_CHANGE_IND_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcWrrMsg:Invalid Msg");
            break;
    }
}


VOS_VOID TAF_CBA_ProcBmcMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_CBS_MSG_DATA                   *pstMsgData;

    pstMsgData = (TAF_CBS_MSG_DATA *)pstMsg;
    switch (pstMsgData->enMsgID)
    {
        case ID_BMC_CBS_CFG_CNF:
            TAF_CBA_RcvAsCbsCfgCnf((BMC_CBS_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_BMC_CBS_DATA_IND :
            TAF_CBA_RcvBmcCbsDataInd((BMC_CBS_DATA_IND_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcBmcMsg:Invalid Msg");
            break;
    }
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID TAF_CBA_ProcLrrcMsg(
    struct MsgCB                       *pstMsg
)
{
    TAF_CBS_MSG_DATA                   *pstMsgData;

    pstMsgData = (TAF_CBS_MSG_DATA *)pstMsg;
    switch (pstMsgData->enMsgID)
    {
#if (FEATURE_ETWS == FEATURE_ON)
        case ID_RR_CBS_ETWS_PRIMARY_NOTIFY_IND:
            TAF_CBA_RcvAsEtwsPrimNotifyInd((RR_CBS_ETWS_PRIMARY_NOTIFY_IND_STRU *)pstMsg);
            break;
#endif

        case ID_LRRC_CBS_DATA_IND:
            TAF_CBA_SetNetRatType(TAF_CBA_NET_RAT_TYPE_LTE);
            TAF_CBA_RcvLrrcCbsDataInd((LRRC_CBS_DATA_IND_STRU *)pstMsg);
            break;

        case ID_RR_CBS_GS_STATUS_CHANGE_IND:
            TAF_CBA_RcvAsGsStatusChangeInd((RR_CBS_GS_STATUS_CHANGE_IND_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcLrrcMsg:Invalid Msg");
            break;
    }

}

#endif  /* (FEATURE_ON == FEATURE_LTE) */

VOS_VOID TAF_CBA_RcvAsCbsCfgCnf(
    BMC_CBS_CFG_CNF_STRU             *pstCfgCnf
)
{

    if ( TAF_CBS_CFG_RSLT_FAIL == pstCfgCnf->enRslt )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvAsCbsCfgCnf: Active cnf fail");
    }

}


VOS_VOID TAF_CBA_RcvGasCbsDataInd(
    GAS_CBS_DATA_IND_STRU              *pstGasDataInd
)
{
    VOS_UINT8                           ucPageLen;
    MN_MSG_CBRAW_TS_DATA_STRU          *pstCbRawData;
    VOS_UINT8                           ucPageNum;
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage;
    TAF_CBA_RECORD_STRU                 stNewRecord;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucTotalPage;
    VOS_UINT8                           ucPageIndex;

    pstCbRawData = (MN_MSG_CBRAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_CBRAW_TS_DATA_STRU) * (pstGasDataInd->ucPageNum));
    if ( VOS_NULL_PTR == pstCbRawData )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvGasCbsDataInd:Alloc Mem Failed");
        return;
    }


    PS_MEM_SET(pstCbRawData, 0x00, sizeof(MN_MSG_CBRAW_TS_DATA_STRU) * (pstGasDataInd->ucPageNum));

    ucPageNum = 0;
    for ( ucIndex = 0 ; ucIndex < pstGasDataInd->ucPageNum; ucIndex++ )
    {
        /* ��ÿ��CBS�ĳ���ȥ�����ֵ,����Ϊʵ�ʵĳ��� */

        if ( VOS_TRUE == TAF_CBA_GetRptAppFullPageFlg() )
        {
            ucPageLen = (VOS_UINT8)(pstGasDataInd->astPageData[ucIndex].ulLength);
        }
        else
        {
            ucPageLen = TAF_CBA_GetGsmCbsPageLen(&(pstGasDataInd->astPageData[ucIndex]));
        }

        /* �������С��ͷ�ĳ���,���ϱ� */
        if ( ucPageLen < TAF_CBA_MAX_CB_HEADER_LEN )
        {
            /* ��ά�ɲ� */
            TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_PAGELEN_INVALID);
            continue;
        }

        pstGsmPage = (MN_MSG_CBGSMPAGE_STRU*)pstGasDataInd->astPageData[ucIndex].aucData;

        /* �жϸ�ҳ������ֵ�Ƿ������ҳ�� */
        ucTotalPage = pstGsmPage->Pagesbit4;
        ucPageIndex = pstGsmPage->Pagebit4;

        /* ��� ucTotalPage��ucPageNumber��һ��Ϊ0,���� 0001 0001 ,�μ�Э��23041 9.4.1.2.4 */
        if ( ( 0x00 == ucTotalPage )
          || ( 0x00 == ucPageIndex ) )
        {
            ucTotalPage = 0x01;
            ucPageIndex = 0x01;
        }

        if (ucPageIndex > ucTotalPage)
        {
            /* ��ά�ɲ� */
            TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_PAGEINDEX_INVALID);
            continue;
        }

        /* �ж�CBS��Ϣ��MSG ID�Ƿ��ڼ����б��У�����������Ƚ���ҳ */
        if ( VOS_TRUE != TAF_CBA_IsCbsMsgIdValid( TAF_CBA_BuildCbsMsgId(pstGsmPage->ucMIdHigh, pstGsmPage->ucMIdLow)) )
        {
            /* ��ά�ɲ� */
            TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_CBS_MSGID_INVALID);
            continue;
        }

        /* ɾ���ظ����ʱ����ʱ��CBS��¼ */
        TAF_CBA_DelCbsExpiredRecord();

        /* �������ݼ�¼ */
        TAF_CBA_BuildGsmCbsRecord(pstGsmPage, &pstGasDataInd->stCurrNetworkInfo, &stNewRecord);

        /* ����Ƿ����ظ�����Ϣҳ, �ظ�����Ϣҳ���ñ�����ϱ���AT */
        if (VOS_TRUE == TAF_CBA_IsDupGsmCbsRecord(&stNewRecord))
        {
            continue;
        }

        /* ����ü�¼�� */
        TAF_CBA_SaveGsmCbsRecord(&stNewRecord);

        pstCbRawData[ucIndex].ulLen = ucPageLen;
        PS_MEM_CPY(pstCbRawData[ucIndex].aucData,
                   pstGasDataInd->astPageData[ucIndex].aucData,
                   ucPageLen);

        ucPageNum++;
    }

    /* ����Чҳ�����ϱ� */
    if (ucPageNum > 0)
    {
        /* ����ͳһ�Ĵ������ϱ�CBS��Envelope��USIM */
        TAF_CBA_ReportRcvCbsData(ucPageNum, pstCbRawData);
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbRawData);
}
VOS_UINT32 TAF_CBA_ConvertBmcCbsToGsmCbsFormat(
    BMC_CBS_DATA_IND_STRU              *pstDataPdu,
    VOS_UINT8                          *pucPageNum,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstPageDataInd
)
{

    VOS_UINT8                           ucPageIdx;
    VOS_UINT32                          ulIndex;
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage;
    VOS_UINT8                           ucPageSegment;
    VOS_UINT8                           ucPageSegmentOffset;
    VOS_UINT8                           ucPageNumInMsg;
    VOS_UINT16                          usLeftLength;
    TAF_CBA_CB_W_AIR_DATA_STRU         *pstCbWData;

    *pucPageNum     = 0;
    ucPageIdx       = 1;

    /* 23041 9.3.19 This parameter is of a fixed length of 82 octets and carries up to and including 82 octets of user information. Where the
    user information is less than 82 octets, the remaining octets must be filled with padding (see 3GPP TS 23.038 [3]).
    The content of a CBS-Message-Information-Page is passed transparently from the CBC to the MS/UE.
    In GSM the CBS-Message-Information-Page n becomes the 'Content of Message' parameter at the MS.
    In UMTS the CBS-Message-Information-Pages together with the associated CBS-Message-Information-Length
    parameter is broadcasted as a single unit over the radio inteface.
    In the case where the user information is GSM 7 bit default alphabet encoded, the appropriate padding characters and
    bit-fill are added to the end of the user information to complete the CBC-Message-Information-Page
    (see 3GPP TS 23.038 [3]).
    In the case where the user information is 8 bit encoded, the appropriate padding octets are added to the end of the user
    information to complete the CBC-Message-Information-Page (see 3GPP TS 23.038 [3]). */

    /*
    23041 9.4.2.2.5 CBDATA
    -    Number-of-Pages;
    - CBS-Message-Information-Page;
    - CBS-Message-Information-Length.
    Octet Number(s) Parameter
    1 Number-of-Pages
    2 �C 83 CBS-Message-Information-Page 1
    84 CBS-Message-Information-Length 1
     �� ��
    CBS-Message-Information-Page n
    CBS-Message-Information-Length n

    */

    /*  ������Ϣ��Я����Page����,��䵽��Ϣ����������Ϣ��Я����Page����Ϊ׼,
        ����ȡҳ����Ҫ�ۺϿ�����Ϣ���Ⱥ���Ϣ��Я����ҳ�� */
    if ( pstDataPdu->usCBDataLen <= TAF_CBA_CB_W_NUM_OF_PAGES_POS )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ConvertBmcCbsToGsmCbsFormat: CbDataLen too small");
        return VOS_ERR;
    }

    /* ��0���ֽڱ�ʾҳ�� */
    ucPageNumInMsg = pstDataPdu->aucCBData[0];

    /* ���㵱ǰCBS��Ϣ�ĳ��ȵķֶ� */
    ucPageSegmentOffset = (pstDataPdu->usCBDataLen
                - TAF_CBA_CB_W_NUM_OF_PAGES_POS)%TAF_CBA_MAX_CB_PAGE_LEN;

    ucPageSegment = (VOS_UINT8)((pstDataPdu->usCBDataLen
                - TAF_CBA_CB_W_NUM_OF_PAGES_POS)/TAF_CBA_MAX_CB_PAGE_LEN);

    if ( 0 != ucPageSegmentOffset )
    {
        ucPageSegment++;
    }

    /* ҳ������ȷ,��ֱ�ӷ��� */
    if ( ( 0 == ucPageNumInMsg ) || ( 0 == ucPageSegment ) )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ConvertBmcCbsToGsmCbsFormat:Empty CbDataLen");
        return VOS_ERR;
    }

    *pucPageNum = ucPageSegment;

    if ( *pucPageNum > TAF_CBA_MAX_CBMPAGE_NUM )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ConvertBmcCbsToGsmCbsFormat:Too Long CbDataLen");
        *pucPageNum = TAF_CBA_MAX_CBMPAGE_NUM;
    }

    pstCbWData = (TAF_CBA_CB_W_AIR_DATA_STRU *)(&(pstDataPdu->aucCBData[TAF_CBA_CB_W_NUM_OF_PAGES_POS]));

    /* ������CBS��Ϣģ��ΪGģ��CBS��Ϣ�ĸ�ʽ */
    usLeftLength = pstDataPdu->usCBDataLen - TAF_CBA_CB_W_NUM_OF_PAGES_POS;

    for ( ulIndex = 0 ; ulIndex < *pucPageNum ; ulIndex++ )
    {
        pstGsmPage = (MN_MSG_CBGSMPAGE_STRU *)(pstPageDataInd->aucData);

        pstGsmPage->ucDCS     = pstDataPdu->ucDataCodeScheme;
        pstGsmPage->ucSnHigh  = (VOS_UINT8)((pstDataPdu->usSerialNum & 0xFF00) >> 8);
        pstGsmPage->ucSnLow   = (VOS_UINT8)(pstDataPdu->usSerialNum & 0x00FF);
        pstGsmPage->ucMIdHigh = (VOS_UINT8)((pstDataPdu->usCBMID & 0xFF00) >> 8);
        pstGsmPage->ucMIdLow  = (VOS_UINT8)((pstDataPdu->usCBMID & 0x00FF));
        pstGsmPage->Pagebit4  = ucPageIdx;
        pstGsmPage->Pagesbit4 = ucPageNumInMsg;

        /* ��ȡ��ǰCBS��Ϣ����Ч���� */
        if (usLeftLength >= TAF_CBA_MAX_CB_PAGE_LEN)
        {
            if ( VOS_TRUE == TAF_CBA_GetRptAppFullPageFlg() )
            {
                pstPageDataInd->ulLen = TAF_CBA_MAX_CBDATA_LEN   + TAF_CBA_MAX_CB_HEADER_LEN;
            }
            else
            {
                pstPageDataInd->ulLen = pstCbWData->ucCbsDataLen + TAF_CBA_MAX_CB_HEADER_LEN;
            }

            /*�˴���Ҫ���б��������������ݳ���*/
            if ( pstPageDataInd->ulLen > TAF_CBA_MAX_CBPAGE_LEN )
            {
                pstPageDataInd->ulLen = TAF_CBA_MAX_CBPAGE_LEN;
            }
            PS_MEM_CPY(pstGsmPage->aucContent,
                   pstCbWData->aucCbsData,
                   TAF_CBA_MAX_CBDATA_LEN);

            usLeftLength -= TAF_CBA_MAX_CB_PAGE_LEN;
        }
        else
        {
            pstPageDataInd->ulLen = usLeftLength + TAF_CBA_MAX_CB_HEADER_LEN;

            PS_MEM_CPY(pstGsmPage->aucContent,
                       pstCbWData->aucCbsData,
                       usLeftLength);
            break;
        }
        ucPageIdx++;
        pstCbWData++;
        pstPageDataInd++;
    }

    return VOS_OK;
}


VOS_VOID TAF_CBA_RcvBmcCbsDataInd(
    BMC_CBS_DATA_IND_STRU              *pstBmcDataInd
)
{
    MN_MSG_CBRAW_TS_DATA_STRU          *pstCbRawData;
    VOS_UINT8                           ucPageNum;
    VOS_UINT32                          ulRet;
    TAF_CBA_RECORD_STRU                 stNewRecord;

    /* �ж���ϢID�Ƿ���Ч */
    if (VOS_TRUE != TAF_CBA_IsCbsMsgIdValid(pstBmcDataInd->usCBMID))
    {
        /* ��ά�ɲ� */
        TAF_CBA_SndOmLogInfo(TAF_CBA_OM_LOG_CBS_MSGID_INVALID);
        return;
    }

    /* ����ɾ���ظ����ʱ����ʱ��CBS��¼ */
    TAF_CBA_DelCbsExpiredRecord();

    /* ����CBS��Ϣ���ݼ�¼ */
    TAF_CBA_BuildBmcCbsRecord(pstBmcDataInd, &stNewRecord);

    /* ����Ƿ����ظ�����Ϣ, �ظ�����Ϣ, ���ñ�����ϱ���AT */
    if (VOS_TRUE == TAF_CBA_IsDupBmcCbsRecord(&stNewRecord))
    {
        return;
    }

    /* �����¼ */
    TAF_CBA_SaveBmcCbsRecord(&stNewRecord);

    pstCbRawData = (MN_MSG_CBRAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_CBRAW_TS_DATA_STRU) * TAF_CBA_MAX_CBMPAGE_NUM);
    if (VOS_NULL_PTR == pstCbRawData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvBmcCbsDataInd:Alloc Mem Failed");
        return;
    }


    PS_MEM_SET(pstCbRawData, 0x00, sizeof(MN_MSG_CBRAW_TS_DATA_STRU) * TAF_CBA_MAX_CBMPAGE_NUM);


    /* �����ϱ���CBS������GSMģʽ��,������Ҫ��W��ʽ��CBS��Ϣת��ΪGģʽ��CBS��Ϣ���� */
    ulRet = TAF_CBA_ConvertBmcCbsToGsmCbsFormat(pstBmcDataInd, &ucPageNum, pstCbRawData);
    if ( VOS_OK != ulRet )
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstCbRawData);
        return;
    }

    /* ����ͳһ�Ĵ������ϱ�CBS��Envelope��USIM */
    TAF_CBA_ReportRcvCbsData(ucPageNum, pstCbRawData);

    PS_MEM_FREE(WUEPS_PID_TAF, pstCbRawData);
}


VOS_VOID TAF_CBA_RcvLrrcCbsDataInd(
    LRRC_CBS_DATA_IND_STRU             *pstBmcDataInd
)
{
    /* LRRC����CBS��Ϣʱ������BMC��ͬ�����ݽṹ, ��ֱ�ӵ���BMC�Ĵ��������� */
    TAF_CBA_RcvBmcCbsDataInd((BMC_CBS_DATA_IND_STRU*)pstBmcDataInd);
}
VOS_VOID TAF_CBA_RcvAsGsStatusChangeInd(
    RR_CBS_GS_STATUS_CHANGE_IND_STRU   *pstGsChangeInd
)
{
    TAF_CBS_GS_CHG_TYPE_ENUM_UINT8      enTmpGsChgType;
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;
    TAF_CBA_NETWORK_INFO_STRU           stCurrNetworkInfo;

    /* ͨ��SenderPid��ȡ����ģʽ */
    enNetRatType = TAF_CBA_GetRatTypeBySenderPid(pstGsChangeInd->ulSenderPid);

    if ( TAF_CBA_NET_RAT_TYPE_BUTT == enNetRatType )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvAsGsStatusChangeInd: ERR enNetRatType.");
        return;
    }

    /* ��ȡGS CHG ��Ϣ�е� CHG TYPE, ���������� */
    enTmpGsChgType = pstGsChangeInd->enGsChgType;

    if (enTmpGsChgType >= TAF_CBS_GS_CHG_TYPE_CHG_BUTT)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvAsGsStatusChangeInd: ERR GS CHG TYPE.");
        return;
    }

    /* ���GS CHG ��Ϣ�е� ������Ϣ */
    if ( (VOS_TRUE != pstGsChangeInd->stCurrNetworkInfo.bitOpPlmnId)
      || (VOS_TRUE != pstGsChangeInd->stCurrNetworkInfo.bitOpSa)
      || (VOS_TRUE != pstGsChangeInd->stCurrNetworkInfo.bitOpCellId) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvAsGsStatusChangeInd: ERR NetworkInfo.");
        return;
    }

    /* ��ȡ��ǰ��������Ϣ */
    PS_MEM_SET( &stCurrNetworkInfo, 0x00, sizeof(stCurrNetworkInfo) );

    stCurrNetworkInfo.enCurrNetRatType = enNetRatType;
    stCurrNetworkInfo.stCurPlmn.ulMcc  = pstGsChangeInd->stCurrNetworkInfo.stCurPlmn.ulMcc;
    stCurrNetworkInfo.stCurPlmn.ulMnc  = pstGsChangeInd->stCurrNetworkInfo.stCurPlmn.ulMnc;
    stCurrNetworkInfo.usSa             = pstGsChangeInd->stCurrNetworkInfo.usSa;
    stCurrNetworkInfo.ulCellId         = pstGsChangeInd->stCurrNetworkInfo.ulCellId;

    /* ��ȡ�ϴ� GS_STATUS_CHANGE_IND �е�������Ϣ */

    /* �������ϵͳ�ĳ���, ��Ҫ�����ж�GS CHG������.
       ��ΪĿǰ:
       Wģ, ������ϢȫΪ��Чֵ(ֻ��IDLE��P̬�ϱ�GS CHG IND).
            ��ϵͳ������, ÿ�����½���Wפ���ɹ�, W����NAS�ϱ�GS_CHG_IND(�仯����������Wģȫ�ֱ����е�������Ϣ�ıȽ�);
       Gģ, ������Ϣ��Ϊ��Чֵ.
            ��ϵͳ������, ÿ�����½���Gפ���ɹ�, G����NAS�ϱ�GS_CHG_IND(Gģ����������Ϣ��ȫ�ֱ���, ���Զ���PLMN�仯);
       Lģ, ������Ϣ��Ϊ��Чֵ.
            ��ϵͳ������, ÿ�����½���Lפ���ɹ�, L����NAS�ϱ�GS_CHG_IND(�仯���ͺ�W����)
    */

    /* ���汾��GS_STATUS_CHANGE_IND �е�������Ϣ */
    TAF_CBA_SetOldNetworkInfo(&stCurrNetworkInfo);

    /* δ�仯�򲻴��� */
    if ( (TAF_CBS_GS_CHG_TYPE_NO_CHG   == enTmpGsChgType)
      || (TAF_CBS_GS_CHG_TYPE_CHG_RAT  == enTmpGsChgType) )
    {
        return;
    }

#if (FEATURE_ETWS == FEATURE_ON)

    /* ɾ����֪ͨ��¼�е���Ч�� */
    TAF_CBA_DelInvalidEtwsPrimNtfRecordByGsChgType(enTmpGsChgType, enNetRatType);
#endif

    /* ɾ��CBS��¼�е���Ч�� */
    TAF_CBA_DelInvalidCbsRecordByGsChgType(enTmpGsChgType, enNetRatType);

}


TAF_CBA_NET_RAT_TYPE_ENUM_UINT8 TAF_CBA_GetRatTypeBySenderPid(
    VOS_UINT32                          ulSenderPid
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;

    switch (ulSenderPid)
    {
        case WUEPS_PID_WRR:
        case WUEPS_PID_BMC:

            enNetRatType = TAF_CBA_NET_RAT_TYPE_WCDMA;
            break;

        case UEPS_PID_GAS:

            enNetRatType = TAF_CBA_NET_RAT_TYPE_GSM;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_ERRC:

            enNetRatType = TAF_CBA_NET_RAT_TYPE_LTE;
            break;
#endif

        default:

            enNetRatType = TAF_CBA_NET_RAT_TYPE_BUTT;
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CBA_GetRatTypeBySenderPid: ERR ulSenderPid.");
            break;
    }

    return enNetRatType;
}



VOS_UINT32  TAF_CBA_IsCbsEnable(VOS_VOID)
{
    TAF_CBA_CBSTATUS_ENUM_UINT8         enCbsStatus;
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;

    /* ��ȡ��ǰCBS��Ϣ�Ƿ񼤻��־ */
    enCbsStatus     = TAF_CBA_GetCbsStatus();

    enNetMode       = TAF_CBA_GetNetRatType();

    /* ��������NV�и�ģʽCBS����ͬʱ��ģʽ�꿪���Ѵ򿪲�Ĭ��CBS���� */
#if (FEATURE_ON == FEATURE_WCBS)
    if ( ((TAF_CBA_CBSTATUS_W_ENABLE == enCbsStatus) || (TAF_CBA_CBSTATUS_WG_ENABLE == enCbsStatus))
      && (TAF_CBA_NET_RAT_TYPE_WCDMA == enNetMode) )
    {
        return  VOS_TRUE;
    }
#endif

#if (FEATURE_ON == FEATURE_GCBS)
    if ( ((TAF_CBA_CBSTATUS_G_ENABLE == enCbsStatus) || (TAF_CBA_CBSTATUS_WG_ENABLE == enCbsStatus))
      && (TAF_CBA_NET_RAT_TYPE_GSM == enNetMode) )
    {
        return VOS_TRUE;
    }
#endif

#if (FEATURE_ON == FEATURE_LTE)
    if (TAF_CBA_NET_RAT_TYPE_LTE == enNetMode)
    {
        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

#if (FEATURE_ETWS == FEATURE_ON)

VOS_UINT32 TAF_CBA_IsCbsMsgIdValid_ETWS(
    VOS_UINT16                          usMsgId
)
{
    VOS_UINT32                          ulIsInCbsActiveList;
    VOS_UINT32                          ulIsInEtwsList;

    ulIsInCbsActiveList = TAF_CBA_IsMsgIdInCbsActiveList(usMsgId);

    /* CBS������ETWS���������, ���û����õļ����б��ж�;
       CBS������ETWS�ر�, ���û����õļ����б��ж�, ETWSҲ������ͨCBS�ϱ� */
    if (VOS_TRUE == TAF_CBA_IsCbsEnable())
    {
        if (VOS_TRUE == ulIsInCbsActiveList)
        {
            return VOS_TRUE;
        }
        return VOS_FALSE;
    }

    ulIsInEtwsList  = TAF_CBA_IsMsgIdInEtwsMsgIdList(usMsgId);

    /* CBS�رգ�ETWS�����������������������б��� ETWS��ص�MSG ID */
    if (VOS_TRUE  == TAF_CBA_GetEtwsEnableFlg())
    {
        if ( (VOS_TRUE == ulIsInCbsActiveList)
          && (VOS_TRUE == ulIsInEtwsList) )
        {
            return VOS_TRUE;
        }
        return VOS_FALSE;
    }

    /* ETWS�رգ�CBS�ر� */
    return VOS_FALSE;
}

#endif


VOS_UINT32  TAF_CBA_IsCbsMsgIdValid(
    VOS_UINT16                          usMsgId
)
{
#if (FEATURE_ETWS == FEATURE_ON)

    return TAF_CBA_IsCbsMsgIdValid_ETWS(usMsgId);

#else

    /* �ж�CBS��ϢID�Ƿ��ڼ����б��� */
    return TAF_CBA_IsMsgIdInCbsActiveList(usMsgId);
#endif
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_GetGsmCbsPageLen
 ��������  : ��ȡGAS�¹㲥����Ϣһҳ��ʵ�ʳ���
 �������  : pstCbTpduData - ��GSM��ʽ��ŵĹ㲥����Ϣҳ
 �������  : ��
 �� �� ֵ  : �㲥����Ϣһҳ��ʵ�ʳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��20��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_CBA_GetGsmCbsPageLen(
    GAS_CBS_PAGE_DATA_STRU             *pstCbPageData
)
{
    VOS_UINT32                          ulPos;
    VOS_UINT8                           ucPageLen;
    VOS_UINT32                          ulCbpageIdx;

    /* 3GPP 23.041 9.4.1.2��:
      Octet Number(s)   Field
      1-2               Serial Number
      3-4               Message Identifier
      5                 Data Coding Scheme
      6                 Page Parameter
      7-88              Content of Message
    */

    ucPageLen = TAF_CBA_MAX_CBPAGE_LEN;

    for (ulCbpageIdx = 0; ulCbpageIdx < TAF_CBA_MAX_CBPAGE_LEN; ulCbpageIdx++)
    {
        ulPos   = (TAF_CBA_MAX_CBPAGE_LEN - ulCbpageIdx) - 1;

        if (TAF_CBA_PADDING_OCTET != pstCbPageData->aucData[ulPos])
        {
            break;
        }
        ucPageLen--;
    }

    return ucPageLen;
}


VOS_VOID TAF_CBA_BuildGsmCbsRecord(
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage,
    TAF_CBS_NETWORK_INFO_STRU          *pstCampPlmnInfo,
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    VOS_UINT8                           ucTotalPage;
    VOS_UINT8                           ucPageIndex;

    ucTotalPage = pstGsmPage->Pagesbit4;
    ucPageIndex = pstGsmPage->Pagebit4;

    /* ��� ucTotalPage��ucPageNumber��һ��Ϊ0,���� 0001 0001 ,�μ�Э��23041 9.4.1.2.4 */
    if ( ( 0x00 == ucTotalPage )
      || ( 0x00 == ucPageIndex ) )
    {
        ucTotalPage = 0x01;
        ucPageIndex = 0x01;
    }

    PS_MEM_SET(pstNewRecord, 0x00, sizeof(TAF_CBA_RECORD_STRU));

    pstNewRecord->enNetMode        = TAF_CBA_NET_RAT_TYPE_GSM;
    pstNewRecord->ucTotalPage      = ucTotalPage;
    pstNewRecord->usMsgID          = TAF_CBA_BuildCbsMsgId(pstGsmPage->ucMIdHigh, pstGsmPage->ucMIdLow);
    pstNewRecord->usSN             = TAF_CBA_BuildCbsSN(pstGsmPage->ucSnHigh, pstGsmPage->ucSnLow);
    pstNewRecord->stPlmn.ulMcc     = pstCampPlmnInfo->stCurPlmn.ulMcc;
    pstNewRecord->stPlmn.ulMnc     = pstCampPlmnInfo->stCurPlmn.ulMnc;
    pstNewRecord->ulRcvTimeTick    = VOS_GetTick();

    /*lint -e701*/
    /* ����bitmap ,�˴�ucPageIndex��СΪ1,������Ҫ����(ucPageIndex - 1) */
    pstNewRecord->usPageBitmap     = TAF_CBA_BuildGsmCbsPageBitmap(ucPageIndex);
    /*lint +e701*/

    /* ��ͨCBSû���ظ����ʱЧҪ�󣬳���ʵ������Ϊ0 ��ʾ������Ч */
    pstNewRecord->ulDupDetcTimeLen = 0;

}
VOS_UINT32 TAF_CBA_IsDupGsmCbsRecord(
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT16                          usRcvCbsNum;
    VOS_UINT16                          ulIndex;
    VOS_UINT32                          ulSameGsCode;
    VOS_UINT32                          ulSameMsgCode;
    VOS_UINT32                          ulSameUpdateNumber;


    if ( VOS_TRUE != TAF_CBA_IsNeedDupDetectCbs((pstNewRecord->usMsgID)) )
    {
        /* ����Ҫ���ظ���������Ϊ �����ظ��ļ�¼�� */
        return VOS_FALSE;
    }


    pstRcvCbsList   = TAF_CBA_GetRcvCbsList();
    usRcvCbsNum     = TAF_CBA_GetRcvCbsNum();

    for ( ulIndex = 0; ulIndex < usRcvCbsNum; ulIndex++ )
    {
        /* �жϽ���ģʽ */
        if (pstNewRecord->enNetMode != pstRcvCbsList[ulIndex].enNetMode)
        {
            continue;
        }

        /* �ж� MSG ID */
        if (pstNewRecord->usMsgID != pstRcvCbsList[ulIndex].usMsgID)
        {
            continue;
        }

        ulSameGsCode       = TAF_CBA_IsSameGsCode(pstNewRecord->usSN, pstRcvCbsList[ulIndex].usSN);
        ulSameMsgCode      = TAF_CBA_IsSameMsgCode(pstNewRecord->usSN, pstRcvCbsList[ulIndex].usSN);
        ulSameUpdateNumber = TAF_CBA_IsSameUpdateNum(pstNewRecord->usSN, pstRcvCbsList[ulIndex].usSN);

        if ( !((VOS_TRUE == ulSameGsCode)
         && (VOS_TRUE == ulSameMsgCode)
         && (VOS_TRUE == ulSameUpdateNumber)))
        {
            continue;
        }
        /* ���˸о���˳��ֳ����������������Э��: GS,MSG ID,MSG CODE��ͬʱ�����յ�update numberΪ1��
           ��ҳ��Ϊ2��indexΪ1��CBS��Ϣ�����յ�update numberΪ0����ҳ��Ϊ2��indexΪ2��CBS��Ϣʱ��
           ��Ȼ�ϱ���������Ϊ������Э�飬�ʴ˴�û������޸ġ�
        */
        if ( pstNewRecord->usSN == pstRcvCbsList[ulIndex].usSN)
        {
            /* �Ƚ� Total Page */
            if (pstNewRecord->ucTotalPage != pstRcvCbsList[ulIndex].ucTotalPage)
            {
                /* ��ά�ɲ� */
                TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_CBS_RECORD,
                                           &(pstRcvCbsList[ulIndex]));

                /* �ѽ��չ������ظ���Ϣҳ */
                return VOS_TRUE;
            }

        /* �жϸ�ҳ�Ƿ��ѽ��չ� */
        if (0 != (pstNewRecord->usPageBitmap & pstRcvCbsList[ulIndex].usPageBitmap))
        {
            /* ��ά�ɲ� */
            TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_CBS_RECORD,
                                       &(pstRcvCbsList[ulIndex]));

                /* �ѽ��չ������ظ���Ϣҳ */
                return VOS_TRUE;
            }
        }
        else
        {
            /* ��ά�ɲ� */
            TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_CBS_RECORD,
                                           &(pstRcvCbsList[ulIndex]));

            /* �ѽ��չ������ظ���Ϣҳ */
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}


VOS_VOID TAF_CBA_AppendCbsRecord(
    TAF_CBA_RECORD_STRU                *pstAppendRecord
)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT16                          usRcvCbsNum;
    VOS_UINT16                          usAppendInx;
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType;

    pstRcvCbsList   = TAF_CBA_GetRcvCbsList();
    usRcvCbsNum     = TAF_CBA_GetRcvCbsNum();
    usAppendInx     = 0;

    /* ��¼���в����ں��¼�¼��MSG ID��MSG CODE��ͬ�ļ�¼��, ��������¼�� */
    if ( TAF_CBA_MAX_CBS_RECORD_NUM == usRcvCbsNum )
    {
        /* �б��������ȡ����ļ�¼���index, ����֮ */
        usAppendInx = TAF_CBA_GetEarliestCbsRecordInx();

        /* �����¼�Ŀ�ά�ɲ���Ϣ */
        TAF_CBA_SndOmDeledRecordInfo(TAF_CBA_OM_MSG_DEL_DEL_CBS_RECORD,
                                     TAF_CBA_OM_DEL_REASON_LIST_FULL,
                                     &pstRcvCbsList[usAppendInx]);

        /* �����¼ */
        pstRcvCbsList[usAppendInx] = (*pstAppendRecord);

        enSaveType  = TAF_CBA_OM_SAVE_TYPE_RECORD_FULL;

    }
    else
    {
        /* �б�δ���������������һ����¼ */
        usAppendInx = usRcvCbsNum;

        /* �����¼ */
        pstRcvCbsList[usAppendInx] = (*pstAppendRecord);

        /* ���¼�¼���� */
        usRcvCbsNum++;
        TAF_CBA_SetRcvCbsNum(usRcvCbsNum);

        enSaveType = TAF_CBA_OM_SAVE_TYPE_APPEND_RECORD;
    }

    /* ��ά�ɲ� */
    TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_CBS_RECORD,
                                 enSaveType,
                                 pstAppendRecord,
                                 usRcvCbsNum);
}


VOS_VOID TAF_CBA_SaveGsmCbsRecord(
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    VOS_UINT32                          ulSameRecordInx;
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT32                          ulSameGsCode;
    VOS_UINT32                          ulSameUpdateNum;
    TAF_CBA_OM_SAVE_TYPE_ENUM_UINT8     enSaveType;

    pstRcvCbsList   = TAF_CBA_GetRcvCbsList();
    ulSameRecordInx = 0;

    /* ��¼���в����ں��¼�¼��MSG ID��MSG CODE��ͬ�ļ�¼��, ��������¼�� */
    if ( VOS_TRUE != TAF_CBA_GetCbsRecordInxByMsgIdCode(pstNewRecord, &ulSameRecordInx) )
    {
        TAF_CBA_AppendCbsRecord(pstNewRecord);
        return;
    }

    /* ��¼���д��ں��¼�¼��MSG ID��MSG CODE��ͬ�ļ�¼��, ������� PageBitmap �� ����ԭ��¼ */

    ulSameGsCode    = TAF_CBA_IsSameGsCode(pstNewRecord->usSN, pstRcvCbsList[ulSameRecordInx].usSN);
    ulSameUpdateNum = TAF_CBA_IsSameUpdateNum(pstNewRecord->usSN, pstRcvCbsList[ulSameRecordInx].usSN);

    /* �ж�GS��UpdaeNumber����ҳ���������ֶ��Ƿ�ȫ��ͬ, ȫ��ͬ������� PageBitMap, ���򸲸�ԭ��¼�� */
    if ( (VOS_TRUE == ulSameGsCode)
      && (VOS_TRUE == ulSameUpdateNum)
      && (pstNewRecord->ucTotalPage == pstRcvCbsList[ulSameRecordInx].ucTotalPage) )
    {
        /* ������ PageBitMap */
        pstRcvCbsList[ulSameRecordInx].usPageBitmap |= (pstNewRecord->usPageBitmap);

        enSaveType = TAF_CBA_OM_SAVE_TYPE_UPDATE_RECORD_BITMAP;
    }
    else
    {
        /* ���� ���� */
        pstRcvCbsList[ulSameRecordInx] = (*pstNewRecord);

        enSaveType = TAF_CBA_OM_SAVE_TYPE_REPLACE_RECORD;
    }

    /* ��ά�ɲ� */
    TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_CBS_RECORD,
                                 enSaveType,
                                 pstNewRecord,
                                 TAF_CBA_GetRcvCbsNum());
}


VOS_UINT32 TAF_CBA_GetCbsRecordInxByMsgIdCode(
    TAF_CBA_RECORD_STRU                *pstRecord,
    VOS_UINT32                         *pulIndex
)
{
    TAF_CBA_RECORD_STRU                *pstListAddr;
    VOS_UINT32                          usCbsRecordNum;
    VOS_UINT32                          ulInx;

    pstListAddr    = TAF_CBA_GetRcvCbsList();
    usCbsRecordNum = TAF_CBA_GetRcvCbsNum();

    for ( ulInx = 0; ulInx < usCbsRecordNum; ulInx++ )
    {
        /* �жϽ���ģʽ */
        if (pstRecord->enNetMode != pstListAddr[ulInx].enNetMode)
        {
            continue;
        }

        /* �ж�PLMN */
        if ( (pstRecord->stPlmn.ulMcc != pstListAddr[ulInx].stPlmn.ulMcc)
          || (pstRecord->stPlmn.ulMnc != pstListAddr[ulInx].stPlmn.ulMnc) )
        {
            continue;
        }

        /* �ж� MSG ID �� MSG CODE */
        if ( (VOS_TRUE == TAF_CBA_IsSameMsgCode(pstRecord->usSN, pstListAddr[ulInx].usSN))
          && (pstRecord->usMsgID == pstListAddr[ulInx].usMsgID) )
        {
            *pulIndex = ulInx;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT16  TAF_CBA_GetEarliestCbsRecordInx(VOS_VOID)
{
    TAF_CBA_RECORD_STRU                *pstRecordList;
    VOS_UINT16                          usEarliestInx;
    VOS_UINT16                          usIndex;
    VOS_UINT32                          ulEarliestTick;

    pstRecordList  = TAF_CBA_GetRcvCbsList();

    usEarliestInx  = 0;
    ulEarliestTick = pstRecordList[0].ulRcvTimeTick;

    for ( usIndex = 1; usIndex < TAF_CBA_GetRcvCbsNum(); usIndex++ )
    {
        if ( pstRecordList[usIndex].ulRcvTimeTick < ulEarliestTick )
        {
            usEarliestInx   = usIndex;
            ulEarliestTick  = pstRecordList[usIndex].ulRcvTimeTick;
        }
    }

    return usEarliestInx;

}


VOS_VOID TAF_CBA_BuildBmcCbsRecord(
    BMC_CBS_DATA_IND_STRU              *pstBmcDataInd,
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = TAF_CBA_GetRatTypeBySenderPid(pstBmcDataInd->ulSenderPid);

    PS_MEM_SET(pstNewRecord, 0x00, sizeof(TAF_CBA_RECORD_STRU));

    pstNewRecord->enNetMode     = enRatType;
    pstNewRecord->usMsgID       = pstBmcDataInd->usCBMID;
    pstNewRecord->usSN          = pstBmcDataInd->usSerialNum;
    pstNewRecord->stPlmn.ulMcc  = pstBmcDataInd->stCurrNetworkInfo.stCurPlmn.ulMcc;
    pstNewRecord->stPlmn.ulMnc  = pstBmcDataInd->stCurrNetworkInfo.stCurPlmn.ulMnc;
    pstNewRecord->ulRcvTimeTick = VOS_GetTick();

#if (FEATURE_ETWS == FEATURE_ON)
    pstNewRecord->ulDupDetcTimeLen = TAF_CBA_GetCbsDupDetcTimeLen(&(pstNewRecord->stPlmn),
                                                                     pstNewRecord->usMsgID);
#else
    /* ��ͨCBSû���ظ����ʱЧҪ�󣬳���ʵ������Ϊ0 ��ʾ������Ч */
    pstNewRecord->ulDupDetcTimeLen = 0;
#endif

}

#if (FEATURE_ON == FEATURE_ETWS)
VOS_UINT32 TAF_CBA_IsCbsRecordSamePlmn(
    TAF_CBA_RECORD_STRU                *pstSrcRecord,
    TAF_CBA_RECORD_STRU                *pstDstRecord
)
{
    /* �ж�PLMN */
    if ( (pstSrcRecord->stPlmn.ulMcc != pstDstRecord->stPlmn.ulMcc)
      || (pstSrcRecord->stPlmn.ulMnc != pstDstRecord->stPlmn.ulMnc) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
#endif
VOS_UINT32 TAF_CBA_IsDupBmcCbsRecord(
    TAF_CBA_RECORD_STRU                *pstRecord
)
{
    TAF_CBA_RECORD_STRU                *pstCbsListAddr;
    VOS_UINT16                          usCbsRecordNum;
    VOS_UINT16                          usInx;
    VOS_UINT32                          ulSameGsCode;
    VOS_UINT32                          ulSameMsgCode;
    VOS_UINT32                          ulSameUpdateNumber;


    if ( VOS_TRUE != TAF_CBA_IsNeedDupDetectCbs(pstRecord->usMsgID) )
    {
        /* ����Ҫ���ظ���������Ϊ �����ظ��ļ�¼�� */
        return VOS_FALSE;
    }


    pstCbsListAddr  = TAF_CBA_GetRcvCbsList();
    usCbsRecordNum  = TAF_CBA_GetRcvCbsNum();

    for ( usInx = 0; usInx < usCbsRecordNum; usInx++ )
    {
        /* �жϽ���ģʽ */
        if (pstRecord->enNetMode != pstCbsListAddr[usInx].enNetMode)
        {
            continue;
        }

#if (FEATURE_ON == FEATURE_ETWS)
        /* DoCoMo��ETWS����ǿ���ظ���ⶨ�����Լ���ʱ, ��Ҫ�ж�PLMN */
        if (VOS_TRUE == TAF_CBA_GetEnhDupDetcFlg())
        {
            if ( VOS_TRUE != TAF_CBA_IsCbsRecordSamePlmn(pstRecord, &(pstCbsListAddr[usInx]) ))
            {
                continue;
            }
        }
#endif
        /* �ж� MSG ID */
        if (pstRecord->usMsgID != pstCbsListAddr[usInx].usMsgID)
        {
            continue;
        }

        /* �Ƚ�����SN, Ŀǰ����ֱ��ж� MSG CODE, GS �� UPDATE NUMBER */
        ulSameGsCode       = TAF_CBA_IsSameGsCode(pstRecord->usSN, pstCbsListAddr[usInx].usSN);
        ulSameMsgCode      = TAF_CBA_IsSameMsgCode(pstRecord->usSN, pstCbsListAddr[usInx].usSN);
        ulSameUpdateNumber = TAF_CBA_IsSameUpdateNum(pstRecord->usSN, pstCbsListAddr[usInx].usSN);

        if ( ((VOS_TRUE == ulSameGsCode)
         && (VOS_TRUE == ulSameMsgCode)
         && (VOS_TRUE == ulSameUpdateNumber)))
        {
            /* ��ά�ɲ� */
            TAF_CBA_SndOmDupRecordInfo(TAF_CBA_OM_MSG_DUP_CBS_RECORD,
                                       &(pstCbsListAddr[usInx]));

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_VOID TAF_CBA_SaveBmcCbsRecord (
    TAF_CBA_RECORD_STRU                *pstNewRecord
)
{
    TAF_CBA_RECORD_STRU                *pstRcvCbsList;
    VOS_UINT16                          usRcvCbsNum;
    VOS_UINT32                          ulSameMsgIdCodeInx;

    pstRcvCbsList      = TAF_CBA_GetRcvCbsList();
    usRcvCbsNum        = TAF_CBA_GetRcvCbsNum();
    ulSameMsgIdCodeInx = 0;
    usRcvCbsNum        = 0;

    /* ��¼���в����ں��¼�¼��MSG ID��MSG CODE��ͬ�ļ�¼��, ������һ����¼�� */
    if ( VOS_TRUE != TAF_CBA_GetCbsRecordInxByMsgIdCode(pstNewRecord, &ulSameMsgIdCodeInx) )
    {
        TAF_CBA_AppendCbsRecord(pstNewRecord);

        return;
    }

    /* ��¼���д��ں��¼�¼��MSG ID��MSG CODE��ͬ�ļ�¼��, �򸲸�ԭ��¼�� */
    pstRcvCbsList[ulSameMsgIdCodeInx] = (*pstNewRecord);

    /* ��ά�ɲ� */
    TAF_CBS_SndOmSavedRecordInfo(TAF_CBA_OM_MSG_SAVE_CBS_RECORD,
                                 TAF_CBA_OM_SAVE_TYPE_REPLACE_RECORD,
                                 pstNewRecord,
                                 usRcvCbsNum);
}

/*lint -e429 -e830*/


VOS_VOID TAF_CBA_ReportRcvCbsData(
    VOS_UINT8                           ucPageNum,
    MN_MSG_CBRAW_TS_DATA_STRU          *pstPageData
)
{

    VOS_UINT16                          usMsgId;
    VOS_UINT32                          ulPageIdx;
    MN_MSG_CBGSMPAGE_STRU              *pstGsmPage;
    VOS_UINT32                          ulNeedDownLoad;

    for ( ulPageIdx = 0 ; ulPageIdx < ucPageNum ; ulPageIdx++ )
    {
        pstGsmPage = (MN_MSG_CBGSMPAGE_STRU *)(pstPageData[ulPageIdx].aucData);

        usMsgId = TAF_CBA_BuildCbsMsgId(pstGsmPage->ucMIdHigh, pstGsmPage->ucMIdLow);

        ulNeedDownLoad = TAF_CBA_IsNeedDownloadToUsim(usMsgId);

        if ( VOS_TRUE ==  ulNeedDownLoad )
        {
            /* һҳһҳenvelop download��UISM */
            TAF_CBA_SndUsimCbMsg(WUEPS_PID_TAF, 0, pstPageData+ulPageIdx);
        }
        else
        {
             /* һҳһҳ�ϱ� */
            TAF_CBA_SndAtRcvCbmMsg(pstPageData+ulPageIdx);
        }

    }

    return;
}
/*lint +e429 +e830*/

VOS_UINT32 TAF_CBA_IsNeedDownloadToUsim(
    VOS_UINT16                                              usMsgId
)
{
    VOS_UINT32                                              ulIsDownLoad;
    TAF_CBA_USIM_EFCBMID_FILE_INFO_STRU                    *pstEfCbmidFileInfo;
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU                        *pstCbmidList;

    pstEfCbmidFileInfo = TAF_CBA_GetEfCbmidInfo();
    pstCbmidList       = TAF_CBA_GetCbmiDownloadList();

    /* ��CBMID�ļ�ʱ֮�䷵�ز���ҪDownLoad */
    if ( ( VOS_FALSE == pstEfCbmidFileInfo->ucEfCbmidExistFlg)
      || (0 == pstEfCbmidFileInfo->usEfCbmidFileLen)
      || (0 == pstCbmidList->usCbmidNum) )
    {
        return VOS_FALSE;
    }

    ulIsDownLoad = TAF_CBA_IsMsgIdInCbmid(usMsgId, pstCbmidList);

    return ulIsDownLoad;
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_IsMsgIdInCbmid
 ��������  : �����ϢID�Ƿ�ΪDOWNLOAD����ϢID
 �������  : usMsgId        - �û���ϢID
             pstCbmidList   - USIMָ����DOWNLOAD����ϢID�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��ϢID��DOWNLOAD����ϢID�б���,����,����DOWNLOAD����ϢID�б���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��17��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_CBA_IsMsgIdInCbmid(
    VOS_UINT16                          usMsgId,
    TAF_CBA_CBMI_DOWNLOAD_LIST_STRU    *pstCbmidList
)
{
    VOS_UINT32                          ulLoop;

    for ( ulLoop = 0; ulLoop < pstCbmidList->usCbmidNum; ulLoop++ )
    {
        if (usMsgId == pstCbmidList->ausMsgId[ulLoop])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_ETWS)

VOS_UINT32 TAF_CBA_GetCbsDupDetcTimeLen(
    TAF_CBA_PLMN_ID_STRU                                   *pstPlmn,
    VOS_UINT16                                              usMsgId
)
{
    TAF_CBA_ENH_DUP_DETECT_TIME_LEN_CFG_STRU               *pstEnhDupDetcTimeLenCfg;
    VOS_UINT8                                               ucEnhDupDetcFlg;
    VOS_UINT32                                              i;

    ucEnhDupDetcFlg         = TAF_CBA_GetEnhDupDetcFlg();

    pstEnhDupDetcTimeLenCfg = TAF_CBA_GetEnhDupDetcTimeLenCfg();

    /* ��ǿ���ظ���ⶨ������δ����ʱ��ȡֵ, ETWS��Ϣ���ظ����ʱЧҪ��, ��ͨCBS��Ϣû��ʱЧҪ�� */
    if (VOS_TRUE != ucEnhDupDetcFlg)
    {
        if ( VOS_TRUE == TAF_CBA_IsMsgIdInEtwsMsgIdList(usMsgId))
        {
            return TAF_CBA_GetNormalDupDetcTimeLen();
        }

        /* ��ͨCBSû���ظ����ʱЧҪ�󣬳���ʵ������Ϊ0 ��ʾ������Ч */
        return 0;
    }

    /* DoCoMo ��ǿ���ظ���ⶨ�����Կ���ʱ��ȡֵ:
       1. ETWS����ͨCBS��Ϣ���ظ����ʱЧҪ����ͬ��
       2. ��ǰPLMN��MCC�ڶ���MCC��Χ��Ͷ���MCC��ȡֵ��ͬ  */
    for ( i = 0; i < TAF_CBA_MAX_ETWS_DUP_DETECT_SPEC_MCC_NUM; i++ )
    {
        if (pstPlmn->ulMcc == pstEnhDupDetcTimeLenCfg->aulSpecMcc[i])
        {
            return pstEnhDupDetcTimeLenCfg->ulSpecMccTimeLen;
        }
    }

    return pstEnhDupDetcTimeLenCfg->ulOtherMccTimeLen;
}
#endif



VOS_UINT32 TAF_CBA_IsNeedDupDetectCbs(
    VOS_UINT16                          usMsgID
)
{
    TAF_CBA_DUP_DETECT_CFG_ENUM_UINT8   enDupDetectCfg;

    enDupDetectCfg = TAF_CBA_GetDupDetectCfg();

    if (TAF_CBA_DUP_DETECT_CFG_ALL_ENABLE == enDupDetectCfg)
    {
        return VOS_TRUE;
    }

    /* �ж����ص�USIM��CBS�Ƿ���Ҫ���� */
    if ( (VOS_TRUE == TAF_CBA_IsNeedDownloadToUsim(usMsgID))
      && (TAF_CBA_DUP_DETECT_CFG_ONLY_DOWNLOAD_TYPE_ENABLE == enDupDetectCfg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*lint -restore */

#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
