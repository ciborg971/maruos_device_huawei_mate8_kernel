/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaRegManagement.c
  Description     : ��C�ļ�ʵ��ע�����ģ��ĳ�ʼ�����ڲ���Ϣ�Ĵ���ͷ���
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaEntity.h"
#include "ImsaRegManagement.h"
#include "ImsaPublic.h"
#include "ImsaImsAdaption.h"
#include "ImsaImsInterface.h"
#include "math.h"
/*lint -e767*/
#define    THIS_FILE_ID             PS_FILE_ID_IMSAREGMANAGEMENT_C
#define    THIS_NAS_FILE_ID         NAS_FILE_ID_IMSAREGMANAGEMENT_C
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

VOS_UINT32 IMSA_RegFsmProcIdleReqReq(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);

VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegSuccess(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
VOS_UINT32 IMSA_RegFsmProcRegisteringProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
VOS_UINT32 IMSA_RegFsmProcRegisteringUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_UINT32 IMSA_RegFsmProcRegisteredImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcRegisteredUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
/* zhaochen 00308719 begin for IMS Dereg for too long 2015-09-14 */
VOS_UINT32 IMSA_RegFsmProcDeregingUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
/* zhaochen 00308719 end for IMS Dereg for too long 2015-09-14 */

VOS_UINT32 IMSA_RegFsmProcDeregingImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcDeregingProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcDeregingUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_UINT32 IMSA_RegFsmProcWaitRetryTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcWaitRetryUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_UINT32 IMSA_RegFsmProcPendingProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcPendingUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcPendingUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcPendingImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
/*
VOS_UINT32 IMSA_RegFsmProcPendingImsRegSuccess(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
*/
VOS_UINT32 IMSA_RegFsmProcRollingBackProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcRollingBackImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcRollingBackUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_UINT32 IMSA_RegFsmProcRollingBackUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);

VOS_UINT32 IMSA_RegFsmProcPeriodTryRegTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);
VOS_VOID IMSA_RegResetPeriodTryImsRegTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);

IMSA_FSM_PROC IMSA_FsmGetProcItem(VOS_UINT32 ulState, VOS_UINT32 ulEvt);
VOS_UINT32 IMSA_FsmRun(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
VOS_VOID IMSA_RegResetRetryTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);
VOS_VOID IMSA_RegConverterReg2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    const VOS_CHAR *pucIpAddr,
    const VOS_CHAR *pacPcscfAddr,
    IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvt
);
VOS_VOID IMSA_RegConfigIpAddress2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    const VOS_CHAR                     *pcUeAddr,
    const VOS_CHAR                     *pacPcscfAddr
);
VOS_VOID IMSA_RegSendImsMsgDereg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    VOS_UINT32                          ulIsLocal
);
VOS_UINT32 IMSA_RegSendImsMsgReg
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    const VOS_CHAR *pcUeAddr,
    const VOS_CHAR *pcPcscfAddr
);
VOS_UINT32 IMSA_RegSendIntraMsgRegInd
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_RESULT_ENUM_UINT32 enResult,
    IMSA_RESULT_ACTION_ENUM_UINT32 enAction
);
VOS_UINT32 IMSA_RegSendIntraMsgDeregInd
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_RESULT_ENUM_UINT32 enResult,
    IMSA_RESULT_ACTION_ENUM_UINT32 enAction
);
VOS_UINT32 IMSA_RegGetAddrByParamType
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32 enParamType,
    VOS_CHAR *pucUeAddr,
    VOS_CHAR *pucPcscfAddr
);
VOS_UINT32 IMSA_RegParseImsError
(
    const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService,
    IMSA_IMS_OUTPUT_ERROR_STRU          *pstImsErrorInfo
);
VOS_UINT32 IMSA_RegCalculateRetryDelayTime
(
    VOS_UINT32                          ulMaxTime,
    VOS_UINT32                          ulBaseTime,
    VOS_UINT32                          ulConsecutiveFailures
);
VOS_UINT32 IMSA_RegCalculateRegFailureRetryIntervelTime
(
    VOS_UINT32                          ulRetryTimes,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration
);
VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailure305
(
    IMSA_REG_ENTITY_STRU               *pstEntity
);
VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut
(
    IMSA_REG_ENTITY_STRU               *pstEntity
);

VOS_VOID IMSA_RegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration,
    VOS_UINT16                          usSipStatusCode
);
VOS_UINT32 IMSA_RegProcImsMsgState(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService);
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairCreate
(
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacUeAddr,
    const VOS_CHAR *pacPcscfAddr
);
VOS_VOID IMSA_RegAddrPairDestroy(IMSA_REG_ADDR_PAIR_STRU *pstAddrPair);
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListAdd
(
    IMSA_REG_ADDR_PAIR_STRU **ppstListHead,
    IMSA_REG_ADDR_PAIR_STRU *pstNode
);
VOS_VOID IMSA_RegAddrPairListDestroy(IMSA_REG_ADDR_PAIR_STRU *pstListHead);
VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr
(
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacPcscfAddr
);
VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewUeAddr
(
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacUeAddr
);
VOS_VOID IMSA_RegGetAddrPairListHead
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    IMSA_REG_ADDR_PAIR_STRU          ***pppstListHead
);
VOS_VOID IMSA_RegAddrPairListClearAllUsedFlag(IMSA_REG_ADDR_PAIR_STRU *pstList);


/**
 *  ע��ģ��״̬����
 *
 */
IMSA_REG_FSM_ITEM_STRU g_stImsaRegFsmTable[] =
{
    {IMSA_REG_STATUS_NOT_REGISTER, IMSA_REG_EVT_USER_REG_REQ,     IMSA_RegFsmProcIdleReqReq},

    {IMSA_REG_STATUS_REGISTERING,  IMSA_REG_EVT_IMS_REG_SUCCESS,  IMSA_RegFsmProcRegisteringImsRegSuccess},
    {IMSA_REG_STATUS_REGISTERING,  IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcRegisteringImsRegFailure},
    {IMSA_REG_STATUS_REGISTERING,  IMSA_REG_EVT_TIMEOUT_PROTECT,  IMSA_RegFsmProcRegisteringProtectTimeout},
    {IMSA_REG_STATUS_REGISTERING,  IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcRegisteringUserDereg},

    {IMSA_REG_STATUS_REGISTERED,   IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcRegisteredImsRegFailure},
    {IMSA_REG_STATUS_REGISTERED,   IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcRegisteredUserDereg},

    {IMSA_REG_STATUS_DEREGING,     IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcDeregingImsRegFailure},
    {IMSA_REG_STATUS_DEREGING,     IMSA_REG_EVT_TIMEOUT_PROTECT,  IMSA_RegFsmProcDeregingProtectTimeout},
    {IMSA_REG_STATUS_DEREGING,     IMSA_REG_EVT_USER_REG_REQ,     IMSA_RegFsmProcDeregingUserReg},
    /* zhaochen 00308719 begin for IMS Dereg for too long 2015-09-14 */
    {IMSA_REG_STATUS_DEREGING,     IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcDeregingUserDereg},
    /* zhaochen 00308719 end for IMS Dereg for too long 2015-09-14 */

    {IMSA_REG_STATUS_WAIT_RETRY,   IMSA_REG_EVT_TIMEOUT_RETRY,    IMSA_RegFsmProcWaitRetryTimeout},
    {IMSA_REG_STATUS_WAIT_RETRY,   IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcWaitRetryUserDereg},

    {IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_TIMEOUT_PROTECT,  IMSA_RegFsmProcPendingProtectTimeout},
    {IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_USER_REG_REQ,     IMSA_RegFsmProcPendingUserReg},
    {IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcPendingUserDereg},
    {IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcPendingImsRegFailure},
    /*{IMSA_REG_STATUS_PENDING,      IMSA_REG_EVT_IMS_REG_SUCCESS,  IMSA_RegFsmProcPendingImsRegSuccess},*/

    {IMSA_REG_STATUS_ROLLING_BACK, IMSA_REG_EVT_TIMEOUT_PROTECT,  IMSA_RegFsmProcRollingBackProtectTimeout},
    {IMSA_REG_STATUS_ROLLING_BACK, IMSA_REG_EVT_IMS_REG_FAILURE,  IMSA_RegFsmProcRollingBackImsRegFailure},
    {IMSA_REG_STATUS_ROLLING_BACK, IMSA_REG_EVT_USER_REG_REQ,     IMSA_RegFsmProcRollingBackUserReg},
    {IMSA_REG_STATUS_ROLLING_BACK, IMSA_REG_EVT_USER_DEREG_REQ,   IMSA_RegFsmProcRollingBackUserDereg},

    {IMSA_REG_STATUS_WAIT_PERIOD_TRY, IMSA_REG_EVT_TIMEOUT_PERIOD_TRY, IMSA_RegFsmProcPeriodTryRegTimeout},
};


VOS_VOID IMSA_RegAddrPairMgrInit(IMSA_REG_ADDR_PAIR_MGR_STRU *pstPairMgr);
VOS_VOID IMSA_RegAddrPairMgrDeinit(const IMSA_REG_ADDR_PAIR_MGR_STRU *pstPairMgr);
VOS_UINT32 IMSA_RegAddrPairMgrGetNextUnused(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                            VOS_CHAR *pacUeIp,
                                            VOS_CHAR *pacPcscfIp);
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListGetNextUnused(IMSA_REG_ADDR_PAIR_STRU *pstList);
IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairMgrGetFirst(IMSA_REG_TYPE_ENUM_UINT8 ulRegType);

VOS_VOID IMSA_RegAddrPairMgrClearAllUsedFlag(IMSA_REG_TYPE_ENUM_UINT8 enRegType);


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e961*/

IMSA_FSM_PROC IMSA_FsmGetProcItem(VOS_UINT32 ulState, VOS_UINT32 ulEvt)
{
    VOS_UINT32 i = 0;

    for (i = 0; i < (sizeof(g_stImsaRegFsmTable)/sizeof(IMSA_REG_FSM_ITEM_STRU)); i++)
    {
        if ((g_stImsaRegFsmTable[i].ulState == ulState) &&
            (g_stImsaRegFsmTable[i].ulEvent == ulEvt))
        {
            return g_stImsaRegFsmTable[i].ProcFun;
        }
    }

    IMSA_INFO_LOG2("IMSA_FsmGetProcItem: not found fsm procedure", ulState, ulEvt);
    TLPS_PRINT2LAYER_INFO2(IMSA_FsmGetProcItem_ENUM, LNAS_PARAM_INVALID, ulState, ulEvt);

    return VOS_NULL_PTR;
}


VOS_UINT32 IMSA_FsmRun(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData)
{
    IMSA_FSM_PROC FsmProcFun;

    IMSA_INFO_LOG2("IMSA_FsmRun:", pstEntity->enStatus, ulEvt);
    TLPS_PRINT2LAYER_INFO2(IMSA_FsmRun_ENUM, 1, pstEntity->enStatus, ulEvt);

    FsmProcFun = IMSA_FsmGetProcItem(pstEntity->enStatus, ulEvt);
    if (VOS_NULL_PTR != FsmProcFun)
    {
        return FsmProcFun(pstEntity, ulEvt, pData);
    }

    IMSA_ERR_LOG("IMSA_FsmRun: Not registered state and event");
    TLPS_PRINT2LAYER_ERROR(IMSA_FsmRun_ENUM, LNAS_PARAM_INVALID);

    return VOS_FALSE;
}


VOS_VOID IMSA_RegResetPeriodTryImsRegTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity = VOS_NULL_PTR;

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        pstRegEntity = IMSA_RegEntityGetByType(enRegType);

        pstRegEntity->ucTryRegTimes = 0;
    }
}



VOS_VOID IMSA_RegResetRetryTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity = VOS_NULL_PTR;

    pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    pstRegEntity->ulRetryTimes = 0;
}


VOS_VOID IMSA_RegConverterReg2Ims(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                    const VOS_CHAR *pucIpAddr,
                                    const VOS_CHAR *pacPcscfAddr,
                                    IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvt)
{
    IMSA_INFO_LOG("IMSA_RegConverterReg2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegConverterReg2Ims_ENUM, LNAS_ENTRY);

    /* ���������¼����� */
    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    /* ��������Reason��opid */
    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_IP;

        /* ����IP��ַ */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalIp.acUeAddress, pucIpAddr, IMSA_IMS_IP_ADDRESS_STRING_SZ);

        /* ����PCSCF��ַ */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalIp.acPcscf, pacPcscfAddr, IMSA_IMS_EVENT_STRING_SZ);
    }
    else
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_EMC_IP;

        /* ����IP��ַ */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcIp.acUeAddress, pucIpAddr, IMSA_IMS_IP_ADDRESS_STRING_SZ);

        /* ����PCSCF��ַ */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcIp.acPcscf, pacPcscfAddr, IMSA_IMS_EVENT_STRING_SZ);
    }

}



VOS_VOID IMSA_RegConfigIpAddress2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    const VOS_CHAR                     *pcUeAddr,
    const VOS_CHAR                     *pacPcscfAddr
)
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegConfigIpAddress2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegConfigIpAddress2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_RegConfigIpAddress2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegConfigIpAddress2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_RegConverterReg2Ims(enRegType, pcUeAddr, pacPcscfAddr, pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}




VOS_VOID IMSA_RegSendImsMsgDereg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    VOS_UINT32                          ulIsLocal
)
{

    /*IMSA_DeregConfigIpAddress2Ims(enRegType,"");*/

    if (VOS_TRUE == ulIsLocal)
    {
        if (IMSA_REG_TYPE_NORMAL == enRegType)
        {
            IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER);
        }
        else
        {
            IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER_EMERGENCY);
        }

    }
    else
    {
        IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_DEREGISTER);
    }


}
VOS_VOID IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32   enInputServeReason)
{
    IMSA_IMS_INPUT_EVENT_STRU   *pstHiInputEvent;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstHiInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstHiInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndD2MsgServiceRegInfo:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndD2MsgServiceRegInfo_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstHiInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstHiInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SERVICE;

    pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = enInputServeReason;

    pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgServiceEvent(pstHiInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstHiInputEvent);

}




VOS_UINT32 IMSA_RegSendImsMsgReg(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                 const VOS_CHAR *pcUeAddr,
                                 const VOS_CHAR *pcPcscfAddr)
{
    IMSA_INFO_LOG("IMSA_RegSendImsMsgReg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSendImsMsgReg_ENUM, LNAS_ENTRY);

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        /* set UE IP address to trigger register */
        IMSA_RegConfigIpAddress2Ims(enRegType, pcUeAddr, pcPcscfAddr);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����begin notify��Ϣ��RRC��֪ͨRRC������Դ*/
        IMSA_SendRrcDsdsBeginNotify(IMSA_LRRC_SESSION_TYPE_REGISTER);
        #endif

        IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_REGISTER);
    }
    else if (IMSA_REG_TYPE_EMC == enRegType)
    {
        /* set UE IP address to trigger register */
        IMSA_RegConfigIpAddress2Ims(enRegType, pcUeAddr, pcPcscfAddr);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����begin notify��Ϣ��RRC��֪ͨRRC������Դ*/
        IMSA_SendRrcDsdsBeginNotify(IMSA_LRRC_SESSION_TYPE_REGISTER);
        #endif

        IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_REGISTER_EMERGENCY);
    }
    else
    {
    }

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegSendIntraMsgRegInd(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                      IMSA_REG_RESULT_ENUM_UINT32 enResult,
                                      IMSA_RESULT_ACTION_ENUM_UINT32 enAction)
{
    IMSA_REG_REG_IND_STRU stRegInd = {0};

    IMSA_INFO_LOG("IMSA_RegSendIntraMsgRegInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSendIntraMsgRegInd_ENUM, LNAS_ENTRY);

    stRegInd.enRegType      = enRegType;
    stRegInd.enResult       = enResult;
    stRegInd.enResultAction = enAction;
    /**
     * ��ʱ���ϱ�SIP Server���صĲ�����Ϣ��
     * ���ϲ��û�������ʱ�����
     */

    return IMSA_RegSendIntraMsg(ID_IMSA_REG_REG_IND, (VOS_UINT8*)&stRegInd, sizeof(IMSA_REG_REG_IND_STRU));
}


VOS_UINT32 IMSA_RegSendIntraMsgDeregInd(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                        IMSA_REG_RESULT_ENUM_UINT32 enResult,
                                        IMSA_RESULT_ACTION_ENUM_UINT32 enAction)
{
    IMSA_REG_DEREG_IND_STRU stDeregInd = {0};

    IMSA_INFO_LOG("IMSA_RegSendIntraMsgDeregInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSendIntraMsgDeregInd_ENUM, LNAS_ENTRY);

    stDeregInd.enRegType      = enRegType;
    stDeregInd.enResult       = enResult;
    stDeregInd.enResultAction = enAction;
    /**
     * ��ʱ���ϱ�SIP Server���صĲ�����Ϣ��
     * ���ϲ��û�������ʱ�����
     */

    return IMSA_RegSendIntraMsg(ID_IMSA_REG_DEREG_IND, (VOS_UINT8*)&stDeregInd, sizeof(IMSA_REG_DEREG_IND_STRU));
}


VOS_UINT32 IMSA_RegSendIntraMsg(VOS_UINT32 ulMsgId, const VOS_UINT8 *pucMsg, VOS_UINT32 ulLen)
{
    /* ������Ϣ�ṹͷ���ֵĶ��� */
    IMSA_REG_REG_IND_STRU *pstIntraMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegSendIntraMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSendIntraMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstIntraMsg = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(ulLen);
    if (VOS_NULL_PTR == pstIntraMsg)
    {
        IMSA_ERR_LOG("IMSA_RegSendIntraMsg: alloc fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegSendIntraMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* �����ض���Ϣ������ */
    IMSA_MEM_CPY(pstIntraMsg, pucMsg, ulLen);

    /* ��д��Ϣͷ */
    IMSA_WRITE_INTRA_MSG_HEAD(pstIntraMsg, ulMsgId, ulLen);

    /* ������Ϣ */
    IMSA_SEND_INTRA_MSG((VOS_VOID*)pstIntraMsg);

    return VOS_TRUE;
}

VOS_UINT32 IMSA_RegGetAddrByParamType(IMSA_REG_TYPE_ENUM_UINT8 enRegType,
                                      IMSA_REG_ADDR_PARAM_ENUM_UINT32 enParamType,
                                      VOS_CHAR *pucUeAddr,
                                      VOS_CHAR *pucPcscfAddr)
{
    VOS_UINT32 ulResult = VOS_TRUE;
    IMSA_REG_ADDR_PAIR_STRU *pstAddrPair = VOS_NULL_PTR;
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    #endif

    IMSA_INFO_LOG1("IMSA_RegGetAddrByParamType is entered!", enParamType);
    TLPS_PRINT2LAYER_INFO1(IMSA_RegGetAddrByParamType_ENUM, LNAS_ENTRY, enParamType);

    #if (FEATURE_ON == FEATURE_PTM)
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        pstControlMagnaer->enNrmAddrType = enParamType;
    }
    else
    {
        pstControlMagnaer->enEmcAddrType = enParamType;
    }
    #endif

    switch (enParamType)
    {
    case IMSA_REG_ADDR_PARAM_NEW:
        IMSA_RegAddrPairMgrClearAllUsedFlag(enRegType);

        IMSA_RegResetRetryTimes(enRegType);

        pstAddrPair = IMSA_RegAddrPairMgrGetFirst(enRegType);
        if (VOS_NULL_PTR != pstAddrPair)
        {
            IMSA_UtilStrNCpy(pucUeAddr, pstAddrPair->acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
            IMSA_UtilStrNCpy(pucPcscfAddr, pstAddrPair->acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);

            IMSA_INFO_LOG(pucUeAddr);
            IMSA_INFO_LOG(pucPcscfAddr);
        }
        else
        {
            ulResult = VOS_FALSE;
        }
        break;
    case IMSA_REG_ADDR_PARAM_NEXT:
        IMSA_RegResetRetryTimes(enRegType);

        ulResult = IMSA_RegAddrPairMgrGetNextUnused(enRegType, pucUeAddr, pucPcscfAddr);
        break;
    case IMSA_REG_ADDR_PARAM_SAME:
        ulResult = IMSA_RegAddrPairMgrGetCurrent(enRegType, pucUeAddr, pucPcscfAddr);
        break;
    case IMSA_REG_ADDR_PARAM_RESTORATION:
        IMSA_RegResetRetryTimes(enRegType);

        if ((VOS_FALSE == IMSA_RegAddrPairMgrGetNextUnused(enRegType, pucUeAddr, pucPcscfAddr)) &&
            (VOS_FALSE == IMSA_RegAddrPairMgrGetCurrent(enRegType, pucUeAddr, pucPcscfAddr)))
        {
            ulResult = VOS_FALSE;
        }
        break;
    default:
        ulResult = VOS_FALSE;
        IMSA_ERR_LOG1("IMSA_RegGetAddrByParamType: invalid param type", enParamType);
        TLPS_PRINT2LAYER_ERROR1(IMSA_RegGetAddrByParamType_ENUM, LNAS_PARAM_INVALID, enParamType);
    }

    return ulResult;
}
VOS_UINT32 IMSA_RegFsmProcIdleReqReq(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    VOS_UINT32 ulResult = VOS_FALSE;
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    IMSA_REG_REG_REQ_STRU *pstRegReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcIdleReqReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcIdleReqReq_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    /* �����ǰ�������Ͳ�֧��IMS�����ٷ���ע�� */
    if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
    {
        if (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
        }
        else
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_NULL);
        }
        return VOS_FALSE;
    }

    pstRegReq = (IMSA_REG_REG_REQ_STRU *)pData;

    /* ����ע�����������ȡһ����ַ�ԣ����ʧ����ظ��û�ע��ʧ�� */
    if (VOS_FALSE == IMSA_RegGetAddrByParamType(pstEntity->enRegType, pstRegReq->enAddrType, aucUeAddr, aucPcscfAddr))
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_NO_ADDR_PAIR, IMSA_RESULT_ACTION_NULL);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_RegErrRecord(pstEntity->enRegType, IMSA_ERR_LOG_REG_FAIL_REASON_NO_ADDR_PAIR);
        IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                 IMSA_ERR_LOG_REG_FAIL_REASON_NO_ADDR_PAIR,
                                 VOS_FALSE,
                                 VOS_FALSE,
                                 IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NO_REG_ADDR_PAIR);
        #endif
        return VOS_FALSE;
    }

    IMSA_CONN_UpdateNicPdpInfo();

    /* ����ע���������D2 IMS Stack��ʼ����ע�� */
    ulResult = IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);
    if (VOS_FALSE == ulResult)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL, IMSA_RESULT_ACTION_NULL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_RegErrRecord(pstEntity->enRegType, IMSA_ERR_LOG_REG_FAIL_REASON_TRANSPORT);
        #endif
        return VOS_FALSE;
    }

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);

    return VOS_TRUE;
}
VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegSuccess(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegSuccess is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegSuccess_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* ֹͣ������ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_REGISTER);
    #endif

    /* ֪ͨ�û�ע��ɹ� */
    (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERED);

    /* ��0���Դ��� */
    IMSA_RegResetRetryTimes(pstEntity->enRegType);

    /* ��0���ڳ���IMSע����� */
    IMSA_RegResetPeriodTryImsRegTimes(pstEntity->enRegType);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegParseImsError
(
    const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService,
    IMSA_IMS_OUTPUT_ERROR_STRU          *pstImsErrorInfo
)
{
    if (VOS_TRUE == pstOutputService->bitOpErrorCode)
    {
        IMSA_MEM_CPY(   pstImsErrorInfo,
                        &pstOutputService->stErrorCode,
                        sizeof(IMSA_IMS_OUTPUT_ERROR_STRU));

        return IMSA_SUCC;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_RegParseImsError: HICSM_parseServiceError failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_RegParseImsError_ENUM, LNAS_FAIL);
        return IMSA_FAIL;
    }
}


VOS_UINT32 IMSA_RegCalculateRetryDelayTime
(
    VOS_UINT32                          ulMaxTime,
    VOS_UINT32                          ulBaseTime,
    VOS_UINT32                          ulConsecutiveFailures
)
{
    VOS_UINT32                          W                   = IMSA_NULL;
    VOS_UINT32                          ulTmp               = IMSA_NULL;
    VOS_UINT32                          ulRetryDelayTime    = IMSA_NULL;

    /*  RFC 5626�涨�ļ��ʱ����㹫ʽ���£�
    W = min (max-time, (base-time * (2 ^ consecutive-failures)))
    retry delay time = rand * W
    rand�Ǹ����ֵ��ȡֵ��Χ��50%~100%*/
    ulTmp = ulBaseTime * (VOS_UINT32)pow(2.0, (double)ulConsecutiveFailures);

    if (ulMaxTime >= ulTmp)
    {
        W = ulTmp;
    }
    else
    {
        W = ulMaxTime;
    }

    ulRetryDelayTime = (VOS_UINT32)(((VOS_Rand(51) + 50) / 100.0) * W);

    return ulRetryDelayTime;
}



VOS_UINT32 IMSA_RegCalculateRegFailureRetryIntervelTime
(
    VOS_UINT32                          ulRetryTimes,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration
)
{
    IMSA_REG_MANAGER_STRU              *pstImsaRegManager   = IMSA_RegCtxGet();
    VOS_UINT32                          ulRetryDelayTime    = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_RegCalculateRegFailureRetryIntervelTime is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegCalculateRegFailureRetryIntervelTime_ENUM, LNAS_ENTRY);

    /* ���NV�����ü���̶�ʱ�����򷵻�NV�����õĹ̶�ʱ���� */
    if (pstImsaRegManager->ulRetryPeriod != 0)
    {
        if (ulRetryAfter == 0)
        {
            return (1000 * pstImsaRegManager->ulRetryPeriod);
        }
        else
        {
            return (1000 * ulRetryAfter);
        }
    }

    /* ���NV�����ü���ǹ̶�ʱ��������24.229 5.1.1.2.1�½��Լ�RFC5626
       ������ע��ʧ�����³��Լ��ʱ�䣬������Բμ�IMS�����ĵ�2.3.9�½� */
    ulRetryDelayTime = IMSA_RegCalculateRetryDelayTime( pstImsaRegManager->ulMaxTime,
                                                        pstImsaRegManager->ulBaseTime,
                                                        ulRetryTimes);

    /* ����ǵ�һ�γ�ʼע�ᣬ�Ҳ�Я��retry after����ȡֵ5���Ӻ�retry delay time
       ����Сֵ��Э������:
       After a first unsuccessful initial registration attempt,  if the Retry-After
       header field was not present and the initial registration was not performed
       as a consequence of a failed reregistration, the UE shall not wait more
       than 5 minutes before attempting a new registration.*/
    if ((1 == ulRetryTimes) && (IMSA_FALSE == ulIsReRegisteration)
       && (0 == ulRetryAfter))
    {
        return 1000 * IMSA_Min(IMSA_REG_FAILURE_RETRY_INTERVEL_5_MIN, ulRetryDelayTime);
    }

    if (0 != ulRetryAfter)
    {
        return 1000 * IMSA_Max(ulRetryAfter, ulRetryDelayTime);
    }
    else
    {
        return (1000 * ulRetryDelayTime);
    }
}


VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut
(
    IMSA_REG_ENTITY_STRU               *pstEntity
)
{
    VOS_UINT32                          ulResult                                = VOS_FALSE;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1]    = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut is entered!");

    /* ֹͣ������ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* ��ȡ��һ��ע���ַ�ԣ����ʧ����ظ��û�ע��ʧ�� */
    if (VOS_FALSE == IMSA_RegGetAddrByParamType(    pstEntity->enRegType,
                                                    IMSA_REG_ADDR_PARAM_NEXT,
                                                    aucUeAddr,
                                                    aucPcscfAddr))
    {
        if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
        {
            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);

            return;
        }

        /*��ͨע�ᣬ�ҳ��Դ���δ���������������������ڳ�ʱ�ڶ�ʱ��*/
        if (pstEntity->ucTryRegTimes < IMSA_PRIOD_TRY_REG_MAX_TIMES)
        {
            IMSA_RegTimerStart(&pstEntity->stPeriodTryRegTimer, pstEntity->enRegType);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_WAIT_PERIOD_TRY);

            pstEntity->ucTryRegTimes++;
        }
        else
        {
            pstEntity->ucTryRegTimes = 0;

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);
        }

        return;
    }

    IMSA_CONN_UpdateNicPdpInfo();

    /* ����ע���������IMS Stack��ʼ����ע�� */
    ulResult = IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);
    if (VOS_FALSE == ulResult)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);
        return;
    }

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);

    return;
}
VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailure305
(
    IMSA_REG_ENTITY_STRU               *pstEntity
)
{
    VOS_UINT32                          ulResult                                = VOS_FALSE;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1]    = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure305 is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure305_ENUM, LNAS_ENTRY);

    /* ֹͣ������ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    /* ��ȡ��һ��ע���ַ�ԣ����ʧ����ظ��û�ע��ʧ�� */
    if (VOS_FALSE == IMSA_RegGetAddrByParamType(    pstEntity->enRegType,
                                                    IMSA_REG_ADDR_PARAM_NEXT,
                                                    aucUeAddr,
                                                    aucPcscfAddr))
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);

        return ;
    }

    IMSA_CONN_UpdateNicPdpInfo();

    /* ����ע���������IMS Stack��ʼ����ע�� */
    ulResult = IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);
    if (VOS_FALSE == ulResult)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL_REMOTE,
                                                IMSA_RESULT_ACTION_NULL);
        return ;
    }

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
}




VOS_VOID IMSA_RegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration,
    VOS_UINT16                          usSipStatusCode
)
{
    VOS_UINT32                          ulRetryTimerLen = IMSA_NULL;

    /* ֹͣ������ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* ����ע��ʧ���ٳ��Լ��ʱ�� */
    ulRetryTimerLen = IMSA_RegCalculateRegFailureRetryIntervelTime( pstEntity->ulRetryTimes,
                                                                    ulRetryAfter,
                                                                    ulIsReRegisteration);
    if (VOS_FALSE == ulIsReRegisteration)
    {
        if (0 != ulRetryTimerLen)
        {
            /* ����retry��ʱ�� */
            pstEntity->stRetryTimer.ulTimerLen = ulRetryTimerLen;
            IMSA_RegTimerStart(&pstEntity->stRetryTimer, pstEntity->enRegType);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_WAIT_RETRY);

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                        usSipStatusCode,
                                        ulRetryTimerLen);
            #endif
        }
        else
        {
            /* ����305�������󣬻��޸�ע���ַ�����ͣ�������Ҫ���ϱ�CHR */
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                        usSipStatusCode,
                                        ulRetryTimerLen);
            #endif
            IMSA_RegFsmProcRegisteringImsRegFailure305(pstEntity);
        }
    }
    else
    {
        if (0 != ulRetryTimerLen)
        {
            /* ����retry��ʱ�� */
            pstEntity->stRetryTimer.ulTimerLen = ulRetryTimerLen;
            IMSA_RegTimerStart(&pstEntity->stRetryTimer, pstEntity->enRegType);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_WAIT_RETRY);

            /* ֪ͨSERVICEʹ�õ�ǰ������������ע�� */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                 IMSA_REG_RESULT_FAIL,
                                                 IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR);
        }
        else
        {
            /* ֪ͨSERVICEʹ����һ�������������ע�� */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                 IMSA_REG_RESULT_FAIL,
                                                 IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);
        }
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                    usSipStatusCode,
                                    ulRetryTimerLen);
        #endif

    }
}
VOS_UINT32 IMSA_RegFsmProcRegisteringImsRegFailure
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulEvt,
    VOS_VOID                           *pData
)
{
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo = VOS_NULL_PTR;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_REG_MANAGER_STRU              *pstImsaRegManager   = IMSA_RegCtxGet();

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;


    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_RegErrRecord(pstEntity->enRegType, IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE);
    #endif

    /* ���Դ�����1 */
    pstEntity->ulRetryTimes++;

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_REGISTER);
    #endif

    /* ĿǰG/W��֧��IMS��IMSA���ٻ�ȡ��һ����ַ����ע�� */
    if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
    {
        IMSA_RegTimerStop(&pstEntity->stProtectTimer);

        /* ״̬�л� */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

        if (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL_REMOTE,
                                                    IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
        }
        else
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL_REMOTE,
                                                    IMSA_RESULT_ACTION_NULL);
        }

        /* ����÷�֧��״̬ʱ����G/W��PS��ûע��ɹ�������IMS�Ѿ�ע��ʧ�ܣ� */
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                 IMSA_ERR_LOG_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT,
                                 VOS_FALSE,
                                 VOS_FALSE,
                                 IMSA_ERR_LOG_EMC_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT);
        #endif
        return VOS_TRUE;
    }

    if (VOS_NULL_PTR == pData)
    {
        IMSA_RegFsmProcRegisteringImsRegFailure305(pstEntity);

        return VOS_TRUE;
    }

    pstImsErrorInfo = (IMSA_IMS_OUTPUT_ERROR_STRU*)pData;

    switch (pstImsErrorInfo->usSipStatusCode)
    {
        case IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT:
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                     IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                     pstImsErrorInfo->usSipStatusCode,
                                     VOS_FALSE,
                                     IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
            #endif
            IMSA_RegFsmProcRegisteringImsRegFailureTimerfOut(pstEntity);
            break;
        case IMSA_SIP_NW_ERROR_CAUSE_USE_PROXY:
        /* case IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT: */
        case IMSA_SIP_NW_ERROR_CAUSE_UNAUTHORIZED:
        case IMSA_IMS_INT_ERROR_CODE_REGISTER_TIMER_OUT:
            /* ��ΪҪ��ȡ����ע��ʧ�ܵĵ�ַ�����ͣ�������Ҫ�ٷ�����һ��ע��ǰ�����ϱ�CHR */
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                     IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                     pstImsErrorInfo->usSipStatusCode,
                                     VOS_FALSE,
                                     IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
            #endif
            IMSA_RegFsmProcRegisteringImsRegFailure305(pstEntity);
            break;
        case IMSA_SIP_NW_ERROR_CAUSE_REQUEST_TIMEOUT:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_INTERNAL_ERROR:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT:
        case IMSA_SIP_NW_ERROR_CAUSE_BUSY_EVERYWHERE:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVICE_UNAVAILABLE:

            /* ���ڽ���������Ҫ���ǽ�ͨ�ٶȵģ����ԾͲ���retry��ʱ���ȴ��ˣ�
               ֱ�ӻظ�����ע��ʧ�ܣ�����SPMȥCS���Խ����� */
            if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
            {
                /* ֹͣ������ʱ�� */
                IMSA_RegTimerStop(&pstEntity->stProtectTimer);

                /* ״̬�л� */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

                /* ֪ͨSERVICE����ע��ʧ�� */
                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL_REMOTE,
                                                        IMSA_RESULT_ACTION_NULL);

                #if (FEATURE_ON == FEATURE_PTM)
                IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        VOS_FALSE,
                                        pstImsErrorInfo->usSipStatusCode,
                                        IMSA_ERR_LOG_CALL_STATUS_IDLE);
                #endif
                return VOS_TRUE;
            }

            IMSA_RegWaitForRetryCommonProc( pstEntity,
                                            pstImsErrorInfo->ulRetryAfter,
                                            IMSA_FALSE,
                                            pstImsErrorInfo->usSipStatusCode);

            break;

        case IMSA_IMS_INT_ERROR_CODE_TCP_ERROR:
        case IMSA_IMS_INT_ERROR_CODE_IPSEC_ERROR:
            /* ��ΪҪ��ȡ����ע��ʧ�ܵĵ�ַ�����ͣ�������Ҫ�ٷ�����һ��ע��ǰ�����ϱ�CHR */
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                     IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                     pstImsErrorInfo->usSipStatusCode,
                                     VOS_FALSE,
                                     IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
            #endif

            /* �����ȡ��ǰ����ʹ�õĵ�ַ�Գɹ�����ʹ�øõ�ַ�����·���ע�� */
            if (VOS_TRUE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                        IMSA_REG_ADDR_PARAM_SAME,
                                                        aucUeAddr,
                                                        aucPcscfAddr))
            {
                /* ֹͣ������ʱ�� */
                IMSA_RegTimerStop(&pstEntity->stProtectTimer);

                IMSA_CONN_UpdateNicPdpInfo();

                /* ��D2 IMS����ע����Ϣ */
                (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

                /* ����������ʱ�� */
                IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

                /* ״̬�л� */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
            }
            else
            {
                IMSA_WARN_LOG("IMSA_RegFsmProcRegisteringImsRegFailure:get current para failed!");
                TLPS_PRINT2LAYER_WARNING(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, LNAS_PARAM_INVALID);

                /* ֹͣ������ʱ�� */
                IMSA_RegTimerStop(&pstEntity->stProtectTimer);

                /* ״̬�л� */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL_TRANSPORT,
                                                        IMSA_RESULT_ACTION_NULL);
            }

            break;

        default:
            /* ����NV���õ��ٳ��Դ�����ʹ�õ�ǰע�������ȥ����ע�ᣬ
               ���NV���õĳ��Դ���Ϊ0����������޴γ��ԣ�
               ���NV���õĳ��Դ�����Ϊ0���������Ч�γ��ԣ������Գ�����Ч��ʱ��
               ��任�������ٴη���ע�� */
            if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
            {
                /* ֹͣ������ʱ�� */
                IMSA_RegTimerStop(&pstEntity->stProtectTimer);

                /* ״̬�л� */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

                /* ֪ͨSERVICE����ע��ʧ�� */
                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL_REMOTE,
                                                        IMSA_RESULT_ACTION_NULL);

                return VOS_TRUE;
            }
            if (0 == pstImsaRegManager->ulSaveRetryTimes)
            {
                IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure: retry limitless times!");
                TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, 1);
                IMSA_RegWaitForRetryCommonProc( pstEntity,
                                                pstImsErrorInfo->ulRetryAfter,
                                                IMSA_FALSE,
                                                pstImsErrorInfo->usSipStatusCode);
            }
            else
            {
                if (pstEntity->ulRetryTimes < pstImsaRegManager->ulSaveRetryTimes)
                {
                    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure: retry limitary times!");
                    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, 2);
                    IMSA_RegWaitForRetryCommonProc( pstEntity,
                                                pstImsErrorInfo->ulRetryAfter,
                                                IMSA_FALSE,
                                                pstImsErrorInfo->usSipStatusCode);
                }
                else
                {
                    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringImsRegFailure: retry with next addr!");
                    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringImsRegFailure_ENUM, 3);
                    /* ��ΪҪ��ȡ����ע��ʧ�ܵĵ�ַ�����ͣ�������Ҫ�ٷ�����һ��ע��ǰ�����ϱ�CHR */
                    #if (FEATURE_ON == FEATURE_PTM)
                    IMSA_RegFailErrLogRecord(pstEntity->enRegType,
                                             IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                             pstImsErrorInfo->usSipStatusCode,
                                             VOS_FALSE,
                                             IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE);
                    #endif
                    IMSA_RegFsmProcRegisteringImsRegFailure305(pstEntity);
                }
            }
            break;

    }

    return VOS_TRUE;
}


VOS_VOID IMSA_RegProcNwNotifyMsgByEvent
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_VOID                           *pData
)
{
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo = VOS_NULL_PTR;

    pstImsErrorInfo = (IMSA_IMS_OUTPUT_ERROR_STRU*)pData;

    IMSA_INFO_LOG1("IMSA_RegProcNwNotifyMsgByEvent:", pstImsErrorInfo->ucServerNtyEvent);
    TLPS_PRINT2LAYER_INFO1(IMSA_RegProcNwNotifyMsgByEvent_ENUM, 1, pstImsErrorInfo->ucServerNtyEvent);

    switch (pstImsErrorInfo->ucServerNtyEvent)
    {
        case IMSA_IMS_SERVICE_NOTIFY_EVENT_DEACTED:
            IMSA_RegWaitForRetryCommonProc( pstEntity,
                                            pstImsErrorInfo->ulRetryAfter,
                                            IMSA_TRUE,
                                            pstImsErrorInfo->usSipStatusCode);
            break;
        case IMSA_IMS_SERVICE_NOTIFY_EVENT_REJED:
        case IMSA_IMS_SERVICE_NOTIFY_EVENT_UNREGED:
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_NULL);
            #if (FEATURE_ON == FEATURE_PTM)
            /* ��¼����ȥע��IMS�¼� */
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_NW_INIT);
            }
            #endif
            break;
        default:
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_NULL);
            #if (FEATURE_ON == FEATURE_PTM)
            /* ��¼����ȥע��IMS�¼� */
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_NW_INIT);
            }
            #endif
            break;
    }
}


VOS_UINT32 IMSA_RegFsmProcRegisteredImsRegFailure
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulEvt,
    VOS_VOID                           *pData
)
{
    IMSA_IMS_OUTPUT_ERROR_STRU         *pstImsErrorInfo = VOS_NULL_PTR;

    IMSA_REG_MANAGER_STRU              *pstImsaRegManager   = IMSA_RegCtxGet();
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1]    = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    /* ���Դ�����1 */
    pstEntity->ulRetryTimes++;

    /* �л�״̬ */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    /* ĿǰG/W��֧��IMS��IMSA���ٻ�ȡ��һ����ַ����ע�� */
    if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
    {
        if  (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
        {
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
        }
        else
        {
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_NULL);
        }
        #if (FEATURE_ON == FEATURE_PTM)
        if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
        {
            IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
        }
        #endif
        return VOS_TRUE;
    }

    /* IMS��������ע���쳣�������ٷ���IMS������ʼע�ᣬֱ�ӽ���IMS��������
       �����ͷţ���Ϊ�������Ѿ����ͷ��� */
    if (IMSA_REG_TYPE_EMC == pstEntity->enRegType)
    {
        /* ֪ͨSERVICE���ٳ���ע�� */
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_NULL);

        return VOS_TRUE;
    }

    if (VOS_NULL_PTR == pData)
    {
        /* ֪ͨSERVICEʹ����һ�������������ע�� */
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                IMSA_REG_RESULT_FAIL,
                                                IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);

        #if (FEATURE_ON == FEATURE_PTM)
        if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
        {
            IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                        VOS_FALSE,
                                        VOS_FALSE);
        }
        #endif
        return VOS_TRUE;
    }

    pstImsErrorInfo = (IMSA_IMS_OUTPUT_ERROR_STRU*)pData;

    switch (pstImsErrorInfo->usSipStatusCode)
    {
        case IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT:
            if (VOS_FALSE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                         IMSA_REG_ADDR_PARAM_NEXT,
                                                         aucUeAddr,
                                                         aucPcscfAddr))
            {
                (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL,
                                                        IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR);
            }
            else
            {
                /* (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL,
                                                        IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR); */
                IMSA_CONN_UpdateNicPdpInfo();

                /* ��D2 IMS����ע����Ϣ */
                (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

                /* ����������ʱ�� */
                IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

                /* ״̬�л� */
                IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
            }
            #if (FEATURE_ON == FEATURE_PTM)
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                            pstImsErrorInfo->usSipStatusCode,
                                            VOS_FALSE);
            }
            #endif
            break;
        case IMSA_SIP_NW_ERROR_CAUSE_USE_PROXY:
        /* case IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT: */

            /* ֪ͨSERVICEʹ����һ�������������ע�� */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);
            /* ����÷�֧��״̬ʱ����G/W��PS��ûע��ɹ�������IMS�Ѿ�ע��ʧ�ܣ� */
            #if (FEATURE_ON == FEATURE_PTM)
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                            pstImsErrorInfo->usSipStatusCode,
                                            VOS_FALSE);
            }
            #endif
            break;

        case IMSA_SIP_NW_ERROR_CAUSE_REQUEST_TIMEOUT:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_INTERNAL_ERROR:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT:
        case IMSA_SIP_NW_ERROR_CAUSE_BUSY_EVERYWHERE:
        case IMSA_SIP_NW_ERROR_CAUSE_SERVICE_UNAVAILABLE:
            IMSA_RegWaitForRetryCommonProc( pstEntity,
                                            pstImsErrorInfo->ulRetryAfter,
                                            IMSA_TRUE,
                                            pstImsErrorInfo->usSipStatusCode);
            break;
        case IMSA_IMS_INT_ERROR_CODE_NOTIFY_DEREGISTER:
            IMSA_RegProcNwNotifyMsgByEvent(pstEntity, pData);
            break;
        case IMSA_IMS_INT_ERROR_CODE_TCP_ERROR:
        case IMSA_IMS_INT_ERROR_CODE_IPSEC_ERROR:

            /* ֪ͨSERVICEʹ�õ�ǰ������������ע�� */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR);
            /* ����÷�֧��״̬ʱ����G/W��PS��ûע��ɹ�������IMS�Ѿ�ע��ʧ�ܣ� */
            #if (FEATURE_ON == FEATURE_PTM)
            if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
            {
                IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                            pstImsErrorInfo->usSipStatusCode,
                                            VOS_FALSE);
            }
            #endif
            break;

        default:
            /* ����NV���õ��ٳ��Դ�����ʹ�õ�ǰע�������ȥ����ע�ᣬ
               ���NV���õĳ��Դ���Ϊ0����������޴γ��ԣ�
               ���NV���õĳ��Դ�����Ϊ0���������Ч�������ԣ������Գ�����Ч����ʱ��
               ��ʹ����һ���������ע�� */
            if (0 == pstImsaRegManager->ulSaveRetryTimes)
            {
                IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredImsRegFailure: retry limitless times!");
                TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredImsRegFailure_ENUM, 1);
                IMSA_RegWaitForRetryCommonProc( pstEntity,
                                                pstImsErrorInfo->ulRetryAfter,
                                                IMSA_TRUE,
                                                pstImsErrorInfo->usSipStatusCode);
            }
            else
            {
                if (pstEntity->ulRetryTimes < pstImsaRegManager->ulSaveRetryTimes)
                {
                    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredImsRegFailure: retry limitary times!");
                    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredImsRegFailure_ENUM, 2);
                    IMSA_RegWaitForRetryCommonProc( pstEntity,
                                                    pstImsErrorInfo->ulRetryAfter,
                                                    IMSA_TRUE,
                                                    pstImsErrorInfo->usSipStatusCode);
                }
                else
                {
                    /* ֪ͨSERVICEʹ����һ�������������ע�� */
                    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredImsRegFailure: retry with next addr!");
                    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredImsRegFailure_ENUM, 3);
                    (VOS_VOID)IMSA_RegSendIntraMsgDeregInd( pstEntity->enRegType,
                                                            IMSA_REG_RESULT_FAIL,
                                                            IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR);
                    /* ����÷�֧��״̬ʱ����G/W��PS��ûע��ɹ�������IMS�Ѿ�ע��ʧ�ܣ� */
                    #if (FEATURE_ON == FEATURE_PTM)
                    if (IMSA_REG_TYPE_NORMAL == pstEntity->enRegType)
                    {
                        IMSA_NormRegFailErrRecord(  IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE,
                                                    pstImsErrorInfo->usSipStatusCode,
                                                    VOS_FALSE);
                    }
                    #endif
                }
            }
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegFsmProcRegisteringProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringProtectTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringProtectTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_REGISTER);
    #endif

    /* ����ȥע�� */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType, VOS_TRUE);

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* ��������״̬ */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_REGISTERED;

    /*����ע�����*/
    pstEntity->enPendingRegParam = IMSA_REG_ADDR_PARAM_NEXT;

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_ROLLING_BACK);

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_RegErrRecord(pstEntity->enRegType,IMSA_ERR_LOG_REG_FAIL_REASON_TIMEOUT);
    #endif

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegFsmProcRegisteringUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteringUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteringUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* ֹͣ������ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_REGISTER);
    #endif

    /* ����ȥע�� */
    IMSA_RegSendImsMsgDereg(pstDeregReq->enDeRegType, pstDeregReq->ulLocalFlag);

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_DEREGING);

    return VOS_TRUE;
}
VOS_UINT32 IMSA_RegFsmProcRegisteredUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcRegisteredUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRegisteredUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* ȥע��D2 IMS */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType,pstDeregReq->ulLocalFlag);

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* �л�״̬ */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_DEREGING);

    return VOS_TRUE;
}

/* zhaochen 00308719 begin for IMS Dereg for too long 2015-09-14 */

VOS_UINT32 IMSA_RegFsmProcDeregingUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcDeregingUserDereg is entered!");

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* ֹͣ������ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* ȥע��D2 IMS */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType,pstDeregReq->ulLocalFlag);

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    return VOS_TRUE;
}
/* zhaochen 00308719 end for IMS Dereg for too long 2015-09-14 */



VOS_UINT32 IMSA_RegFsmProcDeregingImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcDeregingImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcDeregingImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* ֹͣ������ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* ֪ͨ�û� */
    (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);

    /* �л�״̬ */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    return VOS_TRUE;
}
VOS_UINT32 IMSA_RegFsmProcDeregingProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcDeregingProtectTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcDeregingProtectTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /**
     * �������ִ�е��Ǳ���ȥע�ᣬ�������ǲ����г�ʱ�¼�;
     * �������ִ�е�����ͨȥע�ᣬ��ʱ�󱾵�ȥע����ͬ��״̬����ȡ���Ѻõ���Ϊ
     */

    /* ����ȥע�� */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType, VOS_TRUE);

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* ��������״̬ */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_NOT_REGISTER;

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_ROLLING_BACK);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegFsmProcDeregingUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_REG_REQ_STRU *pstRegReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcDeregingUserReg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcDeregingUserReg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstRegReq = (IMSA_REG_REG_REQ_STRU *)pData;

    /* ��������״̬ */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_REGISTERED;

    /* ����ע����� */
    pstEntity->enPendingRegParam = pstRegReq->enAddrType;

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_PENDING);

    return VOS_TRUE;
}
VOS_UINT32 IMSA_RegFsmProcWaitRetryTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1];
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1];

    IMSA_INFO_LOG("IMSA_RegFsmProcWaitRetryTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcWaitRetryTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* �����ǰ�������Ͳ�֧��IMS�����ٷ���ע�� */
    if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
    {
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

        if (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
        }
        else
        {
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                    IMSA_REG_RESULT_FAIL,
                                                    IMSA_RESULT_ACTION_NULL);
        }
        return VOS_TRUE;
    }

    if (VOS_TRUE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                IMSA_REG_ADDR_PARAM_SAME,
                                                aucUeAddr,
                                                aucPcscfAddr))
    {
        /* �����ȡ��ǰ����ʹ�õĵ�ַ�Գɹ�����ʹ�øõ�ַ�����·���ע�� */

        IMSA_CONN_UpdateNicPdpInfo();

        /* ��D2 IMS����ע����Ϣ */
        (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

        /* ����������ʱ�� */
        IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

        /* ״̬�л� */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
    }
    else
    {
        /**
         * �����ߵ������֧��ԭ������ڵȴ����������ӶϿ���CONN��֪ͨSERVICE��
         * SERVICE��֪ͨREG����ȥע�ᣬ����WAIT RETRY״̬�»��ܵ�����ȥע������
         * ��WAIT RETRY״̬ʱ�ϲ㴦��REGING�������ٸ�ע��ģ�鷢ע������
         * ������֣��Ǿ���SERVICEģ���������
         */
    }

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegFsmProcPeriodTryRegTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1];
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1];

    IMSA_INFO_LOG("IMSA_RegFsmProcPeriodTryRegTimeout is entered!");

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* �����ȡ��ǰ����ʹ�õĵ�ַ�Գɹ�����ʹ�øõ�ַ�����·���ע�� */
    if (VOS_TRUE == IMSA_RegGetAddrByParamType( pstEntity->enRegType,
                                                IMSA_REG_ADDR_PARAM_SAME,
                                                aucUeAddr,
                                                aucPcscfAddr))
    {
        IMSA_CONN_UpdateNicPdpInfo();

        /* ��D2 IMS����ע����Ϣ */
        (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

        /* ����������ʱ�� */
        IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

        /* ״̬�л� */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);

    }
    else
    {
    }

    return VOS_TRUE;
}




VOS_UINT32 IMSA_RegFsmProcWaitRetryUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcWaitRetryUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcWaitRetryUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* ֹͣ���Զ�ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stRetryTimer);

    /* ֪ͨ�û� */
    (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

    return VOS_TRUE;
}
VOS_UINT32 IMSA_RegFsmProcPendingProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcPendingProtectTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcPendingProtectTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* ����ȥע�� */
    IMSA_RegSendImsMsgDereg(pstEntity->enRegType, VOS_TRUE);

    /* ����������ʱ�� */
    IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

    /* ״̬�л� */
    IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_ROLLING_BACK);

    return VOS_TRUE;
}
VOS_UINT32 IMSA_RegFsmProcPendingUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_REG_REQ_STRU *pstRegReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcPendingUserReg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcPendingUserReg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstRegReq = (IMSA_REG_REG_REQ_STRU *)pData;

    /* ����ע����� */
    pstEntity->enPendingRegParam = pstRegReq->enAddrType;

    /* ��������״̬ */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_REGISTERED;

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegFsmProcPendingUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcPendingUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcPendingUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* ����ע����� */
    pstEntity->ulPendingDeregParam = pstDeregReq->ulLocalFlag;

    /* ��������״̬ */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_NOT_REGISTER;

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegFsmProcPendingImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_INFO_LOG("IMSA_RegFsmProcPendingImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcPendingImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* ֹͣ������ʱ�� */
    IMSA_RegTimerStop(&pstEntity->stProtectTimer);

    /* �����ǰ״̬������״̬һ�£���֪ͨ�û� */
    if (IMSA_REG_STATUS_NOT_REGISTER == pstEntity->enExceptedStatus)
    {
        (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);
        /* ״̬�л� */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
    }
    /* �������״̬��ע�ᣬ����ע�� */
    else if (IMSA_REG_STATUS_REGISTERED == pstEntity->enExceptedStatus)
    {
        /* ���ݱ����ע�����ѡȡһ���ַ�Խ���ע�� */
        if (VOS_TRUE == IMSA_RegGetAddrByParamType(pstEntity->enRegType, pstEntity->enPendingRegParam, aucUeAddr, aucPcscfAddr))
        {
            IMSA_CONN_UpdateNicPdpInfo();

            (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

            /* ����������ʱ�� */
            IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
        }
        else
        {
            IMSA_ERR_LOG("IMSA_RegFsmProcPendingImsRegFailure: select address pair failure");
            TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcPendingImsRegFailure_ENUM, LNAS_FAIL);

            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_NO_ADDR_PAIR, IMSA_RESULT_ACTION_NULL);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
        }
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegFsmProcPendingImsRegFailure: invalid excepted status");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcPendingImsRegFailure_ENUM, IMSA_STATE_ERROR);

        /* ״̬�л� */
        IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
    }

    return VOS_TRUE;
}

/**
 * ״̬��������
 *
 * Roll-backʱ������ʱ�Ĵ����������Ӧ�þ������ⷢ���Ŷԣ�
 * ��ΪĿǰ��Roll-back��ͨ������ȥע����ʵ�ֵģ�������ע��
 * �����ϲ�Ӧ���г�ʱ�Ŷ�
 *
 * @param[in]   pstEntity   ע��ʵ��
 * @param[in]   ulEvt       �յ����¼�, �ο� #IMSA_REG_EVT_ENUM
 * @param[in]   pData       �¼���Ӧ��������������
 */
VOS_UINT32 IMSA_RegFsmProcRollingBackProtectTimeout(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_INFO_LOG("IMSA_RegFsmProcRollingBackProtectTimeout is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRollingBackProtectTimeout_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* ��������״̬֪ͨ�û� */
    switch (pstEntity->enExceptedStatus)
    {
    case IMSA_REG_STATUS_NOT_REGISTER:
        {
            /* ֹͣ������ʱ�� */
            IMSA_RegTimerStop(&pstEntity->stProtectTimer);

            /* ֪ͨ�û� */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_TIMEOUT, IMSA_RESULT_ACTION_NULL);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
            break;
        }
    case IMSA_REG_STATUS_REGISTERED:
        {
            /* ֹͣ������ʱ�� */
            IMSA_RegTimerStop(&pstEntity->stProtectTimer);

            /* ֪ͨ�û� */
            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_TIMEOUT, IMSA_RESULT_ACTION_NULL);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
            break;
        }
    default:
        IMSA_ERR_LOG("IMSA_RegFsmProcRollingBackProtectTimeout: invalid excepted status");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcRollingBackProtectTimeout_ENUM, IMSA_STATE_ERROR);
    }

    return VOS_TRUE;
}
VOS_UINT32 IMSA_RegFsmProcRollingBackImsRegFailure(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    VOS_CHAR aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    IMSA_INFO_LOG("IMSA_RegFsmProcRollingBackImsRegFailure is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRollingBackImsRegFailure_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;
    (VOS_VOID)pData;

    /* ��������״̬֪ͨ�û� */
    switch (pstEntity->enExceptedStatus)
    {
    case IMSA_REG_STATUS_NOT_REGISTER:
        {
            /* ֹͣ������ʱ�� */
            IMSA_RegTimerStop(&pstEntity->stProtectTimer);

            /* ֪ͨ�û� */
            (VOS_VOID)IMSA_RegSendIntraMsgDeregInd(pstEntity->enRegType, IMSA_REG_RESULT_SUCCESS, IMSA_RESULT_ACTION_NULL);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
            break;
        }
    case IMSA_REG_STATUS_REGISTERED:
        IMSA_RegTimerStop(&pstEntity->stProtectTimer);

        /* �����ǰ�������Ͳ�֧��IMS�����ٷ���ע�� */
        if (VOS_TRUE != IMSA_IsCurrentAccessTypeSupportIms())
        {
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);

            if (VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
            {
                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL,
                                                        IMSA_RESULT_ACTION_REG_LOCAL_DEREG);
            }
            else
            {
                (VOS_VOID)IMSA_RegSendIntraMsgRegInd(   pstEntity->enRegType,
                                                        IMSA_REG_RESULT_FAIL,
                                                        IMSA_RESULT_ACTION_NULL);
            }
            return VOS_TRUE;
        }

        /* �������״̬��ע�ᣬ����ݱ����ע�����ѡȡһ���ַ�Խ���ע�� */
        if (VOS_TRUE == IMSA_RegGetAddrByParamType(pstEntity->enRegType, pstEntity->enPendingRegParam, aucUeAddr, aucPcscfAddr))
        {
            IMSA_CONN_UpdateNicPdpInfo();

            (VOS_VOID)IMSA_RegSendImsMsgReg(pstEntity->enRegType, aucUeAddr, aucPcscfAddr);

            /* ����������ʱ�� */
            IMSA_RegTimerStart(&pstEntity->stProtectTimer, pstEntity->enRegType);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_REGISTERING);
        }
        else
        {
            IMSA_ERR_LOG("IMSA_RegFsmProcRollingBackImsRegFailure: select address pair failure");
            TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcRollingBackImsRegFailure_ENUM, LNAS_FAIL);

            (VOS_VOID)IMSA_RegSendIntraMsgRegInd(pstEntity->enRegType, IMSA_REG_RESULT_FAIL_NO_ADDR_PAIR, IMSA_RESULT_ACTION_NULL);

            /* ״̬�л� */
            IMSA_REG_FSM_STATE_TRANS(pstEntity, IMSA_REG_STATUS_NOT_REGISTER);
        }
        break;

    default:
        IMSA_ERR_LOG("IMSA_RegFsmProcRollingBackImsRegFailure: invalid excepted status");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegFsmProcRollingBackImsRegFailure_ENUM, IMSA_STATE_ERROR);
    }

    return VOS_TRUE;
}
VOS_UINT32 IMSA_RegFsmProcRollingBackUserReg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_REG_REQ_STRU *pstRegReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcRollingBackUserReg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRollingBackUserReg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstRegReq = (IMSA_REG_REG_REQ_STRU *)pData;

    /* ����ע����� */
    pstEntity->enPendingRegParam = pstRegReq->enAddrType;

    /* ��������״̬ */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_REGISTERED;

    return VOS_TRUE;
}


VOS_UINT32 IMSA_RegFsmProcRollingBackUserDereg(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData)
{
    IMSA_REG_DEREG_REQ_STRU *pstDeregReq = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegFsmProcRollingBackUserDereg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegFsmProcRollingBackUserDereg_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulEvt;

    pstDeregReq = (IMSA_REG_DEREG_REQ_STRU *)pData;

    /* ����ע����� */
    pstEntity->ulPendingDeregParam = pstDeregReq->ulLocalFlag;

    /* ��������״̬ */
    pstEntity->enExceptedStatus = IMSA_REG_STATUS_NOT_REGISTER;

    return VOS_TRUE;
}



IMSA_REG_ENTITY_STRU* IMSA_RegEntityGetByType(IMSA_REG_TYPE_ENUM_UINT8 enRegType)
{
    IMSA_REG_MANAGER_STRU *pstRegCtx = IMSA_RegCtxGet();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        return &pstRegCtx->stNormalRegEntity;
    }
    else
    {
        return &pstRegCtx->stEmcRegEntity;
    }
}


VOS_UINT32 IMSA_RegProcUserRegReqMsg(const VOS_VOID *pRcvMsg)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;
    IMSA_REG_REG_REQ_STRU *pstRegReqData = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcUserRegReqMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegProcUserRegReqMsg_ENUM, LNAS_ENTRY);

    pstRegReqData = (IMSA_REG_REG_REQ_STRU *)pRcvMsg;
    pstRegEntity = IMSA_RegEntityGetByType(pstRegReqData->enRegType);

    return IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_USER_REG_REQ, (VOS_VOID *)pstRegReqData);
}


VOS_UINT32 IMSA_RegProcUserDeregReqMsg(const VOS_VOID *pRcvMsg)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;
    IMSA_REG_DEREG_REQ_STRU *pstDeregReqData = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcUserDeregReqMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegProcUserDeregReqMsg_ENUM, LNAS_ENTRY);

    pstDeregReqData = (IMSA_REG_DEREG_REQ_STRU *)pRcvMsg;
    pstRegEntity = IMSA_RegEntityGetByType(pstDeregReqData->enDeRegType);

    return IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_USER_DEREG_REQ, (VOS_VOID *)pstDeregReqData);
}



VOS_UINT32 IMSA_RegProcImsMsgState(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;
    VOS_UINT32 ulResult = VOS_FALSE;
    IMSA_IMS_OUTPUT_ERROR_STRU                      stImsErrorInfo = {0};

    IMSA_INFO_LOG1("IMSA_RegProcImsMsgState: ", pstOutputService->enServeState);
    TLPS_PRINT2LAYER_INFO1(IMSA_RegProcImsMsgState_ENUM, LNAS_ENTRY, pstOutputService->enServeState);

    if (pstOutputService->ulIsEmergency)
    {
        pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_EMC);
    }
    else
    {
        pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_NORMAL);
    }

    switch (pstOutputService->enServeState)
    {
    case IMSA_IMS_SERVICE_STATE_INACTIVE:
    case IMSA_IMS_SERVICE_STATE_FAILED:
    case IMSA_IMS_SERVICE_STATE_UNKNOWN:

        /* Convert IMS extra parameter to REG data structure */
        ulResult = IMSA_RegParseImsError(pstOutputService, &stImsErrorInfo);

        if (IMSA_SUCC == ulResult)
        {
            ulResult = IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_IMS_REG_FAILURE, &stImsErrorInfo);
        }
        else
        {
            ulResult = IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_IMS_REG_FAILURE, VOS_NULL_PTR);
        }

        break;
    case IMSA_IMS_SERVICE_STATE_ACTIVE:
        ulResult = IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_IMS_REG_SUCCESS, VOS_NULL_PTR);
        break;
    case IMSA_IMS_SERVICE_STATE_REGISTERING:
    case IMSA_IMS_SERVICE_STATE_DEREGISTERING:
    case IMSA_IMS_SERVICE_STATE_ROAMING:
    default:
        IMSA_INFO_LOG1("IMSA_RegProcImsMsgState: state need not handle", pstOutputService->enServeState);
        TLPS_PRINT2LAYER_INFO1(IMSA_RegProcImsMsgState_ENUM, IMSA_STATE_ERROR, pstOutputService->enServeState);
        break;
    }

    return ulResult;
}
VOS_VOID IMSA_RegProcTimeoutProtect(const VOS_VOID *pTimerMsg)
{
    IMSA_REG_TYPE_ENUM_UINT8 enRegType;
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcTimeoutProtect is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegProcTimeoutProtect_ENUM, LNAS_ENTRY);

    enRegType = (IMSA_REG_TYPE_ENUM_UINT8)PS_GET_REL_TIMER_PARA(pTimerMsg);

    pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    (VOS_VOID)IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_TIMEOUT_PROTECT, VOS_NULL_PTR);
}


VOS_VOID IMSA_RegProcTimeoutRetry(const VOS_VOID *pTimerMsg)
{
    IMSA_REG_TYPE_ENUM_UINT8 enRegType;
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcTimeoutRetry is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegProcTimeoutRetry_ENUM, LNAS_ENTRY);

    enRegType = (IMSA_REG_TYPE_ENUM_UINT8)PS_GET_REL_TIMER_PARA(pTimerMsg);

    pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    (VOS_VOID)IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_TIMEOUT_RETRY, VOS_NULL_PTR);
}


VOS_VOID IMSA_RegProcTimeoutPeriodTry(const VOS_VOID *pTimerMsg)
{
    IMSA_REG_TYPE_ENUM_UINT8 enRegType;
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegProcTimeoutPeriodTry is entered!");

    enRegType = (IMSA_REG_TYPE_ENUM_UINT8)PS_GET_REL_TIMER_PARA(pTimerMsg);

    pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    (VOS_VOID)IMSA_FsmRun(pstRegEntity, IMSA_REG_EVT_TIMEOUT_PERIOD_TRY, VOS_NULL_PTR);
}



IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairCreate(IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                const VOS_CHAR *pacUeAddr,
                                                const VOS_CHAR *pacPcscfAddr)
{
    IMSA_REG_ADDR_PAIR_STRU *pstAddrPair = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairCreate is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairCreate_ENUM, LNAS_ENTRY);

    pstAddrPair = (IMSA_REG_ADDR_PAIR_STRU*)IMSA_MEM_ALLOC(sizeof(IMSA_REG_ADDR_PAIR_STRU));
    if (pstAddrPair != VOS_NULL_PTR)
    {
        IMSA_MEM_SET(pstAddrPair, 0, sizeof(IMSA_REG_ADDR_PAIR_STRU));

        pstAddrPair->ucHasTryed = VOS_FALSE;
        pstAddrPair->enIpType = enIpType;
        IMSA_UtilStrNCpy(pstAddrPair->acUeAddr, pacUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(pstAddrPair->acPcscfAddr, pacPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);
    }

    return pstAddrPair;
}



VOS_VOID IMSA_RegAddrPairDestroy(IMSA_REG_ADDR_PAIR_STRU *pstAddrPair)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairDestroy is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairDestroy_ENUM, LNAS_ENTRY);

    if (pstAddrPair)
    {
        IMSA_MEM_FREE(pstAddrPair);
    }
}


IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListAdd(IMSA_REG_ADDR_PAIR_STRU **ppstListHead, IMSA_REG_ADDR_PAIR_STRU *pstNode)
{
    IMSA_REG_ADDR_PAIR_STRU *pstTmp = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairListAdd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairListAdd_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == *ppstListHead)
    {
        *ppstListHead = pstNode;

        pstNode->pstNext = VOS_NULL_PTR;
    }
    else
    {
        pstTmp = *ppstListHead;
        /* modify by jiqiang 2014.03.25 pclint fix error 960 begin */
        while (VOS_NULL_PTR != pstTmp->pstNext)
        {
            pstTmp = pstTmp->pstNext;
        }
        /* modify by jiqiang 2014.03.25 pclint fix error 960 end */
        pstTmp->pstNext = pstNode;

        pstNode->pstNext = VOS_NULL_PTR;
    }

    return pstNode;
}


VOS_VOID IMSA_RegAddrPairListDestroy(IMSA_REG_ADDR_PAIR_STRU *pstListHead)
{
    IMSA_REG_ADDR_PAIR_STRU *pstTmpAddrPair = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairListDestroy is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairListDestroy_ENUM, LNAS_ENTRY);

    while (pstListHead)
    {
        pstTmpAddrPair = pstListHead;
        pstListHead = pstListHead->pstNext;

        IMSA_RegAddrPairDestroy(pstTmpAddrPair);
    }
}


VOS_VOID IMSA_RegAddrPairMgrInit(IMSA_REG_ADDR_PAIR_MGR_STRU *pstPairMgr)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairMgrInit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrInit_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET(pstPairMgr, 0, sizeof(IMSA_REG_ADDR_PAIR_MGR_STRU));
}



VOS_VOID IMSA_RegAddrPairMgrDeinit(const IMSA_REG_ADDR_PAIR_MGR_STRU *pstPairMgr)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairMgrDeinit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrDeinit_ENUM, LNAS_ENTRY);

    IMSA_RegAddrPairListDestroy(pstPairMgr->pstIpv6List);
    IMSA_RegAddrPairListDestroy(pstPairMgr->pstIpv4List);
}


VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr(IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
                                                     IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                     const VOS_CHAR *pacPcscfAddr)
{
    VOS_CHAR *pacDstAddr = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU *pstNewPair = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU **ppstDstPairList = VOS_NULL_PTR;
    VOS_UINT8 ulResult = VOS_FALSE;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr_ENUM, LNAS_ENTRY);

    /* ����PCSCF��ַ���;���Ҫ�����ĸ��б��Լ�ʹ���ĸ�UE��ַ */
    if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        pacDstAddr = pstAddrPairMgr->acUeAddrIpv4;
        ppstDstPairList = &pstAddrPairMgr->pstIpv4List;
    }
    else if (enIpType == IMSA_IP_TYPE_IPV6)
    {
        pacDstAddr = pstAddrPairMgr->acUeAddrIpv6;
        ppstDstPairList = &pstAddrPairMgr->pstIpv6List;
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr: invalid ip type");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr_ENUM, IMSA_IP_TYPE_ERROR);
        return VOS_FALSE;
    }

    if (0 != VOS_StrLen(pacDstAddr))
    {
        pstNewPair = IMSA_RegAddrPairCreate(enIpType, pacDstAddr, pacPcscfAddr);
        if (pstNewPair)
        {
            (VOS_VOID)IMSA_RegAddrPairListAdd(ppstDstPairList, pstNewPair);

            ulResult = VOS_TRUE;
        }
        else
        {
            IMSA_ERR_LOG("IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr: alloc memory fail");
            TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr_ENUM, LNAS_NULL_PTR);
        }
    }

    return ulResult;
}
VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewUeAddr(IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
                                                  IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                                  const VOS_CHAR *pacUeAddr)
{
    IMSA_REG_ADDR_PAIR_STRU *pstNewPair = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU **ppstDstPairList = VOS_NULL_PTR;
    VOS_UINT8 ulResult = VOS_FALSE;
    VOS_UINT8 i = 0;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrUpdateWithNewUeAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrUpdateWithNewUeAddr_ENUM, LNAS_ENTRY);

    /* ���ݵ�ַ����ѡ��Ҫ���µ��б� */
    if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        ppstDstPairList = &pstAddrPairMgr->pstIpv4List;
    }
    else if (enIpType == IMSA_IP_TYPE_IPV6)
    {
        ppstDstPairList = &pstAddrPairMgr->pstIpv6List;
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegAddrPairMgrUpdateWithNewUeAddr: invalid ip type");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrUpdateWithNewUeAddr_ENUM, IMSA_IP_TYPE_ERROR);
        return VOS_FALSE;
    }

    for (i = 0; i < IMSA_PCSCF_MAX_NUM; i++)
    {
        /* ѡȡ��ַ����ƥ���PCSCF�������µĵ�ַ�� */
        if ((0 != VOS_StrLen(pstAddrPairMgr->astPcscfs[i].acIpAddr)) &&
            (pstAddrPairMgr->astPcscfs[i].enIpType == enIpType))
        {
            pstNewPair = IMSA_RegAddrPairCreate(enIpType, pacUeAddr, pstAddrPairMgr->astPcscfs[i].acIpAddr);
            if (pstNewPair)
            {
                (VOS_VOID)IMSA_RegAddrPairListAdd(ppstDstPairList, pstNewPair);

                ulResult = VOS_TRUE;
            }
            else
            {
                IMSA_ERR_LOG("IMSA_RegAddrPairMgrUpdateWithNewUeAddr: alloc memory fail");
                TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrUpdateWithNewUeAddr_ENUM, LNAS_NULL_PTR);
            }
        }
    }

    return ulResult;
}

VOS_UINT32 IMSA_RegAddrPairMgrAddPcscfAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                           IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                           IMSA_PCSCF_SRC_TYPE_UINT8 enSrcType,
                                           const VOS_CHAR *pacIpAddr)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);
    VOS_UINT8 i = 0;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrAddPcscfAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrAddPcscfAddr_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_PCSCF_MAX_NUM; i++)
    {
        if (0 == VOS_StrLen(pstRegEntity->stPairMgrCtx.astPcscfs[i].acIpAddr))
        {
            /* Ѱ��δʹ�õĿռ�洢�¼����PCSCF��ַ */
            pstRegEntity->stPairMgrCtx.astPcscfs[i].enIpType = enIpType;
            pstRegEntity->stPairMgrCtx.astPcscfs[i].enSrcType = enSrcType;

            IMSA_UtilStrNCpy(pstRegEntity->stPairMgrCtx.astPcscfs[i].acIpAddr, pacIpAddr, IMSA_IPV6_ADDR_STRING_LEN);

            /* ʹ���µ�PCSCF��ַ���µ�ַ���б� */
            (VOS_VOID)IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr(&pstRegEntity->stPairMgrCtx, enIpType, pacIpAddr);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID IMSA_RegGetAddrPairListHead
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    IMSA_REG_ADDR_PAIR_STRU          ***pppstListHead
)
{
    IMSA_REG_ADDR_PAIR_MGR_STRU        *pstAddrPairMgr      = VOS_NULL_PTR;
    IMSA_REG_ENTITY_STRU               *pstRegEntity        = IMSA_RegEntityGetByType(ulRegType);

    IMSA_INFO_LOG("IMSA_RegGetAddrPairListHead is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegGetAddrPairListHead_ENUM, LNAS_ENTRY);

    pstAddrPairMgr = &pstRegEntity->stPairMgrCtx;

    if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        if (VOS_NULL_PTR == pstAddrPairMgr->pstIpv4List)
        {
            return ;
        }

        *pppstListHead = &pstAddrPairMgr->pstIpv4List;
    }
    else
    {
        if (VOS_NULL_PTR == pstAddrPairMgr->pstIpv6List)
        {
            return ;
        }

        *pppstListHead = &pstAddrPairMgr->pstIpv6List;
    }
}


VOS_UINT32 IMSA_RegAddrPairMgrRmvPcscfAddr
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    VOS_CHAR                           *pacIpAddr
)
{
    VOS_UINT32                          i                   = IMSA_NULL;
    IMSA_REG_ENTITY_STRU               *pstRegEntity        = IMSA_RegEntityGetByType(ulRegType);
    IMSA_REG_ADDR_PAIR_MGR_STRU        *pstAddrPairMgr      = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU            *pstTmpAddrPairPrior = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU            *pstTmpAddrPair      = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU           **ppstListHead        = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrRmvPcscfAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrRmvPcscfAddr_ENUM, LNAS_ENTRY);

    pstAddrPairMgr = &pstRegEntity->stPairMgrCtx;

    /* ���ȥ���������漰����ǰ����ʹ�õĵ�ַ�ԣ�CONNģ��Ḻ��֪ͨSERVICEģ��
       �����ͷŻ��ߵ�ǰע�����ʧЧ��SERVICEģ����֪ͨע��ģ�鱾��ȥע�᣻��ַ��
       �Ĺ���ֻ��Ҫɾ��P-CSCF��ַ��Ϣ�͹����ĵ�ַ�Լ��� */

    /* �����ǰע������е�P-CSCF��ַ�������ͬ�������currentָ�� */
    if (pstAddrPairMgr->pstCurrent != VOS_NULL_PTR)
    {
        if ((0 == VOS_StrCmp(pstAddrPairMgr->pstCurrent->acPcscfAddr, pacIpAddr))
            && (pstAddrPairMgr->pstCurrent->enIpType == enIpType))
        {
            pstAddrPairMgr->pstCurrent = VOS_NULL_PTR;
        }
    }

    /* ����洢��P-CSCF��ַ��Ϣ */
    for (i = 0; i < IMSA_PCSCF_MAX_NUM; i++)
    {
        if (0 == VOS_StrLen(pstAddrPairMgr->astPcscfs[i].acIpAddr))
        {
            continue ;
        }

        if ((0 == VOS_StrCmp(pstAddrPairMgr->astPcscfs[i].acIpAddr, pacIpAddr))
            && (pstAddrPairMgr->astPcscfs[i].enIpType == enIpType))
        {
            IMSA_MEM_SET(   &pstAddrPairMgr->astPcscfs[i],
                            0,
                            sizeof(IMSA_REG_PCSCF_STRU));
        }
    }

    IMSA_RegGetAddrPairListHead(ulRegType, enIpType, &ppstListHead);

    if (VOS_NULL_PTR == ppstListHead)
    {
        return IMSA_SUCC;
    }

    /* ������P-CSCF��صĵ�ַ�� */

    /* ���Ҫɾ���ĵ�ַ�����б�ĵ�һ����¼ */
    pstTmpAddrPair = *ppstListHead;
    if ((0 == VOS_StrCmp(pstTmpAddrPair->acPcscfAddr, pacIpAddr))
            && (pstTmpAddrPair->enIpType == enIpType))
    {
        /* �޸ı�ͷ */
        *ppstListHead = pstTmpAddrPair->pstNext;

         IMSA_RegAddrPairDestroy(pstTmpAddrPair);

         return IMSA_SUCC;
    }

    pstTmpAddrPairPrior = pstTmpAddrPair;
    pstTmpAddrPair      = pstTmpAddrPair->pstNext;
    while (pstTmpAddrPair != VOS_NULL_PTR)
    {
        if ((0 == VOS_StrCmp(pstTmpAddrPair->acPcscfAddr, pacIpAddr))
            && (pstTmpAddrPair->enIpType == enIpType))
        {
            /* ����ǰ��ַ�Դ��б���ɾ�� */
            pstTmpAddrPairPrior->pstNext = pstTmpAddrPair->pstNext;

            IMSA_RegAddrPairDestroy(pstTmpAddrPair);

            return IMSA_SUCC;
        }

        pstTmpAddrPairPrior = pstTmpAddrPair;
        pstTmpAddrPair      = pstTmpAddrPair->pstNext;
    }

    return IMSA_SUCC;
}

VOS_UINT32 IMSA_RegAddrPairMgrAddUeAddr(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                        IMSA_IP_TYPE_ENUM_UINT8 enIpType,
                                        const VOS_CHAR *pacIpAddr)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);
    VOS_CHAR *pacDstAddr = VOS_NULL_PTR;
    VOS_UINT32 ulResult = VOS_FALSE;
    VOS_UINT32      ulLength = 0;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrAddUeAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrAddUeAddr_ENUM, LNAS_ENTRY);

    /* ���ݵ�ַ����ѡȡҪ�洢�ĵ�ַ */
    if (enIpType == IMSA_IP_TYPE_IPV6)
    {
        pacDstAddr = (VOS_CHAR *)pstRegEntity->stPairMgrCtx.acUeAddrIpv6;
        ulLength = IMSA_IPV6_ADDR_STRING_LEN;
    }
    else if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        pacDstAddr = (VOS_CHAR *)pstRegEntity->stPairMgrCtx.acUeAddrIpv4;
        ulLength = IMSA_IPV4_ADDR_STRING_LEN;
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegAddrPairMgrAddUeAddr: invalid ip type");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrAddUeAddr_ENUM, IMSA_IP_TYPE_ERROR);
        return VOS_FALSE;
    }

    /* ���Ŀ���ַδʹ�ã���洢�µ�UE��ַ */
    if (0 == VOS_StrLen(pacDstAddr))
    {
        IMSA_UtilStrNCpy(pacDstAddr, pacIpAddr, ulLength);

        /* ʹ���¼����UE��ַ���µ�ַ���б� */
        (VOS_VOID)IMSA_RegAddrPairMgrUpdateWithNewUeAddr(&pstRegEntity->stPairMgrCtx, enIpType, pacIpAddr);

        ulResult = VOS_TRUE;
    }

    return ulResult;
}
VOS_UINT32 IMSA_RegAddrPairMgrRmvUeAddr
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    VOS_CHAR                           *pacIpAddr
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity        = IMSA_RegEntityGetByType(ulRegType);
    IMSA_REG_ADDR_PAIR_MGR_STRU        *pstAddrPairMgr      = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrRmvUeAddr is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrRmvUeAddr_ENUM, LNAS_ENTRY);

    (VOS_VOID)pacIpAddr;

    pstAddrPairMgr = &pstRegEntity->stPairMgrCtx;

    /* ���ȥ���������漰����ǰ����ʹ�õĵ�ַ�ԣ�CONNģ��Ḻ��֪ͨSERVICEģ��
       �����ͷŻ��ߵ�ǰע�����ʧЧ��SERVICEģ����֪ͨע��ģ�鱾��ȥע�᣻��ַ��
       �Ĺ���ֻ��Ҫɾ��IP��ַ��Ϣ�͹����ĵ�ַ�Լ��� */

    /* �����ǰע������е�IP��ַ�������ͬ�������currentָ�� */
    if (pstAddrPairMgr->pstCurrent != VOS_NULL_PTR)
    {
        if (pstAddrPairMgr->pstCurrent->enIpType == enIpType)
        {
            pstAddrPairMgr->pstCurrent = VOS_NULL_PTR;
        }
    }

    /* ����洢��IP��ַ��Ϣ */
    if (enIpType == IMSA_IP_TYPE_IPV4)
    {
        IMSA_MEM_SET(   pstAddrPairMgr->acUeAddrIpv4,
                        0x0,
                        IMSA_IPV4_ADDR_STRING_LEN + 1);

        IMSA_RegAddrPairListDestroy(pstAddrPairMgr->pstIpv4List);

        pstAddrPairMgr->pstIpv4List = VOS_NULL_PTR;
    }
    else if (enIpType == IMSA_IP_TYPE_IPV6)
    {
        IMSA_MEM_SET(   pstAddrPairMgr->acUeAddrIpv6,
                        0x0,
                        IMSA_IPV6_ADDR_STRING_LEN + 1);

        IMSA_RegAddrPairListDestroy(pstAddrPairMgr->pstIpv6List);
        pstAddrPairMgr->pstIpv6List = VOS_NULL_PTR;
    }
    else
    {
        IMSA_ERR_LOG("IMSA_RegAddrPairMgrRmvUeAddr: invalid ip type");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegAddrPairMgrRmvUeAddr_ENUM, IMSA_IP_TYPE_ERROR);
    }

    return IMSA_SUCC;
}

VOS_UINT32 IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                         VOS_CHAR  *pacUeAddr,
                                         VOS_CHAR  *pacPcscfAddr)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrMgr = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU *pstDstAddrPair = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrGetCurrent is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrGetCurrent_ENUM, LNAS_ENTRY);

    pstAddrMgr = &pstRegEntity->stPairMgrCtx;

    pstDstAddrPair = pstAddrMgr->pstCurrent;

    /* ���ؽ�� */
    if (VOS_NULL_PTR == pstDstAddrPair)
    {
        return VOS_FALSE;
    }
    else
    {
        IMSA_UtilStrNCpy(pacUeAddr, pstDstAddrPair->acUeAddr, IMSA_IPV6_ADDR_STRING_LEN + 1);
        IMSA_UtilStrNCpy(pacPcscfAddr, pstDstAddrPair->acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN + 1);

        IMSA_INFO_LOG(pacUeAddr);
        IMSA_INFO_LOG(pacPcscfAddr);

        return VOS_TRUE;
    }
}

VOS_VOID IMSA_RegAddrPairListClearAllUsedFlag(IMSA_REG_ADDR_PAIR_STRU *pstList)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairListClearAllUsedFlag is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairListClearAllUsedFlag_ENUM, LNAS_ENTRY);

    while (pstList)
    {
        pstList->ucHasTryed = VOS_FALSE;

        pstList = pstList->pstNext;
    }
}


VOS_VOID IMSA_RegAddrPairMgrClearAllUsedFlag(IMSA_REG_TYPE_ENUM_UINT8 enRegType)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(enRegType);

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrClearAllUsedFlag is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrClearAllUsedFlag_ENUM, LNAS_ENTRY);

    IMSA_RegAddrPairListClearAllUsedFlag(pstRegEntity->stPairMgrCtx.pstIpv4List);
    IMSA_RegAddrPairListClearAllUsedFlag(pstRegEntity->stPairMgrCtx.pstIpv6List);
}

IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListGetNextUnused(IMSA_REG_ADDR_PAIR_STRU *pstList)
{
    IMSA_INFO_LOG("IMSA_RegAddrPairListGetNextUnused is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairListGetNextUnused_ENUM, LNAS_ENTRY);

    while (pstList)
    {
        if (VOS_FALSE == pstList->ucHasTryed)
        {
            return pstList;
        }

        pstList = pstList->pstNext;
    }

    return VOS_NULL_PTR;
}

IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairMgrGetFirst(IMSA_REG_TYPE_ENUM_UINT8 ulRegType)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrGetFirst is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrGetFirst_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR != pstRegEntity->stPairMgrCtx.pstIpv6List)
    {
        pstRegEntity->stPairMgrCtx.pstCurrent = pstRegEntity->stPairMgrCtx.pstIpv6List;

        return pstRegEntity->stPairMgrCtx.pstIpv6List;
    }
    else if (VOS_NULL_PTR != pstRegEntity->stPairMgrCtx.pstIpv4List)
    {
        pstRegEntity->stPairMgrCtx.pstCurrent = pstRegEntity->stPairMgrCtx.pstIpv4List;

        return pstRegEntity->stPairMgrCtx.pstIpv4List;
    }
    else
    {
        return VOS_NULL_PTR;
    }
}

VOS_UINT32 IMSA_RegAddrPairMgrGetNextUnused(IMSA_REG_TYPE_ENUM_UINT8 ulRegType,
                                            VOS_CHAR *pacUeIp,
                                            VOS_CHAR *pacPcscfIp)
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = IMSA_RegEntityGetByType(ulRegType);
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrMgr = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU *pstDstAddrPair = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegAddrPairMgrGetNextUnused is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegAddrPairMgrGetNextUnused_ENUM, LNAS_ENTRY);

    pstAddrMgr = &pstRegEntity->stPairMgrCtx;

    /* �����û�е�ǰ��ַ�ԣ���ӵ�ַ�б��е�һ����ʼ */
    if (VOS_NULL_PTR == pstAddrMgr->pstCurrent)
    {
        pstDstAddrPair = IMSA_RegAddrPairMgrGetFirst(ulRegType);
    }
    /* ����Ѿ����ڵ�ַ�б� */
    else
    {
        /* ����Ѿ����ڵ�ǰ��ַ�ԣ������Ƚ���ǰ��ַ������Ϊ�Ѿ����Թ� */
        pstAddrMgr->pstCurrent->ucHasTryed = VOS_TRUE;

        /**
         * TODO: �����´ӵ�һ����ַ�Կ�ʼ����ʱ��
         *       ����ζ��Ҫ��֮ǰ�Ѿ���ǳ��Թ��ĵ�ַ��ȫ����������
         */

        /**
         * ����ӵ�ǰλ�ÿ�ʼ����ң�Ŀǰ�ݲ�������ǰ�ҡ�
         * ��Ҫ�ǳ������ȼ����һ�δ���Թ��ĵ�ַ���ڵ�ǰ��ַ��֮ǰ���ܵ�
         * �����磺
         *     �տ�ʼʹ��IPv4��ַע�ᣬ�ڼ�IPv6�����ӽ����ɹ�����ʱ����
         * ��IPv6���ɵĵ�ַ�Կ��ܻ��ŵ���ǰʹ��IPv4��ǰ�ߡ�
         * Ŀǰ�ݲ�֧�����ֳ���
         */

        /**
         * �����ǰ��IPv6����IPv6���ȣ����Դӵ�ǰλ��(��IPv6�б�)�����ң�
         * ���IPv6�б�δ�ҵ������ٳ��Դ�IPv4���б��в���
         */
        if (IMSA_IP_TYPE_IPV6 == pstAddrMgr->pstCurrent->enIpType)
        {
            pstDstAddrPair = IMSA_RegAddrPairListGetNextUnused(pstAddrMgr->pstCurrent);
            if (VOS_NULL_PTR == pstDstAddrPair)
            {
                pstDstAddrPair = IMSA_RegAddrPairListGetNextUnused(pstAddrMgr->pstIpv4List);
            }
        }
        else
        /**
         * �����ǰ��IPv4����IPv6���ȣ������ȴ�IPv6�б��������ң�
         * ���IPv6�б�δ�ҵ������ٳ��Դ�IPv4�б��м�������
         */
        {
            pstDstAddrPair = IMSA_RegAddrPairListGetNextUnused(pstAddrMgr->pstIpv6List);
            if (VOS_NULL_PTR == pstDstAddrPair)
            {
                pstDstAddrPair = IMSA_RegAddrPairListGetNextUnused(pstAddrMgr->pstCurrent);
            }
        }
    }

    /* ���ؽ�� */
    if (VOS_NULL_PTR == pstDstAddrPair)
    {
        return VOS_FALSE;
    }
    else
    {
        /* ��currentָ��ָ���ȡ���ĵ�ַ�Ե�ַ */
        pstAddrMgr->pstCurrent = pstDstAddrPair;

        IMSA_UtilStrNCpy(pacUeIp, pstDstAddrPair->acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(pacPcscfIp, pstDstAddrPair->acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);

        IMSA_INFO_LOG(pacUeIp);
        IMSA_INFO_LOG(pacPcscfIp);

        return VOS_TRUE;
    }
}


VOS_UINT32 IMSA_RegGetRegedPara
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    VOS_CHAR                           *pacUeAddr,
    VOS_CHAR                           *pacPcscfAddr,
    IMSA_IP_TYPE_ENUM_UINT8            *penIptype
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_RegGetRegedPara is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegGetRegedPara_ENUM, LNAS_ENTRY);

    if ((VOS_NULL_PTR == pacUeAddr) || (VOS_NULL_PTR == pacPcscfAddr)
        || (ulRegType >= IMSA_REG_TYPE_BUTT) || (VOS_NULL_PTR == penIptype))
    {
        IMSA_ERR_LOG("IMSA_RegGetRegedPara:Input Para Illegal");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegGetRegedPara_ENUM, LNAS_PARAM_INVALID);

        return IMSA_FAIL;
    }

    pstRegEntity = IMSA_RegEntityGetByType(ulRegType);

    if ((IMSA_REG_STATUS_REGISTERED != pstRegEntity->enStatus) &&
        (IMSA_REG_STATUS_REGISTERING != pstRegEntity->enStatus))
    {
        return IMSA_FAIL;
    }

    if (VOS_FALSE == IMSA_RegGetAddrByParamType(    ulRegType,
                                                    IMSA_REG_ADDR_PARAM_SAME,
                                                    pacUeAddr,
                                                    pacPcscfAddr))
    {
        return IMSA_FAIL;
    }
    else
    {
        *penIptype = pstRegEntity->stPairMgrCtx.pstCurrent->enIpType;

        return IMSA_SUCC;
    }
}

VOS_VOID IMSA_RegSaveRegedPara
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = VOS_NULL_PTR;
    /* IMSA_REG_ENTITY_STRU                   *pstRegEntity        = VOS_NULL_PTR; */
    VOS_UINT32                              ulRslt          = IMSA_FAIL;
    VOS_CHAR                                acRegUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                                acRegPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_IP_TYPE_ENUM_UINT8                 enIpType = IMSA_IP_TYPE_BUTT;

    IMSA_INFO_LOG("IMSA_RegSaveRegedPara is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegSaveRegedPara_ENUM, LNAS_ENTRY);

    pstImsaControlManager = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == ulRegType)
    {
        ulRslt = IMSA_RegGetRegedPara(  ulRegType,
                                        acRegUeAddr,
                                        acRegPcscfAddr,
                                        &enIpType);

        /* ����ܻ�ȡ��ע��Ĳ���������ɾ��������Ϣǰ���б���  */
        if (IMSA_FAIL != ulRslt)
        {
            /* ɾ��������Ϣǰ�������ͷų��ص����ͺ�CID */
            pstImsaControlManager->stNrmRegParaInfo.ucCid = ucCid;
            pstImsaControlManager->stNrmRegParaInfo.enIpType = enPdpType;

            /* ����IP��ַ */
            IMSA_MEM_CPY( pstImsaControlManager->stNrmRegParaInfo.acUeAddr,
                          acRegUeAddr,
                          IMSA_IPV6_ADDR_STRING_LEN + 1);

            /* ����P-CSCF��ַ */
            IMSA_MEM_CPY( pstImsaControlManager->stNrmRegParaInfo.acPcscfAddr,
                          acRegPcscfAddr,
                          IMSA_IPV6_ADDR_STRING_LEN + 1);
        }
    }
    else
    {
        ulRslt = IMSA_RegGetRegedPara(  ulRegType,
                                        acRegUeAddr,
                                        acRegPcscfAddr,
                                        &enIpType);

        /* ����ܻ�ȡ��ע��Ĳ���������ɾ��������Ϣǰ���б���  */
        if (IMSA_FAIL != ulRslt)
        {
            /* ɾ��������Ϣǰ�������ͷų��ص����ͺ�CID */
            pstImsaControlManager->stEmcRegParaInfo.ucCid = ucCid;
            pstImsaControlManager->stEmcRegParaInfo.enIpType = enPdpType;

            /* ����IP��ַ */
            IMSA_MEM_CPY( pstImsaControlManager->stEmcRegParaInfo.acUeAddr,
                          acRegUeAddr,
                          IMSA_IPV6_ADDR_STRING_LEN + 1);

            /* ����P-CSCF��ַ */
            IMSA_MEM_CPY( pstImsaControlManager->stEmcRegParaInfo.acPcscfAddr,
                          acRegPcscfAddr,
                          IMSA_IPV6_ADDR_STRING_LEN + 1);
        }
    }
}
VOS_VOID IMSA_RegEntityInit(IMSA_REG_ENTITY_STRU *pstRegEntity)
{
    IMSA_INFO_LOG("IMSA_RegEntityInit IMSA_RegEntityInitis entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegEntityInit_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET(pstRegEntity, 0, sizeof(IMSA_REG_ENTITY_STRU));

    pstRegEntity->stProtectTimer.usName = TI_IMSA_REG_PROTECT;
    pstRegEntity->stProtectTimer.ucMode = VOS_RELTIMER_NOLOOP;
    pstRegEntity->stProtectTimer.ulTimerLen = IMSA_REG_TIMER_LEN_PROTECT;

    pstRegEntity->stRetryTimer.usName = TI_IMSA_REG_RETRY;
    pstRegEntity->stRetryTimer.ucMode = VOS_RELTIMER_NOLOOP;
    pstRegEntity->stRetryTimer.ulTimerLen = IMSA_REG_TIMER_LEN_RETRY;

    pstRegEntity->stPeriodTryRegTimer.usName = TI_IMSA_REG_PERIOD_TRY;
    pstRegEntity->stPeriodTryRegTimer.ucMode = VOS_RELTIMER_NOLOOP;
    pstRegEntity->stPeriodTryRegTimer.ulTimerLen = IMSA_REG_TIMER_LEN_PERIOD_TRY_REG;

    IMSA_RegAddrPairMgrInit(&pstRegEntity->stPairMgrCtx);
}


VOS_VOID IMSA_RegEntityDeinit(IMSA_REG_ENTITY_STRU *pstRegEntity)
{
    IMSA_INFO_LOG("IMSA_RegEntityDeinit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegEntityDeinit_ENUM, LNAS_ENTRY);

    if (IMSA_IsTimerRunning(&pstRegEntity->stProtectTimer))
    {
        IMSA_RegTimerStop(&pstRegEntity->stProtectTimer);
    }

    if (IMSA_IsTimerRunning(&pstRegEntity->stRetryTimer))
    {
        IMSA_RegTimerStop(&pstRegEntity->stRetryTimer);
    }

    if (IMSA_IsTimerRunning(&pstRegEntity->stPeriodTryRegTimer))
    {
        IMSA_RegTimerStop(&pstRegEntity->stPeriodTryRegTimer);
    }

    IMSA_RegAddrPairMgrDeinit(&pstRegEntity->stPairMgrCtx);

    IMSA_RegEntityInit(pstRegEntity);
}


VOS_VOID IMSA_RegMgrInit(VOS_VOID)
{
    IMSA_REG_MANAGER_STRU *pstRegCtx = IMSA_RegCtxGet();

    IMSA_INFO_LOG("IMSA_RegMgrInit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegMgrInit_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET(pstRegCtx, 0, sizeof(IMSA_REG_MANAGER_STRU));

    IMSA_RegEntityInit(&pstRegCtx->stNormalRegEntity);
    pstRegCtx->stNormalRegEntity.enRegType = IMSA_REG_TYPE_NORMAL;
    IMSA_RegEntityInit(&pstRegCtx->stEmcRegEntity);
    pstRegCtx->stEmcRegEntity.enRegType = IMSA_REG_TYPE_EMC;
}


VOS_VOID IMSA_RegMgrDeinit( VOS_VOID )
{
    IMSA_REG_MANAGER_STRU *pstRegCtx = IMSA_RegCtxGet();

    IMSA_INFO_LOG("IMSA_RegMgrDeinit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_RegMgrDeinit_ENUM, LNAS_ENTRY);

    IMSA_RegEntityDeinit(&pstRegCtx->stNormalRegEntity);
    pstRegCtx->stNormalRegEntity.enRegType = IMSA_REG_TYPE_NORMAL;
    IMSA_RegEntityDeinit(&pstRegCtx->stEmcRegEntity);
    pstRegCtx->stEmcRegEntity.enRegType = IMSA_REG_TYPE_EMC;

    pstRegCtx->stImsMsg.bitOpImsMsg = VOS_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_RegPrintNrmRegState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lihong00150010    2013-08-29  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_RegPrintNrmRegState( VOS_VOID )
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_NORMAL);

    switch (pstRegEntity->enStatus)
    {
        case IMSA_REG_STATUS_NOT_REGISTER:
            IMSA_INFO_LOG("Current Normal Reg State: NOT REGISTER");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_REG_STATUS_REGISTERING:
            IMSA_INFO_LOG("Current Normal Reg State: REGISTERING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_REG_STATUS_REGISTERED:
            IMSA_INFO_LOG("Current Normal Reg State: REGISTERED");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_REG_STATUS_DEREGING:
            IMSA_INFO_LOG("Current Normal Reg State: DEREGISTERING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_REG_STATUS_WAIT_RETRY:
            IMSA_INFO_LOG("Current Normal Reg State: WATI RETRY");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_WAIT_RETRY);
            break;
        case IMSA_REG_STATUS_PENDING:
            IMSA_INFO_LOG("Current Normal Reg State: PENDING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_PENDING);
            break;
        case IMSA_REG_STATUS_ROLLING_BACK:
            IMSA_INFO_LOG("Current Normal Reg State: ROLLING BACK");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_ROLLING_BACK);
            break;
        default:
            IMSA_INFO_LOG("Current Normal Reg State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintNrmRegState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_RegPrintEmcRegState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lihong00150010    2013-08-29  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_RegPrintEmcRegState( VOS_VOID )
{
    IMSA_REG_ENTITY_STRU *pstRegEntity = VOS_NULL_PTR;

    pstRegEntity = IMSA_RegEntityGetByType(IMSA_REG_TYPE_EMC);

    switch (pstRegEntity->enStatus)
    {
        case IMSA_REG_STATUS_NOT_REGISTER:
            IMSA_INFO_LOG("Current Emc Reg State: NOT REGISTER");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_REG_STATUS_REGISTERING:
            IMSA_INFO_LOG("Current Emc Reg State: REGISTERING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_REG_STATUS_REGISTERED:
            IMSA_INFO_LOG("Current Emc Reg State: REGISTERED");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_REG_STATUS_DEREGING:
            IMSA_INFO_LOG("Current Emc Reg State: DEREGISTERING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_REG_STATUS_WAIT_RETRY:
            IMSA_INFO_LOG("Current Emc Reg State: WAIT RETRY");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_WAIT_RETRY);
            break;
        case IMSA_REG_STATUS_PENDING:
            IMSA_INFO_LOG("Current Emc Reg State: PENDING");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_PENDING);
            break;
        case IMSA_REG_STATUS_ROLLING_BACK:
            IMSA_INFO_LOG("Current Emc Reg State: ROLLING BACK");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_ROLLING_BACK);
            break;
        default:
            IMSA_INFO_LOG("Current Emc Reg State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_RegPrintEmcRegState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID IMSA_SndRegErrLogInfo
(
    IMSA_ERR_LOG_REG_FAIL_STRU  stImsRegRstEvent
)
{
    IMSA_REG_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_REG_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsg), 0, \
                                IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_REG_ERROR_LOG_IND);

    IMSA_MEM_CPY(&pstMsg->stImsaRegErrlog, &stImsRegRstEvent, sizeof(IMSA_ERR_LOG_REG_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}
VOS_VOID IMSA_SndNotInitRegErrLogInfo
(
    IMSA_ERR_LOG_NOT_INIT_REG_STRU  stImsRegRstEvent
)
{
    IMSA_NOT_INIT_REG_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndNotInitRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NOT_INIT_REG_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndNotInitRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsg), 0, \
                                IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NOT_INIT_REG_ERR_LOG_IND);

    IMSA_MEM_CPY(&pstMsg->stImsaNotInitReg, &stImsRegRstEvent, sizeof(IMSA_ERR_LOG_NOT_INIT_REG_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}
VOS_VOID IMSA_SndNormPdnConnFailErrLogInfo
(
    IMSA_ERR_LOG_PDN_CONN_FAIL_STRU  stImsaPdnConnFail
)
{
    IMSA_NORM_PDN_CONN_FAIL_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndNotInitRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORM_PDN_CONN_FAIL_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndNotInitRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsg), 0, \
                                IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NORM_PDN_CONN_REJ_ERR_LOG_IND);

    IMSA_MEM_CPY(&pstMsg->stImsaPdnConnFail, &stImsaPdnConnFail, sizeof(IMSA_ERR_LOG_PDN_CONN_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}
VOS_VOID IMSA_SndNormRegFailErrLogInfo
(
    IMSA_ERR_LOG_NORM_REG_FAIL_STRU  stImsaNormRegFail
)
{
    IMSA_NORM_REG_FAIL_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndNotInitRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORM_REG_FAIL_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndNotInitRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsg), 0, \
                                IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NORM_REG_FAIL_ERR_LOG_IND);

    IMSA_MEM_CPY(&pstMsg->stImsaNormRegFail, &stImsaNormRegFail, sizeof(IMSA_ERR_LOG_NORM_REG_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}
VOS_VOID IMSA_SndNormInitDeregErrLogInfo
(
    IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU  stImsaNormInitDereg
)
{
    IMSA_NORM_INIT_DEREG_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    IMSA_NORM_LOG("IMSA_SndNotInitRegErrLogInfo:ENTER.");
    TLPS_PRINT2LAYER_INFO(IMSA_SndRegErrLogInfo_ENUM, LNAS_ENTRY);

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORM_INIT_DEREG_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndNotInitRegErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndRegErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsg), 0, \
                                IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NORM_REG_FAIL_ERR_LOG_IND);

    IMSA_MEM_CPY(&pstMsg->stImsaInitDereg, &stImsaNormInitDereg, sizeof(IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}
VOS_VOID IMSA_PdnRejErrRecord
(
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enPdnConnRejCause
)
{
    IMSA_ERR_LOG_REG_FAIL_STRU                              stImsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;


    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_REG_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_REG_FAIL_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    PS_MEM_SET(&stImsRegRstEvent, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsRegRstEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_REG_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* ö��ֵ��Ҫת�� */
    stImsRegRstEvent.enRegisterReason       = IMSA_ERR_LOG_REGISTER_REASON_BUTT;
    stImsRegRstEvent.enRegFailReason        = IMSA_ERR_LOG_REG_FAIL_REASON_BUTT;
    stImsRegRstEvent.enVopsStatus           = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsRegRstEvent.enPdnConnRejCause      = enPdnConnRejCause;
    stImsRegRstEvent.enPdnConnStatus        = IMSA_ConnState2ErrlogConnState(IMSA_CONN_GetNormalConnStatus());
    stImsRegRstEvent.enPsServiceStatus      = IMSA_PsSerStates2ErrlogPsStates(IMSA_GetPsServiceStatus());

    if (VOS_FALSE == pstControlMagnaer->ucImsaUsimStatus)
    {
        stImsRegRstEvent.enUsimStatus = IMSA_USIM_STATUS_UNAVAILABLE;
    }
    else
    {
        stImsRegRstEvent.enUsimStatus = IMSA_USIM_STATUS_AVAILABLE;
    }

    /* ������HIDS */
    IMSA_SndRegErrLogInfo(stImsRegRstEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_PdnRejErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_PdnRejErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}

VOS_VOID IMSA_RegErrRecord
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8 enRegFailReason
)
{
    IMSA_ERR_LOG_REG_FAIL_STRU                              stImsRegRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};


    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_REG_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_REG_FAIL_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET(&stImsRegRstEvent, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsRegRstEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_REG_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* ö��ֵ��Ҫת�� */
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        stImsRegRstEvent.enRegisterReason       = IMSA_RegAddrType2ErrlogRegReason(pstControlMagnaer->enNrmAddrType);
    }
    else
    {
        stImsRegRstEvent.enRegisterReason       = IMSA_RegAddrType2ErrlogRegReason(pstControlMagnaer->enEmcAddrType);
    }
    stImsRegRstEvent.enRegFailReason        = enRegFailReason;
    stImsRegRstEvent.enVopsStatus           = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsRegRstEvent.enPdnConnRejCause      = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;
    stImsRegRstEvent.enPdnConnStatus        = IMSA_ConnState2ErrlogConnState(IMSA_CONN_GetNormalConnStatus());
    stImsRegRstEvent.enPsServiceStatus      = IMSA_PsSerStates2ErrlogPsStates(IMSA_GetPsServiceStatus());

    if (VOS_FALSE == pstControlMagnaer->ucImsaUsimStatus)
    {
        stImsRegRstEvent.enUsimStatus = IMSA_USIM_STATUS_UNAVAILABLE;
    }
    else
    {
        stImsRegRstEvent.enUsimStatus = IMSA_USIM_STATUS_AVAILABLE;
    }

    if (VOS_TRUE == IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_NORMAL, aucUeAddr, aucPcscfAddr))
    {
        IMSA_MEM_CPY(stImsRegRstEvent.aucPcscfAddr,
                     aucPcscfAddr,
                     IMSA_IPV6_ADDR_STRING_LEN+1);
    }
    /* HIDS���� */
    IMSA_SndRegErrLogInfo(stImsRegRstEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsRegRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}


VOS_VOID IMSA_NotInitRegErrRecord
(
    VOS_VOID
)
{
    IMSA_ERR_LOG_NOT_INIT_REG_STRU      stImsNotInitRegEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;


    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_NOT_INIT_REG_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_NOT_INIT_REG_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET(&stImsNotInitRegEvent, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNotInitRegEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_NOT_INIT_REG_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    /* ö��ֵ��Ҫת�� */
    stImsNotInitRegEvent.stRegConditionStatus.enVopsStatus               = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsNotInitRegEvent.stRegConditionStatus.enPsServiceStatus          = IMSA_PsSerStates2ErrlogPsStates(IMSA_GetPsServiceStatus());
    stImsNotInitRegEvent.stRegConditionStatus.enImsaCampedRatType        = pstControlMagnaer->stImsaNetworkInfo.enImsaCampedRatType;
    stImsNotInitRegEvent.stRegConditionStatus.enVoiceDomain              = (IMSA_ERR_LOG_VOICE_DOMAIN_ENUM_UINT8)pstControlMagnaer->stImsaConfigPara.enVoiceDomain;
    stImsNotInitRegEvent.stRegConditionStatus.ucImsSupportFlag           = (VOS_UINT8)IMSA_SRV_IsCurRatSupportIms();
    stImsNotInitRegEvent.stRegConditionStatus.ucIsSupportRoamNotRegFlag  = pstControlMagnaer->stImsaConfigPara.ucRoamingImsNotSupportFlag;
    stImsNotInitRegEvent.stRegConditionStatus.ucIsRoamingFlag            = pstControlMagnaer->stImsaNetworkInfo.ucImsaRoamingFlg;


    if (IMSA_OP_TRUE == pstControlMagnaer->stImsaCommonInfo.bitOpHomeNetDomainName)
    {
        stImsNotInitRegEvent.stRegConditionStatus.ucHomeNetDomainNameValid = IMSA_TRUE;
    }

    if (IMSA_OP_TRUE == pstControlMagnaer->stImsaCommonInfo.stImsaUeId.bitOpImpi)
    {
        stImsNotInitRegEvent.stRegConditionStatus.ucImpiValid = IMSA_TRUE;
    }

    if (IMSA_OP_TRUE == pstControlMagnaer->stImsaCommonInfo.stImsaUeId.bitOpTImpu)
    {
        stImsNotInitRegEvent.stRegConditionStatus.ucImpuValid = IMSA_TRUE;
    }

    if (VOS_FALSE == pstControlMagnaer->ucImsaUsimStatus)
    {
        stImsNotInitRegEvent.stRegConditionStatus.enUsimStatus = IMSA_USIM_STATUS_UNAVAILABLE;
    }
    else
    {
        stImsNotInitRegEvent.stRegConditionStatus.enUsimStatus = IMSA_USIM_STATUS_AVAILABLE;
    }

    /* �������ע�������״̬û�з����仯������Ҫ�ظ��ϱ� */
    if (VOS_FALSE == (IMSA_MEM_CMP(  &stImsNotInitRegEvent.stRegConditionStatus,
                                    &pstControlMagnaer->stRegConditionStatus,
                                    sizeof(IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU))))
    {
        return;
    }

    IMSA_MEM_CPY(   &pstControlMagnaer->stRegConditionStatus,
                    &stImsNotInitRegEvent.stRegConditionStatus,
                    sizeof(IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU));

    /* HIDS���� */
    IMSA_SndNotInitRegErrLogInfo(stImsNotInitRegEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNotInitRegEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}


VOS_VOID IMSA_NormPdnConnRejErrRecord
(
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32      enPdnConnRejCause,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enNwRejCause
)
{
    IMSA_ERR_LOG_PDN_CONN_FAIL_STRU     stImsNormPdnConnRejEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_PDN_CONN_REJ_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_PDN_CONN_FAIL_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET(&stImsNormPdnConnRejEvent, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNormPdnConnRejEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_PDN_CONN_REJ_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsNormPdnConnRejEvent.enPdnConnRejCause  = enPdnConnRejCause;
    stImsNormPdnConnRejEvent.enNwRejCause       = enNwRejCause;

    /* HIDS���� */
    IMSA_SndNormPdnConnFailErrLogInfo(stImsNormPdnConnRejEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNormPdnConnRejEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}


VOS_VOID IMSA_NormRegFailErrRecord
(
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8 enRegFailReason,
    VOS_UINT16                              usSipStatusCode,
    VOS_UINT32                              ulRetryTimerLen
)
{
    IMSA_ERR_LOG_NORM_REG_FAIL_STRU     stImsNormRegEvent;
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_REG_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                   = IMSA_GetControlManagerAddress();
    pstNormalConn                       = IMSA_CONN_GetNormalConnAddr();

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_NORM_REG_FAIL_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET(&stImsNormRegEvent, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNormRegEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_REG_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsNormRegEvent.enImsaCampedRatType   = pstControlMagnaer->stImsaNetworkInfo.enImsaCampedRatType;
    stImsNormRegEvent.enRegisterAddrType    = IMSA_RegAddrType2ErrlogRegReason(pstControlMagnaer->enNrmAddrType);
    stImsNormRegEvent.enRegFailReason       = enRegFailReason;
    stImsNormRegEvent.usSipStatusCode       = usSipStatusCode;
    stImsNormRegEvent.ulRetryTimerLen       = ulRetryTimerLen;
    stImsNormRegEvent.ucIsApnChangeFlag     = pstNormalConn->ucIsApnChanged;

    if (VOS_TRUE == IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_NORMAL, aucUeAddr, aucPcscfAddr))
    {
        IMSA_MEM_CPY(stImsNormRegEvent.aucPcscfAddr,
                     aucPcscfAddr,
                     IMSA_IPV6_ADDR_STRING_LEN+1);
    }

    /* HIDS���� */
    IMSA_SndNormRegFailErrLogInfo(stImsNormRegEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNormRegEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}


VOS_VOID IMSA_NormInitDeregErrRecord
(
    IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32  enInitDeregCause
)
{
    IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU  stImsNormInitDeregEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_INIT_DEREG_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET(&stImsNormInitDeregEvent, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNormInitDeregEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_INIT_DEREG_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsNormInitDeregEvent.enImsaCampedRatType = pstControlMagnaer->stImsaNetworkInfo.enImsaCampedRatType;
    stImsNormInitDeregEvent.enInitDeregCause    = enInitDeregCause;

    /* HIDS���� */
    IMSA_SndNormInitDeregErrLogInfo(stImsNormInitDeregEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNormInitDeregEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_RegErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_RegErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}

VOS_VOID IMSA_PdnConnFailErrLogRecord
(
    IMSA_CONN_TYPE_ENUM_UINT32                      enConnType,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32      enPdnConnRejCause,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enNwRejCause,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enEmcRegFailReason
)
{
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_NormPdnConnRejErrRecord(enPdnConnRejCause,
                                     enNwRejCause);
    }
    else
    {
        IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                enEmcRegFailReason,
                                enNwRejCause,
                                VOS_FALSE,
                                VOS_FALSE,
                                IMSA_ERR_LOG_CALL_STATUS_IDLE);
    }
}


VOS_VOID IMSA_RegFailErrLogRecord
(
    IMSA_REG_TYPE_ENUM_UINT8                        enRegType,
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8         enNormRegFailReason,
    VOS_UINT16                                      usSipStatusCode,
    VOS_UINT32                                      ulRetryTimerLen,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enEmcRegFailReason
)
{
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        IMSA_NormRegFailErrRecord(enNormRegFailReason,
                                  usSipStatusCode,
                                  ulRetryTimerLen);
    }
    else
    {
        /* ���IMSע��ʧ�ܣ����¼����ʧ�� */
        IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                enEmcRegFailReason,
                                IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                VOS_FALSE,
                                usSipStatusCode,
                                IMSA_ERR_LOG_CALL_STATUS_IDLE);
    }
}


#endif
/*lint +e961*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaRegManagement.c */
