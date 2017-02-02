

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafMtaMain.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmCpPdeProc.h"
#include "TafXpdsFsmPdeProcComm.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsFsmCpPdeProcTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_CP_FSM_PDE_PROC_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
Func Name    : TAF_XPDS_RcvXpdsCpPdeProcStart_CpL2Pde_Init
Description  : begining of PDE procedures after
                ID_TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ

History      :
    1.Date      :   25-08-2015
    Author      :   Lokesh l00902690
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpPdeProcStart_CpL2Pde_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU               *pstPdeDataReq = VOS_NULL_PTR;
    TAF_XPDS_CFG_INFO_STRU                                 *pstCagpsCfg;

    pstPdeDataReq = (TAF_XPDS_XPDS_CP_PDE_PROC_START_REQ_STRU *)pstMsg;
    pstCagpsCfg   = TAF_XPDS_GetAgpsCfg();

    switch (pstPdeDataReq->enFixMode)
    {
        case TAF_XPDS_MSA_MODE:
        case TAF_XPDS_AFLT_MODE:
            if (TAF_XPDS_SI == pstCagpsCfg->enAgpsType)
            {
                TAF_XPDS_HandleXpdsCpMsaModePdeOperationSI();
            }

            if (TAF_XPDS_NI == pstCagpsCfg->enAgpsType)
            {
                TAF_XPDS_HandleXpdsCpMsaModePdeOperationNI();
            }

            break;

        case TAF_XPDS_MSB_MODE:
            TAF_XPDS_HandleXpdsCpMsbModePdeOperation();
            break;

        default:
            break;
    }

    return VOS_TRUE;
}

/* added by L00902690 IT 2 - begin */
/*****************************************************************************
 Func Name    : TAF_XPDS_HandleXpdsCpMsbModePdeOperation
 Description  : begining of PDE procedures for MSB mode

  History       :
  1.Date        :   25-08-2015
    Author      :   Lokesh l00902690
    Modification:   Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_HandleXpdsCpMsbModePdeOperation(VOS_VOID)
{
    TAF_XPDS_ENCODE_RL_INFO_STRU        stEncodeRlInfo;

    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    /* send request ALM, EPHI, pilot phase meas and provide MS info to PDE */
    TAF_XPDS_UpdatePpmInGlobal();

    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ALM;
    stEncodeRlInfo.aucReqType[1] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_EPH;
    stEncodeRlInfo.ucNumOfReq    = 2;
    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
    stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 2;

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_CTRL_PLANE);

    /* change fsm state to wait CAS cnf */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_CAS_CNF);

    TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF,
                        TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF_TIMER_LEN);

}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsbModeRecieveCasCnf
 Description  : handler for CAS confirm message in MSB mode

  History       :
  1.Date        :   25-08-2015
    Author      :   Lokesh l00902690
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecieveCasCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDataCnf;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_CAS_CNF);

    pstDataCnf  = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU*)pstMsg;

    if (pstDataCnf->enRslt != CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS)
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsCpMsbModeRecieveCasCnf: CAS data CNF failed");
        TAF_XPDS_SendSessionEndAndQuitL2Fsm();
        TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_FAIL);
        return VOS_TRUE;
    }

    /* wait for the PDE response of complete ALM and EPHI */

    /* change fsm state to wait PDE response */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_PDE_EPHI_ALM_RESP);

    TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP,
                        TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP_TIMER_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsbModeRecievePdeResp
 Description  : handler for PDE ALM , EPHI complete message in MSB mode

  History       :
  1.Date        :   25-08-2015
    Author      :   Lokesh l00902690
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecievePdeResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU    *pstPdeDataInd = VOS_NULL_PTR;
    VOS_UINT8                                   ucAlmDataFinishedFlag;
    VOS_UINT8                                   ucEphmDataFinishedFlag;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* �ж��Ƿ����Assist Info */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH & pstPdeDataInd->ulDataMask) != VOS_FALSE)
    {
        TAF_XPDS_SetGpsEphDataFinishedFlag(PS_TRUE);

        /* send ephimeries information to GPS */
        TAF_XPDS_SndAtGpsEphInfo();
    }

    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM & pstPdeDataInd->ulDataMask) != VOS_FALSE)
    {
        TAF_XPDS_SetGpsAlmDataFinishedFlag(PS_TRUE);

        /* send almanac information to GPS */
        TAF_XPDS_SndAtGpsAlmInfo();
    }

    ucAlmDataFinishedFlag   = TAF_XPDS_GetGpsAlmDataFinishedFlag();
    ucEphmDataFinishedFlag  = TAF_XPDS_GetGpsEphDataFinishedFlag();

    /* when both are recieved change the state to waiting GPS location response */
    if ((PS_TRUE == ucAlmDataFinishedFlag) && (PS_TRUE == ucEphmDataFinishedFlag))
    {
        TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_ALM_EPHI_RESP);

        TAF_XPDS_SetGpsEphDataFinishedFlag(PS_FALSE);
        TAF_XPDS_SetGpsAlmDataFinishedFlag(PS_FALSE);

        /* wait for the response from GPS */
        /* change fsm state to wait GPS location response */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_GPS_LOC_RESP);

        TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP,
                            TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP_TIMER_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsMsbModeRecieveGpsLocResp
 Description  : handler for GPS loc response message in MSB mode

  History       :
  1.Date        :   25-08-2015
    Author      :   Lokesh l00902690
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsbModeRecieveGpsLocResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_POS_INFO_RSP_STRU       *pstCagpsPosInfoRsp;
    AT_XPDS_MSG_STRU                    *pstAtXpdsReqMsg;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_GPS_LOC_RESP);

    /* save GPS position information to glo */
    pstAtXpdsReqMsg     = (AT_XPDS_MSG_STRU *)pstMsg;
    pstCagpsPosInfoRsp  = (AT_XPDS_GPS_POS_INFO_RSP_STRU*)(pstAtXpdsReqMsg->aucContent);

    PS_MEM_CPY(&(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfoRsp),
               pstCagpsPosInfoRsp,
               sizeof(AT_XPDS_GPS_POS_INFO_RSP_STRU));

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSB_WAIT_AT_GPS_STOP);

    /* change fsm state to wait gps stop */
    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_AT_GPS_STOP,
                                  TI_TAF_XPDS_CP_L2_PDE_MSB_WAIT_AT_GPS_STOP_TIMER_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpGeneralTimerTimeout
 Description  : general timeout handler for all timeout messages

  History       :
  1.Date        :   25-08-2015
    Author      :   Lokesh l00902690
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpGeneralTimerTimeout(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT);

    TAF_XPDS_SendSessionEndAndQuitL2Fsm();

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvAtGpsStopReq_L2Pde_MsbMode
 Description  : handler for GPS stop request from AT

  History       :
  1.Date        :   25-08-2015
    Author      :   Lokesh l00902690
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsStopReq_L2Pde(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_FAIL);

    TAF_XPDS_SendSessionEndAndQuitL2Fsm();

    /* ����OK */
    TAF_XPDS_SndAtGpsStopCnf();

    return VOS_TRUE;
}

/* added by L00902690 IT 2 - end */

/* added by A00903922 AGPS IT 2 31-08-2015 - begin */
/*****************************************************************************
 Func Name    : TAF_XPDS_HandleXpdsCpMsaModePdeOperationSI
 Description  : begining of SI PDE procedures for MSA mode

  History       :
  1.Date        :   31-08-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_HandleXpdsCpMsaModePdeOperationSI(VOS_VOID)
{
    TAF_XPDS_ENCODE_RL_INFO_STRU        stEncodeRlInfo;

    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    /* send provide MS Info and pilot phase measurement data */

    TAF_XPDS_UpdatePpmInGlobal();

    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST;
    stEncodeRlInfo.ucNumOfReq    = 1;
    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
    stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 2;

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_CTRL_PLANE);

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                                  TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM_TIMER_LEN);

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM);

}

/*****************************************************************************
 Func Name    : TAF_XPDS_HandleXpdsCpMsaModePdeOperationNI
 Description  : begining of SI PDE procedures for MSA mode

  History       :
  1.Date        :   31-08-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_HandleXpdsCpMsaModePdeOperationNI(VOS_VOID)
{
    TAF_XPDS_ENCODE_RL_INFO_STRU        stEncodeRlInfo;
    VOS_UINT32                          ulPPMTimerVal;

    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    /* send provide MS Info and pilot phase measurement data */

    stEncodeRlInfo.ucNumOfReq    = 0;
    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
    stEncodeRlInfo.ucNumOfResp   = 1;

    ulPPMTimerVal   = (TAF_XPDS_GetPilotPhaseTimerLimitLen() / TAF_XPDS_PPM_TIMER_FRACTION);

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_CTRL_PLANE);

    /* start timer for PPM Measurement completion */
    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PPM_COMPLETE_NI_QUALITY,
                                  ulPPMTimerVal);


    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_MS_INFO,
                                  TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_MS_INFO_TIMER_LEN);

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_MS_INFO);

}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM
 Description  : handler for CAS confirm message in MSA mode,
                after the Pilot phase measeurement is sent out

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDataCnf;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM);

    pstDataCnf  = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU*)pstMsg;

    if (pstDataCnf->enRslt != CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS)
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM: CAS data CNF failed");
        TAF_XPDS_SendSessionEndAndQuitL2Fsm();
        TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_FAIL);
        return VOS_TRUE;
    }

    /* change fsm state to wait PDE assist data cnf */

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PDE_ASSIST_DATA_CNF,
                                  TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PDE_ASSIST_DATA_CNF_TIMER_LEN);

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO);

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM_NI
 Description  : handler for CAS confirm message in MSA mode,
                after the Pilot phase measeurement is sent out

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_ENCODE_RL_INFO_STRU        stEncodeRlInfo;
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDataCnf;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM);

    pstDataCnf  = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU*)pstMsg;

    if (pstDataCnf->enRslt != CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS)
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterPPM_NI: CAS data CNF failed");
        TAF_XPDS_SendSessionEndAndQuitL2Fsm();
        TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_FAIL);
        return VOS_TRUE;
    }

    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    /* send GPS aquisition assistance request if PRM request has come
       else wait for request to come from PDE */
    if (VOS_TRUE == TAF_XPDS_GetReqPsuRangMeasFlag())
    {
        stEncodeRlInfo.ucNumOfReq    = 1;
        stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST;
        stEncodeRlInfo.ucNumOfResp   = 0;

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_CTRL_PLANE);

        (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSI,
                                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQU_ASSI_TIMER_LEN);

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSIS_NI);
    }
    else
    {
        (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM,
                                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM_TIMER_LEN);

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PRM_REQ_NI);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsaModeRecievePrmReq_NI
 Description  : handler for PRM request from PDE

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecievePrmReq_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU        *pstPdeDataInd = VOS_NULL_PTR;
    TAF_XPDS_ENCODE_RL_INFO_STRU                    stEncodeRlInfo;
    VOS_UINT32                                      ulPrmTimerLength;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_REQ_AFTER_PPM);

    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* if PRM request is there then send auisition assis request */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PSEURANGE_MEAS & pstPdeDataInd->ulDataMask) != VOS_FALSE)
    {
        stEncodeRlInfo.ucNumOfReq    = 1;
        stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST;
        stEncodeRlInfo.ucNumOfResp   = 0;

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_CTRL_PLANE);

        ulPrmTimerLength = TAF_XPDS_GetPrmTimerLimitLen();

        if (ulPrmTimerLength != 0)
        {
            TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY,
                                ulPrmTimerLength);
        }

        (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSI,
                                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQU_ASSI_TIMER_LEN);

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSIS_NI);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterAquiAssis_NI
 Description  : handler for CAS confirm message in MSA mode,
                after the Pilot phase measeurement is sent out

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterAquiAssis_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDataCnf;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_AQUI_ASSI);

    pstDataCnf  = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU*)pstMsg;

    if (pstDataCnf->enRslt != CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS)
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterAquiAssis_NI: CAS data CNF failed");
        TAF_XPDS_SendSessionEndAndQuitL2Fsm();
        TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_FAIL);
        return VOS_TRUE;
    }

    /* change fsm state to wait PDE assist data cnf */

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PDE_ASSIST_DATA_CNF,
                                  TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PDE_ASSIST_DATA_CNF_TIMER_LEN);

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO);

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsaModePPMComplete_NI
 Description  : all ppm recieved message handler

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModePPMComplete_NI(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SendPilotPhaseMeasurement();

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                                  TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM_TIMER_LEN);

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM_NI);

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_SendPilotPhaseMeasurement
 Description  : for sending PPM

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_SendPilotPhaseMeasurement(VOS_VOID)
{
    TAF_XPDS_ENCODE_RL_INFO_STRU        stEncodeRlInfo;

    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    TAF_XPDS_UpdatePpmInGlobal();

    /* send pilot phase measurement data */
    stEncodeRlInfo.ucNumOfReq    = 0;
    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 1;

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_CTRL_PLANE);

    TAF_XPDS_SetPpmTimerExpireFlag(VOS_FALSE);

    return;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterMsInfo
 Description  : handler for CAS confirm message in MSA mode,
                after the Pilot phase measeurement is sent out

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterMsInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDataCnf;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM);

    pstDataCnf  = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU*)pstMsg;

    if (pstDataCnf->enRslt != CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS)
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterMsInfo: CAS data CNF failed");
        TAF_XPDS_SendSessionEndAndQuitL2Fsm();
        TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_FAIL);
        return VOS_TRUE;
    }

    /* if PPM complete msg is not recieved */
    if (VOS_FALSE == TAF_XPDS_GetPpmTimerExpireFlag())
    {
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PPM_COMPLETE_NI);
    }
    else
    {
        TAF_XPDS_SendPilotPhaseMeasurement();

        (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM,
                                      TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_PPM_TIMER_LEN);

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_PPM_NI);

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeAssistInfo
 Description  : handler for PDE Assist info indication in Control plane .

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeAssistInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

     /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* �ж��Ƿ����Assist Info */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_ACQ_ASSIST & pstPdeDataInd->ulDataMask) != VOS_FALSE)
    {
        /* ����Assit Info */

        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF);

        /* before send acq assist to gps ,trace assist ctx first */
        TAF_XPDS_MNTN_TraceAssistDataCtxIndMsg();

        /* send assist data to gps, ��GPS��ȡα����Ϣ  */
        TAF_XPDS_SndAtGpsAcqAssistData();

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 Func Name    : TAF_XPDS_RcvAtGpsPrmInfoRsp_CpL2Pde_MsaWaitGpsPseudoInfo
 Description  : handler for PDE Assist info indication in Control plane .

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsPrmInfoRsp_CpL2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* TODO: ���͵�Ƶ��λ������Ϣ��α����Ϣ��PDE������ */
    AT_XPDS_MSG_STRU                                       *pstAtXpdsMsg;
    AT_XPDS_GPS_PRM_INFO_RSP_STRU                          *pstPrmInfo;
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    VOS_UINT8                                               ucLoopCount;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_PRM_COMPLETE_NI_QUALITY);

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    pstAtXpdsMsg  = (AT_XPDS_MSG_STRU*)pstMsg;

    pstPrmInfo = (AT_XPDS_GPS_PRM_INFO_RSP_STRU*)(pstAtXpdsMsg->aucContent);

    /* ��Ϣ��Ч */
    if (VOS_FALSE == pstPrmInfo->ucPrmValid)
    {
        return VOS_TRUE;
    }

    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    PS_MEM_SET(pstPseuMeas, 0, sizeof(TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU));

    pstPseuMeas->ucPartNum    = 0;
    pstPseuMeas->ucTotalparts = 0;

    if ((pstPrmInfo->ucMeasNum > 0)
     && (pstPrmInfo->ucMeasNum <= TAF_MSG_CDMA_MAX_SV_NUM))
    {
        pstPseuMeas->ucNumOfPS    = pstPrmInfo->ucMeasNum - 1;  /* Э��涨���͸�����ʱ��1 */
    }

    pstPseuMeas->ulTimeRef    = pstPrmInfo->ulMeasTow % 14400000; /* 4Сʱ��λ */
    pstPseuMeas->ucTimeRefSrc = 1;    /* 01 GPS time reference */

    /* ��ȫ�ֱ����л��ʹ�õ�ֵ */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

    for (ucLoopCount = 0; ucLoopCount < pstPrmInfo->ucMeasNum; ucLoopCount++)
    {
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucSvPRNNum      = pstPrmInfo->astMseasData[ucLoopCount].ucSvId;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucSvCNO         = pstPrmInfo->astMseasData[ucLoopCount].ucSvCn0;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].sPsDoppler      = pstPrmInfo->astMseasData[ucLoopCount].sPsDopp;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].usSvCodePhWh    = pstPrmInfo->astMseasData[ucLoopCount].usSvCodePhWhole;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].usSvCodePhFr    = pstPrmInfo->astMseasData[ucLoopCount].usSvCodePhFract;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucMulPathInd    = pstPrmInfo->astMseasData[ucLoopCount].ucMulpathInd;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucPsRangeRmsEr  = pstPrmInfo->astMseasData[ucLoopCount].ucPsRmsErr;
    }

    TAF_XPDS_UpdatePpmInGlobal();

    /* �ظ������������ */
    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
    stEncodeRlInfo.ucNumOfReq    = 1;

    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 2;

    /* Before send msg to PDE, hook current Pseu Range Ctx info */
    TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_CTRL_PLANE);

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP,
                                  TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP_TIMER_LEN);

    /* ״̬Ǩ�Ƶ�: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP);


    return VOS_TRUE;
}


/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterReqLocRsp
 Description  : handler for CAS confirm message in MSA mode,
                after the req location response is sent out

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterReqLocRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU        *pstDataCnf;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_CP_L2_PDE_MSA_WAIT_CAS_CNF_AFTER_REQ_LOC_RSP);

    pstDataCnf  = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU*)pstMsg;

    if (pstDataCnf->enRslt != CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS)
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsCpMsaModeRecieveCasCnf_AfterReqLocRsp: CAS data CNF failed");
        TAF_XPDS_SendSessionEndAndQuitL2Fsm();
        TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_FAIL);
        return VOS_TRUE;
    }

    /* change fsm state to wait PDE data ind */
    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF,
                                  TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);
    /* ״̬Ǩ�Ƶ�: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_CP_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_SendSessionEndAndQuitL2Fsm
 Description  : processing pde data end

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_SendSessionEndAndQuitL2Fsm(VOS_VOID)
{

    TAF_XPDS_SndCasPdeSessionEndMsg();

    TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader();

    TAF_XPDS_InitPdePublicDataPdeInit();

    TAF_XPDS_QuitFsmL2();
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeLocRespInfo
 Description  : The handling of loc resp from PDE for msa mode

  History       :
  1.Date        :   01-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_CpL2Pde_MsaWaitPdeLocRespInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;


    /* �ж��Ƿ����Assist Info */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP & pstPdeDataInd->ulDataMask) != VOS_NULL)
    {

        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF);

        /* before send locationg to gps , trace locationg ctx first */
        TAF_XPDS_MNTN_TraceLocationInfoCtxIndMsg();

        /* Get Location INfo From GPS, And need to send to GPS */
        TAF_XPDS_SndAtGpsPositionInfo();

        /* send internal result cnf msg to main FSM */
        TAF_XPDS_SndInternalCpPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_SendSessionEndAndQuitL2Fsm();

    }

    return VOS_TRUE;
}

/* added by A00903922 AGPS IT 2 31-08-2015 - end */

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */








