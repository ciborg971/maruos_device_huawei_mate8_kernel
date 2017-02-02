

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnMsgInclude.h"
#include "NasGmmInterface.h"
#include "NVIM_Interface.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"

#include "TafCbaCtx.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "NasUsimmApi.h"
#include "TafSdcCtx.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasComm.h"
#include "TafSdcLib.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_COMM_C

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_CLOSE_SMS_CAPABILITY_MSG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

MN_MSG_DISCARD_DELIVER_MSG_STRU         f_stMnMsgDiscardDeliverMsg;
MN_MSG_REPLACE_DELIVER_MSG_STRU         f_stMnMsgReplaceDeliverMsg;

MN_MSG_CLOSE_SMS_CAPABILITY_MSG_STRU    f_stMnMsgCloseSmsCapabilityMsg;

extern VOS_VOID NAS_MM_CsSimValid(VOS_BOOL *pbCsSimValid);
extern VOS_VOID NAS_MM_CsCellBar(VOS_BOOL *pbCsCellBar);


/*lint -save -e958 */

VOS_VOID MN_MSG_DeliverMsgNotSupport(
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_BOOL                            *pbSupportFlag,
    MN_MSG_TP_CAUSE_ENUM_U8             *penTpCause
)
{
    VOS_UINT32                          ulLoop;
    const MN_MSG_DCS_CODE_STRU         *pstDcs;
    const MN_MSG_USER_DATA_STRU        *pstUserData;

    *penTpCause     = MN_MSG_TP_CAUSE_UNSPECIFIED_ERR;
    *pbSupportFlag  = VOS_TRUE;

    /* �ж��Ƿ����ö��Ŷ������ԣ�����Ӧ�û�UE�಻֧�ֵĶ��� */
    if (MN_MSG_NVIM_ITEM_INACTIVE == f_stMnMsgDiscardDeliverMsg.ucActFlg)
    {
        return;
    }

    /* ����TP-UD�а���Special SMS Message Indication IE�Ķ��ţ��ö���Ӧ�ò�֧�� */
    pstUserData = &pstTsData->u.stDeliver.stUserData;
    for (ulLoop = 0; ulLoop < pstUserData->ucNumofHeaders; ulLoop++)
    {
        if (MN_MSG_UDH_SPECIAL_SM == pstUserData->astUserDataHeader[ulLoop].enHeaderID)
        {
            *pbSupportFlag = VOS_FALSE;
            return;
        }
    }

    /* ����TP-DCS��ʽ��Ϊ00XX��ʽ�Ķ��ţ��ö���Ӧ�ò�֧�� */
    pstDcs = &pstTsData->u.stDeliver.stDcs;
    if ((MN_MSG_MSG_WAITING_DISCARD == pstDcs->enMsgWaiting)
     || (MN_MSG_MSG_WAITING_STORE == pstDcs->enMsgWaiting)
     || (MN_MSG_MSG_WAITING_AUTO_DELETE == pstDcs->enMsgWaiting))
    {
        *pbSupportFlag = VOS_FALSE;
        *penTpCause = MN_MSG_TP_CAUSE_DCS_NOT_SUPPORTED;
        return;
    }

    if (MN_MSG_MSG_WAITING_NONE_1111 == pstDcs->enMsgWaiting)
    {
        *pbSupportFlag = VOS_FALSE;
        *penTpCause = MN_MSG_TP_CAUSE_DCS_NOT_SUPPORTED;
        return;
    }

    return;
}
VOS_VOID MN_MSG_MtSpecificFeatureInit(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = NV_Read(en_NV_Item_DISCARD_DELIVER_MSG_FEATURE,
                    &f_stMnMsgDiscardDeliverMsg,
                    sizeof(f_stMnMsgDiscardDeliverMsg));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_MtSpecificFeatureInit: Read en_NV_Item_Sms_MeStorageEnable Failed");
        f_stMnMsgDiscardDeliverMsg.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;
    }

    ulRet = NV_Read(en_NV_Item_REPLACE_DELIVER_MSG_FEATURE,
                    &f_stMnMsgReplaceDeliverMsg,
                    sizeof(f_stMnMsgReplaceDeliverMsg));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_MtSpecificFeatureInit: Read en_NV_Item_SMS_REPLACEMENT_FEATURE Failed");
        f_stMnMsgReplaceDeliverMsg.ucActFlg = MN_MSG_NVIM_ITEM_ACTIVE;
    }

    return;
}


VOS_VOID MN_MSG_GetReplaceFeature(VOS_UINT8 *pucActFlg)
{
    *pucActFlg = f_stMnMsgReplaceDeliverMsg.ucActFlg;
}


VOS_VOID MN_MSG_Init(VOS_VOID)
{
    MN_MSG_ReadNvimInfo();

    MN_MSG_SmInit();
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    TAF_CBA_Init();
#endif

    return;
}


VOS_VOID MN_MSG_PowerOff()
{
    MN_MSG_FinishMoProc();

    MN_MSG_DestroyMtInfo();

    MN_MSG_UpdateSendFailFlag(MN_MSG_SEND_FAIL_NO_DOMAIN);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* ��ʼ��CBA������Ϣ.  ������Ҫ��ʼ��ΪBUTTֵ��ԭ����: ���ٴ������յ�MMC��NET MODE INDʱ,
       �Ż���AS���ͼ���CBS������ */
    TAF_CBA_InitNetworkInfo();
#endif


    /* ֹͣ�����������еĶ�ʱ�� */
    MN_MSG_StopAllRunningTimer();

    /*��ʼ����ʱ����ز���*/
    MN_MSG_InitAllTimers();
}


VOS_VOID MN_MSG_CfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
)
{
    MN_MSG_SmCfgDataInit(enUsimStatus);
}

VOS_VOID MN_MSG_PrintBcdAddrStru(
    MN_MSG_BCD_ADDR_STRU                *pstAddr
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: addr len is ", pstAddr->ucBcdLen);
    MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: addr type is ", pstAddr->addrType);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_BCD_NUM_LEN; ulLoop++)
    {
        MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: ", pstAddr->aucBcdNum[ulLoop]);
    }
    return;
}


VOS_VOID MN_MSG_PrintSrvParamStru(
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{

    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS SERVICE PARAM INFO ");
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: Parameter indicate ", pstSrvParam->ucParmInd);
    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS DEST ADDRESS");
    MN_MSG_PrintBcdAddrStru(&pstSrvParam->stDestAddr);
    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS SCA ADDRESS");
    MN_MSG_PrintBcdAddrStru(&pstSrvParam->stScAddr);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucPid ", pstSrvParam->ucPid);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucDcs ", pstSrvParam->ucDcs);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucValidPeriod ", pstSrvParam->ucValidPeriod);
    return;
}


VOS_VOID MN_MSG_InitSmsServiceData(MN_MSG_CONFIG_PARM_STRU  *pstServicePara)
{
    pstServicePara->enAppMemStatus = MN_MSG_MEM_FULL_UNSET;
    pstServicePara->enCbmMemStore = MN_MSG_MEM_STORE_NONE;
    pstServicePara->enRcvSmAct = MN_MSG_RCVMSG_ACT_STORE;
    pstServicePara->enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstServicePara->enRcvStaRptAct = MN_MSG_RCVMSG_ACT_STORE;
    pstServicePara->enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
}


VOS_VOID MN_MSG_CsDomainAvailable(VOS_BOOL *pbCsDomainAvailable)
{
    VOS_BOOL                            bCsSimValid;
    VOS_BOOL                            bCsCellBar;
    VOS_UINT8                           ucUeServiceDomain;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucPsOnlyCsServiceSupportFlg)
    {
        ucUeServiceDomain = MN_MMA_GetServiceDomain();
        /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        if (TAF_MMA_SERVICE_DOMAIN_PS == ucUeServiceDomain)
        /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
        {
            *pbCsDomainAvailable = VOS_FALSE;
            return;
        }
    }


    NAS_MM_CsSimValid(&bCsSimValid);
    NAS_MM_CsCellBar(&bCsCellBar);

    if ((VOS_TRUE == bCsSimValid) && (VOS_FALSE == bCsCellBar))
    {
        *pbCsDomainAvailable = VOS_TRUE;
    }
    else
    {
        *pbCsDomainAvailable = VOS_FALSE;
        
        MN_NORM_LOG("MN_MSG_CsDomainAvailable: IS FALSE.");
        
    }

    return;
}
VOS_UINT32 MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl(
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU        *pstEnvelope,
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
)
{
    VOS_UINT32                          ulRet;
    SI_STK_ENVELOPE_RSP_STRU            stMoSmsRsp;

    PS_MEM_SET(&stMoSmsRsp, 0, sizeof(stMoSmsRsp));

    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    if (VOS_OK != (pstEnvelope->stCmdResult.ulResult))
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    {
        /*���ŷ���ʧ������*/
        stMoSmsRsp.Result = SI_STK_CTRL_NOT_ALLOW;

        NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);

        return MN_ERR_CLASS_SMS_MO_CTRL_ACTION_NOT_ALLOWED;
    }
    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    if (0 != pstEnvelope->stCnfData.ulRspDataLen)
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    {
        /* ������Ϣ�еĶ������ĺ����Ŀ�ĺ���������װTPDU�������� */
        /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
        (VOS_VOID)NAS_STKAPI_EnvelopeRsp_Decode(pstEnvelope->enEnvelopeType, pstEnvelope->stCnfData.ulRspDataLen, pstEnvelope->stCnfData.aucRspData, &stMoSmsRsp);
        /* Modified by h00313353 for iteration 9, 2015-2-13, end */

        /* ��Ӧ��Ϣ�д���RP-DA���¶������ĺ��� */
        if (SI_STK_CTRL_NOT_ALLOW == stMoSmsRsp.Result)
        {

            NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


            NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

            return MN_ERR_CLASS_SMS_MO_CTRL_ACTION_NOT_ALLOWED;
        }

        if(SI_STK_CTRL_ALLOW_MODIFY == stMoSmsRsp.Result)
        {
            ulRet = MN_MSG_MoCtrlAllowedWithModification(&stMoSmsRsp.uResp.MoSmsCtrlRsp,
                                           pstMoEntity);

            if (MN_ERR_NO_ERROR != ulRet)
            {
                stMoSmsRsp.Result = SI_STK_CTRL_NOT_ALLOW;

                NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


                NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

                return ulRet;
            }

            MN_MSG_CreateMoInfo(pstMoEntity);
        }

    }
    else
    {
        stMoSmsRsp.Result = SI_STK_CTRL_ALLOW_NOMODIFY;
    }


    NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


    NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

    /* ���Ͷ��ŵ�SMS�� */
    ulRet = MN_MSG_SendSmsRpDataReq(pstMoEntity->enSendDomain,
                                    pstMoEntity->aucRpDataInfo,
                                    pstMoEntity->ucRpDataLen,
                                    pstMoEntity->enMsgSignallingType);

    if (VOS_ERR == ulRet)
    {
        return MN_ERR_SEND_MSG_ERROR;
    }

    return MN_ERR_NO_ERROR;
}



VOS_VOID MN_MSG_GetCloseSMSFeature(VOS_UINT8 *pucActFlg)
{
    *pucActFlg = f_stMnMsgCloseSmsCapabilityMsg.ucActFlg;
}


VOS_VOID MN_MSG_CloseSmsCapabilityFeatureInit(VOS_VOID)
{
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLength;

    NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU                  stCloseSmsCapabilityCfg;

    PS_MEM_SET(&stCloseSmsCapabilityCfg, 0, sizeof(NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU));

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Close_SMS_Capability_Config, &ulLength);

    if (ulLength > sizeof(stCloseSmsCapabilityCfg))
    {
        MN_ERR_LOG("MN_MSG_CloseSmsCapabilityFeatureInit():WARNING: en_NV_Item_Close_SMS_Capability_Config length Error");
        return;
    }

    ulRet = NV_Read(en_NV_Item_Close_SMS_Capability_Config,
                   &stCloseSmsCapabilityCfg,
                    ulLength);

    f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = stCloseSmsCapabilityCfg.ucActFlg;

    /* ��ȡ�رն��Ŷ���NVʧ��,Ĭ�ϲ��رն��Ź��� */
    if (NV_OK != ulRet)
    {
        f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;

        MN_ERR_LOG("MN_MSG_CloseSmsCapabilityFeatureInit: Read en_NV_Item_CLOSE_SMS_Capability_Config Failed");
    }

    return;
}
VOS_VOID MN_MSG_SetCloseSMSFeature(VOS_UINT8 ucActFlg)
{
    f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = ucActFlg;
}



VOS_VOID MN_MSG_GetMtCustomizeInfo(MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MT_CUSTOMIZE_INFO_STRU       stMtCustomize;


    PS_MEM_SET(&stMtCustomize, 0x00, sizeof(stMtCustomize));

    *penMtCustomize = MN_MSG_MT_CUSTOMIZE_NONE;

    ulRet = NV_Read(en_NV_Item_SMS_MT_CUSTOMIZE_INFO,
                    &stMtCustomize,
                    sizeof(stMtCustomize));
    if (NV_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_GetMtCustomizeInfo: Fail to read ");
        return;
    }

    if (MN_MSG_NVIM_ITEM_ACTIVE == stMtCustomize.ucActFlag)
    {
        *penMtCustomize = stMtCustomize.enMtCustomize;
    }

    return;
}


VOS_VOID MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;
    
    PS_MEM_SET(&stSmssInfo, 0, sizeof(MN_MSG_SMSS_INFO_STRU));

    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_UpdateMemExceedFlag: fail to MN_MSG_ReadSmssInfo. ");
        return;
    }

    if (enMemCapExcNotFlag != stSmssInfo.enMemCapExcNotFlag)
    {
        stSmssInfo.enMemCapExcNotFlag = enMemCapExcNotFlag;
        MN_MSG_WriteSmssFile(&stSmssInfo);
    }

    return;
}



VOS_VOID MN_MSG_SetTpRd(MN_MSG_MO_ENTITY_STRU *pstMoEntity)
{
    VOS_UINT32                          ulPos;
    VOS_UINT8                           ulRpOaLength;
    VOS_UINT8                           ulRpDaLength;

    /* ��ȡTP-RD��λ�� */
    ulPos = 0;

    /* RP��MESSGGE TYPE */
    ulPos++;

    /* RP��RP-MR */
    ulPos++;

    /* RP��RP-OA */
    ulRpOaLength = pstMoEntity->aucRpDataInfo[ulPos];
    ulPos++;
    ulPos       += ulRpOaLength;

    /* RP��RP-DA */
    ulRpDaLength = pstMoEntity->aucRpDataInfo[ulPos];
    ulPos++;
    ulPos       += ulRpDaLength;

    /* RP��RP-USERDATA length */
    ulPos++;

    MN_MSG_EncodeTpRd(VOS_TRUE, &pstMoEntity->aucRpDataInfo[ulPos]);

    return;
}


VOS_UINT32 MN_MSG_IsProtocolSendDomain(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU  stSmsSrvParam;

    ulRet = NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_IsProtocolSendDomain: Read Service Parm From Nvim Failed");
        return VOS_FALSE;
    }

    if (MN_MSG_MO_DOMAIN_CUSTOMIZE_PROTOCOL == (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_MO_DOMAIN_PROTOCOL_OFFSET])
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_VOID TAF_MSG_RcvMmaCsServiceChangeNotify(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSG_CS_SERVICE_IND             *pstCsServInd = VOS_NULL_PTR;
    VOS_UINT8                           ucUsimtatus;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    pstCsServInd    = (MMA_MSG_CS_SERVICE_IND*)pstMsg;
    ucUsimtatus     = TAF_MSG_GetUsimStatus();
    MN_MSG_GetUsimPowerState(&enPowerState);

    /* �������ڣ�����Ҫ���¶���������USIM�ļ� */
    if (MN_MSG_SIM_NOT_EXIST == ucUsimtatus)
    {
        return;
    }

    if (TAF_CS_OFF == pstCsServInd->enCSState)
    {
        /* CS������������ʱ����Ϊ���Ź��ܹر� */
        MN_MSG_SetCloseSMSFeature(MN_MSG_NVIM_ITEM_ACTIVE);
    }
    else
    {
        /* CS����������ʱ����Ҫ���¶���NV,��NV��ֵΪ׼ */
        MN_MSG_CloseSmsCapabilityFeatureInit();

        /* ͬ��USIM�ļ���ͬ��USIM�ļ�����˳��ģ��ȶ�EF_SMS_SMSS_ID��
           �յ��ظ��󣬻���MSG_ProcEfSmssGetFileRsp�и���һ���ļ����Ͷ��ļ�����
           Ϊ�˱����ظ���ʼ������Ҫ���ϵ������ʱ��ͬ��USIM�ļ� */
        if (MN_MSG_USIM_POWER_ON == enPowerState)
        {
            /* Modified by h00313353 for iteration 9, 2015-3-9, begin */
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSS_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-3-9, end */
        }
    }
    return;

}

#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID MN_MSG_FailErrRecord(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode)
{
    NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU                      stSmsMoFailEvent;
    MN_MSG_SEND_DOMAIN_ENUM_U8                              enAvailableSendDomain;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_SMS_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU);

    /* ��д���ŷ���ʧ���¼���Ϣ */
    PS_MEM_SET(&stSmsMoFailEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stSmsMoFailEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_SMS_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* ��ȡ��״̬��Ϣ */
    NAS_MMA_OutputUsimInfo(&stSmsMoFailEvent.stUsimInfo);

    /* ��ȡλ����Ϣ */
    NAS_MNTN_OutputPositionInfo(&stSmsMoFailEvent.stPositionInfo);

    MN_MSG_OutputSmsMoFailureInfo(enErrorCode, &stSmsMoFailEvent.stMoFail);

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_PS, &enAvailableSendDomain);
    if (MN_MSG_SEND_DOMAIN_PS == enAvailableSendDomain)
    {
        stSmsMoFailEvent.enPsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE;
    }
    else
    {
        stSmsMoFailEvent.enPsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE;
    }

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS, &enAvailableSendDomain);
    if (MN_MSG_SEND_DOMAIN_CS == enAvailableSendDomain)
    {
        stSmsMoFailEvent.enCsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE;
    }
    else
    {
        stSmsMoFailEvent.enCsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE;
    }

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stSmsMoFailEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_MSG_FailErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_SMS_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stSmsMoFailEvent,
                           sizeof(stSmsMoFailEvent));
    return;
}
#endif


VOS_VOID TAF_MSG_RcvSpmSmmaRsp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SMMA_RSP_STRU              *pstSmmaMsg  = VOS_NULL_PTR;

    pstSmmaMsg = (TAF_SPM_SMMA_RSP_STRU *)pstMsg;

    /* �����ѡ����ΪBUFFER_MESSAGE��SEND_FAIL,��������ΪBUTT,������������ */
    if (TAF_MSG_SIGNALLING_TYPE_BUTT == pstSmmaMsg->enMsgSignallingType)
    {
        return;
    }

    /* ��SMS/IMSA����SMMA��Ϣ */
    (VOS_VOID)MN_MSG_SendSmma(pstSmmaMsg->clientId, pstSmmaMsg->opId, VOS_FALSE, pstSmmaMsg->enMsgSignallingType);

    return;

}

/* TAF_MSG_SendSpmSmmaInd�Ѿ��Ƶ�MnMsgSendSpm.c�ļ��� */
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

