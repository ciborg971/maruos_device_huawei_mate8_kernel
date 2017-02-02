

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafLog.h"
#include "TafSpmSndUsim.h"
#include "siappstk.h"
#include "UsimPsInterface.h"
#include "TafSpmMntn.h"
#include "TafMmiEncode.h"
#include "TafSdcCtx.h"
#include "MnErrorCode.h"
#include "TafStdlib.h"
#include "MnMsgApi.h"
#include "mnmsgcbencdec.h"

#include "NasUsimmApi.h"

#include "NasCcIe.h"
#include "MnCallBcProc.h"
#include "TafSpmComFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_SND_USIM_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/

VOS_UINT32  TAF_SPM_SendUsimSsEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    VOS_UINT8                           aucSsString[TAF_SPM_CALL_CTRL_SS_STRING_LEN];
    VOS_UINT8                           ucSscStringBcdLen;
    SI_STK_ENVELOPE_STRU                stEnvelopeMsg;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcSscString     = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppReq       = VOS_NULL_PTR;
    MN_APP_SS_REGISTER_REQ_STRU        *pstRegister     = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;

    pcSscString = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SPM_SSC_MAX_LEN);

    if (VOS_NULL_PTR == pcSscString)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimSsEnvelopeReq: Fail to alloc memory for SS info.");
        return VOS_FALSE;
    }

    PS_MEM_SET(pcSscString, 0, TAF_SPM_SSC_MAX_LEN);
    /* ������Ϣת����SSC STRING */
    ulRet        = TAF_MmiEncodeMmiString(pstMsg, pcSscString);
    if (VOS_TRUE != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimSsEnvelopeReq: Fail to Encode SSC string.");
        PS_MEM_FREE(WUEPS_PID_TAF, pcSscString);
        return VOS_FALSE;
    }

    /*
    SS STRING�ĵ�һ���ֽ���TON and NPI���ӵڶ��ֽڿ�ʼΪSSC ��BCD����
    �ο�Э�� 11.11: 10.5.1  EFADN (Abbreviated dialling numbers)
    TON and NPI
    Contents:
        Type of number (TON) and numbering plan identification (NPI).
    Coding:
        according to TS 04.08 [15]. If the Dialling Number/SSC String does not contain a dialling number,
        e.g. a control string deactivating a service, the TON/NPI byte shall be set to 'FF' by the ME (see note 2).
    NOTE 2: If a dialling number is absent, no TON/NPI byte is transmitted over the radio interface (see TS 04.08 [15]).
        Accordingly, the ME should not interpret the value 'FF' and not send it over the radio interface.
    */
    PS_MEM_SET(aucSsString, 0, TAF_SPM_CALL_CTRL_SS_STRING_LEN);
    aucSsString[0] = TAF_SPM_NUM_TYPE_INVALID;
    pstAppReq = (MN_APP_REQ_MSG_STRU *)pstMsg;
    ulEventType = TAF_BuildEventType(pstAppReq->ulSenderPid, pstAppReq->usMsgName);
    ulRet = TAF_MmiGetOperationType(ulEventType, &enSsOpType);
    if ((VOS_TRUE == ulRet)
     && (TAF_MMI_REGISTER_SS == enSsOpType))
    {
        pstRegister    = (MN_APP_SS_REGISTER_REQ_STRU *)pstMsg;
        /* ������ת����ע�����������ת��ע����������к������� */
        aucSsString[0] = pstRegister->stTafSsRegisterSsReq.NumType;
    }

    ulRet = TAF_STD_ConvertAsciiNumberToBcd(pcSscString,
                                &aucSsString[TAF_SPM_SSC_OFFSET],
                                &ucSscStringBcdLen);
    PS_MEM_FREE(WUEPS_PID_TAF, pcSscString);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(&stEnvelopeMsg, 0, sizeof(SI_STK_ENVELOPE_STRU));
    PS_MEM_SET(aucLI, 0, MN_MO_CTRL_LAI_LEN);

    /*
    3GPP 1114:
    9.1.6   Structure of ENVELOPE (CALL CONTROL)
    Description                         Section M/O Min Length
    Call control tag                    13.1    M   Y   1
    Length (A+B+C+D+E+F)                -       M   Y   1 or 2
    Device identities                   12.7    M   Y   A
    Address or SS string or USSD string 12.1,   M   Y   B
                                        12.14
                                        or 12.17
    Location information                12.19   M   N   E
    ���У�
    Location information ͨ��TAF_SDC_GetCurrentLai��ȡ
    Call control tag��ӦstEnvelopeMsg.EnvelopeType
    Device identities��ӦstEnvelopeMsg.DeviceId
    Address or SS string or USSD string������SS string���ο�Э��1114 12.14
    */
    stEnvelopeMsg.enEnvelopeType    = SI_STK_ENVELOPE_CALLCRTL;
    stEnvelopeMsg.DeviceId.ucSDId   = SI_STK_DEV_TERMINAL;
    stEnvelopeMsg.DeviceId.ucDDId   = SI_STK_DEV_UICC;

    /*
        12.14    SS string
        SS or USSD string:
        for SS:
            Byte(s)                 Description         Length
            1                       SS string tag           1
            2 to (Y 1)+2            Length (X)              Y
            (Y 1)+3                 TON and NPI             1
            (Y 1)+4 to (Y 1)+X+2    SS or USSD string   X - 1
        ���У�
        SS string tag��ӦstEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag
        Length��ӦstEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen
        TON and NPI��SS string��ӦstEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue
    */
    stEnvelopeMsg.uEnvelope.CallCtrl.OP_SepcialData          = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag       = SI_CC_SS_TAG;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen       = (VOS_UINT8)(ucSscStringBcdLen + TAF_SPM_SSC_OFFSET);
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue      = aucSsString;

    /* ��ȡENVELOPE��Ϣ����: ����С����Ϣ */
    stEnvelopeMsg.uEnvelope.CallCtrl.OP_LocInfo              = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.pucATSLI        = aucLI;
    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    TAF_SDC_Get3GppCurrentLai(aucLI, &stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.ulLen);
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */

    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, usClientId, &stEnvelopeMsg);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimSsEnvelopeReq: Usim Returns Error.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_SPM_BuildUssdStringInfo(
    TAF_SS_DATA_CODING_SCHEME           ucDatacodingScheme,
    TAF_SS_USSD_STRING_STRU            *pstSrcUssd,
    TAF_SS_USSD_STRING_STRU            *pstDstUssd
)
{
    VOS_UINT32                          ulRslt;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;

    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));

    /* USSD��CBS��DCS��Э����ͬ������CBS��DCS�����������룬��ϸ����ο�23038 */
    ulRslt = MN_MSG_DecodeCbsDcs(ucDatacodingScheme,
                                 pstSrcUssd->aucUssdStr,
                                 pstSrcUssd->usCnt,
                                 &stDcsInfo);
    if (MN_ERR_NO_ERROR != ulRslt)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo:WARNING: Decode Failure");
        return VOS_FALSE;
    }

    if (MN_MSG_MSG_CODING_7_BIT == stDcsInfo.enMsgCoding)
    {
        PS_MEM_CPY(pstDstUssd, pstSrcUssd, sizeof(TAF_SS_USSD_STRING_STRU));

        /* ��͸��ģʽ�����뷽ʽΪ7bitʱ���ϲ���û�а�7Bitѹ���ģ�
           ��Ȼ��ASCII���˴���Ҫ��֤DCSָʾ�ı��뷽ʽ��ʵ�����ݵı��뷽ʽһ�� */
        if (TAF_SDC_USSD_NON_TRAN_MODE == TAF_SDC_GetUssdTransMode())
        {
            ulRslt = TAF_MmiEncodeUssdMessage(pstDstUssd);
            if (VOS_FALSE == ulRslt)
            {
                TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo: SSA_EncodeUssdMessage encode failure");
                return VOS_FALSE;
            }
        }
        /* ͸��ģʽ�����뷽ʽΪ7bitʱ���ϲ��ǰ�7Bitѹ���ģ����û�����ÿһ��USSD���֣�
           ����7Bitѹ���� ÿ���ֽڵĸ�4bit�͵�4bit�ڴ˴��Ƿֱ���һ��Byte��ʾ�ģ��˴���Ҫ������byte��ԭΪһ���ֽ�
           �����û�Ҫ����*199#,7bitѹ����Ϊaa 58 2e 37 02����ֺ�Ϊ61 61 35 38 32 65 33 37 30 32
            */
        else
        {
            if (pstDstUssd->usCnt > TAF_SS_MAX_USSD_CHAR_HEX_FORMAT)
            {
                TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo: String too Long failure");
                return VOS_FALSE;
            }

            ulRslt = TAF_STD_AsciiNum2HexString(pstDstUssd->aucUssdStr, &pstDstUssd->usCnt);

            if (VOS_FALSE == ulRslt)
            {
                TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo: TAF_AsciiNum2HexString encode failure");
                return VOS_FALSE;
            }
        }
    }
    else
    {
        if (pstSrcUssd->usCnt > TAF_SS_MAX_USS_CHAR)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdStringInfo: String too Long failure");
            return VOS_FALSE;
        }

        PS_MEM_CPY(pstDstUssd, pstSrcUssd, sizeof(TAF_SS_USSD_STRING_STRU));
    }

    return VOS_TRUE;
}


VOS_UINT32  TAF_SPM_SendUsimUssdEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    SI_STK_ENVELOPE_STRU                stEnvelopeMsg;
    VOS_UINT32                          ulRet;
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    TAF_SS_PROCESS_USS_REQ_STRU        *pstUssdMsg      = VOS_NULL_PTR;
    TAF_SS_USSD_STRING_STRU            *pstUssdInfo     = VOS_NULL_PTR;
    VOS_UINT8                           aucCallCtrlUssdString[TAF_SPM_CALL_CTRL_USSD_STRING_LEN];

    PS_MEM_SET(aucCallCtrlUssdString, 0, sizeof(aucCallCtrlUssdString));

    pstUssdInfo = PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_SS_USSD_STRING_STRU));

    if (VOS_NULL_PTR == pstUssdInfo)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimUssdEnvelopeReq: Fail to alloc memory for USSD string.");
        return VOS_FALSE;
    }

    PS_MEM_SET(pstUssdInfo, 0, sizeof(TAF_SS_USSD_STRING_STRU));

    pstAppMsg                = (MN_APP_REQ_MSG_STRU *)pstMsg;
    pstUssdMsg               = (TAF_SS_PROCESS_USS_REQ_STRU *)pstAppMsg->aucContent;
    aucCallCtrlUssdString[0] = pstUssdMsg->DatacodingScheme;

    /* ת���û������е�USSD�ַ���Ϊ�տ���Ϣ��USSD����  */
    ulRet = TAF_SPM_BuildUssdStringInfo(pstUssdMsg->DatacodingScheme,
                                        &pstUssdMsg->UssdStr,
                                        pstUssdInfo);
    if (VOS_FALSE == ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstUssdInfo);
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimUssdEnvelopeReq: Fail to TAF_SPM_BuildUssdStringInfo.");
        return VOS_FALSE;
    }

    PS_MEM_CPY(&aucCallCtrlUssdString[TAF_SPM_SSC_OFFSET], pstUssdInfo->aucUssdStr, pstUssdInfo->usCnt);

    /*
    3GPP 1114:
    9.1.6   Structure of ENVELOPE (CALL CONTROL)
    Description                         Section M/O Min Length
    Call control tag                    13.1    M   Y   1
    Length (A+B+C+D+E+F)                -       M   Y   1 or 2
    Device identities                   12.7    M   Y   A
    Address or SS string or USSD string 12.1,   M   Y   B
                                        12.14
                                        or 12.17
    Location information                12.19   M   N   E
    ���У�
    Location information ͨ��TAF_SDC_GetCurrentLai��ȡ
    Call control tag��ӦstEnvelopeMsg.EnvelopeType
    Device identities��ӦstEnvelopeMsg.DeviceId
    Address or SS string or USSD string������USSD string���ο�Э��1114 12.17
    */
    PS_MEM_SET(&stEnvelopeMsg, 0, sizeof(SI_STK_ENVELOPE_STRU));

    stEnvelopeMsg.enEnvelopeType    = SI_STK_ENVELOPE_CALLCRTL;
    stEnvelopeMsg.DeviceId.ucSDId   = SI_STK_DEV_TERMINAL;
    stEnvelopeMsg.DeviceId.ucDDId   = SI_STK_DEV_UICC;

    /*
        3GPP 1114:
        12.17    USSD string
        for USSD:
            Byte(s)                 Description         Length
            1                       USSD string tag         1
            2 to (Y-1)+2            Length (X)              Y
            (Y-1)+3                 Data coding scheme      1
            (Y-1)+4 to (Y-1)+X+2    USSD string           X-1
        ���У�
        USSD string tag��ӦstEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag
        Length��ӦstEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen
        Data coding scheme��USSD string��ӦstEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue
    */
    stEnvelopeMsg.uEnvelope.CallCtrl.OP_SepcialData          = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag       = SI_CC_USSD_TAG;

    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen       = (VOS_UINT8)(sizeof(pstUssdMsg->DatacodingScheme)
                                                             + pstUssdInfo->usCnt);
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue      = (SI_UINT8 *)aucCallCtrlUssdString;

    /* ��ȡENVELOPE��Ϣ����: ����С����Ϣ */
    stEnvelopeMsg.uEnvelope.CallCtrl.OP_LocInfo              = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.pucATSLI        = aucLI;
    /* Added by l00301449 for CDMA STK, 2015-07-03, begin */
    TAF_SDC_Get3GppCurrentLai(aucLI, &stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.ulLen);
    /* Added by l00301449 for CDMA STK, 2015-07-03, end */

    PS_MEM_FREE(WUEPS_PID_TAF, pstUssdInfo);

    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, usClientId, &stEnvelopeMsg);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimUssdEnvelopeReq: Usim Returns Error.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32  TAF_SPM_BuildSsFdnInfo(
    struct MsgCB                       *pstMsg,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *pcMmiStr       = VOS_NULL_PTR;

    /* ������Ϣת����SSC STRING */
    pcMmiStr   = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SPM_SSC_MAX_LEN);

    if (VOS_NULL_PTR == pcMmiStr)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildSsFdnInfo: Fail to alloc memory for encode SSC.");
        return VOS_FALSE;
    }

    PS_MEM_SET(pcMmiStr, 0, TAF_SPM_SSC_MAX_LEN);
    ulRet          = TAF_MmiEncodeMmiString(pstMsg, pcMmiStr);

    if (VOS_TRUE != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildSsFdnInfo: Fail to Encode SSC string.");
        PS_MEM_FREE(WUEPS_PID_TAF, pcMmiStr);

        return VOS_FALSE;
    }

    ulRet = TAF_STD_ConvertAsciiNumberToBcd(pcMmiStr, pstFdnInfo->aucNum1, (VOS_UINT8 *)&(pstFdnInfo->ulNum1Len));
    PS_MEM_FREE(WUEPS_PID_TAF, pcMmiStr);

    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32  TAF_SPM_SendPbSsFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-5, begin */
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    /* Modified by h00313353 for iteration 9, 2015-2-5, end */
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stFdnInfo, 0x00, sizeof(stFdnInfo));
    ulRet = TAF_SPM_BuildSsFdnInfo(pstMsg, &stFdnInfo);

    if (VOS_FALSE == ulRet)
    {
        return VOS_FALSE;
    }


    ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, usClientId, &stFdnInfo);


    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_GetUssdStringSeptetLength(
    VOS_UINT32                          ulOctetLength,
    VOS_UINT8                           ucLastByte
)
{
    VOS_UINT16                          usFillBit;
    VOS_UINT32                          ulSeptetLength;

    /*
    23038 6.1.2.3 USSD packing
    If the total number of characters to be sent equals (8n-1) where n=1,2,3 etc.
    then there are 7 spare bits at the end of the message. To avoid the situation
    where the receiving entity confuses 7 binary zero pad bits as the @ character,
    the carriage return or <CR> character (defined in clause 6.1.1) shall be used
    for padding in this situation, just as for Cell Broadcast.
    USSD 7BITѹ����ʽ�£���8λλ�������BIT����1��7λλ���BIT����Э��Ҫ�����CR
    ����USSD��7λλ����ʱ��Ҫȥ����Ч��CRռ�õ�1��7λλ��
    */
    ulSeptetLength = (VOS_UINT32)((TAF_SDC_BITS_PER_OCTET * ulOctetLength) / TAF_SDC_BITS_PER_SEPTET);
    usFillBit      = (VOS_UINT32)((TAF_SDC_BITS_PER_OCTET * ulOctetLength) % TAF_SDC_BITS_PER_SEPTET);
    if (0 == usFillBit)
    {
        if (TAF_SDC_USSD_7BIT_PAD == (ucLastByte & TAF_SDC_USSD_7BIT_PAD))
        {
            ulSeptetLength--;
        }
    }

    return ulSeptetLength;
}


VOS_UINT32 TAF_SPM_TransUssdMsgToAsciiStr(
    TAF_SS_PROCESS_USS_REQ_STRU        *pstUssdMsg,
    VOS_UINT8                          *pucAsciiStr,
    VOS_UINT32                         *pulAsciiStrLength
)
{
    VOS_UINT8                          *pucUssdStr          = VOS_NULL_PTR;
    VOS_UINT8                          *pucUssdTransTbl     = VOS_NULL_PTR;
    VOS_UINT8                           aucUnpackUssdStr[TAF_SS_MAX_USSDSTRING_LEN];
    VOS_UINT32                          ulUssdStrLength;
    VOS_UINT32                          ulUnpackUssdStrLength;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    MN_MSG_CBDCS_CODE_STRU              stDcsInfo;

    PS_MEM_SET(&stDcsInfo, 0, sizeof(stDcsInfo));

    ulRet = MN_MSG_DecodeCbsDcs(pstUssdMsg->DatacodingScheme,
                                pstUssdMsg->UssdStr.aucUssdStr,
                                pstUssdMsg->UssdStr.usCnt,
                                &stDcsInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr:WARNING: Decode Failure");
        return VOS_FALSE;
    }

    /*
       ��͸��ģʽ���7BIT���룬TAF���յ����û�USSD�ַ��������ʽΪASCII���UCS2������
       ����Ҫת����ֱ�ӿ������������
    */
    if ((TAF_SDC_USSD_TRAN_MODE != TAF_SDC_GetUssdTransMode())
     || (MN_MSG_MSG_CODING_7_BIT != stDcsInfo.enMsgCoding))
    {
        if (pstUssdMsg->UssdStr.usCnt > TAF_SS_MAX_USSDSTRING_LEN)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr: USSD length overflow in none transparent mode.");
            return VOS_FALSE;
        }

        *pulAsciiStrLength  = pstUssdMsg->UssdStr.usCnt;

         PS_MEM_CPY(pucAsciiStr, pstUssdMsg->UssdStr.aucUssdStr, *pulAsciiStrLength);

        return VOS_TRUE;
    }

    /*
       ��δ�����ɴ�7BITѹ������������ַ�����ASCII������ת��
       ͸��ģʽ����DCSΪ7bit�����ʽ���û�����ÿһ��USSD���֣�����7Bitѹ����
       ÿ���ֽڵĸ�4bit�͵�4bit�ڴ˴��Ƿֱ���һ��Byte��ʾ��
       TAF���յ����û�USSD�ַ�������2���ַ���ʾһ�����֣���󳤶�Ϊ320�ַ���
       USSD�տ���������Ϊ160BYTE��160BYTE ����7BIT������ַ������Դ���182���ַ���

       ʾ��:
       �û�����*199#�������Ӧ�ý��յ�ASCII����2A 31 39 39 23������7BIT�����Ϊ
       aa 58 2e 37 02��ת��Ϊ�����ַ���Ϊ61 61 35 38 32 65 33 37 30 32��ͨ��AT����
       AT+CUSD=1,"61613538326533373032",15 AT͸��"61613538326533373032"��TAF������
       ����������: 61 61 35 38 32 65 33 37 30 32
       ���������: ASCII����Ϊ2A 31 39 39 23������Ϊ5
       ʵ�ֲ���:
       1) TAF_AsciiNum2HexStr: 61 61 35 38 32 65 33 37 30 32 => aa 58 2e 37 02
       2) MN_UnPack7Bit:          aa 58 2e 37 02                => 2A 31 39 39 23
       ��Ϊ�˴���ASCII�����ڱ�׼ASCII�룬����USSD���ַ�ת���������ַ�����Ӱ��

       16���Ʊ�ʾ��USSD�����ַ���ת��Ϊ16���Ʊ�ʾ��USSD����
       ����˵��:
       16���Ʊ�ʾ��7BIT�ַ���ѹ�������USSD�����ַ��� 0x61 0x61 0x35 0x38 0x32 0x65 0x33 0x37 0x30 0x32
       ת����
               16���Ʊ�ʾ��7BIT�ַ���ѹ����������� 0xaa 0x58 0x2e 0x37 0x02
       ���У�0x61��ʾASCII���a 0x65��ʾASCII���e
    */
    if (pstUssdMsg->UssdStr.usCnt > TAF_SS_MAX_USSD_CHAR_HEX_FORMAT)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr: USSD length overflow in transparent mode.");
        return VOS_FALSE;
    }

    pucUssdStr = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SS_MAX_USSD_CHAR_HEX_FORMAT);
    if (VOS_NULL_PTR == pucUssdStr)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr: Fail to alloc memory.");
        return VOS_FALSE;
    }

    PS_MEM_SET(pucUssdStr, 0, TAF_SS_MAX_USSD_CHAR_HEX_FORMAT);

    ulUssdStrLength = pstUssdMsg->UssdStr.usCnt;
    PS_MEM_CPY(pucUssdStr, pstUssdMsg->UssdStr.aucUssdStr, pstUssdMsg->UssdStr.usCnt);
    ulRet = TAF_STD_AsciiNum2HexString(pucUssdStr, (VOS_UINT16 *)&ulUssdStrLength);
    if (VOS_FALSE == ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr: Fail to TAF_AsciiNum2HexString.");
        PS_MEM_FREE(WUEPS_PID_TAF, pucUssdStr);
        return VOS_FALSE;
    }

    /*
    16���Ʊ�ʾ��7BIT�ַ���ѹ������USSD����ת����7BIT�ַ����ѹ������USSD����
    ����˵��:
          16���Ʊ�ʾ��7BIT�ַ���ѹ������USSD���� 0xaa 0x58 0x2e 0x37 0x02
    ת����
          7BIT�ַ����ѹ������USSD����           0x2A 0x31 0x39 0x39 0x23
    */
    /*lint -e961*/
    ulUnpackUssdStrLength = TAF_SPM_GetUssdStringSeptetLength(ulUssdStrLength,
                                            *(pucUssdStr + ulUssdStrLength - 1));
    /*lint +e961*/

    PS_MEM_SET(aucUnpackUssdStr, 0, sizeof(aucUnpackUssdStr));
    if (ulUssdStrLength > TAF_SS_MAX_USSDSTRING_LEN)
    {
        ulUssdStrLength = TAF_SS_MAX_USSDSTRING_LEN;
    }
    ulRet = TAF_STD_UnPack7Bit(pucUssdStr, ulUssdStrLength, 0, aucUnpackUssdStr);

    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_TransUssdMsgToAsciiStr:TAF_STD_UnPack7Bit Err.");
    }
    PS_MEM_FREE(WUEPS_PID_TAF, pucUssdStr);

    /*
    7BIT�ַ����ѹ������USSD����ת����ASCII���ַ�����������
    ʾ���в��漰7BIT�ַ����ASCII���ַ�����ڲ�����ַ��������ޱ仯
    */
    pucUssdTransTbl = TAF_SDC_GetCurr7BitToAsciiTableAddr();
    for (i = 0; i < ulUnpackUssdStrLength; i++)
    {
        pucAsciiStr[i]  = pucUssdTransTbl[aucUnpackUssdStr[i]];
    }

    return VOS_TRUE;
}



VOS_UINT32  TAF_SPM_BuildUssdFdnInfo(
    struct MsgCB                       *pstMsg,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
)
{
    VOS_UINT32                          ulAsciiStrLen;
    VOS_UINT8                          *pucAsciiStr = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ����ת��������ȡASCII��ʽ���ַ��� */
    pucAsciiStr = PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SS_MAX_USSDSTRING_LEN);
    if (VOS_NULL_PTR == pucAsciiStr)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdFdnInfo: Fail to alloc memory.");
        return VOS_FALSE;
    }

    pstAppMsg       = (MN_APP_REQ_MSG_STRU *)pstMsg;

    ulAsciiStrLen  = 0;
    PS_MEM_SET(pucAsciiStr,  0, TAF_SS_MAX_USSDSTRING_LEN);

    ulRet = TAF_SPM_TransUssdMsgToAsciiStr((TAF_SS_PROCESS_USS_REQ_STRU*)pstAppMsg->aucContent,
                                            pucAsciiStr,
                                            &ulAsciiStrLen);
    if (VOS_FALSE == ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pucAsciiStr);
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_BuildUssdFdnInfo: Fail to TAF_SDC_TransUssdMsgToAsciiStr.");
        return VOS_FALSE;
    }

    /* FDN�е�num1ֻ�ܱ���40��ascii�� */
    PS_MEM_SET(pucAsciiStr + TAF_SPM_FDN_CHECK_STR_MAX_LEN, 0, TAF_SPM_FDN_CHECK_7BIT_MAX_LEN - TAF_SPM_FDN_CHECK_STR_MAX_LEN);

    ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)pucAsciiStr, pstFdnInfo->aucNum1, (VOS_UINT8 *)&pstFdnInfo->ulNum1Len);
    PS_MEM_FREE(WUEPS_PID_TAF, pucAsciiStr);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_SendPbUssdFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-5, begin */
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    /* Modified by h00313353 for iteration 9, 2015-2-5, end */
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stFdnInfo, 0x00, sizeof(stFdnInfo));
    ulRet = TAF_SPM_BuildUssdFdnInfo(pstMsg, &stFdnInfo);

    if (VOS_FALSE == ulRet)
    {
        return VOS_FALSE;
    }

    ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, usClientId, &stFdnInfo);

    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_SendPbCallFdnCheckReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-5, begin */
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    /* Modified by h00313353 for iteration 9, 2015-2-5, end */

#if (FEATURE_ON == FEATURE_IMS)
	VOS_UINT32                          ulEventType;
#endif
    MN_CALL_CALLED_NUM_STRU             stDialNumber;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;
    MN_CALL_CS_DATA_CFG_STRU            stDataCfg;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stFdnInfo, 0x00, sizeof(stFdnInfo));
    PS_MEM_SET(&stDataCfg, 0x00, sizeof(stDataCfg));
    PS_MEM_SET(&stDialNumber, 0x00, sizeof(stDialNumber));

#if (FEATURE_ON == FEATURE_IMS)
    ulEventType         = TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg();
#endif

    /* ������ǿ�Ͷ෽ͨ���Ѿ��������ˣ����ﲻ����Ҫ����  */
#if (FEATURE_ON == FEATURE_IMS)
    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        return TAF_SPM_SendUsimEconfFdnReq(usClientId, pstMsg);
    }
#endif

    /* ��ȡ���з�������������stDialNumber */
    TAF_SPM_GetCallInfoFromFsmEntryMsg(&stDialNumber, &enCallType, &enCallMode, &stDataCfg);

    stFdnInfo.ulNum1Len = (stDialNumber.ucNumLen <= MN_CALL_MAX_BCD_NUM_LEN) ?
                          stDialNumber.ucNumLen : MN_CALL_MAX_BCD_NUM_LEN;

    PS_MEM_CPY(stFdnInfo.aucNum1, stDialNumber.aucBcdNum, MN_CALL_MAX_BCD_NUM_LEN);

    ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, usClientId, &stFdnInfo);

    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32  TAF_SPM_SendUsimCallEnvelopeReq(
    MN_CALL_CALLED_NUM_STRU            *pstCalledNumber,
    MN_CALL_CS_DATA_CFG_INFO_STRU      *pstDataCfgInfo,
    VOS_UINT32                          ulSendPara,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    VOS_UINT8                           aucStkBcdNum[MN_CALL_MAX_CALLED_BCD_NUM_LEN + 1];
    SI_STK_ENVELOPE_STRU                stEnvelopeMsg;
    NAS_CC_IE_BC_STRU                   stBc1;
    NAS_CC_IE_BC_STRU                   stBc2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;
    VOS_UINT32                          ulNumOfBc;


    PS_MEM_SET(&stEnvelopeMsg, 0, sizeof(SI_STK_ENVELOPE_STRU));

    stEnvelopeMsg.enEnvelopeType    = SI_STK_ENVELOPE_CALLCRTL;
    stEnvelopeMsg.DeviceId.ucSDId   = SI_STK_DEV_TERMINAL;
    stEnvelopeMsg.DeviceId.ucDDId   = SI_STK_DEV_UICC;
    enBcRepeatInd                   = MN_CALL_REP_IND_NULL;

    /* ���ݺ�������, ����ģʽ�����ݺ�����������BC��Repeat Ind���� */
    PS_MEM_SET(&stBc1, 0, sizeof(NAS_CC_IE_BC_STRU));
    PS_MEM_SET(&stBc2, 0, sizeof(NAS_CC_IE_BC_STRU));

    ulNumOfBc = MN_CALL_BuildBcOfSetup(enCallType,
                                       enCallMode,
                                       pstDataCfgInfo,
                                       &stBc1,
                                       &stBc2);

    if (0 == ulNumOfBc)
    {
        return VOS_FALSE;
    }

    if (TAF_CALL_MAX_BC_NUM == ulNumOfBc)
    {
        /* ������BC������£�repeat indicator��Ϊalternate */
        enBcRepeatInd = MN_CALL_REP_IND_ALTER;
    }
    else
    {
        /* �˴���Ҫ�ο�24.008 10.5.4.22 �еĶ���ȷ�� */
        enBcRepeatInd = MN_CALL_REP_IND_NULL;
    }

    stEnvelopeMsg.uEnvelope.CallCtrl.OP_Capability1          = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.Capability1.ulLen       = stBc1.LastOctOffset;
    stEnvelopeMsg.uEnvelope.CallCtrl.Capability1.pucCCP      = (VOS_UINT8 *)&stBc1.Octet3;

    if ((MN_CALL_REP_IND_NULL != enBcRepeatInd)
     && (0                    != stBc2.IsExist))
    {
        stEnvelopeMsg.uEnvelope.CallCtrl.OP_Capability2      = VOS_TRUE;
        stEnvelopeMsg.uEnvelope.CallCtrl.OP_BCRepInd         = VOS_TRUE;
        stEnvelopeMsg.uEnvelope.CallCtrl.Capability2.ulLen   = stBc2.LastOctOffset;
        stEnvelopeMsg.uEnvelope.CallCtrl.Capability2.pucCCP  = (VOS_UINT8 *)&stBc2.Octet3;
    }

    stEnvelopeMsg.uEnvelope.CallCtrl.OP_SepcialData          = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucTag       = SI_CC_ADDRESS_TAG;
    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.ucLen       = pstCalledNumber->ucNumLen
                                                             + sizeof(MN_CALL_NUM_TYPE_ENUM_U8);
    PS_MEM_SET(aucStkBcdNum, 0, sizeof(aucStkBcdNum));
    aucStkBcdNum[0]                                          = pstCalledNumber->enNumType;
    PS_MEM_CPY(&aucStkBcdNum[sizeof(pstCalledNumber->enNumType)],
               pstCalledNumber->aucBcdNum,
               pstCalledNumber->ucNumLen);

    stEnvelopeMsg.uEnvelope.CallCtrl.SpecialData.pValue      = aucStkBcdNum;

    stEnvelopeMsg.uEnvelope.CallCtrl.OP_LocInfo              = VOS_TRUE;
    stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.pucATSLI        = aucLI;
    TAF_SDC_GetCurrentLai(aucLI, &stEnvelopeMsg.uEnvelope.CallCtrl.LocInfo.ulLen);

    /* Modified by h00313353 for Iteration 9, 2015-3-19, begin */
    if (VOS_OK != NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, ulSendPara, &stEnvelopeMsg))
    /* Modified by h00313353 for Iteration 9, 2015-3-19, end */
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_SendUsimCallEnvelopeReq: Usim Returns Error.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32  TAF_SPM_SendUsimEconfEnvelopeReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;
    VOS_UINT32                          ulSendPara;

    PS_MEM_SET(&stCalledNumber, 0x0, sizeof(stCalledNumber));
    PS_MEM_SET(&stDataCfgInfo, 0x0, sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();

    pstEconfInfoAddr->ucSendSuccNum = 0;
    pstEconfInfoAddr->ucRcvNum      = 0;
    enCallType                      = pstEconfInfoAddr->enCallType;
    enCallMode                      = pstEconfInfoAddr->enCallMode;
    PS_MEM_CPY(&stDataCfgInfo, &pstEconfInfoAddr->stDataCfg, sizeof(stDataCfgInfo));

    for (ucIndex = 0; ucIndex < pstEconfInfoAddr->ucCallNum; ucIndex++)
    {
        PS_MEM_CPY(&stCalledNumber,
               &pstEconfInfoAddr->astEconfCheckInfo[ucIndex].stCalledNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));

        pstEconfInfoAddr->astEconfCheckInfo[ucIndex].ulCheckCnfFlag = VOS_FALSE;

        /* ��ǿ�Ͷ෽ͨ������£���16λΪ��ʾ�ڼ����绰���룬��16λΪClinedId */
        ulSendPara = TAF_SPM_ECONF_SET_SEND_PARA(ucIndex, usClientId);

        ulRet = TAF_SPM_SendUsimCallEnvelopeReq(&stCalledNumber,
                                                &stDataCfgInfo,
                                                ulSendPara,
                                                enCallType,
                                                enCallMode);
        if (VOS_FALSE == ulRet)
        {
            /* ��¼Ϊʧ�� */
            TAF_SPM_RecordEconfCheckRslt(ucIndex, TAF_CS_CAUSE_CALL_CTRL_INVALID_PARAMETER);
        }
        else
        {
            pstEconfInfoAddr->ucSendSuccNum++;
        }
    }

    /* ȫ������ʧ�ܣ����˳� */
    if (0 == pstEconfInfoAddr->ucSendSuccNum)
    {
        /* �ϱ���� */
        TAF_SPM_ReportEconfCheckRslt();
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_UINT32  TAF_SPM_SendUsimEconfFdnReq(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    MN_CALL_CALLED_NUM_STRU            *pstCalledNumber     = VOS_NULL_PTR;
    SI_PB_FDN_NUM_STRU                  stFdnInfo;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulSendPara;

    PS_MEM_SET(&stFdnInfo, 0x0, sizeof(stFdnInfo));
    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();

    pstEconfInfoAddr->ucSendSuccNum = 0;
    pstEconfInfoAddr->ucRcvNum      = 0;
    for (ucIndex = 0; ucIndex < pstEconfInfoAddr->ucCallNum; ucIndex++)
    {
        pstEconfInfoAddr->astEconfCheckInfo[ucIndex].ulCheckCnfFlag = VOS_FALSE;

        pstCalledNumber = &pstEconfInfoAddr->astEconfCheckInfo[ucIndex].stCalledNumber;

        stFdnInfo.ulNum1Len = pstCalledNumber->ucNumLen <= MN_CALL_MAX_BCD_NUM_LEN ?
                          pstCalledNumber->ucNumLen : MN_CALL_MAX_BCD_NUM_LEN;

        PS_MEM_CPY(stFdnInfo.aucNum1, pstCalledNumber->aucBcdNum, stFdnInfo.ulNum1Len);

        /* ��ǿ�Ͷ෽ͨ������£���16λΪ��ʾ�ڼ����绰���룬��16λΪClinedId */
        ulSendPara = TAF_SPM_ECONF_SET_SEND_PARA(ucIndex, usClientId);

        ulRet = NAS_PBAPI_FdnNumCheck(WUEPS_PID_TAF, 0, ulSendPara, &stFdnInfo);
        if (VOS_OK != ulRet)
        {
            /* ��¼Ϊʧ�� */
            TAF_SPM_RecordEconfCheckRslt(ucIndex, TAF_CS_CAUSE_FDN_CHECK_FAILURE);
        }
        else
        {
            pstEconfInfoAddr->ucSendSuccNum++;
        }
    }

    /* ȫ������ʧ�ܣ����˳� */
    if (0 == pstEconfInfoAddr->ucSendSuccNum)
    {
        /* �ϱ���� */
        TAF_SPM_ReportEconfCheckRslt();
        return VOS_FALSE;
    }

    return VOS_TRUE;

}
#endif


VOS_UINT32  TAF_SPM_SendUsimCallEnvelopeReq_Call(
    VOS_UINT16                          usClientId,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulEventType;
#endif
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_MODE_ENUM_U8                enCallMode;

    PS_MEM_SET(&stCalledNumber, 0x0, sizeof(stCalledNumber));
    PS_MEM_SET(&stDataCfgInfo, 0x0, sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));
#if (FEATURE_ON == FEATURE_IMS)
    ulEventType         = TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg();
#endif

    /* ������ǿ�Ͷ෽ͨ���Ѿ��������ˣ����ﲻ����Ҫ����  */
#if (FEATURE_ON == FEATURE_IMS)
    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        return TAF_SPM_SendUsimEconfEnvelopeReq(usClientId, pstMsg);
    }
    else
#endif
    {
        /* ����Ϣ�л�ȡ�绰���������Ϣ */
        TAF_SPM_GetCallInfoFromFsmEntryMsg(&stCalledNumber, &enCallType, &enCallMode, (MN_CALL_CS_DATA_CFG_STRU *)&stDataCfgInfo);

        /* ������ */
        return TAF_SPM_SendUsimCallEnvelopeReq(&stCalledNumber,
                                               &stDataCfgInfo,
                                               usClientId,
                                               enCallType,
                                               enCallMode);
    }
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

