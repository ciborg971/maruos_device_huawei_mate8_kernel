/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcImsRegMsg.c
  Description     : ��C�ļ�ʵ��IMSע����Ϣ�����IMSע����Ϣ����
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaProcImsRegMsg.h"
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaImsInterface.h"
#include "UsimPsInterface.h"
#include "ImsaImsInterface.h"
#include "ImsaProcMsccMsg.h"
#include "ImsaImsAdaption.h"
#include "ImsaRegManagement.h"
/*lint -e767*/
#define    THIS_FILE_ID       PS_FILE_ID_IMSAPROCIMSREGMSG_C
#define    THIS_NAS_FILE_ID   NAS_FILE_ID_IMSAPROCIMSREGMSG_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/
extern VOS_UINT32 IMSA_RegProcImsMsgState(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU *pstOutputService);

/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_RegProcImsMsgAuth()
 Description    : IMS��Ȩ��Ϣ����
 Input          : CSM_OutputService* pstCsmOutputService
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-01  Draft Enact
      2.zhaochen 00308719  2015-02-09  Modify for USIM Interface change
*****************************************************************************/
VOS_VOID IMSA_RegProcImsMsgAuth(IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU* pstOutputService)
{
    VOS_UINT8                           ulOpId;
    USIMM_AUTH_DATA_UNION               uAuth;

    IMSA_MEM_SET(   &uAuth,
                    0,
                    sizeof(USIMM_AUTH_DATA_UNION));

    if(pstOutputService->bitOpAka == 0)
    {
        IMSA_WARN_LOG("IMSA_RegProcImsMsgAuth: AKA bit is empty!");
        TLPS_PRINT2LAYER_WARNING(IMSA_RegProcImsMsgAuth_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*����IMS��Ϣ��Ӧ��OPID*/
    /* ���IMS�ϱ����ǽ������͵ļ�Ȩ������OPID�����ڽ���ȫ�ֱ����� */
    ulOpId = IMSA_AllocUsimOpId();
    if (IMSA_TRUE == pstOutputService->ulIsEmergency)
    {
        IMSA_SaveRcvImsEmcOpid(pstOutputService->ulOpId);

        /* Ϊ��ֹopid��ת�󣬽�����OPID����ͨ��OPID��ͬ����˽�OPID�ĵڰ�λ����Ϊ1��������� */
        IMSA_SetUsimEmcOpid(ulOpId);
        ulOpId = IMSA_GetUsimEmcOpid();
    }
    else
    {
        IMSA_SaveRcvImsNormOpid(pstOutputService->ulOpId);
        IMSA_SetUsimNormOpid(ulOpId);
        ulOpId = IMSA_GetUsimNormOpid();
    }


    /* zhaochen 00308719 begin for USIM Interface modify 2015-02-07 */
    uAuth.stImsAuth.stAutn.ucDataLen = 16;
    //uAuth.stImsAuth.stAutn.aucData = (VOS_UINT8*)&pstOutputService->stAkaPara.ucAkaAutn[0];
    IMSA_MEM_CPY(   uAuth.stImsAuth.stAutn.aucData,
                    (VOS_UINT8*)&pstOutputService->stAkaPara.ucAkaAutn[0],
                    IMSA_IMS_AKA_AUTN_STRING_SZ);

    uAuth.stImsAuth.stRand.ucDataLen = 16;
    //uAuth.stImsAuth.stRand.aucData = (VOS_UINT8*)&pstOutputService->stAkaPara.ucAkaRand[0];
    IMSA_MEM_CPY(   uAuth.stImsAuth.stRand.aucData,
                    (VOS_UINT8*)&pstOutputService->stAkaPara.ucAkaRand[0],
                    IMSA_IMS_AKA_RAND_STRING_SZ);

    /*���ͼ�Ȩ��Ϣ*/
    IMSA_SndUsimAuthenticationReq(USIMM_IMS_APP, \
                                  USIMM_IMS_AUTH, \
                                  ulOpId, \
                                  &uAuth);
    /* zhaochen 00308719 end for USIM Interface modify 2015-02-07 */


}


/*****************************************************************************
 Function Name  : IMSA_ImsMsgServiceEvent()
 Description    : D2IMS�������͵��¼�������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-20  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsMsgServiceEvent(VOS_VOID *pSeriveEvent)
{
    IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU *pstOutSerive = VOS_NULL_PTR;

    pstOutSerive = (IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU*)pSeriveEvent;

    /* ע�������Ϣ���� */
    /*lint -e788*/
    switch (pstOutSerive->enOutputServiceReason)
    {
    case IMSA_IMS_OUTPUT_SEVICE_REASON_STATE:
        (VOS_VOID)IMSA_RegProcImsMsgState(pstOutSerive);
        break;

    case IMSA_IMS_OUTPUT_SEVICE_REASON_AUTH_CHALLENGE:
        IMSA_RegProcImsMsgAuth(pstOutSerive);
        break;

    case IMSA_IMS_OUTPUT_SEVICE_REASON_IPSEC_RELEASE:
        IMSA_INFO_LOG("IMSA_ImsMsgServiceEvent: IPSEC_RELEASE.");
        TLPS_PRINT2LAYER_INFO(IMSA_ImsMsgServiceEvent_ENUM, 3);
        break;

    case IMSA_IMS_OUTPUT_SEVICE_REASON_IPSEC_SETUP:
        IMSA_INFO_LOG("IMSA_ImsMsgServiceEvent: IPSEC_SETUP.");
        TLPS_PRINT2LAYER_INFO(IMSA_ImsMsgServiceEvent_ENUM, 4);
        break;

    case IMSA_IMS_OUTPUT_SEVICE_REASON_OK:
        IMSA_INFO_LOG("IMSA_ImsMsgServiceEvent: REASON_OK.");
        TLPS_PRINT2LAYER_INFO(IMSA_ImsMsgServiceEvent_ENUM, 5);
        break;


    default:
        IMSA_WARN_LOG("IMSA_ImsMsgServiceEvent: err sevice reason!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ImsMsgServiceEvent_ENUM, LNAS_MSG_INVALID);
        break;
    }/*lint +e788*/


}
VOS_VOID IMSA_ImsMsgSystemEvent(VOS_VOID *pSystemEvent)
{
    IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU       *pstOutSystem;

    pstOutSystem = (IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU*)pSystemEvent;

    if(IMSA_IMS_OUTPUT_SYSTM_REASON_OK == pstOutSystem->enOutputSysReason)
    {
        IMSA_ProcImsMsgStartOrStopCnf();
    }
    else
    {
        IMSA_ERR_LOG("IMSA_ImsMsgSystemEvent: err System reason!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ImsMsgSystemEvent_ENUM, LNAS_MSG_INVALID);
    }

}


VOS_VOID IMSA_ImsMsgParaEvent(VOS_VOID *pParaEvent)
{
    IMSA_IMS_OUTPUT_PARA_EVENT_STRU       *pstOutPara;
    IMSA_ENTITY_STRU                      *pstImsaEntity = IMSA_CtxGet();

    pstOutPara = (IMSA_IMS_OUTPUT_PARA_EVENT_STRU*)pParaEvent;

    IMSA_INFO_LOG2("IMSA_ImsMsgParaEvent: reason:,opid:", pstOutPara->enOutputParaReason,pstOutPara->ulOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_ImsMsgParaEvent_ENUM, 1, pstOutPara->enOutputParaReason);
    TLPS_PRINT2LAYER_INFO1(IMSA_ImsMsgParaEvent_ENUM, IMSA_NORMAL_OPID, pstOutPara->ulOpId);

    switch (pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmReason)
    {
        case IMAS_IMS_INPUT_PARA_REASON_QUERY_IMPU:

            if (pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmId == pstOutPara->ulOpId)
            {
                IMSA_ProcImsMsgQryVolteImpuCnf(pstOutPara);

                IMSA_ImsInputParaMsgClear();
            }
            break;

        case IMAS_IMS_INPUT_PARA_REASON_SET_CALL_WAITING:

            if (pstImsaEntity->stImsaControlManager.stImsMsg.ulCsmId == pstOutPara->ulOpId)
            {
                IMSA_ProcImsMsgCcwaiSetCnf(pstOutPara);

                IMSA_ImsInputParaMsgClear();
            }
            break;

        default:
            break;
    }

}


VOS_VOID IMSA_ImsMsgNvInfoEvent(VOS_VOID *pParaEvent)
{
    IMSA_IMS_OUTPUT_NV_INFO_EVENT_STRU       *pstOutNvInfo;

    pstOutNvInfo = (IMSA_IMS_OUTPUT_NV_INFO_EVENT_STRU*)pParaEvent;

    IMSA_INFO_LOG2("IMSA_ImsMsgNvInfoEvent: reason:,opid:", pstOutNvInfo->enOutputNvInfoReason, pstOutNvInfo->ulOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_ImsMsgNvInfoEvent_ENUM, 1, pstOutNvInfo->enOutputNvInfoReason);
    TLPS_PRINT2LAYER_INFO1(IMSA_ImsMsgNvInfoEvent_ENUM, IMSA_NORMAL_OPID, pstOutNvInfo->ulOpId);

}

/*lint +e961*/
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcImsRegMsg.c */










