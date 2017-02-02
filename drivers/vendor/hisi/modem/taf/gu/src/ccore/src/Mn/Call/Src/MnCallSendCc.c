


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallSendCc.h"
#include "NasIeUtil.h"
#include "MnCall.h"
#include "MnCallApi.h"
#include "NasCcIe.h"
#include "PsCommonDef.h"
#include "MnComm.h"
#include "MnCallMgmt.h"
#include "MnCallFacilityEncode.h"
#include "NasIeUtil.h"
#include "MnErrorCode.h"
#include "MnCallReqProc.h"

#include "MnCallCtx.h"

#include "MnCallSendApp.h"

/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_SEND_CC_C

/*lint -save -e958 */

/*****************************************************************************
   2 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MN_CALL_FillIeBc
 ��������  :
 �������  : enCauseVal - ԭ��ֵ
 �������  : pstCauseIe - ��õ�Cause IE
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_FillIeCause(
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCauseVal,
    NAS_CC_IE_CAUSE_STRU                *pstCauseIe
)
{
    NAS_IE_SET_PRESENT(pstCauseIe);

    /* Set octet3 to 0xe0:
           Coding standard: GSM
           Location :       User
           No extended octet
    */
    NAS_IE_SET_OCTET(pstCauseIe, Octet3, 0xe0);

    pstCauseIe->Octet4.CauseValue = enCauseVal;
    pstCauseIe->Octet4.Ext = NAS_CC_IE_NO_EXT;

    NAS_IE_SET_LAST_OCTET_OFFSET(pstCauseIe, Octet4);
}

/*****************************************************************************
 �� �� ��  : MN_CALL_FillIeRepeatInd
 ��������  :
 �������  : enCauseVal - ԭ��ֵ
 �������  : pstRepeatInd - ��õ�Cause IE
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_FillIeRepeatInd(
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    NAS_CC_IE_REPEAT_INDICATOR_STRU     *pstRepeatInd
)
{

    /* ���repeat indicator�����ڣ���λ�����ڣ����� */
    if (MN_CALL_REP_IND_NULL == enRepeatInd)
    {
        NAS_IE_SET_ABSENT(pstRepeatInd);
        return;
    }

    /* ���repeat indicator���ڣ����ô��ڣ�����ֵ */
    NAS_IE_SET_PRESENT(pstRepeatInd);

    pstRepeatInd->RepeatIndication = enRepeatInd;

}


LOCAL VOS_VOID  MN_CALL_FillIeSupCodecList(
    NAS_CC_IE_SUPPORTED_CODEC_LIST_STRU *pstCodecList
)
{
    MN_CALL_SUPPORT_CODEC_UNION         unCodec;

    NAS_IE_SET_PRESENT(pstCodecList);

    /* ����֧�ֵ��б�Ŀǰ������GSM��UMTS֧�ֵ�codec list,
       00 ��ʾGSM, 04��ʾUMTS */
    /* ���帳ֵ�ĺ���μ�26.103 */

    PS_MEM_SET(&unCodec,0x00,sizeof(unCodec));
    pstCodecList->LastOctOffset = 8;
    pstCodecList->CodecInfo[0].SysId = 0x04;
    pstCodecList->CodecInfo[0].LastOctOffsetengthOfBitMap = 0x02;
    MN_CALL_FillUmtsSupCodecList(&(unCodec));
    pstCodecList->CodecInfo[0].CodecBitmapL = (VOS_UINT8)(unCodec.usSupportCodec);
    pstCodecList->CodecInfo[0].CodecBitmapH = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

    /* ��дGSM֧�ֵ�codec���� */
    PS_MEM_SET(&unCodec,0x00,sizeof(unCodec));
    MN_CALL_FillGsmSupCodecList(&(unCodec));
    pstCodecList->CodecInfo[1].SysId = 0x00;
    pstCodecList->CodecInfo[1].LastOctOffsetengthOfBitMap = 0x02;
    pstCodecList->CodecInfo[1].CodecBitmapL = (VOS_UINT8)(unCodec.usSupportCodec);
    pstCodecList->CodecInfo[1].CodecBitmapH = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

}


/*****************************************************************************
 �� �� ��  : MN_CALL_FillIeLlc
 ��������  :
 �������  : pstLLC1 - IE��LLC
 �������  : pstLLC1 - LLC��ֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_FillIeLlc(
    NAS_CC_IE_LLC_STRU                  *pstLLC1
)
{
    NAS_IE_SET_PRESENT(pstLLC1);

    pstLLC1->LastOctOffset = 3;

    /* �˴�����IOT �������ԣ������д��������д */
    pstLLC1->LLCContents[0] = 0x88;
    pstLLC1->LLCContents[1] = 0x90;
    pstLLC1->LLCContents[2] = 0xA6;
}
LOCAL VOS_VOID  MN_CALL_FillIeCcCap(
    NAS_CC_IE_CC_CAP_STRU               *pstCcCap
)
{
    NAS_IE_SET_PRESENT(pstCcCap);

    pstCcCap->LastOctOffset = 3;


    pstCcCap->Octet3.DTMF  = NAS_CC_DTMF_SPECIFIED;
    pstCcCap->Octet3.PCP   = NAS_CC_PCP_NOT_SUPPORT;
    pstCcCap->Octet3.ENICM = NAS_CC_ENICM_NOT_SUPPORT;
    pstCcCap->Octet4.MaxSpeechBearers = NAS_CC_SPEECH_BEARER_1;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_AllocMnccPrimitive
 ��������  : ����һ��MNCCԭ����Ϣ
 �������  : callId    - ԭ���е�CallIdֵ
             enPrimName  - ԭ������
 �������  : ppunParam - ԭ�����ݵĴ��λ��(������������дԭ������)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
MsgBlock* MN_CALL_AllocMnccPrimitive(
    VOS_UINT8                           callId,
    MNCC_PRIM_NAME_ENUM_U16             enPrimName,
    MNCC_REQ_PARAM_UNION                **ppunParam
)
{
/*
    ����VOS��Ϣ, ��СΪsizeof(MNCC_REQ_PRIM_MSG_STRU)
    if ����ʧ��
        ���� NULL

    ��дVOS��Ϣͷ

    ����CallId���CCʵ��ID

    ��дCCʵ��ID, CallId, enPrimName�ȹ�����Ϣ

    ���Payloadָ��

    ����VOS��Ϣͷָ��
*/
    MNCC_REQ_PRIM_MSG_STRU *pstMsg =
        (MNCC_REQ_PRIM_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                sizeof(MNCC_REQ_PRIM_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_CALL_AllocMnccPrimitive: Failed to alloc VOS message.");
        return VOS_NULL_PTR;
    }


    PS_MEM_SET(pstMsg, 0, sizeof(MNCC_REQ_PRIM_MSG_STRU));

    /* ��дVOS��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_TAF;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_CC;
    pstMsg->ulLength        = sizeof(MNCC_REQ_PRIM_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д������Ϣ */
    pstMsg->enPrimName = enPrimName;
    pstMsg->ucTi       = (VOS_UINT8)MN_CALL_GetCcTi(callId);
    pstMsg->ucCallId     = callId;
    pstMsg->ulParamLen = sizeof(MNCC_REQ_PARAM_UNION);

    MN_INFO_LOG4("MN_CALL_AllocMnccPrimitive: enPrimName, ucTi, ucCallId, ulParamLen:",
                 pstMsg->enPrimName,
                 pstMsg->ucTi,
                 pstMsg->ucCallId,
                 (VOS_INT32)pstMsg->ulParamLen);


    *ppunParam = &pstMsg->unParam;

    return (MsgBlock*)pstMsg;


}


/*****************************************************************************
 �� �� ��  : MN_CALL_SendMnccPrimitive
 ��������  : ����һ��MNCCԭ����Ϣ
 �������  : pMsg - ָ����Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendMnccPrimitive(MsgBlock * pMsg)
{
    /*
    ����VOS_SendMsg������Ϣ
    */
    return PS_SEND_MSG(WUEPS_PID_TAF, pMsg);
}


VOS_UINT32  MN_CALL_SendCcSetupReq(
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU            *pstBc1,
    const NAS_CC_IE_BC_STRU            *pstBc2,
    const MN_CALL_MGMT_STRU            *pstCallInfo
)
{

    NAS_CC_MSG_SETUP_MO_STRU            *pstSetup;
    MsgBlock                            *pMsg;
    MN_CALL_SS_COMPONENT_UNION          unComponent;
    VOS_UINT32                          ulLen;

    MN_CALL_MSG_BUFF_STRU              *pstBufferdSetupMsg = VOS_NULL_PTR;

    /* ����MNCC_SETUP_REQԭ�� */
    pMsg = MN_CALL_AllocMnccPrimitive(pstCallInfo->stCallInfo.callId,
                                      MNCC_SETUP_REQ,
                                      (MNCC_REQ_PARAM_UNION**)&pstSetup);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcSetupReq: Failed to alloc setup message.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* ��дredial��־  */
    ((MNCC_REQ_PRIM_MSG_STRU *)pMsg)->ucRedialFlg = VOS_FALSE;

    /* ��дrepeat indicator*/
    MN_CALL_FillIeRepeatInd(enRepeatInd, &pstSetup->stBCRepeatInd);

    /* ��дBC1��BC2 */
    pstSetup->stBC1 = *pstBc1;
    pstSetup->stBC2 = *pstBc2;


    /* ��д���к��� */
    if (0 != pstCallInfo->stCallInfo.stCalledNumber.ucNumLen)
    {
        NAS_IE_SET_PRESENT(&pstSetup->stCalledNum);

        *((VOS_UINT8*)&pstSetup->stCalledNum.Octet3) = pstCallInfo->stCallInfo.stCalledNumber.enNumType;

        PS_MEM_CPY(pstSetup->stCalledNum.BCDNum,
                   pstCallInfo->stCallInfo.stCalledNumber.aucBcdNum,
                   pstCallInfo->stCallInfo.stCalledNumber.ucNumLen);

        NAS_IE_SET_BLOCK_SIZE(&pstSetup->stCalledNum,
                              BCDNum,
                              pstCallInfo->stCallInfo.stCalledNumber.ucNumLen);
    }
    else
    {
        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* ��д���к�����ӵ�ַ */
    if (VOS_TRUE == pstCallInfo->stCallInfo.stCalledSubAddr.IsExist)
    {
        NAS_IE_SET_PRESENT(&pstSetup->stCalledSubaddr);
        pstSetup->stCalledSubaddr.LastOctOffset = pstCallInfo->stCallInfo.stCalledSubAddr.LastOctOffset;

        PS_MEM_CPY((VOS_UINT8 *)&pstSetup->stCalledSubaddr.Octet3,
                   &pstCallInfo->stCallInfo.stCalledSubAddr.Octet3,
                   sizeof(VOS_UINT8));

        ulLen = pstCallInfo->stCallInfo.stCalledSubAddr.LastOctOffset - sizeof(pstCallInfo->stCallInfo.stCalledSubAddr.Octet3);
        PS_MEM_CPY(pstSetup->stCalledSubaddr.SubAddrInfo,
                   pstCallInfo->stCallInfo.stCalledSubAddr.SubAddrInfo,
                   ulLen);
    }


    /* �������CUG��Ϣ����ô����CUG���� */
    if (VOS_TRUE == pstCallInfo->stCugCfg.bEnable)
    {
        unComponent.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
        if (VOS_OK == MN_CALL_InvokeIdAlloc(pstCallInfo->stCallInfo.callId,
                                            &unComponent.invokeComp.ucInvokeId,
                                            MN_CALL_SS_CUG_OPERATION))
        {
            unComponent.invokeComp.ucCompType       = MN_CALL_SS_INVOKE_TYPE_TAG;
            unComponent.invokeComp.ucOperateCode    = MN_CALL_SS_CUG_OPERATION;
            unComponent.invokeComp.bitOpArg         = 1;
            unComponent.invokeComp.unArg.cugInfoArg = pstCallInfo->stCugCfg;

            NAS_IE_SET_PRESENT(&pstSetup->stFacility);
            ulLen = MN_CALL_FacilityEncode(pstSetup->stFacility.aucFacility, &unComponent);

            /*���ݿ��е����ݳ���ΪTLV�ṹ�е�V�ĳ���*/
            NAS_IE_SET_BLOCK_SIZE(&pstSetup->stFacility,
                                  aucFacility,
                                  ulLen);
        }
    }

    /*��дCLIR����������*/
    switch(pstCallInfo->enClirCfg)
    {
    case MN_CALL_CLIR_AS_SUBS:
        break;

    case MN_CALL_CLIR_INVOKE:
        NAS_IE_SET_PRESENT(&pstSetup->stCLIR_I);
        break;

    case MN_CALL_CLIR_SUPPRESS:
        NAS_IE_SET_PRESENT(&pstSetup->stCLIR_S);
        break;

    default:
        MN_WARN_LOG("MN_CALL_SendCcSetupReq: Failed to send message.");
        break;

    }

    /* Ŀǰû����д�����Ĳ����������Ҫ���������Ը�������������Ӧ�Ĳ��� */
    if (MN_CALL_TYPE_VIDEO != pstCallInfo->stCallInfo.enCallType)
    {
        MN_CALL_FillIeCcCap(&(pstSetup->stCCCap));
        MN_CALL_FillIeSupCodecList(&pstSetup->stCodecList);
    }
    else
    {
        MN_CALL_FillIeLlc(&pstSetup->stLLC1);
        MN_CALL_FillIeCcCap(&pstSetup->stCCCap);
    }

    /* ���֧�ֺ����ؽ����ܣ��򻺴�setup����Ϣ */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(pstCallInfo->stCallInfo.callId))
    {
        pstBufferdSetupMsg                        = MN_CALL_GetBufferedMsg();
        pstBufferdSetupMsg->bitOpBufferedSetupMsg = VOS_TRUE;
        PS_MEM_CPY(&pstBufferdSetupMsg->stBufferedSetupMsg,
                   (MNCC_REQ_PRIM_MSG_STRU *)pMsg, sizeof(MNCC_REQ_PRIM_MSG_STRU));
    }

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcSetupReq: Failed to send message.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    MN_NORM_LOG("MN_CALL_SendCcSetupReq: send message to cc.");
    return TAF_CS_CAUSE_SUCCESS;

}



VOS_UINT32  MN_CALL_SendCcEmergSetupReq(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                          *pucCategory
)
{
/*
    ����MNCC_EMERG_SETUP_REQԭ��
    if ����ʧ��
        ���� FAIL

    �������������дpayload�е�stEmerg�ṹ

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/
    NAS_CC_MSG_EMERGENCY_STEUP_STRU    *pstEmerg = VOS_NULL_PTR;
    MsgBlock                           *pMsg     = VOS_NULL_PTR;


    MN_CALL_MSG_BUFF_STRU              *pstBufferdSetupMsg = VOS_NULL_PTR;

    NAS_CC_IE_BC_STRU                   stBc1;
    NAS_CC_IE_BC_STRU                   stBc2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;
    VOS_UINT32                          ulRet;

    ulRet = MN_CALL_GetMoCallBc(callId, &stBc1, &stBc2, &enBcRepeatInd);
    if (VOS_OK != ulRet)
    {
        /* ����BCʧ�ܣ��ͷź��� */
        MN_WARN_LOG("MN_CALL_SendCcEmergSetupReq: BUILD BC FAIL.");

        return TAF_CS_CAUSE_UNKNOWN;
    }

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_EMERG_SETUP_REQ, (MNCC_REQ_PARAM_UNION **)&pstEmerg);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcEmergSetupReq: Failed to alloc EmergSetup message.");

        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* ��дredial��־  */
    ((MNCC_REQ_PRIM_MSG_STRU *)pMsg)->ucRedialFlg = VOS_FALSE;

    pstEmerg->stBC = stBc1;

    if (VOS_NULL_PTR != pucCategory)
    {
        NAS_IE_SET_PRESENT(&pstEmerg->stEmergencyCAT);
        pstEmerg->stEmergencyCAT.Octet3.EmergencyCAT = *pucCategory;
        NAS_IE_SET_LAST_OCTET_OFFSET(&pstEmerg->stEmergencyCAT,Octet3);
    }

    /* 2010-05-22, OuyangFei:
       ���������ڽ���G->W�л�ʱ������Ὣ�绰��ֹ�������˱ȶԣ������ǿ�ѡIE Supported Codecs����
       ԭ��δ֪�������ǽ�����ʱ��֧��Supported Codecsѡ�
       ��˽���IEȥ����
    MN_CALL_FillIeSupCodecList(&pstEmerg->stCodecList);
    */
    /* ����24.008 9.3.8.3,UEӦ�ð�����IE */
    MN_CALL_FillIeSupCodecList(&pstEmerg->stCodecList);

    /* ���֧�ֺ����ؽ����ܣ��򻺴�setup����Ϣ */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(callId))
    {
        pstBufferdSetupMsg                        = MN_CALL_GetBufferedMsg();
        pstBufferdSetupMsg->bitOpBufferedSetupMsg = VOS_TRUE;
        PS_MEM_CPY(&pstBufferdSetupMsg->stBufferedSetupMsg,
                   (MNCC_REQ_PRIM_MSG_STRU *)pMsg, sizeof(MNCC_REQ_PRIM_MSG_STRU));
    }

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcEmergSetupReq: Failed to send message.");

        return TAF_CS_CAUSE_UNKNOWN;
    }

    MN_NORM_LOG("MN_CALL_SendCcEmergSetupReq: send message to cc.");

    return TAF_CS_CAUSE_SUCCESS;
}
VOS_UINT32  MN_CALL_SendCcCallConfReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU             *pstBc1,
    const NAS_CC_IE_BC_STRU             *pstBc2,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{
/*
    ����MNCC_CALL_CONF_REQԭ��
    if ����ʧ��
        ���� FAIL

    �������������дpayload�е�stCallConf�ṹ

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/

    NAS_CC_MSG_CALL_CNF_STRU            *pstCallCnf;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_CALL_CONF_REQ, (MNCC_REQ_PARAM_UNION **)&pstCallCnf);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcCallConfReq: Failed to alloc CallConf message.");
        return VOS_ERR;
    }

    /*��дpstCallCnf�ṹ�е�repeat indicatorֵ*/
    MN_CALL_FillIeRepeatInd(enRepeatInd, &pstCallCnf->stRepeatInd);

    /* ��дpstCallCnf�ṹ�е�Causeֵ */
    if(MN_CALL_INVALID_CAUSE != enCause)
    {
        MN_CALL_FillIeCause(enCause, &pstCallCnf->stCause);
    }

    /* ��BC1��BC2���и�ֵ */
    pstCallCnf->stBC1 = *pstBc1;
    pstCallCnf->stBC2 = *pstBc2;

    if (MN_CALL_TYPE_VIDEO != MN_CALL_GetCallType(callId))
    {
        MN_CALL_FillIeSupCodecList(&pstCallCnf->stCodecList);
    }
    else
    {
        MN_CALL_FillIeCcCap(&pstCallCnf->stCCCap);
    }

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcCallConfReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcCallConfReq: send message to cc.");

    return VOS_OK;


}



VOS_UINT32  MN_CALL_SendCcDiscReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{
/*
    ����MNCC_DISC_REQԭ��
    if ����ʧ��
        ���� FAIL

    �������������дpayload�е�stDisc�ṹ

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/
    NAS_CC_MSG_DISCONNECT_MO_STRU       *pstDisc;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_DISC_REQ, (MNCC_REQ_PARAM_UNION **)&pstDisc);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcDiscReq: Failed to alloc Disc message.");
        return VOS_ERR;
    }

#if (FEATURE_ON == FEATURE_PTM)
    MN_CALL_CsCallDiscInfoRecord(callId, enCause);
#endif

    /* ��дpstDisc�ṹ�е�Causeֵ */
    MN_CALL_FillIeCause(enCause, &pstDisc->stCause);

    /* �·�CALL DISCONNECT EVENT��USIMģ�� */
    MN_CALL_SndStkCallDiscEvent(pMsg, MNCC_DISC_REQ, VOS_FALSE);

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcDiscReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcDiscReq: send message to cc.");

    return VOS_OK;


}
VOS_UINT32  MN_CALL_SendCcRelReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{
/*
    ����MNCC_REL_REQԭ��
    if ����ʧ��
        ���� FAIL

    �������������дpayload�е�stRel�ṹ

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/
    NAS_CC_MSG_RELEASE_MO_STRU          *pstRel;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_REL_REQ, (MNCC_REQ_PARAM_UNION **)&pstRel);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcRelReq: Failed to alloc CcRel message.");
        return VOS_ERR;
    }

    /* ��дpstRel�ṹ�е�Causeֵ */
    MN_CALL_FillIeCause(enCause, &pstRel->stCause);

    /* ��¼�����ͷŵ�ԭ��ֵ */
    MN_CALL_UpdateCcCause(callId, enCause);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* �·�CALL DISCONNECT EVENT��USIMģ�� */
    MN_CALL_SndStkCallDiscEvent(pMsg, MNCC_REL_REQ, VOS_FALSE);

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcRelReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcRelReq: send message to cc.");

    return VOS_OK;


}
VOS_VOID  MN_CALL_SendCcRejReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{
/*
    ����MNCC_REJ_REQԭ��
    if ����ʧ��
        ���� FAIL

    �������������дpayload�е�stRej�ṹ

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/

    /*����MNCC_REJ_REQԭ��*/
    NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU *pstRelComp;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_REJ_REQ, (MNCC_REQ_PARAM_UNION **)&pstRelComp);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcRejReq: Failed to alloc CcRel message.");
        return;
    }

    /* ��дpstRelComp�ṹ�е�Causeֵ */
    MN_CALL_FillIeCause(enCause, &pstRelComp->stCause);

    /* ��¼�ܾ�ԭ��ֵ */
    MN_CALL_UpdateCcCause(callId, enCause);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* �·�CALL DISCONNECT EVENT��USIMģ�� */
    MN_CALL_SndStkCallDiscEvent(pMsg, MNCC_REJ_REQ, VOS_FALSE);

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcRejReq: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcRejReq: send message to cc.");

    return;

}



VOS_UINT32  MN_CALL_SendCcSetupRsp(
    MN_CALL_ID_T                        callId
)
{
/*
    ����MNCC_SETUP_RESԭ��
    if ����ʧ��
        ���� FAIL

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/

    MNCC_REQ_PARAM_UNION                *punParam;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_SETUP_RES, &punParam);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcSetupRsp: Failed to alloc SetupRsp message.");
        return VOS_ERR;
    }

    /* Ŀǰ��ʱ������Ҫ��CONNECT��Ϣ���������� */

    MN_CALL_SndStkCallConnEvent((VOS_UINT8)MN_CALL_GetCcTi(callId), MN_CALL_DIR_MT);

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcSetupRsp: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcSetupRsp: send message to cc.");

    return VOS_OK;


}


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcHoldReq
 ��������  : ����MNCC_HOLD_REQԭ��
 �������  : CallId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SendCcHoldReq(
    MN_CALL_ID_T                        callId
)
{
/*
    ����MNCC_HOLD_REQԭ��
    if ����ʧ��
        ���� FAIL

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/

    MNCC_REQ_PARAM_UNION                *punParam;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_HOLD_REQ, &punParam);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcHoldReq: Failed to alloc Hold message.");
        return;
    }

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcHoldReq: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcHoldReq: send message to cc.");

    return;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcRetrieveReq
 ��������  : ����MNCC_RETRIEVE_REQԭ��
 �������  : CallId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcRetrieveReq(
    MN_CALL_ID_T                        callId
)
{
/*
    ����MNCC_RETRIEVE_REQԭ��
    if ����ʧ��
        ���� FAIL

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/

    MNCC_REQ_PARAM_UNION                *punParam;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_RETRIEVE_REQ, &punParam);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcRetrieveReq: Failed to alloc Retrieve message.");
        return;
    }

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcRetrieveReq: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcRetrieveReq: send message to cc.");

    return;
}
VOS_VOID  MN_CALL_SendCcSimpleFacility(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_OPERATION_CODE_T         opCode
)
{
/*
    ����MNCC_FACILITY_REQԭ��
    if ����ʧ��
        ���� FAIL

    �������������дpayload�е�stFac�ṹ

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/
    NAS_CC_MSG_FACILITY_MO_STRU         *pstFac;
    MsgBlock                            *pMsg;
    MN_CALL_SS_COMPONENT_UNION          unComponent;
    VOS_UINT32                          ulLen;

    MN_INFO_LOG2("MN_CALL_SendCcSimpleFacility: callId, opCode", callId, opCode);

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_FACILITY_REQ, (MNCC_REQ_PARAM_UNION **)&pstFac);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcSimpleFacility: Failed to alloc Facility message.");
        return;
    }

    NAS_IE_SET_PRESENT(&pstFac->stFacility);

    /* ��6610�Ĵ��뿴��Ŀǰֻ��AOC�п��ܻظ�return result */
    #if 0
    if (opCode == MN_CALL_SS_AOC_OPERATION)
    {
        unComponent.ucCompType = MN_CALL_SS_RETURN_RESULT_TYPE_TAG;
        unComponent.resultComp.ucCompType = MN_CALL_SS_RETURN_RESULT_TYPE_TAG;
        unComponent.resultComp.ucOperateCode = MN_CALL_SS_AOC_OPERATION;

        /*�˴���ʱ��©Invoke Id����д*/
    }
    else
    #endif
    {
        unComponent.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
        unComponent.invokeComp.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
        unComponent.invokeComp.ucOperateCode = opCode;
        unComponent.invokeComp.bitOpLinkId = 0;
        if (VOS_OK != MN_CALL_InvokeIdAlloc(callId, &unComponent.invokeComp.ucInvokeId,
                                             opCode))
        {
            MN_ERR_LOG("MN_CALL_SendCcSimpleFacility: Invoke Id Alloc Fail.");
            return;
        }

    }

    ulLen = MN_CALL_FacilityEncode( pstFac->stFacility.aucFacility, &unComponent);

    /*�Ƿ�����SS version indicator,Ŀǰ��1*/
    pstFac->stSSVersion.IsExist         = 1;
    pstFac->stSSVersion.LastOctOffset   = 1;
    pstFac->stSSVersion.Version         = 0;

    /*���ݿ��е����ݳ���ΪLV�ṹ�е�L�Ĵ�С����Tag�ĳ��ȣ�Ҳ����ΪL+1*/
    NAS_IE_SET_BLOCK_SIZE(&pstFac->stFacility, aucFacility, ulLen);

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcSimpleFacility: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcSimpleFacility: send message to cc.");

    return;



}


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcStartDtmfReq
 ��������  : ����MNCC_START_DTMF_REQԭ��
 �������  : CallId - ���е�ID
             ucKey  - Ҫ���͵�DTMF����
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcStartDtmfReq(
    MN_CALL_ID_T                        callId,
    VOS_INT8                            cKey
)
{
/*
    ����MNCC_START_DTMF_REQԭ��
    if ����ʧ��
        ���� FAIL

    �������������дpayload�е�stStartDtmf�ṹ

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/

    NAS_CC_MSG_START_DTMF_STRU          *pstDtmf = VOS_NULL_PTR;
    MsgBlock                            *pMsg    = VOS_NULL_PTR;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_START_DTMF_REQ, (MNCC_REQ_PARAM_UNION **)&pstDtmf);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcStartDtmfReq: Failed to alloc StartDtmf message.");
        return VOS_ERR;
    }

    /* ��дpstDtmf�ṹ�е�KeypadFacilityֵ */
    NAS_IE_SET_PRESENT(&pstDtmf->stKeypadFacility);
    pstDtmf->stKeypadFacility.KeypadInfo = (VOS_UINT8)cKey;


    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcStartDtmfReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcStartDtmfReq: send message to cc.");

    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcStopDtmfReq
 ��������  : ����MNCC_STOP_DTMF_REQԭ��
 �������  : CallId - ���е�ID
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcStopDtmfReq(
    MN_CALL_ID_T                        callId
)
{
    MNCC_REQ_PARAM_UNION                *punParam;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_STOP_DTMF_REQ, &punParam);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcStopDtmfReq: Failed to alloc StopDtmf message.");
        return VOS_ERR;
    }

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcStopDtmfReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcStopDtmfReq: send message to cc.");
    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcAlertReq
 ��������  : ����MNCC_ALERT_REQԭ��
 �������  : CallId        - ���е�ID
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcAlertReq(
    MN_CALL_ID_T                        callId
)
{
    /*����MNCC_ALERT_REQԭ��*/
    NAS_CC_MSG_ALERTING_MO_STRU         *pstAlert;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_ALERT_REQ, (MNCC_REQ_PARAM_UNION **)&pstAlert);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcRejReq: Failed to alloc CcRel message.");
        return VOS_ERR;
    }

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcRejReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcRejReq: send message to cc.");
    return VOS_OK;

}



VOS_VOID  MN_CALL_SendCcActCcbsReq(
    MN_CALL_ID_T                        callId
)
{
/*
    ����MNCC_REL_REQԭ��
    if ����ʧ��
        ���� FAIL

    ��дpayload��stRel�е�Facility IE

    ����ԭ��
    if ����ʧ��
        �ͷ������ԭ��
        ���� FAIL
    else
        ���� OK
*/
       NAS_CC_MSG_RELEASE_MO_STRU          *pstRel;
       MsgBlock                            *pMsg;
       MN_CALL_SS_COMPONENT_UNION           unComponent;
       VOS_UINT32                           ulLen;

       pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_REL_REQ, (MNCC_REQ_PARAM_UNION **)&pstRel);
       if (VOS_NULL_PTR == pMsg)
       {
           MN_ERR_LOG("MN_CALL_SendCcActCcbsReq: Failed to alloc CcRel message.");
           return;
       }

       /* ��дpstRel�ṹ�е�facilityֵ */
       NAS_IE_SET_PRESENT(&pstRel->stFacility);
       unComponent.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
       unComponent.invokeComp.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
       unComponent.invokeComp.ucOperateCode = MN_CALL_SS_REG_CC_ENTRY_OPERATION;
       unComponent.invokeComp.bitOpLinkId = 0;
       if (VOS_OK != MN_CALL_InvokeIdAlloc(callId, &unComponent.invokeComp.ucInvokeId,
                                           MN_CALL_SS_REG_CC_ENTRY_OPERATION))
       {
            MN_ERR_LOG("MN_CALL_SendCcActCcbsReq: Invoke Id Alloc Fail.");
            return;
       }
       ulLen = MN_CALL_FacilityEncode(pstRel->stFacility.aucFacility, &unComponent);

       /*���ݿ��е����ݳ���ΪLV�ṹ�е�L�Ĵ�С����Tag�ĳ��ȣ�Ҳ����ΪL+1*/
       NAS_IE_SET_BLOCK_SIZE(&pstRel->stFacility, aucFacility, ulLen);
       NAS_IE_SET_PRESENT(&pstRel->stSSVersion);
       pstRel->stSSVersion.LastOctOffset = 1;
       pstRel->stSSVersion.Version = NAS_SS_VERSION_INDICATOR_PHASE2;

       /* ������Ϣ��CC */
       if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
       {
           MN_ERR_LOG("MN_CALL_SendCcActCcbsReq: Failed to send message.");
           return;
       }

       MN_NORM_LOG("MN_CALL_SendCcActCcbsReq: send message to cc.");

       return;

}
VOS_UINT32  MN_CALL_SendCcEstCnfReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU             *pstBc1,
    const NAS_CC_IE_BC_STRU             *pstBc2,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
)
{

    NAS_CC_MSG_CC_EST_CNF_STRU          *pstCcEstCnf;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId,
                                      MNCC_EST_CNF_REQ,
                                      (MNCC_REQ_PARAM_UNION **)&pstCcEstCnf);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcEstCnfReq: Failed to alloc cc establishment cnf message.");
        return VOS_ERR;
    }

    /*��дpstCcEstCnf�ṹ�е�repeat indicatorֵ*/
    MN_CALL_FillIeRepeatInd(enRepeatInd, &pstCcEstCnf->stRepeatInd);

    /* ��дpstCcEstCnf�ṹ�е�Causeֵ */
    if(MN_CALL_INVALID_CAUSE != enCause)
    {
        MN_CALL_FillIeCause(enCause, &pstCcEstCnf->stCause);
    }

    /* ��BC1��BC2���и�ֵ */
    pstCcEstCnf->stBC1 = *pstBc1;
    pstCcEstCnf->stBC2 = *pstBc2;

    MN_CALL_FillIeSupCodecList(&pstCcEstCnf->stCodecList);

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcEstCnfReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcEstCnfReq: send message to cc.");

    return VOS_OK;


}


VOS_UINT32  MN_CALL_SendCcbsSetupReq(
    MN_CALL_ID_T                        callId
)
{
    NAS_CC_MSG_SETUP_MO_STRU            *pstSetup;
    MsgBlock                            *pMsg;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_SETUP_REQ, (MNCC_REQ_PARAM_UNION**)&pstSetup);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcbsSetupReq: Failed to alloc setup message.");
        return VOS_ERR;
    }
    MN_CALL_GetCcbsSetup(pstSetup);

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcbsSetupReq: Failed to send message.");
        return VOS_ERR;
    }

    MN_NORM_LOG("MN_CALL_SendCcbsSetupReq: send message to cc.");
    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcDeflectFacility
 ��������  : ����MNCC_DISC_REQԭ��, ����Я���������ƫתҵ���Facility IE
 �������  : CallId      - ���е�ID
             pstRedirNum - ƫת����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SendCcDeflectFacility(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNum
)
{
    NAS_CC_MSG_DISCONNECT_MO_STRU       *pstDiscMo;
    MsgBlock                            *pMsg;
    MN_CALL_SS_COMPONENT_UNION          unComponent;
    VOS_UINT32                          ulLen;

    pMsg = MN_CALL_AllocMnccPrimitive(callId, MNCC_DISC_REQ, (MNCC_REQ_PARAM_UNION **)&pstDiscMo);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcDeflectFacility: Failed to alloc StartDtmf message.");
        return;
    }

    /* ��дpstDiscMo�ṹ�е�Facilityֵ */
    PS_MEM_SET(&unComponent, 0, sizeof(unComponent));
    unComponent.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
    if (VOS_OK == MN_CALL_InvokeIdAlloc(callId, &unComponent.invokeComp.ucInvokeId,
                                        MN_CALL_SS_CD_OPERATION))
    {
        unComponent.invokeComp.ucCompType = MN_CALL_SS_INVOKE_TYPE_TAG;
        unComponent.invokeComp.ucOperateCode = MN_CALL_SS_CD_OPERATION;
        unComponent.invokeComp.bitOpArg = 1;
        unComponent.invokeComp.unArg.stCdArg.ucNumberLen = pstRedirNum->ucNumLen + sizeof(MN_CALL_NUM_TYPE_ENUM_U8);

        unComponent.invokeComp.unArg.stCdArg.aucNumber[0] = pstRedirNum->enNumType;
        PS_MEM_CPY(unComponent.invokeComp.unArg.stCdArg.aucNumber + 1,
                   pstRedirNum->aucBcdNum,
                   pstRedirNum->ucNumLen);


        NAS_IE_SET_PRESENT(&pstDiscMo->stFacility);
        ulLen = MN_CALL_FacilityEncode(pstDiscMo->stFacility.aucFacility, &unComponent);

        /*���ݿ��е����ݳ���ΪTLV�ṹ�е�V�ĳ���*/
        NAS_IE_SET_BLOCK_SIZE(&pstDiscMo->stFacility,
                              aucFacility,
                              ulLen);
    }
    else
    {
        MN_ERR_LOG("MN_CALL_SendCcDeflectFacility: Failed to alloc Invoke Id.");
        return;
    }

    MN_CALL_FillIeCause(NAS_CC_CAUSE_127, &pstDiscMo->stCause);

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcDeflectFacility: Failed to send message.");
        return;
    }

    MN_NORM_LOG("MN_CALL_SendCcDeflectFacility: send message to cc.");

    return;

}
VOS_UINT32  MN_CALL_SendCcBufferedSetupReq(
    MNCC_REQ_PRIM_MSG_STRU             *pstBufferdSetupMsg
)
{
    NAS_CC_MSG_SETUP_MO_STRU           *pstSetup = VOS_NULL_PTR;
    MsgBlock                           *pMsg     = VOS_NULL_PTR;

    /* ����MNCC_SETUP_REQԭ�� */
    pMsg = MN_CALL_AllocMnccPrimitive(pstBufferdSetupMsg->ucCallId,
                                      MNCC_SETUP_REQ,
                                      (MNCC_REQ_PARAM_UNION**)&pstSetup);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcBufferedSetupReq: Failed to alloc setup message.");
        return VOS_FALSE;
    }

    /* ��дredial��־  */
    ((MNCC_REQ_PRIM_MSG_STRU *)pMsg)->ucRedialFlg = VOS_TRUE;

    PS_MEM_CPY(pstSetup, &pstBufferdSetupMsg->unParam.stSetup, sizeof(NAS_CC_MSG_SETUP_MO_STRU));

    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcBufferedSetupReq: Failed to send message.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32  MN_CALL_SendCcBufferedEmgSetupReq(
    MNCC_REQ_PRIM_MSG_STRU             *pstBufferdEmgSetupMsg
)
{
    NAS_CC_MSG_EMERGENCY_STEUP_STRU    *pstEmgSetup = VOS_NULL_PTR;
    MsgBlock                           *pMsg        = VOS_NULL_PTR;

    /* ����MNCC_SETUP_REQԭ�� */
    pMsg = MN_CALL_AllocMnccPrimitive(pstBufferdEmgSetupMsg->ucCallId,
                                      MNCC_EMERG_SETUP_REQ,
                                      (MNCC_REQ_PARAM_UNION**)&pstEmgSetup);
    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("MN_CALL_SendCcBufferedEmgSetupReq: Failed to alloc setup message.");
        return VOS_FALSE;
    }


    /* ��дredial��־  */
    ((MNCC_REQ_PRIM_MSG_STRU *)pMsg)->ucRedialFlg = VOS_TRUE;

    PS_MEM_CPY(pstEmgSetup, &pstBufferdEmgSetupMsg->unParam.stEmerg, sizeof(NAS_CC_MSG_EMERGENCY_STEUP_STRU));

    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("MN_CALL_SendCcBufferedEmgSetupReq: Failed to send message.");
        return VOS_FALSE;
    }

    return VOS_TRUE;
}




VOS_VOID TAF_CALL_ProcCallStatusFail(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    /* ����״̬Ϊactive��heldʱ��֮ǰ�Ѿ�֪ͨ��cc setup_succ�ˣ�����Ҫ��֪ͨʧ�� */
    if ((MN_CALL_S_ACTIVE == enCallState)
     || (MN_CALL_S_HELD == enCallState))
    {
        return;
    }

    TAF_CALL_SendCcCallStatusNty(ucCallId, MNCC_CALL_STATUS_SETUP_FAIL);

    return;
}
VOS_VOID TAF_CALL_SendCcCallStatusNty(
    VOS_UINT8                           ucCallId,
    MNCC_CALL_STATUS_ENUM_UINT8         enCallStatus
)
{
    /* ֪ͨMNCC_CALL_STATUS_NTY�ĵ�:
        1.�绰��ͨʱ
        2.�绰��ͨǰʧ�ܣ���Ҫ֪ͨAT MN_CALL_EVT_RELEASE�¼�ʱ
    */

    MNCC_CALL_STATUS_NTY_STRU          *pstCallStatusNty    = VOS_NULL_PTR;
    MsgBlock                           *pstMsg                = VOS_NULL_PTR;

    /* ����MNCC_CALL_STATUS_NTYԭ�� */
    pstMsg = MN_CALL_AllocMnccPrimitive(ucCallId,
                                      MNCC_CALL_STATUS_NTY,
                                      (MNCC_REQ_PARAM_UNION**)&pstCallStatusNty);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_CALL_SendCcCallStatusNty: Failed to alloc call status nty message.");
        return;
    }

    pstCallStatusNty->enCallStatus  = enCallStatus;

    if (VOS_OK != MN_CALL_SendMnccPrimitive(pstMsg))
    {
        MN_ERR_LOG("TAF_CALL_SendCcCallStatusNty: Failed to send message.");
    }

    return;
}

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  TAF_CALL_SendCcSrvccCallInfoNtf(
    VOS_UINT8                           ucCallNum,
    MNCC_ENTITY_STATUS_STRU            *pstEntitySta
)
{
    VOS_UINT8                           i;
    MsgBlock                           *pMsg                = VOS_NULL_PTR;
    MNCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstSrvccCallInfoNtf = VOS_NULL_PTR;

    /* ����MNCC_ALERT_REQԭ��:call id�Ը���Ϣ��˵����Ч��,���ù�ע,�����дΪ0 */
    pMsg = MN_CALL_AllocMnccPrimitive(0, MNCC_SRVCC_CALL_INFO_NOTIFY, (MNCC_REQ_PARAM_UNION **)&pstSrvccCallInfoNtf);

    if (VOS_NULL_PTR == pMsg)
    {
        MN_ERR_LOG("TAF_CALL_SendCcSrvccCallInfoNtf: Failed to alloc CcRel message.");
        return;
    }

    /* �����Ϣ */
    pstSrvccCallInfoNtf->ucCallNum = ucCallNum;

    for (i = 0; i < ucCallNum; i++)
    {
        PS_MEM_CPY(&(pstSrvccCallInfoNtf->astEntityStatus[i]), &pstEntitySta[i], sizeof(MNCC_ENTITY_STATUS_STRU));
    }

    if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
    {
        pstSrvccCallInfoNtf->ucTchAvail  = VOS_TRUE;
    }

    /* ������Ϣ��CC */
    if (VOS_OK != MN_CALL_SendMnccPrimitive(pMsg))
    {
        MN_ERR_LOG("TAF_CALL_SendCcSrvccCallInfoNtf: Failed to send message.");
        return;
    }

    MN_NORM_LOG("TAF_CALL_SendCcSrvccCallInfoNtf: send message to cc.");

    return;
}
#endif

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
