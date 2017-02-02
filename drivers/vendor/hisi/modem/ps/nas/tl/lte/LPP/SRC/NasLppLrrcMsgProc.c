

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "NasLppLrrcMsgProc.h"
#include    "NasLppPublic.h"
#include    "LPPLRrcInterface.h"
#include    "NasLppSendMsg.h"



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPLRRCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPLRRCMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)
extern VOS_VOID NAS_LPP_SendUplinkMsg
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity
);
extern VOS_UINT16  NAS_LPP_EncodeMessage
(
    LPP_MESSAGE_STRU                   *pstLppMsg,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
);
/*****************************************************************************
 Function Name  : NAS_LPP_RcvLrrcLppLasLcsCapabilityInd
 Description    : LPPģ�鴦��LRRC�ϱ���Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
   1. wangensheng 00324863 2015-7-16
*****************************************************************************/
VOS_VOID    NAS_LPP_RcvLrrcLppLasLcsCapabilityInd
(
    LRRC_LPP_LAS_LCS_CAPABILITY_IND_STRU                   *pRcvMsg
)
{
    NAS_LPP_INFO_LOG("NAS_LPP_RcvLrrcLppLasLcsCapabilityInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrcLppLasLcsCapabilityInd_ENUM, LNAS_LPP_Func_Enter);


    NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.stRrcCapbility.ucUeRxTxTimeDiffMeasFlag =
            pRcvMsg->ucUeRxTxTimeDiffMeasFlag;

    NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.stRrcCapbility.ucOtdoaUeAssistFlag =
            pRcvMsg->ucOtdoaUeAssistFlag;

    NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.stRrcCapbility.ucInterFreqRSTDMeasFlag =
            pRcvMsg->ucInterFreqRSTDMeasFlag;

    NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.stRrcCapbility.ucAddOtdoaNeighbourCellInfoListFlag =
            pRcvMsg->ucAddOtdoaNeighbourCellInfoListFlag;

    NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.stRrcCapbility.ulBandNum =
            pRcvMsg->ulBandNum;

    NAS_LPP_MEM_CPY(NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.stRrcCapbility.aulBandInd, pRcvMsg->aulBandInd, LRRC_LPP_MAX_BAND_IND_ARRAY_NUM*sizeof(VOS_UINT32));


    NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.bRrcCapbilityFlag = PS_TRUE;

    return;
}


VOS_VOID NAS_LPP_RcvLrrclppEcidMeasCnf
(
    LRRC_LPP_ECID_MEAS_CNF_STRU         *pstEcidMeasCnf
)
{
    VOS_UINT32                          ulRslt              = 0;
    LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8 enLcsMeasRslt       = 0;
    VOS_UINT8                           ucSessionIndx       = 0;
    VOS_UINT8                           ucSessionTransIndx  = 0;
    NAS_LPP_LOC_TECH_MAP_STRU           *pstLppLocMap  = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvLrrclppEcidMeasCnf enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrclppEcidMeasCnf_ENUM,LNAS_LPP_Func_Enter);

    /*ͨ����λ�������͵õ���Ӧ��runingʵ��*/
    pstLppLocMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_ECID);
    if(NAS_LPP_NULL_PTR == pstLppLocMap)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLrrclppEcidMeasCnf: No Running Entity!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLrrclppEcidMeasCnf_ENUM, LNAS_LPP_SEARCH_RUNNING_TECH_FAIL);

        return;
    }

    ucSessionIndx       = pstLppLocMap->ucSessionIndx;
    ucSessionTransIndx  = pstLppLocMap->ucSessionTranIndx;

    /*����ȴ�ecid����cnf�ı�־*/
    NAS_LPP_SetWaitMeasCnfFlag(ucSessionIndx,ucSessionTransIndx,NAS_LPP_POSITION_TECH_ECID,NAS_LPP_NO_SLCT);

    ulRslt = NAS_LPP_TransFsmCheck(NAS_LPP_GetLppMainState(ucSessionIndx, ucSessionTransIndx),
                                   NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx),
                                   (PS_MSG_HEADER_STRU *)pstEcidMeasCnf);
    if(NAS_LPP_SUCCESS != ulRslt)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvLrrclppEcidMeasCnf: Check status!",
                            NAS_LPP_GetLppMainState(ucSessionIndx, ucSessionTransIndx),
                            NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx));
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvLrrclppEcidMeasCnf_ENUM, LNAS_LPP_MAIN_STATE,NAS_LPP_GetLppMainState(ucSessionIndx, ucSessionTransIndx));
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvLrrclppEcidMeasCnf_ENUM, LNAS_LPP_SUB_STATE, NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx));
        return;
    }

    enLcsMeasRslt = pstEcidMeasCnf->ucResult;
    switch(enLcsMeasRslt)
    {
        case LRRC_LPP_LCS_MEAS_RESULT_SUCC:

            /*����cnf�ɹ���û���ٵȴ�otdoa��lrrc cnf,���ң���transactionҲû�еȴ���������*/
            if ( (NAS_LPP_SLCT != NAS_LPP_GetWaitMeasCnfFlag(ucSessionIndx,ucSessionTransIndx,NAS_LPP_POSITION_TECH_OTDOA))
               &&(LPP_SS_WAIT_ASSISTDATA_RCV_CMP != NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx))
               &&(LPP_SS_WAIT_ASSISTDATA_REQ_PROCESS_CMP != NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx)) )
            {
                /*����LRRC�����ظ��ɹ�������������Բ���������Ҫ���������Զ�ʱ��*/
                if(NAS_LPP_REPORT_LOCATION_TYPE_PERIOD ==
                        NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx))
                {
                    NAS_LPP_INFO_LOG("NAS_LPP_RcvLrrclppEcidMeasCnf: start period timer!");
                    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrclppEcidMeasCnf_ENUM,LNAS_LPP_START_PERIOD_TIMER);

                    NAS_LPP_TimerStart(ucSessionIndx,
                                       ucSessionTransIndx,
                                       TI_NAS_LPP_PERIODICAL_REPORT);
                }

                /*��ǰֻ��һ�ֶ�λ��������ôһ����ECID���������*/
                /*ת״���Ȳ����ظ�*/
                NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_MEAS_IND);
            }
            else
            {
                /*�ж��ֶ�λ���������ڵȴ�otdoa��lrrc cnf����ת��״̬��*/
            }
            break;

        case LRRC_LPP_LCS_MEAS_IDLE_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_CONN_REL_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_PHY_FAIL_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_RESULT_OTHER_CAUSE:
            /*���ڲ���cnfʧ�ܵĳ��������ݲ�ͨ�����͵Ĵ��󣬷ֱ���*/
            /*���׶ζ�ӦLRRC�ϱ��Ĳ���cnf fail��ԭ��ֵͳһ�ͷ�����session����*/
            NAS_LPP_SndIntraLppMsg(0 ,NAS_LPP_NULL_PTR, NAS_LPP_CONN_MANAGE_FAIL);
            break;

        default:
            break;
    }

    return;
}
VOS_VOID NAS_LPP_RcvLrrcLppOtdoaMeasCnf
(
    LRRC_LPP_OTDOA_MEAS_CNF_STRU         *pstOtdoaMeasCnf
)
{
    VOS_UINT32                          ulRslt              = 0;
    LRRC_LPP_LCS_MEAS_RESULT_ENUM_UINT8 enLcsMeasRslt       = 0;
    VOS_UINT8                           ucSessionIndx       = 0;
    VOS_UINT8                           ucSessionTransIndx  = 0;
    NAS_LPP_LOC_TECH_MAP_STRU           *pstLppLocMap  = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLrrcLppOtdoaMeasCnf enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrcLppOtdoaMeasCnf_ENUM,LNAS_LPP_Func_Enter);

    /*ͨ����λ�������͵õ���Ӧ��runingʵ��*/
    pstLppLocMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
    if(NAS_LPP_NULL_PTR == pstLppLocMap)
    {
        NAS_LPP_ERR_LOG("RCV OTDOA CNF, No Running Entity!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLrrcLppOtdoaMeasCnf_ENUM, LNAS_LPP_SEARCH_RUNNING_TECH_FAIL);
        return;
    }

    ucSessionIndx       = pstLppLocMap->ucSessionIndx;
    ucSessionTransIndx  = pstLppLocMap->ucSessionTranIndx;

    /*����ȴ�ecid����cnf�ı�־*/
    NAS_LPP_SetWaitMeasCnfFlag(ucSessionIndx,ucSessionTransIndx,NAS_LPP_POSITION_TECH_OTDOA,NAS_LPP_NO_SLCT);

    ulRslt = NAS_LPP_TransFsmCheck(NAS_LPP_GetLppMainState(ucSessionIndx, ucSessionTransIndx),
                                   NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx),
                                   (PS_MSG_HEADER_STRU *)pstOtdoaMeasCnf);
    if(NAS_LPP_SUCCESS != ulRslt)
    {
        NAS_LPP_ERR_LOG2("NAS_LPP_RcvLrrcLppOtdoaMeasCnf: Check status!",
                            NAS_LPP_GetLppMainState(ucSessionIndx, ucSessionTransIndx),
                            NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx));

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLrrcLppOtdoaMeasCnf_ENUM, LNAS_LPP_FsmStateNotMatch);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvLrrcLppOtdoaMeasCnf_ENUM, LNAS_LPP_MAIN_STATE,NAS_LPP_GetLppMainState(ucSessionIndx, ucSessionTransIndx));
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvLrrcLppOtdoaMeasCnf_ENUM, LNAS_LPP_SUB_STATE, NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx));
        return;
    }

    //NAS_LPP_GetCfgPara()->bitOtdoaAssisChng = NAS_LPP_NO_SLCT;
    if (LPP_SS_WAIT_RELEASE_LRRC_MEAS_CNF == NAS_LPP_GetLppSubState(ucSessionIndx, ucSessionTransIndx))
    {
        NAS_LPP_StopTechLocForLackOfAssistData();
        return;
    }

    enLcsMeasRslt = pstOtdoaMeasCnf->ucResult;
    switch(enLcsMeasRslt)
    {
        case LRRC_LPP_LCS_MEAS_RESULT_SUCC:

            /*����cnf�ɹ���û���ٵȴ�ECID��lrrc cnf*/
            if ( (NAS_LPP_SLCT != NAS_LPP_GetWaitMeasCnfFlag(ucSessionIndx,ucSessionTransIndx,NAS_LPP_POSITION_TECH_ECID)) )
            {
                /*����LRRC�����ظ��ɹ�������������Բ���������Ҫ���������Զ�ʱ��*/
                if(NAS_LPP_REPORT_LOCATION_TYPE_PERIOD ==
                        NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx))
                {
                    NAS_LPP_INFO_LOG("NAS_LPP_RcvLrrcLppOtdoaMeasCnf: start period timer!");
                    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrcLppOtdoaMeasCnf_ENUM, LNAS_LPP_START_PERIOD_TIMER);

                    NAS_LPP_TimerStart(ucSessionIndx,
                                       ucSessionTransIndx,
                                       TI_NAS_LPP_PERIODICAL_REPORT);
                }

                /* ��ǰֻ��һ�ֶ�λ��������ôһ����ECID��������� */
                /*ת״���Ȳ����ظ�*/
                NAS_LPP_ChangeTransFsmState(ucSessionIndx, ucSessionTransIndx, LPP_MS_LOCATION, LPP_SS_WAIT_MEAS_IND);
            }
            else
            {
                /*�ж��ֶ�λ���������ڵȴ�otdoa��lrrc cnf����ת��״̬��*/
            }
            break;

        case LRRC_LPP_LCS_MEAS_IDLE_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_CONN_REL_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_PHY_FAIL_STATUS_ERROR:
        case LRRC_LPP_LCS_MEAS_RESULT_OTHER_CAUSE:
            /*���ڲ���cnfʧ�ܵĳ��������ݲ�ͨ�����͵Ĵ��󣬷ֱ���*/
            /*���׶ζ�ӦLRRC�ϱ��Ĳ���cnf fail��ԭ��ֵͳһ�ͷ�����session����*/
            NAS_LPP_SndIntraLppMsg(0 ,NAS_LPP_NULL_PTR, NAS_LPP_CONN_MANAGE_FAIL);
            break;

        default:
            break;
    }

    return;
}
VOS_VOID NAS_LPP_SaveEcidMeasResultInfo
(
    LRRC_LPP_ECID_MEAS_IND_STRU         *pstEcidMeasInd
)
{
    NAS_LPP_ECID_MEAS_RESULT_STRU       *pstEcidMeasRslt = NAS_LPP_NULL_PTR;

    pstEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();
    NAS_LPP_MEM_CPY(&(pstEcidMeasRslt->stLrrcLppEcidMeasResultList),
                    &(pstEcidMeasInd->stLrrcLppEcidMeasResultList),
                    sizeof(LRRC_LPP_ECID_MEAS_RESULT_LIST_STRU));
    pstEcidMeasRslt->bHaveEcidMeasFlag = PS_TRUE;

    return;
}


LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_GetNeighberMeasRsltElement
(
    LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU   *pstProvideLocR9Ies,
    VOS_UINT32                               ulLoop
)
{
    return &(pstProvideLocR9Ies->stEcidPRovideLocationInfo.stEcidSignalMeasInfo.stMeasResultList.astMeasResultsList[ulLoop]);
}


LPP_MEAS_RESULT_ELEMENT_STRU* NAS_LPP_GetPrimaryMeasRsltElement
(
    LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU   *pstProvideLocR9Ies
)
{
    return &(pstProvideLocR9Ies->stEcidPRovideLocationInfo.stEcidSignalMeasInfo.stPrimaryCellMeasResult);
}



LRRC_LPP_ECID_MEAS_RESULT_STRU* NAS_LPP_GetLrrcEcidMeasRslt
(
    NAS_LPP_ECID_MEAS_RESULT_STRU         *pstEcidMeasRslt,
    VOS_UINT32                             ulLoop
)
{
    return &(pstEcidMeasRslt->stLrrcLppEcidMeasResultList.astLrrcLppEcidMeasResult[ulLoop]);
}


VOS_VOID NAS_LPP_PrePareGloIdPara
(
    LPP_MEAS_RESULT_ELEMENT_STRU            *pstMeasRsltEle,
    LRRC_LPP_ECID_MEAS_RESULT_STRU          *pstLrrcLppMeasRslt
)
{

    pstMeasRsltEle->bitOpCellGlobalId = NAS_LPP_SLCT;

    NAS_LPP_NasPlmn2LppPlmn(pstLrrcLppMeasRslt->stGlobalIdInfo.aucPlmnId,
                            &pstMeasRsltEle->stCellGloId.stPlmnIdentity);

    /*identity*/
    pstMeasRsltEle->stCellGloId.stCellIdentity.ulChoice = LPP_EUTRA_CHOSEN;
    pstMeasRsltEle->stCellGloId.stCellIdentity.u.ulEutra =
                           pstLrrcLppMeasRslt->stGlobalIdInfo.ulCellIdentity;

    return;
}
VOS_VOID NAS_LPP_PrePareEcidParameterElement
(
    LPP_MEAS_RESULT_ELEMENT_STRU            *pstMeasRsltEle,
    LRRC_LPP_ECID_MEAS_RESULT_STRU          *pstLrrcLppMeasRslt,
    NAS_LPP_LOCATION_REQ_STRU               *pstLocationReqBuff
)
{
    VOS_UINT8                   ucLocReqLocFlag = 0;

    ucLocReqLocFlag = pstLocationReqBuff->stEcidReqLocationInfo.stRequestedMeasurements.ucRequestedMeas;

    /*phyCellId*/
    pstMeasRsltEle->ulPhyCellId = pstLrrcLppMeasRslt->usPhyCellId;

    /*Arfcn*/
    /*This field specifies the ARFCN of the measured E-UTRA carrier frequency,
    as defined in [12]. In case the target device includes arfcnEUTRA-v9a0,
    the target device shall set the corresponding arfcnEUTRA (i.e. without suffix)
    to maxEARFCN.*/
    if(pstLrrcLppMeasRslt->ulArfcn <= LPP_MAX_EARFCN)
    {
        /*Ƶ��ֵС�ڵ���65535*/
        pstMeasRsltEle->stArfcnEutra.ulArfcnValueEUTRA = pstLrrcLppMeasRslt->ulArfcn;
    }
    else
    {
        pstMeasRsltEle->bitOpMeasResultElementExt = NAS_LPP_SLCT;
        pstMeasRsltEle->stArfcnEutra.ulArfcnValueEUTRA = LPP_MAX_EARFCN;
        pstMeasRsltEle->bitOpArfcnEutraV9a0 = NAS_LPP_SLCT;
        pstMeasRsltEle->stArfcnEutraV9a0.ulArfcnValueEUTRAv9a0 = pstLrrcLppMeasRslt->ulArfcn;
    }

    /*RxTxTimeDiff&SFN*/
    if((NAS_LPP_SLCT == pstLrrcLppMeasRslt->ucUeRxTxTimeDiffMeasFlag)
       && (0 != (ucLocReqLocFlag & 0x01)))
    {
        pstMeasRsltEle->bitOpUeRxTxTimeDiff = NAS_LPP_SLCT;
        pstMeasRsltEle->ulUeRxTxTimeDiff = pstLrrcLppMeasRslt->usUeRxTxTimeDiff;

        pstMeasRsltEle->bitOpSystemFrameNumber = NAS_LPP_SLCT;
        pstMeasRsltEle->usSystemFrameNumber = pstLrrcLppMeasRslt->usSfn;
    }

    /*cellGlobalId*/
    if(NAS_LPP_SLCT == pstLrrcLppMeasRslt->ucCellGlobalIdFlag)
    {
        NAS_LPP_PrePareGloIdPara(pstMeasRsltEle, pstLrrcLppMeasRslt);
    }

    /*RSRP*/
    if(0 != (ucLocReqLocFlag & 0x04))
    {
        pstMeasRsltEle->bitOpRsrpResult = NAS_LPP_SLCT;
        pstMeasRsltEle->ucRsrpResult = pstLrrcLppMeasRslt->ucRsrp;
    }

    /*RSRQ*/
    if(0 != (ucLocReqLocFlag & 0x02))
    {
        pstMeasRsltEle->bitOpRsrqResult = NAS_LPP_SLCT;
        pstMeasRsltEle->ucRsrqResult = pstLrrcLppMeasRslt->ucRsrq;
    }

    return;
}
VOS_VOID NAS_LPP_PrePareEcidParameter
(
    LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU   *pstProvideLocR9Ies,
    NAS_LPP_ECID_MEAS_RESULT_STRU           *pstEcidMeasRslt,
    VOS_UINT8                                ucSessionIndx
)
{
    VOS_UINT32                          ulLoop = 0;
    LPP_MEAS_RESULT_ELEMENT_STRU       *pstNeighberMeasRsltEle= NAS_LPP_NULL_PTR;
    LRRC_LPP_ECID_MEAS_RESULT_STRU     *pstLrrcLppMeasRslt  = NAS_LPP_NULL_PTR;
    LPP_MEAS_RESULT_ELEMENT_STRU       *pstPrimaryMeasRslt  = NAS_LPP_NULL_PTR;
    VOS_UINT32                          ulCellNum           = 0;
    NAS_LPP_LOCATION_REQ_STRU          *pstLocationReqBuff  = NAS_LPP_NULL_PTR;

    /*�õ��洢��λ�����������Ϣ*/
    pstLocationReqBuff  = NAS_LPP_GetLocationReqBuff();

    pstProvideLocR9Ies->bitOpEcidPRovideLocationInfo = NAS_LPP_SLCT;
    pstProvideLocR9Ies->stEcidPRovideLocationInfo.bitOpEcidSignalMeasInfo = NAS_LPP_SLCT;

    ulCellNum = pstEcidMeasRslt->stLrrcLppEcidMeasResultList.ulCellNum;

    if(1 == ulCellNum)
    {
        /*��ǰֻ����С��һ���ϱ�������Ϣ*/
        /*
        ����Э��Ҫ�������ǰ��С�����������в�����Ϣ������Դ洢���ɣ������ǰֻ��
        ��С���Ĳ�����Ϣ������С���Ĳ�����Ϣ����������
        */
        /*This field contains measurements for the primary cell, when the target device reports
        measurements for both primary cell and neighbour cells. This field shall be omitted when
        the target device reports measurements for the primary cell only, in which case the
        measurements the primary cell is reported in the measuredResultsList.*/
        pstNeighberMeasRsltEle = NAS_LPP_GetNeighberMeasRsltElement(pstProvideLocR9Ies, 0);
        /*�õ�LRRC�ò���ʵ���ָ��*/
        pstLrrcLppMeasRslt  = NAS_LPP_GetLrrcEcidMeasRslt(pstEcidMeasRslt, 0);

        pstProvideLocR9Ies->stEcidPRovideLocationInfo.stEcidSignalMeasInfo.stMeasResultList.ulMeasResultsListCnt = 1;
        NAS_LPP_PrePareEcidParameterElement(pstNeighberMeasRsltEle,
                                            pstLrrcLppMeasRslt,
                                            pstLocationReqBuff);

    }
    else
    {
        /*LRRC�ϱ��Ĳ����������ڵ���1�� ���ķ���С������������Ԫ��������Ϣ���ڸ�С���б�*/
        pstProvideLocR9Ies->stEcidPRovideLocationInfo.stEcidSignalMeasInfo.bitOpPrimaryCellMeasRslt = NAS_LPP_SLCT;
        pstPrimaryMeasRslt = NAS_LPP_GetPrimaryMeasRsltElement(pstProvideLocR9Ies);
        pstLrrcLppMeasRslt = NAS_LPP_GetLrrcEcidMeasRslt(pstEcidMeasRslt, 0);

        /*������С����Ϣ*/
        NAS_LPP_PrePareEcidParameterElement(pstPrimaryMeasRslt,
                                            pstLrrcLppMeasRslt,
                                            pstLocationReqBuff);

        /*��������Ϣ*/
        pstProvideLocR9Ies->stEcidPRovideLocationInfo.stEcidSignalMeasInfo.stMeasResultList.ulMeasResultsListCnt = ulCellNum - 1;

        for(ulLoop = 1; ulLoop < ulCellNum ; ulLoop++)
        {
            pstNeighberMeasRsltEle = NAS_LPP_GetNeighberMeasRsltElement(pstProvideLocR9Ies, ulLoop - 1);
            /*�õ�LRRC�ò���ʵ���ָ��,������ĵڶ���Ԫ�ؿ�ʼȡ*/
            pstLrrcLppMeasRslt  = NAS_LPP_GetLrrcEcidMeasRslt(pstEcidMeasRslt, ulLoop);
            /*����������Ϣ*/
            NAS_LPP_PrePareEcidParameterElement(pstNeighberMeasRsltEle,
                                                pstLrrcLppMeasRslt,
                                                pstLocationReqBuff);
        }

    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_PrepareOtdoaQuality
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_PrepareOtdoaQuality
(
    LRRC_LPP_OTDOA_MEAS_QUALITY_STRU        *pstMeasRsltQuality,
    LPP_OTDOA_MEAS_QUALITY_STRU             *pstLppQuality
)
{
    pstLppQuality->ucErrorResolution = pstMeasRsltQuality->ucErrorResolution;

    pstLppQuality->ucErrorValuse = pstMeasRsltQuality->ucErrorValue;

    if (LPP_LRRC_INFO_FLAG_VALID == pstMeasRsltQuality->ucErrorNumSampleFlag )
    {
        pstLppQuality->ucErrorNumSamples = pstMeasRsltQuality->ucErrorNumSample;

        pstLppQuality->bitOpErrorNumSampiles = NAS_LPP_SLCT;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_PrePareOtdoaParameter
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_PrePareOtdoaParameter
(
    LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU   *pstProvideLocR9Ies,
    NAS_LPP_OTDOA_MEAS_RESLT_STRU           *pstOtdoaMeasRslt,
    VOS_UINT8                                ucSessionIndx,
    VOS_UINT8                                ucSessionTranIndx
)
{
    LPP_OTDOA_SIGNAL_MEAS_INFO_STRU        *pstOtdoaSignalMeasInfo;
    NAS_LPP_OTDOA_ASSIST_CFG_STRU          *pstOtdoaAssisCfg;
    LPP_NEIGHBOUR_MEAS_ELEMENT_STRU        *pstNghbrMeasElement;
    VOS_UINT32                              ulLoop,ulCellCnt;

    pstOtdoaAssisCfg = NAS_LPP_GetOtdoaAssisCfg();

    pstProvideLocR9Ies->bitOpOtdoaPRovideLocationInfo = NAS_LPP_SLCT;
    pstProvideLocR9Ies->stOtdoaPRovideLocationInfo.bitOpOtdoaSignalMeasInfo = NAS_LPP_SLCT;

    pstOtdoaSignalMeasInfo = &pstProvideLocR9Ies->stOtdoaPRovideLocationInfo.stOtdoaSignalMeasInfo;
    pstOtdoaSignalMeasInfo->usSystemFrameNumber = pstOtdoaMeasRslt->usSfn;
    pstOtdoaSignalMeasInfo->usPhysCellIdRef     = pstOtdoaMeasRslt->usPhyCellIdRef;

    /* 36.355   OTDOA Location Information Elements
    NotSameAsRef0
    The field is absent if the corresponding earfcnRef-v9a0 is present. Otherwise, the target device shall include this field if the EARFCN of the
    RSTD reference cell is not the same as the EARFCN of the assistance data reference cell provided in the OTDOA assistance data.
     */
    if ( pstOtdoaMeasRslt->ulEarfcn <= LPP_MAX_EARFCN)
    {
        if ( pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.ulEarfcn != pstOtdoaMeasRslt->ulEarfcn)
        {
            pstOtdoaSignalMeasInfo->stEarfcnRef.ulArfcnValueEUTRA = pstOtdoaMeasRslt->ulEarfcn;
            pstOtdoaSignalMeasInfo->bitOpArfcnValueEutra = NAS_LPP_SLCT;
        }
    }
    else
    {
        if ( pstOtdoaAssisCfg->stOtdoaReferenceCellInfo.ulEarfcn != pstOtdoaMeasRslt->ulEarfcn)
        {
            pstOtdoaSignalMeasInfo->stEarfcnRefV9a0.ulArfcnValueEUTRAv9a0 = pstOtdoaMeasRslt->ulEarfcn;
            pstOtdoaSignalMeasInfo->bitOpArfcnValueEutraV9a0 = NAS_LPP_SLCT;
            pstOtdoaSignalMeasInfo->bitOpOtdoaSignalMeasInfoExt = NAS_LPP_SLCT;
            pstOtdoaSignalMeasInfo->stEarfcnRefV9a0.bitOpARFCNValueEutraV9A0 = NAS_LPP_SLCT;
        }
    }

    if (LPP_LRRC_INFO_FLAG_VALID == pstOtdoaMeasRslt->ucCellGlobalIdFlag)
    {
       pstOtdoaSignalMeasInfo->bitOpCellGlobalIdRef = NAS_LPP_SLCT;
       pstOtdoaSignalMeasInfo->stCellGlobalIdRef.ulCellIdentity = pstOtdoaMeasRslt->stCellGlobalIdInfo.ulCellIdentity;

       NAS_LPP_NasPlmn2LppPlmn(pstOtdoaMeasRslt->stCellGlobalIdInfo.aucPlmnId,
                               &pstOtdoaSignalMeasInfo->stCellGlobalIdRef.stPlmnIdentity);
    }

    if (LPP_LRRC_INFO_FLAG_VALID == pstOtdoaMeasRslt->ucOtdoaMeasqualityFlag)
    {
        pstOtdoaSignalMeasInfo->bitOpRefQuality = NAS_LPP_SLCT;

        NAS_LPP_PrepareOtdoaQuality(&pstOtdoaMeasRslt->stReferenceMeasQuality, &pstOtdoaSignalMeasInfo->stReferenceQuality);
    }

    /*����Ѿ��ϱ������е�neighbour С��*/
    if ( pstOtdoaMeasRslt->ulNghbrRptNum >= pstOtdoaMeasRslt->stNeighbourMeasurementList.ulCellNum)
    {
        pstOtdoaMeasRslt->ulNghbrRptNum = 0;
        pstOtdoaSignalMeasInfo->stNeighbourMeasList.ulNeighbourMeasListCnt = 0;
        return;
    }

    /*
     If there are more than 24 NeighbourMeasurementElement to be sent, the target device may send them in multiple ProvideLocationInformation messages,
      as described under  sub-clause 5.3
     */
    ulCellCnt = pstOtdoaMeasRslt->stNeighbourMeasurementList.ulCellNum - pstOtdoaMeasRslt->ulNghbrRptNum;
    if ( ulCellCnt > LPP_MAX_NEIGHBOUR_MEAS_ELEMENT_LEN )
    {
        ulCellCnt = LPP_MAX_NEIGHBOUR_MEAS_ELEMENT_LEN;
    }



    pstOtdoaSignalMeasInfo->stNeighbourMeasList.ulNeighbourMeasListCnt = ulCellCnt;
    pstNghbrMeasElement = pstOtdoaSignalMeasInfo->stNeighbourMeasList.astNeighbourMeasListArray;

    for ( ulLoop =  pstOtdoaMeasRslt->ulNghbrRptNum; ulLoop < (pstOtdoaMeasRslt->ulNghbrRptNum + ulCellCnt); ulLoop++ )
    {
     /*NotSameAsRef2
       The field is absent if the corresponding earfcnNeighbour-v9a0 is present. Otherwise, the target device shall include this field if the EARFCN of
       this neighbour cell is not the same as the earfcnRef for the RSTD reference cell.
       */
        if ( pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn <= LPP_MAX_EARFCN )
        {
            if ( pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn != pstOtdoaMeasRslt->ulEarfcn)
            {
                pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].bitOpArfcnValueEutra = NAS_LPP_SLCT;

                pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].stEarfcnNeighbour.ulArfcnValueEUTRA
                    = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn;
            }
        }
        else
        {
            if ( pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn != pstOtdoaMeasRslt->ulEarfcn)
            {
                pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].bitOpArfcnValueEutraV9a0 = NAS_LPP_SLCT;
                pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].bitOpNeighbourMeasElementExt = NAS_LPP_SLCT;
                pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].stEarfcnNeighbourV9a0.bitOpARFCNValueEutraV9A0 = NAS_LPP_SLCT;
                pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].stEarfcnNeighbourV9a0.ulArfcnValueEUTRAv9a0
                    = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ulEarfcn;
            }
        }

        pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].ulPhysCellIdNeighbor
            = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].usPhyCellIdNeighbour;

        pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].ulRstd = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].usRstd;

        if (LPP_LRRC_INFO_FLAG_VALID == pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].ucCellGlobalIdFlag)
        {
            pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].stCellGlobalIdNeighbour.ulCellIdentity
                = pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].stCellGlobalIdInfo.ulCellIdentity;

            NAS_LPP_NasPlmn2LppPlmn(pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].stCellGlobalIdInfo.aucPlmnId,
                                   &pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].stCellGlobalIdNeighbour.stPlmnIdentity);

            pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].bitOpCellGlobalIdNeighbour = NAS_LPP_SLCT;
        }

        NAS_LPP_PrepareOtdoaQuality(&pstOtdoaMeasRslt->stNeighbourMeasurementList.stNeighbourMeasurement[ulLoop].stNeighboureMeasQuality,
                                    &pstNghbrMeasElement[ulLoop - pstOtdoaMeasRslt->ulNghbrRptNum].stRstdQuality);

    }

    /*�����Ѿ��ϱ�����������*/
    pstOtdoaMeasRslt->ulNghbrRptNum = pstOtdoaMeasRslt->ulNghbrRptNum + ulCellCnt;

}

/*****************************************************************************
 Function Name   : NAS_LPP_OnlyEncodeOtdoa
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-29  Draft Enact

*****************************************************************************/
VOS_BOOL  NAS_LPP_OnlyEncodeOtdoa( VOS_VOID )
{
    NAS_LPP_MEAS_RESULT_STRU               *pstMeasRslt;

    pstMeasRslt = NAS_LPP_GetMeasRsltAddr();

    if (pstMeasRslt->stOtdoaMeasRslt.ulNghbrRptNum > 0)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_VOID NAS_LPP_EncodeProvideLocationMsgWithIndentityInfo
(
    VOS_UINT32                         *pulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity,
    LPP_TRANSACTION_ID_STRU            *pstTransactionId,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucSessionTranIndx
)
{
    LPP_MESSAGE_STRU                       *pstUplinkProvideLoc = NAS_LPP_NULL_PTR;
    LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU  *pstProvideLocR9Ies  = NAS_LPP_NULL_PTR;
    NAS_LPP_ECID_MEAS_RESULT_STRU          *pstEcidMeasRslt     = NAS_LPP_NULL_PTR;
    NAS_LPP_MEAS_RESULT_STRU               *pstMeasRslt;
    VOS_UINT16                              usRslt              = 0;
    VOS_UINT16                              usBitPos            = 0;
    VOS_UINT8                               ucSessionIndx       = 0;
    VOS_UINT8                               ucTransIndx         = 0;
    LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU  *pstProvideLocstR9   = NAS_LPP_NULL_PTR;

    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);
    if(PS_NULL_UINT8 == ucSessionIndx)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_EncodeProvideLocationMsgWithIndentityInfo: don't find Session!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeProvideLocationMsgWithIndentityInfo_ENUM,LNAS_LPP_SearchSessionIndxFail);
        return;
    }

    ucTransIndx = NAS_LPP_GetTransIdIndex( ucSessionIndx, ucSessionTranIndx);
    if(PS_NULL_UINT8 == ucTransIndx)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_EncodeProvideLocationMsgWithIndentityInfo: trans index fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeProvideLocationMsgWithIndentityInfo_ENUM,LNAS_LPP_GetTransIdIndexFail);
        return;
    }

    /*���LPP MSG BUFF*/
    NAS_LPP_ClearLppMsgBuff();

    /*��ȡLPP MSG BUFF*/
    pstUplinkProvideLoc = NAS_LPP_GetLppMsgBuff();

    pstEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();
    pstMeasRslt = NAS_LPP_GetMeasRsltAddr();

    /*�õ������ṩλ����Ϣ�ĵ�ַ*/
    pstProvideLocR9Ies  = NAS_LPP_GetUpLinkProvideLocIEAddr(pstUplinkProvideLoc);

    /*�����ṩ������Ԫ*/
    pstUplinkProvideLoc->bitOpLppTransactionId    = NAS_LPP_SLCT;
    pstUplinkProvideLoc->bitOpSequenceNumber      = NAS_LPP_SLCT;
    pstUplinkProvideLoc->bitOpAcknowledgement     = NAS_LPP_SLCT;
    pstUplinkProvideLoc->bitOpLppMessageBody      = NAS_LPP_SLCT;
    /* ������ϱ�����OTDOA���ݣ������ϱ�С��������24����ʱ���ܽ���transaction�����һ������ʱ����transaction���� */
    if ((NAS_LPP_SLCT == NAS_LPP_GetPositionTechOtdoa(ucTransIndx))&&(pstMeasRslt->stOtdoaMeasRslt.stNeighbourMeasurementList.ulCellNum > pstMeasRslt->stOtdoaMeasRslt.ulNghbrRptNum) &&
        (LPP_MAX_NEIGHBOUR_MEAS_ELEMENT_LEN < pstMeasRslt->stOtdoaMeasRslt.stNeighbourMeasurementList.ulCellNum - pstMeasRslt->stOtdoaMeasRslt.ulNghbrRptNum))
    {
        pstUplinkProvideLoc->bEndTransaction          =PS_FALSE;
    }
    else
    {
        pstUplinkProvideLoc->bEndTransaction          =
                            NAS_LPP_GetEndTransFlg(ucSessionIndx, ucSessionTranIndx);
    }
    pstUplinkProvideLoc->stTransactionId.enInitiator =
                                pstTransactionId->enInitiator;
    pstUplinkProvideLoc->stTransactionId.ucTransactionNumber  =
                                pstTransactionId->ucTransactionNumber;
    pstUplinkProvideLoc->stSequenceNumber.ucSequenceNumber =
                                NAS_LPP_GetUpMsgSequenceNum();
    pstUplinkProvideLoc->stAcknowledgement.bitOpAckIndicator = NAS_LPP_NO_SLCT;
    /*��Ҫ�����ظ�ACK*/
    pstUplinkProvideLoc->stAcknowledgement.bAckRequested  = PS_TRUE;
    pstUplinkProvideLoc->stLppMessageBody.ulChoice        =
                        LPP_C1_MESSAGE_BODY_CHOSEN;
    pstUplinkProvideLoc->stLppMessageBody.u.stC1.ulChoice =
                        LPP_SUPPORT_MESSAGE_BODY_PROVIDE_LOCATION_INFO_CHOSEN;
    pstUplinkProvideLoc->stLppMessageBody.u.stC1.u.stProvideLocationInformation.ulChoice =
                        LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN;
    pstUplinkProvideLoc->stLppMessageBody.u.stC1.u.stProvideLocationInformation.u.stC1.ulChoice =
                        LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_R9_CHOSEN;
    pstProvideLocstR9 = &(pstUplinkProvideLoc->stLppMessageBody.u.stC1.u.stProvideLocationInformation.u.stC1.u.stProLocationInfoR9);

    /*���������ECID��λ����Ϣ�������ECID���ṩλ����Ϣ*/
    if( (VOS_FALSE == NAS_LPP_OnlyEncodeOtdoa() )
      &&(NAS_LPP_SLCT == NAS_LPP_GetPositionTechEcid(ucTransIndx)) )
    {
        /*
        �����ǰECID�Ĳ���IND��־λtrue��˵����ǰ����Ч�Ĳ�����Ϣ��ֱ�ӱ��룬
        �����ǰ�ı�־λfalse����˵��ĳһ�ϱ����������ʱ�򣬻�û����Ч��λ��
        ��Ϣ�����ϱ�location error������OTDOA�� �����Ե��ϱ���ʽ�������ȡ����
        ������Ϣ�����ϱ��գ������Ҫ��ʵЭ�飬ȷ���Ƿ���ȷ
        */
        if(PS_TRUE == pstEcidMeasRslt->bHaveEcidMeasFlag)
        {
            /*�����ǰ����ECID�Ĳ�����Ϣ����ֱ�ӶԲ������и�ֵ*/
            NAS_LPP_PrePareEcidParameter(pstProvideLocR9Ies, pstEcidMeasRslt, ucSessionIndx);
        }
        else
        {
            /*���������ʱ��û��ECID�Ĳ�����Ϣ����ֱ�ӱ���ECID-ERROR��Ϣ*/
            pstProvideLocstR9->bitOpEcidPRovideLocationInfo = NAS_LPP_SLCT;
            pstProvideLocstR9->stEcidPRovideLocationInfo.bitOpEcidError = NAS_LPP_SLCT;
            pstProvideLocstR9->stEcidPRovideLocationInfo.stEcidError.ulChoice = LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_CHOSEN;
            pstProvideLocstR9->stEcidPRovideLocationInfo.stEcidError.u.stTargetDeviceErrorCauses.enEcidTargetDeviceErrorCause
                    = LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_REQ_MEAS_NOT_AVAIL;
        }
    }

    /*���OTDOA���������ڱ仯�����ϱ�otdoa��*/
    if( (NAS_LPP_SLCT == NAS_LPP_GetPositionTechOtdoa(ucTransIndx) )
       &&(VOS_FALSE == NAS_LPP_IsOtdoaAssistDataChng() ) )
    {
        if (PS_TRUE == pstMeasRslt->stOtdoaMeasRslt.bMeasRsltFlag)
        {
            NAS_LPP_PrePareOtdoaParameter(pstProvideLocR9Ies, &pstMeasRslt->stOtdoaMeasRslt, ucSessionIndx,ucSessionTranIndx);
        }
        else
        {
            pstProvideLocstR9->bitOpOtdoaPRovideLocationInfo = NAS_LPP_SLCT;
            pstProvideLocstR9->stOtdoaPRovideLocationInfo.bitOpOtdoaError = NAS_LPP_SLCT;
            pstProvideLocstR9->stOtdoaPRovideLocationInfo.stOtdoaError.ulChoice = LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_CHOSEN;
            pstProvideLocstR9->stOtdoaPRovideLocationInfo.stOtdoaError.u.stTargetDeviceErrorCauses.enOtoaTargetDeviceErrorCause
                        = LPP_OTDOA_LOCATION_TARGET_DEVICE_ERROR_ATTEMP_BUT_UNABLE_TO_MEAS_SOME_NEIGHBOUR_CELL;

        }
    }

    /*���gnss���������ڱ仯�����ϱ�gnss��*/
    if( (VOS_FALSE == NAS_LPP_OnlyEncodeOtdoa() )
      &&(NAS_LPP_SLCT == NAS_LPP_GetPositionTechGnss(ucTransIndx))
      &&(VOS_FALSE == NAS_LPP_IsGnssAssistDataChng() ) )
    {
        /*LIFUXIN: TODO*/
    }

    /*��ʼ����*/
    usRslt = NAS_LPP_EncodeMessage(pstUplinkProvideLoc,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_EncodeProvideLocationMsgWithIndentityInfo: Encode ProvideLoc msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeProvideLocationMsgWithIndentityInfo_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
        return;
    }

    *pulLppMsgLen = usBitPos/8;

    /*���������Ϣ���ʶ����Ϣ*/
    pstLppMsgIdentity->ulSessionId                      = ulSessionId;
    pstLppMsgIdentity->stTransId.enInitiator            = pstUplinkProvideLoc->stTransactionId.enInitiator;
    pstLppMsgIdentity->stTransId.ucTransactionNumber    = pstUplinkProvideLoc->stTransactionId.ucTransactionNumber;
    pstLppMsgIdentity->usSequnceNum                     = pstUplinkProvideLoc->stSequenceNumber.ucSequenceNumber;
    pstLppMsgIdentity->enUplinkMsgType                  = NAS_LPP_UPLINK_MSG_TYPE_PROCESS;

    /*����ɹ�*/
    return;
}


VOS_VOID NAS_LPP_SndUplinkProvideLocationMsg
(
    LPP_TRANSACTION_ID_STRU            *pstTransactionId,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucSessionTransIndx
)
{
    VOS_UINT32                          ulLppMsgLen     = 0;
    VOS_UINT8                          *pucEncodeOutMsg = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_IDENTITY_STRU           stLppMsgIdentity = {0};

    /*�������֮�������Ĵ洢�ռ�*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_SndUplinkProvideLocationMsg:  Alloc Mem Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndUplinkProvideLocationMsg_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    /*���*/
    NAS_LPP_MEM_SET(pucEncodeOutMsg, 0, sizeof(VOS_UINT8) * NAS_LPP_MAX_BUFF_MSG_LEN);

    /*��װ�ṩ������Ϣ,���һ�ȡ���ʶ����Ϣ*/
    NAS_LPP_EncodeProvideLocationMsgWithIndentityInfo(&ulLppMsgLen,
                                                      pucEncodeOutMsg,
                                                      &stLppMsgIdentity,
                                                      pstTransactionId,
                                                      ulSessionId,
                                                      ucSessionTransIndx);
    /*���ͱ���õ����ݸ�����*/
    NAS_LPP_SendUplinkMsg(ulSessionId,
                          ulLppMsgLen,
                          pucEncodeOutMsg,
                          &stLppMsgIdentity);

    /*�ͷŶ�̬�ڴ�*/
    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_CmplOtdoaLocationInfo
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_CmplOtdoaLocationInfo
(
    LPP_TRANSACTION_ID_STRU            *pstTransactionId,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucSessionTransIndx
)
{
    NAS_LPP_MEAS_RESULT_STRU           *pstMeasRslt;
    VOS_UINT32                          ulLoop = 0;

    pstMeasRslt = NAS_LPP_GetMeasRsltAddr();

    while( (pstMeasRslt->stOtdoaMeasRslt.ulNghbrRptNum < pstMeasRslt->stOtdoaMeasRslt.stNeighbourMeasurementList.ulCellNum)
         &&(ulLoop < (LPP_MAX_FREQ_LAYERS_LEN - 1) ) )
    {
        NAS_LPP_SndUplinkProvideLocationMsg(pstTransactionId, ulSessionId, ucSessionTransIndx);
        ulLoop++;
    }

    pstMeasRslt->stOtdoaMeasRslt.ulNghbrRptNum = 0;
}


VOS_VOID NAS_LPP_SndProvideLocInfoAndChngState
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity      = NAS_LPP_NULL_PTR;
    VOS_UINT32                                  ulSessionId         = 0;
    LPP_TRANSACTION_ID_STRU                     stTransactionId;

    /* ��ȡtransactionʵ�� */
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /*�ͷ�����Ķ�̬�ڴ�*/
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLrrcLppEcidMeasInd: Don't find the transaction!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndProvideLocInfoAndChngState_ENUM, LNAS_LPP_GetTransElementByIndexFail);
        return;
    }

    /*��ȡSessionId*/
    ulSessionId = NAS_LPP_GetSessionIdBySessionIndx(ucSessionIndx);

    /*���transactionID*/
    stTransactionId.enInitiator         = pstTransEntity->stTransId.enInitiator;
    stTransactionId.ucTransactionNumber = pstTransEntity->stTransId.ucTransactionNumber;

    /*�ظ�ProvideLocation��Ϣ*/
    NAS_LPP_SndUplinkProvideLocationMsg(&stTransactionId, ulSessionId, ucSessionTransIndx);

    /*�ж��Ƿ���Ҫ����ʣ�µ�otodoa��neighbourС����֯����ļ���provide location information*/
    NAS_LPP_CmplOtdoaLocationInfo(&stTransactionId, ulSessionId, ucSessionTransIndx);

    /*��¼��ǰ���͵Ŀտ���Ϣ�������յ���������Ϣ֮�����ת��ʲô״̬*/
    pstTransEntity->enLastUpMsgId    = NAS_LPP_AIR_MSG_PROVIDE_LOCATION_INFO;

    NAS_LPP_ChangeTransFsmState(ucSessionIndx,
                        ucSessionTransIndx,
                        LPP_MS_LOCATION,
                        LPP_SS_WAIT_INTRA_DATA_CNF);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ReportOnceProcess
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.WangEnSheng 00324863      2015-9-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReportOnceProcess
(
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{

    NAS_LPP_MEAS_RESULT_STRU               *pstMeasRslt;
    NAS_LPP_LOC_TECH_RUNING_STRU            stPosSearchRslt = {0};
    VOS_UINT16                              usMeasReadyNum      = 0;
    VOS_UINT32                              ulLoop;

    pstMeasRslt = NAS_LPP_GetMeasRsltAddr();

    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx,&stPosSearchRslt);

    for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum ; ulLoop++ )
    {
        if (NAS_LPP_POSITION_TECH_ECID == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
        {
            if (VOS_TRUE == pstMeasRslt->stEcidMeasRslt.bHaveEcidMeasFlag)
            {
                usMeasReadyNum++;
            }
        }
        else if (NAS_LPP_POSITION_TECH_OTDOA == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
        {
            if (VOS_TRUE == pstMeasRslt->stOtdoaMeasRslt.bMeasRsltFlag)
            {
                usMeasReadyNum++;
            }
        }
        else
        {
           /* if (  )
            {
                usMeasReadyNum++;
            }*/
        }

    }

    if (stPosSearchRslt.ucNum == usMeasReadyNum)
    {
        NAS_LPP_SetEndTransFlg(ucSessionIndx, ucSessionTransIndx, PS_TRUE);

        /*�ϱ�λ����Ϣ*/
        NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,
                                              ucSessionTransIndx,
                                              ucTransIndx);
    }
}

/*lint -e438*/

VOS_VOID NAS_LPP_RcvLrrcLppEcidMeasInd
(
    LRRC_LPP_ECID_MEAS_IND_STRU         *pstEcidMeasInd

)
{
    VOS_UINT32                              ulGloIdRslt         = 0;
    VOS_UINT8                               ucSessionIndx       = 0;
    VOS_UINT8                               ucSessionTransIndx  = 0;
    VOS_UINT8                               ucTransIndx         = 0;
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8 enReprotLocationType= 0;
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLppLocMap        = NAS_LPP_NULL_PTR;
    LRRC_LPP_ECID_MEAS_RESULT_STRU         *pstLrrcLppEcidMeas  = NAS_LPP_NULL_PTR;
    LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU      *pstGloIdInfo        = NAS_LPP_NULL_PTR;
    NAS_LPP_ECID_MEAS_RESULT_STRU          *pstLppEcidMeasRslt  = NAS_LPP_NULL_PTR;
    VOS_UINT16                              usPhyCellId         = 0;


    NAS_LPP_INFO_LOG("NAS_LPP_RcvLrrcLppEcidMeasInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrcLppEcidMeasInd_ENUM, LNAS_LPP_Func_Enter);

    /*ͨ����λ�������͵õ���Ӧ��runingʵ��*/
    pstLppLocMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_ECID);
    if(NAS_LPP_NULL_PTR == pstLppLocMap)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvLrrcLppEcidMeasInd: No Running Entity!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLrrcLppEcidMeasInd_ENUM, LNAS_LPP_SEARCH_RUNNING_TECH_FAIL);
        return;
    }

    ucSessionIndx       = pstLppLocMap->ucSessionIndx;
    ucSessionTransIndx  = pstLppLocMap->ucSessionTranIndx;
    ucTransIndx         = pstLppLocMap->ucTransIndx;

    /*�õ�λ����Ϣ���ϱ�����*/
    enReprotLocationType = NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx);

    /*����EcidMeasInd��Ϣ*/
    NAS_LPP_SaveEcidMeasResultInfo(pstEcidMeasInd);


    pstLppEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();
    pstLrrcLppEcidMeas = NAS_LPP_GetLrrcEcidMeasRslt(pstLppEcidMeasRslt, 0);


    switch(enReprotLocationType)
    {
        case NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER:
        {
            NAS_LPP_INFO_LOG("NAS_LPP_RcvLrrcLppEcidMeasInd: Trigger Report!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrcLppEcidMeasInd_ENUM, LNAS_LPP_TriggerReport);

            /*�����ϱ�,����Э��Լ����������Ǵ���ʽ�ϱ�����ô��ǰ�Ķ�λ����һ��ֻ��ECID*/
            NAS_LPP_SetEndTransFlg(ucSessionIndx, ucSessionTransIndx, PS_FALSE);

            /*�����ϱ��ж��߼�*/
            pstGloIdInfo = NAS_LPP_GetLastTriggerCellGloId();
            if(NAS_LPP_NULL_PTR == pstGloIdInfo)
            {
                NAS_LPP_ERR_LOG("NAS_LPP_RcvLrrcLppEcidMeasInd: don't find GloId!");
                TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLrrcLppEcidMeasInd_ENUM, LNAS_LPP_FindGloIdFail);
                return;
            }

            /*��ȡ�µ�����С��ID*/
            usPhyCellId = pstLppEcidMeasRslt->stLrrcLppEcidMeasResultList.astLrrcLppEcidMeasResult[0].usPhyCellId;

            /*��ʹ���״�Ҳ��Ҳ���бȽϣ�����϶�����ȣ�һ�����ϱ�λ����Ϣ*/
            if(PS_TRUE == pstLrrcLppEcidMeas->ucCellGlobalIdFlag)
            {
                NAS_LPP_NORM_LOG("NAS_LPP_RcvLrrcLppEcidMeasInd: GLOID valid!");
                TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrcLppEcidMeasInd_ENUM, LNAS_LPP_GloIdInvalid);

                /*lint -e732*/
                ulGloIdRslt = NAS_LPP_MEM_CMP(pstGloIdInfo,
                    &(pstLrrcLppEcidMeas->stGlobalIdInfo),
                    sizeof(LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU));
                /*lint +e732*/

                /*����GLOID��Ϣ*/
                NAS_LPP_MEM_CPY(pstGloIdInfo,
                    &(pstLrrcLppEcidMeas->stGlobalIdInfo),
                    sizeof(LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU));
            }

            /*С���ı䣬 gloID��Ч�����ǵ�ǰ�ǵ�һ���ϱ�,����Ҫ�ϱ�����λ����Ϣ, ���ߵ�ǰ������С��ID�����˱仯*/
            if((0 != ulGloIdRslt)
                ||(NAS_LPP_GetLastTriggerLastPhyCellId() != usPhyCellId))
            {
                NAS_LPP_INFO_LOG1("NAS_LPP_RcvLrrcLppEcidMeasInd: ulGloIdRslt = !", ulGloIdRslt);
                TLPS_PRINT2LAYER_INFO1(NAS_LPP_RcvLrrcLppEcidMeasInd_ENUM, LNAS_LPP_GloIdRsltVal,ulGloIdRslt);

                /*С����Ϣ�����ı䣬�ϱ�λ����Ϣ*/
                NAS_LPP_SndProvideLocInfoAndChngState(ucSessionIndx,ucSessionTransIndx,ucTransIndx);

                /*���±��ر��������С��ID*/
                NAS_LPP_SetLastTriggerLastPhyCellId(usPhyCellId);
                ulGloIdRslt = 0;
            }
            break;
        }
        case NAS_LPP_REPORT_LOCATION_TYPE_PERIOD:
            /*�������ϱ�*/
            break;

        case NAS_LPP_REPORT_LOCATION_TYPE_ONCE:

            /*����һ�ֶ�λ��������ôһ����ECID*/
            NAS_LPP_INFO_LOG("NAS_LPP_RcvLrrcLppEcidMeasInd:only one pos tech, ECID!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvLrrcLppEcidMeasInd_ENUM, LNAS_LPP_ReportLocationTypeOnce);

            NAS_LPP_ReportOnceProcess(ucSessionIndx,ucSessionTransIndx,ucTransIndx);
            break;

        default:
            break;
    }

}
/*lint +e438*/

/*****************************************************************************
 Function Name   : NAS_LPP_RcvLrrcLppOtdoaMeasInd
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-26  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RcvLrrcLppOtdoaMeasInd
(
    LRRC_LPP_OTDOA_MEAS_IND_STRU        *pstOtdoaMeasInd
)
{
    VOS_UINT8                               ucSessionIndx       = 0;
    VOS_UINT8                               ucSessionTransIndx  = 0;
    VOS_UINT8                               ucTransIndx         = 0;
    NAS_LPP_REPORT_LOCATION_TYPE_ENUM_UINT8 enReprotLocationType= 0;
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLppLocMap        = NAS_LPP_NULL_PTR;
    NAS_LPP_OTDOA_MEAS_RESLT_STRU          *pstOtdoaMeasRslt;
    NAS_LPP_MEAS_RESULT_STRU               *pstMeasRslt;

    /*ͨ����λ�������͵õ���Ӧ��runingʵ��*/
    pstLppLocMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
    if(NAS_LPP_NULL_PTR == pstLppLocMap)
    {
        NAS_LPP_ERR_LOG("otdoa No Running Entity!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLrrcLppOtdoaMeasInd_ENUM, LNAS_LPP_SEARCH_RUNNING_TECH_FAIL);
        return;
    }

    pstMeasRslt = NAS_LPP_GetMeasRsltAddr();
    pstOtdoaMeasRslt = &pstMeasRslt->stOtdoaMeasRslt;
    ucSessionIndx       = pstLppLocMap->ucSessionIndx;
    ucSessionTransIndx  = pstLppLocMap->ucSessionTranIndx;
    ucTransIndx         = pstLppLocMap->ucTransIndx;

    if (NAS_LPP_SUCCESS != NAS_LPP_TransFsmCheck(NAS_LPP_GetLppMainState(ucSessionIndx,ucSessionTransIndx),
                                                 NAS_LPP_GetLppSubState(ucSessionIndx,ucSessionTransIndx),
                                                 (PS_MSG_HEADER_STRU *)pstOtdoaMeasInd) )
    {
        NAS_LPP_ERR_LOG2("wrong state for otdoa meas ind,",
                         NAS_LPP_GetLppMainState(ucSessionIndx,ucSessionTransIndx),
                         NAS_LPP_GetLppSubState(ucSessionIndx,ucSessionTransIndx));

        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLrrcLppOtdoaMeasInd_ENUM, LNAS_LPP_FsmStateNotMatch);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvLrrcLppOtdoaMeasInd_ENUM, LNAS_LPP_MAIN_STATE,NAS_LPP_GetLppMainState(ucSessionIndx,ucSessionTransIndx));
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RcvLrrcLppOtdoaMeasInd_ENUM, LNAS_LPP_SUB_STATE,NAS_LPP_GetLppSubState(ucSessionIndx,ucSessionTransIndx));
        return;
    }

    if ( VOS_TRUE == NAS_LPP_IsOtdoaAssistDataChng() )
    {
        NAS_LPP_ERR_LOG("otdoa ind,assis data changed");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvLrrcLppOtdoaMeasInd_ENUM, LNAS_LPP_OtdoaAssistDataChange);
        return;
    }

    pstOtdoaMeasRslt->bMeasRsltFlag = PS_TRUE;

    pstOtdoaMeasRslt->ucCellGlobalIdFlag = pstOtdoaMeasInd->ucCellGlobalIdFlag;
    pstOtdoaMeasRslt->ucOtdoaMeasqualityFlag = pstOtdoaMeasInd->ucOtdoaMeasqualityFlag;
    pstOtdoaMeasRslt->usSfn = pstOtdoaMeasInd->usSfn;
    pstOtdoaMeasRslt->usPhyCellIdRef = pstOtdoaMeasInd->usPhyCellIdRef;
    pstOtdoaMeasRslt->ulEarfcn = pstOtdoaMeasInd->ulEarfcn;

    NAS_LPP_MEM_CPY(&pstOtdoaMeasRslt->stCellGlobalIdInfo, &pstOtdoaMeasInd->stCellGlobalIdInfo, sizeof(LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU));
    NAS_LPP_MEM_CPY(&pstOtdoaMeasRslt->stReferenceMeasQuality, &pstOtdoaMeasInd->stReferenceMeasQuality, sizeof(LRRC_LPP_OTDOA_MEAS_QUALITY_STRU));
    NAS_LPP_MEM_CPY(&pstOtdoaMeasRslt->stNeighbourMeasurementList, &pstOtdoaMeasInd->stNeighbourMeasurementList, sizeof(LRRC_LPP_OTDOA_NEIGHBOUR_MEAS_LIST_STRU));

    /*�õ�λ����Ϣ���ϱ�����*/
    enReprotLocationType = NAS_LPP_GetSessionEntityReportType(ucSessionIndx,ucSessionTransIndx);
    /* ������ϱ�һ�εģ��ͼ���Ƿ���Ҫ���ͣ�������������ϱ�ֱ�ӷ��� */
    if ( NAS_LPP_REPORT_LOCATION_TYPE_ONCE == enReprotLocationType )
    {
        NAS_LPP_ReportOnceProcess(ucSessionIndx,ucSessionTransIndx,ucTransIndx);
    }
}
VOS_VOID NAS_LPP_LrrcMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_LrrcMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LrrcMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pEmmMsg->ulMsgName)
    {
        case ID_LRRC_LPP_LAS_LCS_CAPABILITY_IND:
            NAS_LPP_RcvLrrcLppLasLcsCapabilityInd( (LRRC_LPP_LAS_LCS_CAPABILITY_IND_STRU *) pRcvMsg );
            break;

        case ID_LRRC_LPP_ECID_MEAS_CNF:
            NAS_LPP_RcvLrrclppEcidMeasCnf( (LRRC_LPP_ECID_MEAS_CNF_STRU *) pRcvMsg );
            break;

        case ID_LRRC_LPP_OTDOA_MEAS_CNF:
            NAS_LPP_RcvLrrcLppOtdoaMeasCnf( (LRRC_LPP_OTDOA_MEAS_CNF_STRU *) pRcvMsg );
            break;

        case ID_LRRC_LPP_ECID_MEAS_IND:
            NAS_LPP_RcvLrrcLppEcidMeasInd( (LRRC_LPP_ECID_MEAS_IND_STRU *) pRcvMsg );
            break;

        case ID_LRRC_LPP_OTDOA_MEAS_IND:
            NAS_LPP_RcvLrrcLppOtdoaMeasInd( (LRRC_LPP_OTDOA_MEAS_IND_STRU *) pRcvMsg );
            break;
        default:
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
/* end of NasLppLrrcMsgProc.c */
