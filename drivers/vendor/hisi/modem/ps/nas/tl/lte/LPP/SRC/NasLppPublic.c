

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsCommonDef.h"
#include    "PsTypeDef.h"
#include    "NasLppPublic.h"
#include    "NasCommPrint.h"
#include    "LNasNvInterface.h"
#include    "LNvCommon.h"
#include    "PsLogdef.h"
#include    "NasLppOm.h"
#include    "NasLppTimerMsgProc.h"
#include    "NasLppSendMsg.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLPPPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPPUBLIC_C
/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
NAS_LPP_ENTITY_STRU     g_stNasLppEntity; /*LPP ʵ�嶨��*/
LPP_MESSAGE_STRU        stLppMsgBuff;


/*״̬���Ķ�ʱ���ĺ�����*/
NAS_LPP_TIMER_PROC_FUNC g_afNasLppTimerFun[TI_NAS_LPP_TIMER_PARA_BUTT] = {0};

/* ״̬��ʱ���ĳ��ȡ����ڶ�ʱ���ĳ��ȷֱ�ŵ�transaction��seesion��*/
VOS_UINT32 g_aulTimerLen[TI_NAS_LPP_STATE_TIMER_MAX_NUM] = {0};



/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e701*/

VOS_VOID  NAS_LPP_ReadLppNvConfig( VOS_VOID)
{
    LNAS_LPP_NV_CONFIG_PARA_STRU        stNvLppConfig;
    VOS_UINT32                          ulRslt;
    NAS_LPP_NV_CONFIG_STRU             *pstLppNvParaConfig = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_ReadLppNvConfig enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ReadLppNvConfig_ENUM, LNAS_LPP_ReadLppNvConfigEnter);
    pstLppNvParaConfig = NAS_LPP_GetLppNvParaConfig();

    ulRslt = LPP_NV_Read(EN_NV_ID_LPP_PARA_CONFIG, &stNvLppConfig,\
                 sizeof(LNAS_LPP_NV_CONFIG_PARA_STRU));

    if(ulRslt == VOS_OK)
    {
        /*����NV��������*/
        pstLppNvParaConfig->usAttempeTransCnt  = stNvLppConfig.usAttempeTransCnt;
        NAS_LPP_ModifyTimerLen(TI_NAS_LPP_UPLINK_MSG_RETRANS,
                               PS_NULL_UINT8,
                               PS_NULL_UINT8,
                               stNvLppConfig.usReTransTimerLen);
        pstLppNvParaConfig->ucLppLayerSwitch    = stNvLppConfig.ucLppLayerSwitch;
        pstLppNvParaConfig->ucLppLayerNorm      = stNvLppConfig.ucLppLayerNorm;
        pstLppNvParaConfig->ucLppLayerInfo      = stNvLppConfig.ucLppLayerInfo;
        pstLppNvParaConfig->ucLppLayerWarn      = stNvLppConfig.ucLppLayerWarn;
        pstLppNvParaConfig->ucLppLayerErr       = stNvLppConfig.ucLppLayerErr;
    }
    else
    {
        NAS_LPP_WARN_LOG("NAS_LPP_ReadLppNvConfig, Read NV Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_ReadLppNvConfig_ENUM, LNAS_LPP_ReadLppNvConfigReadNVError);
        /*��NV���ɹ������ó�ʼֵ*/
        pstLppNvParaConfig->usAttempeTransCnt  = 3; /*Ĭ��������Ϣ�������β��ɹ������ٳ���*/
        NAS_LPP_ModifyTimerLen(TI_NAS_LPP_UPLINK_MSG_RETRANS,
                               PS_NULL_UINT8,
                               PS_NULL_UINT8,
                               250);/*�ش���ʱ��ʱ����Ĭ������250ms*/
        pstLppNvParaConfig->ucLppLayerSwitch    = NAS_LPP_SLCT;
        pstLppNvParaConfig->ucLppLayerNorm      = NAS_LPP_NO_SLCT;
        pstLppNvParaConfig->ucLppLayerInfo      = NAS_LPP_NO_SLCT;
        pstLppNvParaConfig->ucLppLayerWarn      = NAS_LPP_SLCT;
        pstLppNvParaConfig->ucLppLayerErr       = NAS_LPP_SLCT;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_TimerReg
 Description     :  ��ʱ���Ǽǵ���
 Input           : ulTimerLen:��Ҫ����Э��LPP��Ϣ����ȷ����Э�鶨ʱ�����ȣ�����ֵ��Ϊ0;
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-7-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_TimerReg
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    NAS_LPP_TIMER_PROC_FUNC             fFun,
    VOS_UINT32                          ulTimerLen

)
{
    if (enTimeName >= TI_NAS_LPP_TIMER_PARA_BUTT)
    {
        NAS_LPP_ERR_LOG1("TimerReg with wrong timer name", enTimeName);
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerReg_ENUM, LNAS_LPP_TimerRegInvalidTimerName);
        return;
    }
    g_afNasLppTimerFun[enTimeName] = fFun;

    if (enTimeName < TI_NAS_LPP_STATE_TIMER_MAX_NUM)
    {
        g_aulTimerLen[enTimeName] = ulTimerLen;
    }

}
/*****************************************************************************
 Function Name   : NAS_LPP_ModifyPrtclTimerLen
 Description     : �޸ĳ���״̬��ʱ��֮��Ķ�ʱ���ĳ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ModifyPrtclTimerLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT32                          ulTimerLen
)
{
    NAS_LPP_ENTITY_STRU                 *pstCtx;
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    pstCtx = NAS_LPP_GetLppEntityCtx();
    if ( TI_NAS_LPP_LOCATION_INVALID == enTimeName)
    {
        pstCtx->ulInvalidLen = ulTimerLen ;
        return;
    }

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("mod ptl timer len: don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenNotFindTransaction,ucTransIndx);
        return;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1(": period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenNotFindCFGIndex, pstTransElementEntity->ucCommCfgIndex);
        return;
    }

    switch (enTimeName)
    {
        case TI_NAS_LPP_RESPONSE_TIMER :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1(": response timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenReportOnceTimerTypeError, pstTransElementEntity->ucCommCfgIndex);
            }
            else
            {
                pstLppCommCfgInfo->stReportCriteria.u.stReportOnce.ulResponseTime = ulTimerLen;
            }
            break;
        }
        case TI_NAS_LPP_PERIODICAL_REPORT :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1(": period timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenPeriodTimerTypeError, pstTransElementEntity->ucCommCfgIndex);

            }
            else
            {
                pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ulReportIntraval = ulTimerLen;
            }
            break;
        }
        case TI_NAS_LPP_REPORT_DURATION :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1(": trigger timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenDurationTimerTypeError, pstTransElementEntity->ucCommCfgIndex);

            }
            else
            {
                pstLppCommCfgInfo->stReportCriteria.u.stReportTrigger.ulReportDuration = ulTimerLen;
            }
            break;
        }
        default:
            NAS_LPP_ERR_LOG("error timer name");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_ModifyPrtclTimerLen_ENUM, LNAS_LPP_ModifyPrtclTimerLenErrorTimerName);
            break;
    }


}

/*****************************************************************************
 Function Name   : NAS_LPP_ModifyTimerLen
 Description     : �޸Ķ�ʱ���ĳ���
 Input           : ������޸�״̬���Ķ�ʱ����ucSessionIndex��ucSessionTransIndx����0XFF.
                   �޸�Э�鶨ʱ����ucSessionIndex��ucSessionTransIndxҪ���Ӧ��ֵ.�����ʱ����transaction�޹أ�ucSessionTransIndxҲ�� 0xff��
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ModifyTimerLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT32                          ulTimerLen
)
{
    if (enTimeName >= TI_NAS_LPP_TIMER_PARA_BUTT)
    {
        NAS_LPP_ERR_LOG1("mod timer len with wrong timer name", enTimeName);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ModifyTimerLen_ENUM, LNAS_LPP_ModifyTimerLenErrorTimerName,enTimeName);
        return;
    }
    if (enTimeName < TI_NAS_LPP_STATE_TIMER_MAX_NUM)
    {
        g_aulTimerLen[enTimeName] = ulTimerLen;
    }
    else
    {   /*�޸�Э�鶨ʱ���ĳ���*/
        NAS_LPP_ModifyPrtclTimerLen(enTimeName,ucSessionIndex,ucSessionTransIndx,ulTimerLen);
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetTimerProcFun
 Description     : �õ���ʱ����Ӧ�Ĵ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-3  Draft Enact

*****************************************************************************/
NAS_LPP_TIMER_PROC_FUNC  NAS_LPP_GetTimerProcFun( NAS_LPP_TIMER_PARA_ENUM_UINT8 enTimeName )
{
    NAS_LPP_TIMER_PROC_FUNC pfTimerFun = NAS_LPP_NULL_PTR;

   if ( enTimeName < TI_NAS_LPP_TIMER_PARA_BUTT )
    {
         pfTimerFun = g_afNasLppTimerFun[enTimeName];

    }
    else
    {
        NAS_LPP_ERR_LOG1("Wrong timer type for distribute,timer type", enTimeName);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetTimerProcFun_ENUM, LNAS_LPP_GetTimerProcFunErrorTimerName,enTimeName);
    }

    return pfTimerFun;
}


VOS_UINT32  NAS_LPP_IsTimerNameValid
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ucSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    switch(enTimerType)
    {
        case TI_NAS_LPP_WAIT_EST_CNF:
        case TI_NAS_LPP_WAIT_RE_EST:
            return PS_TRUE;

        case TI_NAS_LPP_UPLINK_MSG_RETRANS:
        case TI_NAS_LPP_WAIT_CN_ASSIST_DATA:
        case TI_NAS_LPP_LOCATION_INVALID:
        case TI_NAS_LPP_WAIT_LRRC_MEAS_CNF:
        case TI_NAS_LPP_RESPONSE_TIMER:
        case TI_NAS_LPP_PERIODICAL_REPORT:
        case TI_NAS_LPP_REPORT_DURATION:
        case TI_NAS_LPP_WAIT_INTRA_DATE_CNF:
            if ((ulSessionIndex < NAS_LPP_MAX_SESSION_COUNT)
                && (ucSessionTransIndx < NAS_LPP_MAX_TRANS_COUNT))
            {
                return PS_TRUE;
            }
            break;



        default:
            break;
    }

    return PS_FALSE;
}


NAS_LPP_TIMER_STRU*  NAS_LPP_GetTimer
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ulSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
)

{
    NAS_LPP_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;

    /*���ݶ�ʱ����ͬ���ͣ���ȡ��ʱ��*/
    switch( enTimerType )
    {
        case TI_NAS_LPP_UPLINK_MSG_RETRANS:
        case TI_NAS_LPP_WAIT_CN_ASSIST_DATA:
        case TI_NAS_LPP_LOCATION_INVALID:
        case TI_NAS_LPP_WAIT_LRRC_MEAS_CNF:
        case TI_NAS_LPP_WAIT_INTRA_DATE_CNF:
            pstTimerInfo = NAS_LPP_GetTransactionTimer(ulSessionIndex, ulSessionTransIndx);
            break;

        case TI_NAS_LPP_RESPONSE_TIMER:
            pstTimerInfo = NAS_LPP_GetResPonseTimer((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ulSessionTransIndx);
            break;

        case TI_NAS_LPP_PERIODICAL_REPORT:
            pstTimerInfo = NAS_LPP_GetPeriodTimer((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ulSessionTransIndx);
            break;

        case TI_NAS_LPP_REPORT_DURATION:
            pstTimerInfo = NAS_LPP_GetDurationTimer((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ulSessionTransIndx);
            break;

        case TI_NAS_LPP_WAIT_EST_CNF:
        case TI_NAS_LPP_WAIT_RE_EST:
            pstTimerInfo = NAS_LPP_GetConnManageTimer();
            break;

        default :
            break;
    }

    return pstTimerInfo;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetPrtclTimeLen
 Description     : ��ȡЭ�鶨ʱ���ĳ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-5  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_GetPrtclTimeLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx
)
{
    NAS_LPP_ENTITY_STRU                 *pstCtx;
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;
    VOS_UINT32 ulLen = PS_NULL_UINT32;

    pstCtx = NAS_LPP_GetLppEntityCtx();
    if ( TI_NAS_LPP_LOCATION_INVALID == enTimeName)
    {
        return pstCtx->ulInvalidLen;
    }

    ucTransIndx = NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get ptl timer len: don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenNotFindTransaction, ucTransIndx);
        return ulLen;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("get period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorCFGIndex, pstTransElementEntity->ucCommCfgIndex);
        return ulLen;
    }

    switch (enTimeName)
    {
        case TI_NAS_LPP_RESPONSE_TIMER :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1("get response timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorReportTime, pstTransElementEntity->ucCommCfgIndex);

            }
            else
            {
                ulLen = pstLppCommCfgInfo->stReportCriteria.u.stReportOnce.ulResponseTime;
            }
            break;
        }
        case TI_NAS_LPP_PERIODICAL_REPORT :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1("get period timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorPeriodType, pstTransElementEntity->ucCommCfgIndex);
            }
            else
            {
                ulLen = pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.ulReportIntraval;
            }
            break;
        }
        case TI_NAS_LPP_REPORT_DURATION :
        {
            if (NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER != pstLppCommCfgInfo->stReportCriteria.enType)
            {
                NAS_LPP_ERR_LOG1("get trigger timer not match ! index",  pstTransElementEntity->ucCommCfgIndex);
                TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorTriggerType, pstTransElementEntity->ucCommCfgIndex);
            }
            else
            {
                ulLen = pstLppCommCfgInfo->stReportCriteria.u.stReportTrigger.ulReportDuration;
            }
            break;
        }
        default:
            NAS_LPP_ERR_LOG("get error timer name");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_GetPrtclTimeLen_ENUM, LNAS_LPP_GetPrtclTimeLenErrorTimerName);
            break;
    }

    return ulLen;
}



VOS_UINT32  NAS_LPP_GetTimerLen
(
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimeName,
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndx
)
{
    VOS_UINT32                  ulTimerLen   = 0;


    /*��ȡ״̬����ʱ������*/
    if (enTimeName < TI_NAS_LPP_STATE_TIMER_MAX_NUM)
    {
        ulTimerLen  = g_aulTimerLen[enTimeName];
    }
    else
    {
        ulTimerLen = NAS_LPP_GetPrtclTimeLen(enTimeName,ucSessionIndex,ucSessionTransIndx);
    }

    return ulTimerLen;
}
VOS_VOID NAS_LPP_TimerStart
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ucSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
)
{
    VOS_UINT32                  ulTimerLen   = 0;
    NAS_LPP_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                  ulTimerIndex = 0;

    TLPS_PRINT2LAYER_INFO(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartEnter);
    /*��ulIndex�Ϸ����ж�*/
    if (PS_FALSE == NAS_LPP_IsTimerNameValid(ulSessionIndex, ucSessionTransIndx, enTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_WARN_LOG("NAS_LPP_TimerStart: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerNameInvalid);
        return;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = NAS_LPP_GetTimer(ulSessionIndex, ucSessionTransIndx, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG("NAS_LPP_TimerStart:ERROR: Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerInfoError);
        return;
    }

    /*����timer index*/
    /*��16λ��transaction���������� ��16��session��������*/
    ulTimerIndex = (ucSessionTransIndx << 16) | (ulSessionIndex & 0x00ff);

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_LPP_WARN_LOG("NAS_LPP_TimerStart:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerCloseOldTimerFail);
            return;
        }

        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG2("(TimerType) Timer not close!",pstTimerInfo->enTimerId, ulTimerIndex);
        TLPS_PRINT2LAYER_INFO(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerCloseOldTimer);
    }

    /*���ݶ�ʱ����ͬ���ͣ���ʱ����Ϣ��ͬ*/
    ulTimerLen = NAS_LPP_GetTimerLen(enTimerType, (VOS_UINT8)ulSessionIndex,(VOS_UINT8)ucSessionTransIndx);
    if (0 == ulTimerLen)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG("NAS_LPP_TimerStart:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerGetTimerLenFail);
        return;
    }

    /*�趨��ʱ��NAME,enTimerType�趨��ʱ��Para����ʧ���򱨾�����*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimerInfo->hTimer),PS_PID_LPP,\
                                ulTimerLen, (VOS_UINT32)enTimerType,\
                                 ulTimerIndex, VOS_RELTIMER_NOLOOP))
    {
          /*��ӡ�쳣��Ϣ*/
          NAS_LPP_WARN_LOG("NAS_LPP_TimerStart:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStart_ENUM, LNAS_LPP_TimerStartTimerSetTimerFail);
          return;
    }

    /*���¶�ʱ��������Ϣ�Ͷ�ʱ�����*/
    pstTimerInfo->enTimerId     = enTimerType;


    /*������ǰ�Ķ�ʱ����Ϣ */
    NAS_LPP_OmTimerStartInd((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ucSessionTransIndx,enTimerType,ulTimerLen);

    /* ��ӡ��ʱ��������Ϣ */
    /*TODO*/
}


/*lint -e438*/
VOS_VOID NAS_LPP_TimerStop
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ulSessionTransIndx,
    NAS_LPP_TIMER_PARA_ENUM_UINT8       enTimerType
)

{
    NAS_LPP_TIMER_STRU         *pstTimerInfo = VOS_NULL_PTR;
    VOS_UINT32                 ulTimerRemainLen = 0;

    TLPS_PRINT2LAYER_INFO(NAS_LPP_TimerStop_ENUM, LNAS_LPP_TimerStopEnter);
    /*��ulIndex�Ϸ����ж�*/
    if (PS_FALSE == NAS_LPP_IsTimerNameValid(ulSessionIndex, ulSessionTransIndx, enTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_WARN_LOG("NAS_LPP_TimerStop: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStop_ENUM, LNAS_LPP_TimerStopTimerNameInvalid);
        return;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = NAS_LPP_GetTimer(ulSessionIndex, ulSessionTransIndx, enTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG("NAS_LPP_TimerStop:ERROR:Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStop_ENUM, LNAS_LPP_TimerStopTimerInfoError);
        return;
    }

    /*��ʱ�����ڴ�״̬����رգ����򣬺���*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerInfo->hTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_LPP_WARN_LOG("NAS_LPP_TimerStop:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_TimerStop_ENUM, LNAS_LPP_TimerStopTimerFailToCloseTimer);
            return;
        }

        /*������ǰ�Ķ�ʱ����Ϣ */
        NAS_LPP_OmTimerStopInd((VOS_UINT8)ulSessionIndex,(VOS_UINT8)ulSessionTransIndx,enTimerType,ulTimerRemainLen);

        /* ��ӡ��ʱ���ر���Ϣ */
        /*TODO*/
    }
}
/*lint +e438*/

NAS_LPP_ENTITY_STRU*  NAS_LPP_GetLppEntityCtx( VOS_VOID )
{
    return (&g_stNasLppEntity);
}


VOS_VOID  NAS_LPP_ClearLppMsgBuff( VOS_VOID )
{
    NAS_LPP_MEM_SET(&stLppMsgBuff, 0, sizeof(LPP_MESSAGE_STRU));

    return;
}


LPP_MESSAGE_STRU*  NAS_LPP_GetLppMsgBuff( VOS_VOID )
{
    NAS_LPP_ClearLppMsgBuff();
    return (&stLppMsgBuff);
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetCommCfgInfoPool
 Description     : ��ȡcommon�����ò�����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
NAS_LPP_COMM_CONFIG_INFO_POOL_STRU *NAS_LPP_GetCommCfgInfoPool( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig.stCommCfgInfoPool);
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLocationReq
 Description     : ��ȡ�洢��location information request����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
NAS_LPP_LOCATION_REQ_STRU  *NAS_LPP_GetLocationReqBuff( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig.stLocationReq);
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetOtdoaAssisCfg
 Description     : ��ȡ�洢��otdoa��assistant data
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
NAS_LPP_OTDOA_ASSIST_CFG_STRU *NAS_LPP_GetOtdoaAssisCfg( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig.stOtdoaAssisCfg);
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetServingCell
 Description     : ��ȡ����С������Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-18  Draft Enact

*****************************************************************************/
NAS_LPP_SERVING_CELL_STRU *NAS_LPP_GetServingCell( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig.stServingCell);
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetCfgPara
 Description     : ��ȡ���ò����ĵ�ַ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
NAS_LPP_CONFIG_PARA_STRU *NAS_LPP_GetCfgPara( VOS_VOID )
{
    return &(g_stNasLppEntity.stLppConfig);
}

/*****************************************************************************
 Function Name   : NAS_LPP_LppCtxInit
 Description     : ��ʼ��LPP��context
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_LppCtxInit( VOS_VOID )
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;
    VOS_UINT32  ulLoop;
    VOS_UINT32  ulLoop1 = 0;

    NAS_LPP_ERR_LOG("NAS_LPP_LppCtxInit enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LppCtxInit_ENUM, LNAS_LPP_LppCtxInitEnter);
    pstLppCtx = NAS_LPP_GetLppEntityCtx();

    NAS_LPP_MEM_SET(pstLppCtx, 0, sizeof(NAS_LPP_ENTITY_STRU));

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_POS_TECH; ulLoop++ )
    {
        pstLppCtx->stLppConfig.stCommCfgInfoPool.astLppCommCfgInfo[ulLoop].stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_BUTT;
    }

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_TRANS_POOL_COUNT; ulLoop++ )
    {
        pstLppCtx->stTransEntityPool.astTransElementEntity[ulLoop].enLastUpMsgId = NAS_LPP_AIR_MSG_BUTT;
        pstLppCtx->stTransEntityPool.astTransElementEntity[ulLoop].ucCommCfgIndex = PS_NULL_UINT8;
    }

    /*��ʼ��ÿ��session���transactionindex*/
    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        for (ulLoop1 = 0; ulLoop1 <NAS_LPP_MAX_TRANS_COUNT ;ulLoop1++)
        {
            pstLppCtx->stSessionEntityPool.astLppSessionEntity[ulLoop].stLppTrans.aucTransElementIdx[ulLoop1] = PS_NULL_UINT8;
        }
    }

    /*��ʼ��timer*/
    NAS_LPP_TimerInit();


}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLppSessionEntityPool
 Description     : ��ȡsession pool
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/

NAS_LPP_SESSION_ENTITY_POOL_STRU* NAS_LPP_GetLppSessionEntityPool( VOS_VOID )
{
    return (&(g_stNasLppEntity.stSessionEntityPool));
}


/*****************************************************************************
 Function Name   : NAS_LPP_GetLppTransEntityPool
 Description     : ��ȡtrans pool
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ENTITY_POOL_STRU * NAS_LPP_GetLppTransEntityPool( VOS_VOID )
{
    return (&(g_stNasLppEntity.stTransEntityPool));
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetRuningPosTch
 Description     : ��ȡ�������еĶ�λ����
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
NAS_LPP_LOC_TECH_RUNING_STRU  *NAS_LPP_GetRuningLocTech( VOS_VOID )
{
    return (&(g_stNasLppEntity.stRuningLocTech));
}


/*****************************************************************************
 Function Name   : NAS_LPP_GetLppUpMsgBuffPool
 Description     :  ��ȡ�ش��ĵ�ַ
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
NAS_LPP_UP_MSG_BUFF_POOL_STRU * NAS_LPP_GetLppUpMsgBuffPool( VOS_VOID )
{
    return (&(g_stNasLppEntity.stUpMsgBuffPool));
}


NAS_LPP_CONN_STATUS_ENUM_UINT32  NAS_LPP_GetLppConnStatus( VOS_VOID )
{
    return (NAS_LPP_GetLppEntityCtx()->stLppConnManage.enConectStatus);
}


VOS_VOID  NAS_LPP_SetLppConnStatus(NAS_LPP_CONN_STATUS_ENUM_UINT32 enConnStatus)
{
    NAS_LPP_INFO_LOG1("NAS_LPP_SetLppConnStatus: CONN STATUS =!", enConnStatus);
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_SetLppConnStatus_ENUM,LNAS_LPP_SetLppConnStatusHandle,enConnStatus);
    NAS_LPP_GetLppEntityCtx()->stLppConnManage.enConectStatus = enConnStatus;

    return;
}


NAS_LPP_NV_CONFIG_STRU*  NAS_LPP_GetLppNvParaConfig(VOS_VOID)
{

    return &(NAS_LPP_GetLppEntityCtx()->stLppNvConfig);
}


VOS_UINT32  NAS_LPP_GetLppTransAttepCnt(VOS_VOID)
{
    VOS_UINT32      usAttempeTransCnt = 0;

    usAttempeTransCnt = NAS_LPP_GetLppEntityCtx()->stLppNvConfig.usAttempeTransCnt;
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetLppTransAttepCnt_ENUM, LNAS_LPP_GetLppTransAttepCnt, usAttempeTransCnt);

    return usAttempeTransCnt;
}


VOS_UINT8  NAS_LPP_GetLppLayerSwitchFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerSwitch);
}


VOS_UINT8  NAS_LPP_GetLppLayerNormFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerNorm);
}


VOS_UINT8  NAS_LPP_GetLppLayerInfoFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerInfo);
}


VOS_UINT8  NAS_LPP_GetLppLayerWarnFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerWarn);
}


VOS_UINT8  NAS_LPP_GetLppLayerErrFlag(VOS_VOID)
{

    return (NAS_LPP_GetLppEntityCtx()->stLppNvConfig.ucLppLayerErr);
}


VOS_UINT32  NAS_LPP_GetLppIntraDataCnfTimerLen(VOS_VOID)
{
    /*���ڲ�data cnf��ʱ����ڽ��������������ĵȴ�������ʱ��ʱ��10s��Ȼ�����1000ת�ɺ���*/
    /* ��������Ϊ0ʱ��ȱʡΪ1 */
    if ( 0 == NAS_LPP_GetLppTransAttepCnt())
    {
        return 10 * 1000;
    }
    return (NAS_LPP_GetLppTransAttepCnt()* 10 * 1000);
}


VOS_UINT32  NAS_LPP_GetTransLppMsgCnt( VOS_VOID )
{
    VOS_UINT32      ulEstOrDataCnt = 0;

    ulEstOrDataCnt = NAS_LPP_GetLppEntityCtx()->stLppConnManage.ulEstOrDataCnt;
    TLPS_PRINT2LAYER_INFO1(NAS_LPP_GetTransLppMsgCnt_ENUM, LNAS_LPP_GetTransLppMsgCnt, ulEstOrDataCnt);

    return ulEstOrDataCnt;
}


VOS_VOID  NAS_LPP_TransLppMsgAddCnt(VOS_VOID)
{
    NAS_LPP_GetLppEntityCtx()->stLppConnManage.ulEstOrDataCnt += 1;

    return;
}


VOS_VOID  NAS_LPP_ClearLppTransCnt(VOS_VOID)
{
    NAS_LPP_GetLppEntityCtx()->stLppConnManage.ulEstOrDataCnt = 0;

    return;
}



NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*  NAS_LPP_GetSessionEntity
(
    VOS_UINT32                          ulSessionIndex
)
{
    if (NAS_LPP_MAX_SESSION_COUNT <= ulSessionIndex)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_GetSessionEntity_ENUM, LNAS_LPP_GetSessionEntityIncorrectIndex);
        return  NAS_LPP_NULL_PTR;
    }
    return &(NAS_LPP_GetLppEntityCtx()->stSessionEntityPool.astLppSessionEntity[ulSessionIndex]);
}


VOS_UINT8  NAS_LPP_GetTransIdIndex
(
    VOS_UINT8                          ucSessionIndex,
    VOS_UINT8                          ucSessionTransIndex
)
{
    VOS_UINT8 ucIndex = PS_NULL_UINT8;

    if ( (ucSessionIndex >= NAS_LPP_MAX_SESSION_COUNT)||(ucSessionTransIndex >= NAS_LPP_MAX_TRANS_COUNT))
    {
        NAS_LPP_ERR_LOG2("Get trans index with wrong ulSessionIndex,ulSessionTransIndex", ucSessionIndex, ucSessionTransIndex);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetTransIdIndex_ENUM, LNAS_LPP_GetTransIdIndexErrorIndexValue, ucSessionIndex, ucSessionTransIndex);
        return ucIndex;
    }

    ucIndex = NAS_LPP_GetSessionEntity(ucSessionIndex)->stLppTrans.aucTransElementIdx[ucSessionTransIndex];

    return ucIndex;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetTransEntity
 Description     : ��ȡtransaction��ʵ��ָ��
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU  *NAS_LPP_GetTransEntity
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ulSessionTransIndex
)
{
    VOS_UINT8                                   ucTransIndex = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity = NAS_LPP_NULL_PTR;

    /*ȡ��session��transactionʵ���д洢��Ԫ��index*/
    ucTransIndex = (VOS_UINT8)NAS_LPP_GetTransIdIndex((VOS_UINT8)ulSessionIndex, (VOS_UINT8)ulSessionTransIndex);

    /*����indexȥ�õ��ڴ���е�transactionʵ��*/
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);

    return pstTransElementEntity;
}


NAS_LPP_TIMER_STRU*  NAS_LPP_GetTransactionTimer
(
    VOS_UINT32                          ulSessionIndex,
    VOS_UINT32                          ulSessionTransIndx
)
{
    VOS_UINT8                                   ucTransIndex = 0;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity = NAS_LPP_NULL_PTR;

    /*ȡ��session��transactionʵ���д洢��Ԫ��index*/
    ucTransIndex = (VOS_UINT8)NAS_LPP_GetTransIdIndex((VOS_UINT8)ulSessionIndex, (VOS_UINT8)ulSessionTransIndx);

    /*����indexȥ�õ��ڴ���е�transactionʵ��*/
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);

    return &(pstTransElementEntity->stLppTimer);
}


NAS_LPP_TIMER_STRU*  NAS_LPP_GetResPonseTimer
(
    VOS_UINT8                          ucSessionIndex,
    VOS_UINT8                          ucSessionTransIndx
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get response timer : don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetResPonseTimer_ENUM, LNAS_LPP_GetResPonseTimerNotFindTransaction, ucSessionIndex, ucSessionTransIndx);
        return NAS_LPP_NULL_PTR;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("response don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetResPonseTimer_ENUM, LNAS_LPP_GetResPonseTimerCFGIndexError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    if (NAS_LPP_REPORT_LOCATION_TYPE_ONCE != pstLppCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ERR_LOG1("get response don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetResPonseTimer_ENUM, LNAS_LPP_GetResPonseTimerCFGTypeError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    return &(pstLppCommCfgInfo->stReportCriteria.u.stReportOnce.stLppTimer);
}


NAS_LPP_TIMER_STRU*  NAS_LPP_GetPeriodTimer
(
    VOS_UINT8                          ucSessionIndex,
    VOS_UINT8                          ucSessionTransIndx
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get period timer : don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetPeriodTimer_ENUM, LNAS_LPP_GetPeriodTimerNOTFindTransaction, ucSessionIndex, ucSessionTransIndx);
        return NAS_LPP_NULL_PTR;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPeriodTimer_ENUM, LNAS_LPP_GetPeriodTimerCFGIndexError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    if (NAS_LPP_REPORT_LOCATION_TYPE_PERIOD != pstLppCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ERR_LOG1("get period don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetPeriodTimer_ENUM, LNAS_LPP_GetPeriodTimerCFGReportTypeError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    return &(pstLppCommCfgInfo->stReportCriteria.u.stReportPeriod.stLppTimer);
}



NAS_LPP_TIMER_STRU*  NAS_LPP_GetDurationTimer
(
    VOS_UINT8                          ucSessionIndex,
    VOS_UINT8                          ucSessionTransIndx
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get duration timer : don't find TransEntity!", ucSessionIndex, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetDurationTimer_ENUM, LNAS_LPP_GetDurationTimerNOTFindTransaction, ucSessionIndex, ucSessionTransIndx);
        return NAS_LPP_NULL_PTR;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("duration don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetDurationTimer_ENUM, LNAS_LPP_GetDurationTimerCFGIndexError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    if (NAS_LPP_REPORT_LOCATION_TYPE_TRIGGER != pstLppCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ERR_LOG1("get duration don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetDurationTimer_ENUM, LNAS_LPP_GetDurationTimerReportTypeError, pstTransElementEntity->ucCommCfgIndex);
        return NAS_LPP_NULL_PTR;
    }

    return &(pstLppCommCfgInfo->stReportCriteria.u.stReportTrigger.stLppTimer);
}



LRRC_LPP_CELL_GLOBAL_ID_INFO_STRU*  NAS_LPP_GetLastTriggerCellGloId( VOS_VOID )
{
    NAS_LPP_ECID_MEAS_RESULT_STRU *pstEcidMeasRslt;

    pstEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();

    return &(pstEcidMeasRslt->stLastGlobalIdInfo);
}


VOS_UINT16  NAS_LPP_GetLastTriggerLastPhyCellId( VOS_VOID )
{
    NAS_LPP_ECID_MEAS_RESULT_STRU *pstEcidMeasRslt;

    pstEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();

    return (pstEcidMeasRslt->usLastPhyCellId);
}


VOS_VOID  NAS_LPP_SetLastTriggerLastPhyCellId(VOS_UINT16 usPhyCellId)
{
    NAS_LPP_ECID_MEAS_RESULT_STRU *pstEcidMeasRslt;

    pstEcidMeasRslt = NAS_LPP_GetEcidMeasRsltAddr();

    pstEcidMeasRslt->usLastPhyCellId = usPhyCellId;

    return;
}


NAS_LPP_TIMER_STRU*  NAS_LPP_GetConnManageTimer( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stLppConnManage.stLppTimer);
}

VOS_UINT8  NAS_LPP_GetSessionEntityReportType
(
    VOS_UINT8                           ucSessionIndex,
    VOS_UINT8                           ucSessionTransIndex
)
{
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity;
    VOS_UINT8 ucTransIndx;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndex,ucSessionTransIndex);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get reprt type : don't find TransEntity!", ucSessionIndex, ucSessionTransIndex);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetSessionEntityReportType_ENUM, LNAS_LPP_GetSessionEntityReportTypeTransElement, ucSessionIndex, ucSessionTransIndex);
        return NAS_LPP_REPORT_LOCATION_TYPE_BUTT;
    }

    pstLppCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(pstTransElementEntity->ucCommCfgIndex);
    if ( NAS_LPP_NULL_PTR == pstLppCommCfgInfo )
    {
        NAS_LPP_ERR_LOG1("get reprt type don't find comm cfg! index",  pstTransElementEntity->ucCommCfgIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetSessionEntityReportType_ENUM, LNAS_LPP_GetSessionEntityReportTypeCFGError, pstTransElementEntity->ucCommCfgIndex);

        return NAS_LPP_REPORT_LOCATION_TYPE_BUTT;
    }

    return(pstLppCommCfgInfo->stReportCriteria.enType);
}


LPP_REQ_LOCATION_INFO_R9_IES_STRU*  NAS_LPP_GetDownLinkLocationReqIEAddr
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return &(pstLppMsg->stLppMessageBody.u.stC1.u.stRequestLocationInformation.u.stC1.u.stReqLocationInfoR9);
}


LPP_REQUEST_CAPABILITIES_R9_IES_STRU*  NAS_LPP_GetDownLinkCapReqIEAddr
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return &(pstLppMsg->stLppMessageBody.u.stC1.u.stRequestCapabilities.u.stC1.u.stRequestCapabilitiesR9);
}



LPP_PROVIDE_CAPABILITIES_R9_IES_STRU*  NAS_LPP_GetUpLinkProvideCapIEAddr
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return &(pstLppMsg->stLppMessageBody.u.stC1.u.stProvideCapabilities.u.stC1.u.stProvideCapabilitiesR9);
}


LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU*  NAS_LPP_GetUpLinkProvideLocIEAddr
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return &(pstLppMsg->stLppMessageBody.u.stC1.u.stProvideLocationInformation.u.stC1.u.stProLocationInfoR9);
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLrrcCap
 Description     : ��ȡLRRC������ֵ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
LRRC_SUPPORT_CAPABILITY_STRU *NAS_LPP_GetLrrcCap( VOS_VOID )
{
    return (&g_stNasLppEntity.stLrrcSupCapability);
}



VOS_UINT8  NAS_LPP_GetLrrcRxTxTimeDiffMeasFlag(VOS_VOID)
{
    return (NAS_LPP_GetLppEntityCtx()->stLrrcSupCapability.stRrcCapbility.ucUeRxTxTimeDiffMeasFlag);
}




VOS_UINT32  NAS_LPP_GetPositionTechEcid(VOS_UINT8 ucTransIndx)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  stPosSearchRslt;
    VOS_UINT32 ulRslt = 0,ulLoop;

    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx,&stPosSearchRslt);
     for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
     {
         if (NAS_LPP_POSITION_TECH_ECID == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
         {
             ulRslt= NAS_LPP_SLCT;
             break;
         }
     }

    return ulRslt;
}


VOS_UINT32  NAS_LPP_GetPositionTechOtdoa(VOS_UINT8 ucTransIndx)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  stPosSearchRslt;
    VOS_UINT32 ulRslt = 0,ulLoop;

    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx,&stPosSearchRslt);
     for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
     {
         if (NAS_LPP_POSITION_TECH_OTDOA == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
         {
             ulRslt= NAS_LPP_SLCT;
             break;
         }
     }

    return ulRslt;
}



VOS_UINT32  NAS_LPP_GetPositionTechGnss(VOS_UINT8 ucTransIndx)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  stPosSearchRslt;
    VOS_UINT32 ulRslt = 0,ulLoop;

    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx,&stPosSearchRslt);
     for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
     {
         if (NAS_LPP_POSITION_TECH_GNSS == stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech)
         {
             ulRslt= NAS_LPP_SLCT;
             break;
         }
     }

    return ulRslt;
}


VOS_UINT8  NAS_LPP_GetPosTechNum
(
    VOS_UINT8                           ucSessionIndx
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  stPosSearchRslt;

    NAS_LPP_SearchRunningPosTechBySessionIndx(ucSessionIndx,&stPosSearchRslt);

    return  (stPosSearchRslt.ucNum);
}

NAS_LPP_LOC_TECH_MAP_STRU*  NAS_LPP_SearchRunningPositionTech
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG1("Search runing pos tech num overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchRunningPositionTech_ENUM, LNAS_LPP_SearchRunningPositionTechRunningTechNumOverFlow, pstRunLocTech->ucNum);
        return NAS_LPP_NULL_PTR;
    }

    for(ulLoop = 0; ulLoop < pstRunLocTech->ucNum; ulLoop++)
    {
        if(pstRunLocTech->astLocTechMap[ulLoop].enPositionTech == enPositionTech)
        {
            /*�ҵ��˶�Ӧ�Ķ�λ����������ʵ��*/
            return &(pstRunLocTech->astLocTechMap[ulLoop]);
        }
    }

    /*û���ҵ������ؿ�*/
    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetUpMsgSequenceNum
 Description     : ��ȡ�洢����SequenceNumber
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.lifuxin      2015-7-30  Draft Enact

*****************************************************************************/
VOS_UINT16 NAS_LPP_GetDownLinkMsgSequenceNum
(
    VOS_UINT8               ucSessionIndx
)
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();
    return (pstLppCtx->stSessionEntityPool.astLppSessionEntity[ucSessionIndx].ucLastDownSequenceNum);
}

/*****************************************************************************
 Function Name   : NAS_LPP_SetUpMsgSequenceNum
 Description     : ��ȡ�洢����SequenceNumber
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.lifuxin      2015-7-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SetDownLinkMsgSequenceNum
(
    VOS_UINT8               ucSessionIndx,
    VOS_UINT8               ucSequenceNumber
)
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();

    pstLppCtx->stSessionEntityPool.astLppSessionEntity[ucSessionIndx].ucLastDownSequenceNum =
              ucSequenceNumber;
}


/*****************************************************************************
 Function Name   : NAS_LPP_SearchRunningPosTechByTransIndx
 Description     : һ��transaction�����ͬʱ���ڶ����λ����
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchRunningPosTechByTransIndx
(
    VOS_UINT8 ucTransIndx,
    NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstPosSearchRslt->ucNum = 0;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG1("Search runing pos tech by index, num overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchRunningPosTechByTransIndx_ENUM, LNAS_LPP_SearchRunningPosTechByTransIndxNumOverFlow, pstRunLocTech->ucNum);
        return;
    }

    for(ulLoop = 0; ulLoop < pstRunLocTech->ucNum; ulLoop++)
    {
        if(pstRunLocTech->astLocTechMap[ulLoop].ucTransIndx == ucTransIndx)
        {
            pstPosSearchRslt->astLocTechMap[pstPosSearchRslt->ucNum] = pstRunLocTech->astLocTechMap[ulLoop];
            pstPosSearchRslt->ucNum++;
        }
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_SearchRunningPosTechBySessionIndx
 Description     : һ��Session�����ͬʱ���ڶ����λ����
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchRunningPosTechBySessionIndx
(
    VOS_UINT8 ucSessionIndx,
    NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstPosSearchRslt->ucNum = 0;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG1("Search runing pos tech by index, num overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchRunningPosTechBySessionIndx_ENUM, LNAS_LPP_SearchRunningPosTechBySessionIndxNumOverFlow, pstRunLocTech->ucNum);
        return;
    }

    for(ulLoop = 0; ulLoop < pstRunLocTech->ucNum; ulLoop++)
    {
        if(pstRunLocTech->astLocTechMap[ulLoop].ucSessionIndx == ucSessionIndx)
        {
            pstPosSearchRslt->astLocTechMap[pstPosSearchRslt->ucNum] = pstRunLocTech->astLocTechMap[ulLoop];
            pstPosSearchRslt->ucNum++;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchRunningPosTechByIndx2
 Description     : һ��transaction�����ͬʱ���ڶ����λ����
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchRunningPosTechByIndx2
(
    VOS_UINT8 ucSessionIndx,
    VOS_UINT8 ucSessionTranIndx,
    NAS_LPP_LOC_TECH_RUNING_STRU *pstPosSearchRslt
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstPosSearchRslt->ucNum = 0;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();
    if ( pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG1("Search runing pos tech by index 2, num overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchRunningPosTechByIndx2_ENUM, LNAS_LPP_SearchRunningPosTechByIndx2TechNumOverFlow, pstRunLocTech->ucNum);
        return;
    }

    for(ulLoop = 0; ulLoop < pstRunLocTech->ucNum; ulLoop++)
    {
        if( (pstRunLocTech->astLocTechMap[ulLoop].ucSessionIndx == ucSessionIndx)
          &&(pstRunLocTech->astLocTechMap[ulLoop].ucSessionTranIndx == ucSessionTranIndx) )
        {
            pstPosSearchRslt->astLocTechMap[pstPosSearchRslt->ucNum] = pstRunLocTech->astLocTechMap[ulLoop];
            pstPosSearchRslt->ucNum++;
        }
    }

    return;
}



VOS_VOID  NAS_LPP_AddRunningPositionTech
(
    NAS_LPP_POSITION_TECH_ENUM_UINT8        enPositionTech,
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx,
    VOS_UINT8                               ucTransIndx
)
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( pstRunLocTech->ucNum >= NAS_LPP_MAX_POS_TECH)
    {
        NAS_LPP_ERR_LOG2("add running tech overflow", ucSessionIndx,ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_AddRunningPositionTech_ENUM, LNAS_LPP_AddRunningPositionTechRunningTechOverFlow, ucSessionIndx, ucSessionTransIndx);
        return;
    }

    ulLoop = pstRunLocTech->ucNum;

    /*��λ�ÿ��ã�����*/
    pstRunLocTech->astLocTechMap[ulLoop].enPositionTech = enPositionTech;
    pstRunLocTech->astLocTechMap[ulLoop].ucSessionIndx  = ucSessionIndx;
    pstRunLocTech->astLocTechMap[ulLoop].ucSessionTranIndx  = ucSessionTransIndx;
    pstRunLocTech->astLocTechMap[ulLoop].ucTransIndx    = ucTransIndx;

    pstRunLocTech->ucNum++;

    NAS_LPP_OmAddLocTechInd(enPositionTech, pstRunLocTech);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_DeleteRunningPositionTech
 Description     : ɾ��һ���������еĶ�λ����
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_DeleteRunningPositionTech(  NAS_LPP_POSITION_TECH_ENUM_UINT8 enPositionTech )
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;
    VOS_UINT32 ulLoop,ulIndex = PS_NULL_UINT32,ulLastIndex;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    if ( (pstRunLocTech->ucNum > NAS_LPP_MAX_POS_TECH)||(0 == pstRunLocTech->ucNum) )
    {
        NAS_LPP_ERR_LOG1("del running tech overflow", pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_DeleteRunningPositionTech_ENUM, LNAS_LPP_DeleteRunningPositionTechRunningTechNumError, pstRunLocTech->ucNum);
        return;
    }

    ulLastIndex = pstRunLocTech->ucNum - 1;

    for ( ulLoop = 0 ; ulLoop < pstRunLocTech->ucNum; ulLoop++ )
    {
        if ( pstRunLocTech->astLocTechMap[ulLoop].enPositionTech == enPositionTech)
        {
            ulIndex = ulLoop;
            break;
        }
    }

    if ( ulIndex <= ulLastIndex)
    {
        if ( ulIndex == ulLastIndex )
        {
        }
        else
        {
/*lint -e797*/
/*lint -e804*/

            NAS_LPP_MEM_CPY(&(pstRunLocTech->astLocTechMap[ulIndex]), &(pstRunLocTech->astLocTechMap[ulLastIndex]), sizeof(NAS_LPP_LOC_TECH_MAP_STRU));
/*lint +e804*/
/*lint +e797*/
        }

        pstRunLocTech->ucNum--;

        NAS_LPP_OmDelLocTechInd( enPositionTech,  pstRunLocTech );
    }
    else
    {
        NAS_LPP_ERR_LOG2("del running tech not found,PosTch,all tech num", enPositionTech,pstRunLocTech->ucNum);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_DeleteRunningPositionTech_ENUM, LNAS_LPP_DeleteRunningPositionTechErrorTechOrNum, enPositionTech, pstRunLocTech->ucNum);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_LPP_InitRunningPositionTech
 Description     : ��ʼ��
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_InitRunningLocTech( VOS_VOID )
{
    NAS_LPP_LOC_TECH_RUNING_STRU  *pstRunLocTech;

    pstRunLocTech = NAS_LPP_GetRuningLocTech();

    NAS_LPP_MEM_SET(pstRunLocTech,0,sizeof(NAS_LPP_LOC_TECH_RUNING_STRU));

}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleasePosTechMeas
 Description     : �ͷŶ�Ӧ�Ķ�λ����
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleasePosTechMeas
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech
)
{
    if (NAS_LPP_POSITION_TECH_ECID == enPosTech)
    {
        NAS_LPP_SndLppLrrcEcidMeasReq(ucSessionIndx,ucSessionTransIndx,LPP_LRRC_LCS_MEAS_CMD_REL);
    }
    else if (NAS_LPP_POSITION_TECH_OTDOA == enPosTech)
    {
        NAS_LPP_SndOtdoaMeasReq(ucSessionIndx,ucSessionTransIndx,LPP_LRRC_LCS_MEAS_CMD_REL);
    }
    else if (NAS_LPP_POSITION_TECH_GNSS == enPosTech)
    {

    }
    else
    {
    }

    /*���������еĶ�λ��¼����ɾ���˶�λ*/
    NAS_LPP_DeleteRunningPositionTech(enPosTech);
}
/*****************************************************************************
 Function Name   : NAS_LPP_SetWaitMeasCnfFlag
 Description     :
 Input           : ulFlag:NAS_LPP_SLCT��NAS_LPP_NO_SLCT
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-6  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SetWaitMeasCnfFlag
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTranIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech,
    VOS_UINT32                          ulFlag
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity = NAS_LPP_NULL_PTR;
    pstTransElementEntity = NAS_LPP_GetTransEntity(ucSessionIndx,ucSessionTranIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("set flag with wrong index", ucSessionIndx, ucSessionTranIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_SetWaitMeasCnfFlag_ENUM, LNAS_LPP_SetWaitMeasCnfFlagNOTFindTransaction, ucSessionIndx, ucSessionTranIndx);
        return;
    }

    switch ( enPosTech )
    {
        case NAS_LPP_POSITION_TECH_ECID:
            pstTransElementEntity->bitOpWaitEcidMeasCnf = ulFlag;
            break;
        case NAS_LPP_POSITION_TECH_OTDOA :
            pstTransElementEntity->bitOpWaitOtdoaMeasCnf = ulFlag;
            break;
        default:
            NAS_LPP_ERR_LOG1("set flag with wrong tech", enPosTech);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SetWaitMeasCnfFlag_ENUM, LNAS_LPP_SetWaitMeasCnfErrorTechFlag, enPosTech);
            break;
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetWaitMeasCnfFlag
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-6  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LPP_GetWaitMeasCnfFlag
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTranIndx,
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech
)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransElementEntity;
    VOS_UINT32 ulFlag = NAS_LPP_NO_SLCT;

    pstTransElementEntity = NAS_LPP_GetTransEntity(ucSessionIndx,ucSessionTranIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("get flag with wrong index", ucSessionIndx, ucSessionTranIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_GetWaitMeasCnfFlag_ENUM, LNAS_LPP_NOTFindTransactionBySessionSessionTransIndex, ucSessionIndx, ucSessionTranIndx);
        return NAS_LPP_NO_SLCT;
    }

    switch ( enPosTech )
    {
        case NAS_LPP_POSITION_TECH_ECID:
            ulFlag = pstTransElementEntity->bitOpWaitEcidMeasCnf;
            break;
        case NAS_LPP_POSITION_TECH_OTDOA :
            ulFlag = pstTransElementEntity->bitOpWaitOtdoaMeasCnf;
            break;
        default:
            NAS_LPP_ERR_LOG1("Get flag with wrong tech", enPosTech);
            TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetWaitMeasCnfFlag_ENUM, LNAS_LPP_GetErrorTechFlag, enPosTech);
            break;
    }

    return ulFlag;
}



/*****************************************************************************
 Function Name   : NAS_LPP_GetMeasRsltAddr
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-28  Draft Enact

*****************************************************************************/
NAS_LPP_MEAS_RESULT_STRU*  NAS_LPP_GetMeasRsltAddr( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stMeasResult);
}


NAS_LPP_ECID_MEAS_RESULT_STRU*  NAS_LPP_GetEcidMeasRsltAddr( VOS_VOID )
{
    return &(NAS_LPP_GetLppEntityCtx()->stMeasResult.stEcidMeasRslt);
}


VOS_UINT32  NAS_LPP_GetSessionIdBySessionIndx
(
    VOS_UINT8                           ucSessionIndx
)
{

    return (NAS_LPP_GetLppEntityCtx()->stSessionEntityPool.astLppSessionEntity[ucSessionIndx].ulSessionId);
}

/*****************************************************************************
 Function Name   : NAS_LPP_SetEndTransFlg
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32
 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SetEndTransFlg( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx ,PS_BOOL_ENUM_UINT8 enTransEndFlg)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity  = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx            = 0;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("wrong session index,session trans index for end flag set",ucSessionIndx,ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_SetEndTransFlg_ENUM, LNAS_LPP_NOTFindTransactionBySessionSessionTransIndex, ucSessionIndx, ucSessionTransIndx);
        return;
    }

    pstTransElementEntity->ucTransEndFlag = enTransEndFlg;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetEndTransFlg
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32
 History         :
    1.LIFUXIN      2015-7-29  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_LPP_GetEndTransFlg( VOS_UINT8 ucSessionIndx,VOS_UINT8 ucSessionTransIndx )
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransElementEntity  = NAS_LPP_NULL_PTR;
    VOS_UINT8                                ucTransIndx            = 0;

    ucTransIndx= NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransElementEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if (NAS_LPP_NULL_PTR == pstTransElementEntity)
    {
        NAS_LPP_ERR_LOG2("wrong session index,session trans index for end flag set", ucSessionIndx, ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_SetEndTransFlg_ENUM, LNAS_LPP_NOTFindTransactionBySessionSessionTransIndex, ucSessionIndx, ucSessionTransIndx);

        return NAS_LPP_NULL_PTR;
    }

   return pstTransElementEntity->ucTransEndFlag;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchSessionIndx
 Description     :  ����session id����session entity
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LPP_SearchSessionIndx( VOS_UINT32 ulSessionId )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucLoop,ucSessionIndex;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    ucSessionIndex = PS_NULL_UINT8;
    for ( ucLoop = 0 ; ucLoop < NAS_LPP_MAX_SESSION_COUNT; ucLoop++ )
    {
        /*������ʹ�õ�session entity�в���*/
        if (0 != ( pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ucLoop) ) )
        {
            if ( pstSessionEntityPool->astLppSessionEntity[ucLoop].ulSessionId == ulSessionId )
            {
                ucSessionIndex = ucLoop;
                break;
            }
        }
    }

    return ucSessionIndex;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetTransElementByIndex
 Description     : ͨ����������ȡ��transaction entity pool���entityʵ���ָ
                   �롣
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-16  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_GetTransElementByIndex(VOS_UINT8 ucIndex)
{
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU    *pstTransEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;

    pstTransEntityPool = NAS_LPP_GetLppTransEntityPool();
    if (ucIndex < NAS_LPP_MAX_TRANS_POOL_COUNT)
    {
        pstTransEntity = &pstTransEntityPool->astTransElementEntity[ucIndex];
    }

    return pstTransEntity;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetSessionElementByIndex
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-21  Draft Enact

*****************************************************************************/
NAS_LPP_SESSION_ENTITY_ELEMENT_STRU * NAS_LPP_GetSessionElementByIndex(VOS_UINT8 ucIndex)
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();
    if (ucIndex >= NAS_LPP_MAX_SESSION_COUNT)
    {
        return pstSessionEntity;
    }

    pstSessionEntity = &pstSessionEntityPool->astLppSessionEntity[ucIndex];
    return pstSessionEntity;
}


/*****************************************************************************
 Function Name   : NAS_LPP_SearchSessionElement
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-21  Draft Enact

*****************************************************************************/
NAS_LPP_SESSION_ENTITY_ELEMENT_STRU*  NAS_LPP_SearchSessionElement( VOS_UINT32 ulSessionId )
{
    VOS_UINT8 ucIndx;

    ucIndx = NAS_LPP_SearchSessionIndx(ulSessionId);

    return (NAS_LPP_GetSessionElementByIndex(ucIndx));
}

/*****************************************************************************
 Function Name   : NAS_LPP_DelTransEntityFromSession
 Description     : ��session�Ѵ�transaction entityɾ��
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_DelTransEntityFromSession( NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity, VOS_UINT8 ucSessionTransIndx )
{
    VOS_UINT8 ucLastIndx = 0;

    if ( (0 == pstSessionEntity->stLppTrans.ucTransIdCount)
      || (NAS_LPP_MAX_TRANS_COUNT < pstSessionEntity->stLppTrans.ucTransIdCount) )
    {
        NAS_LPP_ERR_LOG1("wrong trans num in session",pstSessionEntity->stLppTrans.ucTransIdCount);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_DelTransEntityFromSession_ENUM, LNAS_LPP_ErrorTransNumInSession, pstSessionEntity->stLppTrans.ucTransIdCount);
        return;
    }

    ucLastIndx = pstSessionEntity->stLppTrans.ucTransIdCount - 1;

    /*��������һ��*/
    if ( ucLastIndx == ucSessionTransIndx )
    {
        /*null*/
    }
    else
    {
        pstSessionEntity->stLppTrans.aucTransElementIdx[ucSessionTransIndx]
                = pstSessionEntity->stLppTrans.aucTransElementIdx[ucLastIndx];
    }

    pstSessionEntity->stLppTrans.ucTransIdCount--;
}

/*****************************************************************************
 Function Name   : NAS_LPP_AddTransEntityToSession
 Description     : ��trans entityʵ����뵽session��
 Input           : None
 Output          : None
 Return          : VOS_UITN32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LPP_AddTransEntityToSession( NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity ,VOS_UINT8 ucIndex,VOS_UINT8 *pucSessionTransIndex)
{

    if ( NAS_LPP_MAX_TRANS_COUNT <= pstSessionEntity->stLppTrans.ucTransIdCount )
    {
        NAS_LPP_ERR_LOG1("overflow trans num in session",pstSessionEntity->stLppTrans.ucTransIdCount);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_AddTransEntityToSession_ENUM, LNAS_LPP_ErrorTransNumInSession, pstSessionEntity->stLppTrans.ucTransIdCount);

        return NAS_LPP_FAILURE;
    }

    *pucSessionTransIndex = pstSessionEntity->stLppTrans.ucTransIdCount;
    pstSessionEntity->stLppTrans.aucTransElementIdx[ pstSessionEntity->stLppTrans.ucTransIdCount ] = ucIndex;

    pstSessionEntity->stLppTrans.ucTransIdCount++;

    NAS_LPP_OmAddTransToSessionInd(NAS_LPP_SearchSessionIndx(pstSessionEntity->ulSessionId),
                                   ucIndex,
                                   &pstSessionEntity->stLppTrans);

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ReInitTransEntity
 Description     : ��transaction entityȫ���ٴγ�ʼ��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_ReInitTransEntity
(
    VOS_UINT8       ucTransIndex,
    VOS_UINT8       ucSessionIndx,
    VOS_UINT8       ucSessionTransIndx
)
{
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU    *pstTransEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;

    pstTransEntityPool = NAS_LPP_GetLppTransEntityPool();
    if ( ucTransIndex >= NAS_LPP_MAX_TRANS_POOL_COUNT )
    {
        NAS_LPP_ERR_LOG1("re_init wrong trans  index in pool",ucTransIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReInitTransEntity_ENUM, LNAS_LPP_WrongTransactionIndex, ucTransIndex);
        return;
    }

    pstTransEntity = &pstTransEntityPool->astTransElementEntity[ucTransIndex];

    /*��ͣ��ʱ��*/
    NAS_LPP_TimerStop(ucSessionIndx,
                      ucSessionTransIndx,
                      pstTransEntity->stLppTimer.enTimerId);

    NAS_LPP_MEM_SET(pstTransEntity,0,
                    sizeof(NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU));

    pstTransEntity->enLastUpMsgId = NAS_LPP_AIR_MSG_BUTT;
    pstTransEntity->ucCommCfgIndex = PS_NULL_UINT8;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ReturnTransEntityToPool
 Description     :  ��transaction entity �黹��pool��
 Input           : ucTransIndx--Ҫ�黹��TransEntity��pool���Ӧ������
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReturnTransEntityToPool( VOS_UINT8 ucTransIndex )
{
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU    *pstTransEntityPool = NAS_LPP_NULL_PTR;

    pstTransEntityPool = NAS_LPP_GetLppTransEntityPool();
    if ( ucTransIndex >= NAS_LPP_MAX_TRANS_POOL_COUNT )
    {
        NAS_LPP_ERR_LOG1("return wrong  trans  index in pool",ucTransIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReturnTransEntityToPool_ENUM, LNAS_LPP_WrongTransactionIndex, ucTransIndex);
        return;
    }

    /* �Ѵ�trans entity��trans pool���״̬��Ϊ����*/

    /*lint -e502*/
    pstTransEntityPool->ulTransBitmap = (pstTransEntityPool->ulTransBitmap & (~(0x1<<ucTransIndex)));
    /*lint +e502*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransEntityByIndx
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseTransEntityByIndx(VOS_UINT8 ucSessionIndx ,VOS_UINT8 ucSessionTransIndx )
{
    NAS_LPP_ReleaseTransEntity(ucSessionIndx,ucSessionTransIndx);
}


/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransEntityElementOnly
 Description     : �ͷ�һ��transaction entity��pool��
 Input           : ucSessionTransIndx---NAS_LPP_TRANSACTION_STRU���aucTransElementIdx[ucSessionTransIndx]
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-15  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_ReleaseTransEntityElementOnly( VOS_UINT8 ucSessionIndx, VOS_UINT8 ucSessionTransIndx )
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucTransIndex = 0;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity )
    {
        NAS_LPP_ERR_LOG1("release trans only wrong sessiong index,",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseTransEntityElementOnly_ENUM, LNAS_LPP_WrongSessionIndex, ucTransIndex);
        return;
    }

    if ( ucSessionTransIndx >= pstSessionEntity->stLppTrans.ucTransIdCount )
    {
        NAS_LPP_ERR_LOG2("rel wrong session transaction indx",ucSessionTransIndx,pstSessionEntity->stLppTrans.ucTransIdCount);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseTransEntityElementOnly_ENUM, LNAS_LPP_WrongSessionTransactionIndex, ucSessionTransIndx);
        return;
    }

    ucTransIndex = pstSessionEntity->stLppTrans.aucTransElementIdx[ucSessionTransIndx];
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndex);
    if ( NAS_LPP_NULL_PTR == pstTransEntity )
    {
        NAS_LPP_ERR_LOG1("releas trans wrong trans  index in pool",ucTransIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseTransEntityElementOnly_ENUM, LNAS_LPP_WrongSessionIndex, ucTransIndex);
        return;
    }

    /*��trans element��������pstSessionEntity->stLppTranɾ��*/
    NAS_LPP_DelTransEntityFromSession( pstSessionEntity,  ucSessionTransIndx );

    /* �黹��pool��*/
    NAS_LPP_ReturnTransEntityToPool(ucTransIndex);

    NAS_LPP_ReInitTransEntity(ucTransIndex, ucSessionIndx, ucSessionTransIndx);

    NAS_LPP_OmTransRelInd(ucSessionIndx, ucTransIndex, &pstSessionEntity->stLppTrans);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransEntityAction
 Description     : �ͷ�һ��transactionʱ���ͷŶ�Ӧ�Ĳ������õĶ���
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseTransEntityAction
(
    VOS_UINT8                               ucSessionIndx,
    VOS_UINT8                               ucSessionTransIndx
)
{
    NAS_LPP_POSITION_TECH_ENUM_UINT8    enPosTech;
    VOS_UINT8                           ucTransIndx;
    VOS_UINT32                          ulLoop;
    NAS_LPP_LOC_TECH_RUNING_STRU        stPosSearchRslt = {0};
    NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU stSearchRslt = {0};
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;

    ucTransIndx = NAS_LPP_GetTransIdIndex(ucSessionIndx,ucSessionTransIndx);
    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransIndx);
    if ( NAS_LPP_NULL_PTR == pstTransEntity)
    {
        NAS_LPP_ERR_LOG2("relase trans err sessinon index and session trans index", ucSessionIndx,ucSessionTransIndx);
        TLPS_PRINT2LAYER_ERROR2(NAS_LPP_ReleaseTransEntityAction_ENUM, LNAS_LPP_NOTFindTransactionBySessionSessionTransIndex, ucSessionIndx, ucSessionTransIndx);
        return;
    }

    /*�жϴ�transaction�Ƿ��Ӧn����λ�����Ĳ��� ,����ǣ�Ҫֹͣ��Ӧ�Ĳ���*/
    NAS_LPP_SearchRunningPosTechByTransIndx(ucTransIndx, &stPosSearchRslt);

    for ( ulLoop = 0 ; ulLoop < stPosSearchRslt.ucNum; ulLoop++ )
    {
        enPosTech = stPosSearchRslt.astLocTechMap[ulLoop].enPositionTech;
        if ( (enPosTech < NAS_LPP_POSITION_TECH_BUTT)&&(NAS_LPP_POSITION_TECH_NULL != enPosTech) )
        {
            NAS_LPP_ReleasePosTechMeas(ucSessionIndx, ucSessionTransIndx, enPosTech);
        };
    }

    NAS_LPP_ReleaseCommCfgInfoElementByIndex(ucTransIndx,pstTransEntity->ucCommCfgIndex);

    /*ɾ����transaction��Ӧ������Buffer:�ж��ɾ�����*/
    NAS_LPP_SearchUpMsgBuffByTrnasId(&(pstTransEntity->stTransId),&stSearchRslt);

    for ( ulLoop = 0 ; ulLoop < stSearchRslt.ucNum; ulLoop++ )
    {
        NAS_LPP_RelUpMsgBufferByIndex(stSearchRslt.aucIndex[ulLoop]);
    }

    for ( ulLoop = 0 ; ulLoop < pstTransEntity->stFsmBuff.ucHighNum; ulLoop++ )
    {
        NAS_LPP_MEM_FREE(pstTransEntity->stFsmBuff.astHighMsg[ulLoop].pMsg);
        pstTransEntity->stFsmBuff.astHighMsg[ulLoop].pMsg = NAS_LPP_NULL_PTR;
    }

    for ( ulLoop = 0 ; ulLoop < pstTransEntity->stFsmBuff.ucLowNum; ulLoop++ )
    {
        NAS_LPP_MEM_FREE(pstTransEntity->stFsmBuff.astLowMsg[ulLoop].pMsg);
        pstTransEntity->stFsmBuff.astLowMsg[ulLoop].pMsg = NAS_LPP_NULL_PTR;
    }

}

/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransEntity
 Description     : �ͷŶ�Ӧ��transʵ�壬���ж��Ƿ���Ҫ���������ͷŶ������磬
                   ͣ����
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseTransEntity( VOS_UINT8 ucSessionIndx, VOS_UINT8 ucSessionTransIndx )
{

    NAS_LPP_ReleaseTransEntityAction( ucSessionIndx, ucSessionTransIndx );

    NAS_LPP_ReleaseTransEntityElementOnly( ucSessionIndx, ucSessionTransIndx );
}

/*****************************************************************************
 Function Name   : NAS_LPP_RelAllTransEntity
 Description     : VOS_VOID
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-21  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RelAllTransEntity( VOS_VOID )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulLoop;
    VOS_UINT8 ucLoop1,ucTransIdCount;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        /*�ҵ�һ�������session entity*/
        if (0 != ( pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ulLoop) ) )
        {
            pstSessionEntity = (&pstSessionEntityPool->astLppSessionEntity[ulLoop]);
            ucTransIdCount = pstSessionEntity->stLppTrans.ucTransIdCount;

            if (ucTransIdCount > 0)
            {
                for ( ucLoop1 = (ucTransIdCount ) ; ucLoop1 > 0; ucLoop1-- )
                {
                    NAS_LPP_ReleaseTransEntity((VOS_UINT8)ulLoop, ucLoop1-1);
                }
            }
            /*lint -e502*/
            pstSessionEntityPool->ulSessionActiveBitmap = (pstSessionEntityPool->ulSessionActiveBitmap & (~(0x1<<ulLoop)));
            /*lint +e502*/
        }
    }

    return;
}



/*****************************************************************************
 Function Name   : NAS_LPP_MallocTransEntityIndx
 Description     : ��transaction entity pool������һ�����е�entity
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_UINT8 NAS_LPP_MallocTransEntityIndx
(
    LPP_TRANSACTION_ID_STRU                 *pstUuTransactionId
)
{
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU    *pstTransEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucLoop;
    VOS_UINT8 ucIndex = PS_NULL_UINT8;

    pstTransEntityPool = NAS_LPP_GetLppTransEntityPool();

    for ( ucLoop = 0; ucLoop < NAS_LPP_MAX_TRANS_POOL_COUNT; ucLoop++ )
    {
        if ( 0 == (pstTransEntityPool->ulTransBitmap & (0x1<<ucLoop)) )
        {
            pstTransEntityPool->ulTransBitmap = pstTransEntityPool->ulTransBitmap | (0x1<<ucLoop);
            ucIndex = ucLoop;
            pstTransEntityPool->astTransElementEntity[ucLoop].stTransId.enInitiator =
                                                        pstUuTransactionId->enInitiator;
            pstTransEntityPool->astTransElementEntity[ucLoop].stTransId.ucTransactionNumber =
                                                        pstUuTransactionId->ucTransactionNumber;

            break;
        }
    }

    if (NAS_LPP_MAX_TRANS_POOL_COUNT <= ucIndex)
    {
        return ucIndex;
    }
    NAS_LPP_OmTransMallocInd(ucIndex,
                             pstTransEntityPool->ulTransBitmap,
                             &pstTransEntityPool->astTransElementEntity[ucIndex].stTransId);

    return ucIndex;
}


NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU* NAS_LPP_MallocTransEntity
(
    LPP_TRANSACTION_ID_STRU                 *pstUuTransactionId
)
{

    VOS_UINT8 ucIndex = PS_NULL_UINT8;

    ucIndex = NAS_LPP_MallocTransEntityIndx(pstUuTransactionId);
    if(PS_NULL_UINT8 == ucIndex)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_MallocTransEntity: Transaction space is full!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_MallocTransEntity_ENUM, LNAS_LPP_MALLOCTRANSENTITYFAIL);
        return NAS_LPP_NULL_PTR;
    }

    return NAS_LPP_GetTransElementByIndex(ucIndex);
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchTransEntityIndx
 Description     :  ����transaction ʵ��
 Input           : None
 Output          : pucTransIndx---��transaction entity pool���λ��,
                   pucSessionTransIndx-- pucTransIndx-��session entity��aucTransElementIdx[NAS_LPP_MAX_TRANS_COUNT]��λ��
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-16  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchTransEntityIndx(
    VOS_UINT8                       ucSessionIndx,
    NAS_LPP_TRANS_ID_STRU          *pstTransId,
    VOS_UINT8                      *pucTransIndx,
    VOS_UINT8                      *pucSessionTransIndx )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucTranIndx, ucLoop, ucTransIdCount;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    *pucTransIndx = PS_NULL_UINT8;
    *pucSessionTransIndx = PS_NULL_UINT8;

    if ( ucSessionIndx >= NAS_LPP_MAX_SESSION_COUNT )
    {
        NAS_LPP_ERR_LOG1("search wrong session Id when search trans entity",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchTransEntityIndx_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);
        return;
    }

    ucTransIdCount = pstSessionEntityPool->astLppSessionEntity[ucSessionIndx].stLppTrans.ucTransIdCount;
    for ( ucLoop = 0 ; ucLoop < ucTransIdCount; ucLoop++ )
    {
        ucTranIndx = pstSessionEntityPool->astLppSessionEntity[ucSessionIndx].stLppTrans.aucTransElementIdx[ucLoop];
        pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTranIndx);
        if(NAS_LPP_NULL_PTR == pstTransEntity)
        {
            NAS_LPP_ERR_LOG1("search wrong transaction index",ucTranIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchTransEntityIndx_ENUM, LNAS_LPP_SEARCHWRONGTRANSACTIONINDEX, ucTranIndx);
            continue;
        }
        if ((pstTransEntity->stTransId.ucTransactionNumber == pstTransId->ucTransactionNumber)
          &&(pstTransEntity->stTransId.enInitiator == pstTransId->enInitiator) )
        {
            *pucTransIndx = ucTranIndx;
            *pucSessionTransIndx = ucLoop;
            break;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_IsThereOtherTransactionRunningInSession
 Description     : ����sessionIdȥ���ҵ�ǰsession�£��Ƿ�����pstTransId֮���transaction����running
 Input           : pstTransId:��ʾ��֮���transaction
 Output          : VOS_TRUE:    ��ʾ����pstTransId֮�⣬����������transaction�ڱ�session���С�
 Return          : UINT32

 History         :
    1.lifuxin      2015-9-6  Draft Enact

*****************************************************************************/
VOS_BOOL NAS_LPP_IsThereOtherTransactionRunningInSession
(
    VOS_UINT8                       ucSessionIndx,
    NAS_LPP_TRANS_ID_STRU          *pstTransId
)
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8  ucTransIdCount;
    VOS_UINT8  ucTransIndx = PS_NULL_UINT8, ucSessionTransIndx = PS_NULL_UINT8;


    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    if ( ucSessionIndx >= NAS_LPP_MAX_SESSION_COUNT )
    {
        NAS_LPP_ERR_LOG1("NAS_LPP_IsThereOtherTransactionRunningInSession: ",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_IsThereOtherTransactionRunningInSession_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);
        return PS_FALSE;
    }

    ucTransIdCount = pstSessionEntityPool->astLppSessionEntity[ucSessionIndx].stLppTrans.ucTransIdCount;
    if( ucTransIdCount > 0)
    {
        NAS_LPP_SearchTransEntityIndx(ucSessionIndx,pstTransId,&ucTransIndx,&ucSessionTransIndx);
        if (PS_NULL_UINT8 == ucTransIndx)
        {
            /*ָ����transaction�Ͳ���session��*/
            return PS_TRUE;
        }
        else
        {
            /*pstTransIdָ����transaction��sessioon��*/
            if ( ucTransIdCount > 1)
            {
                /*��������transaction������*/
                return PS_TRUE;
            }
            else
            {
                return PS_FALSE;
            }
        }
    }
    else
    {
        /*û��*/
        return PS_FALSE;
    }

}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchTransEntity
 Description     : ����session id��transaction number����transaction element
                   ������transaction elementָ��
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU * NAS_LPP_SearchTransEntity
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU               *pstTransId,
    VOS_UINT8                           *pucSessionTransIndx
)
{
    VOS_UINT8 ucSessionIndx,ucTransEntityIndx;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity = NAS_LPP_NULL_PTR;

    ucSessionIndx = NAS_LPP_SearchSessionIndx(ulSessionId);

    NAS_LPP_SearchTransEntityIndx(ucSessionIndx,pstTransId,&ucTransEntityIndx,pucSessionTransIndx);

    pstTransEntity = NAS_LPP_GetTransElementByIndex(ucTransEntityIndx);

    return pstTransEntity;
}
/*****************************************************************************
 Function Name   : NAS_LPP_CreatNewTrans
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_CreatNewTrans
(
    VOS_UINT8       ucSessionIndx ,
    VOS_UINT8      *pucSessionTransIndx,
    VOS_UINT8      *pucTransIndex
)
{

    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU    *pstSessionEntity = NAS_LPP_NULL_PTR;
    LPP_TRANSACTION_ID_STRU                 stUuTransactionId;
    VOS_UINT8 ucIndex;

    *pucTransIndex = PS_NULL_UINT8;
    *pucSessionTransIndx = PS_NULL_UINT8;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity )
    {
        NAS_LPP_ERR_LOG1("creat new trans with wrong session index", ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CreatNewTrans_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);
        return;
    }

    if (pstSessionEntity->stLppTrans.ucTransIdCount >= NAS_LPP_MAX_TRANS_COUNT)
    {
        NAS_LPP_ERR_LOG1("creat new trans with  session full", pstSessionEntity->stLppTrans.ucTransIdCount);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_CreatNewTrans_ENUM, LNAS_LPP_ERRORSESIONTRANSACTIONCOUNT, pstSessionEntity->stLppTrans.ucTransIdCount);
        return;
    }

    stUuTransactionId.enInitiator = LPP_INITIATOR_TYPE_TARGET_DEVICE;
    stUuTransactionId.ucTransactionNumber = NAS_LPP_ApplyTransNum();
    ucIndex = NAS_LPP_MallocTransEntityIndx(&stUuTransactionId);
    if ( PS_NULL_UINT8 == ucIndex )
    {
        NAS_LPP_ERR_LOG("creat new trans malloc trans fail" );
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_CreatNewTrans_ENUM, LNAS_LPP_MALLOCTRANSENTITYFAIL);
        return;
    }

    *pucTransIndex = ucIndex;

    (VOS_VOID)NAS_LPP_AddTransEntityToSession(pstSessionEntity,ucIndex,pucSessionTransIndx);
}
/*****************************************************************************
 Function Name   : NAS_LPP_SessionEntityReInit
 Description     : VOS_VOID
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_SessionEntityReInit( VOS_UINT8 ucSessionIndx )
{
    VOS_UINT8 ucLoop,ucTransIdCount;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU *pstSessionEntity = NAS_LPP_NULL_PTR;

    pstSessionEntity = NAS_LPP_GetSessionElementByIndex(ucSessionIndx);
    if ( NAS_LPP_NULL_PTR == pstSessionEntity )
    {
        NAS_LPP_ERR_LOG1("session reinit  wrong sessiong index,",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SessionEntityReInit_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);
        return;
    }

    ucTransIdCount = pstSessionEntity->stLppTrans.ucTransIdCount;

    if ( ucTransIdCount > 0 )
    {
        /*�Ȱѵ���transactionʵ�嵥���ͷŵ�,�����һ��ɾ��*/
        for ( ucLoop = (ucTransIdCount) ; ucLoop > 0; ucLoop-- )
        {
            NAS_LPP_ReleaseTransEntity(ucSessionIndx, ucLoop-1);
        }
    }

    NAS_LPP_MEM_SET(pstSessionEntity, 0, sizeof(NAS_LPP_SESSION_ENTITY_ELEMENT_STRU));

}

/*****************************************************************************
 Function Name   : NAS_LPP_MallocSessionEntity
 Description     : Ϊ���µ�һ��session����һ��sessionʵ��
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
NAS_LPP_SESSION_ENTITY_ELEMENT_STRU* NAS_LPP_MallocSessionEntity( VOS_UINT32  ulSessionId )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    NAS_LPP_SESSION_ENTITY_ELEMENT_STRU     *pstSessionEntity = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulLoop;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        /*�ҵ�һ�����е�session entity*/
        if (0 == ( pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ulLoop) ) )
        {
            /*����session entity��Ϊæ*/
            pstSessionEntityPool->ulSessionActiveBitmap = pstSessionEntityPool->ulSessionActiveBitmap | (0x1<<ulLoop);
            pstSessionEntity = (&pstSessionEntityPool->astLppSessionEntity[ulLoop]);
            pstSessionEntity->ulSessionId = ulSessionId;
            break;
        }
    }

    NAS_LPP_OmSessionMallocInd((VOS_UINT8)ulLoop,ulSessionId,pstSessionEntityPool->ulSessionActiveBitmap);

    return pstSessionEntity;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseSessionEntity
 Description     :  �ͷ�һ��session ʵ��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_ReleaseSessionEntity(VOS_UINT32 ulSessionId)
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucIndex;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    ucIndex = NAS_LPP_SearchSessionIndx(ulSessionId);

    if ( ucIndex < NAS_LPP_MAX_SESSION_COUNT )
    {
    /*lint -e502*/
        pstSessionEntityPool->ulSessionActiveBitmap
            = (pstSessionEntityPool->ulSessionActiveBitmap & (~(0x1<<ucIndex)));
    /*lint +e502*/

        NAS_LPP_SessionEntityReInit(ucIndex);
    }
    else
    {
        NAS_LPP_ERR_LOG1("release wrong session Id",ulSessionId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseSessionEntity_ENUM, LNAS_LPP_SearchWrongSessionBySessionID, ulSessionId);

    }

    NAS_LPP_OmSessionRelInd(ucIndex,ulSessionId,pstSessionEntityPool->ulSessionActiveBitmap);

}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseSessionEntityByIndex
 Description     : ����session index�ͷ�session
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseSessionEntityByIndex( VOS_UINT8 ucSessionIndx )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulSessionId = PS_NULL_UINT32;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();
    if ( ucSessionIndx < NAS_LPP_MAX_SESSION_COUNT )
    {
    /*lint -e502*/
        pstSessionEntityPool->ulSessionActiveBitmap
            = (pstSessionEntityPool->ulSessionActiveBitmap & (~(0x1<<ucSessionIndx)));
    /*lint +e502*/
        ulSessionId = pstSessionEntityPool->astLppSessionEntity[ucSessionIndx].ulSessionId;

        NAS_LPP_SessionEntityReInit(ucSessionIndx);
    }
    else
    {
        NAS_LPP_ERR_LOG1("release wrong session index",ucSessionIndx);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseSessionEntityByIndex_ENUM, LNAS_LPP_SEARCHWRONGSESSIONBYINDEX, ucSessionIndx);

    }

    NAS_LPP_OmSessionRelInd(ucSessionIndx,ulSessionId,pstSessionEntityPool->ulSessionActiveBitmap);
}


/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseAllSession
 Description     : �ͷ����е�session
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseAllSession( VOS_VOID )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT32 ulLoop;
    VOS_UINT32 ulSessionId = PS_NULL_UINT32;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_SESSION_COUNT; ulLoop++ )
    {
        if ( 0 != (pstSessionEntityPool->ulSessionActiveBitmap & (0x1<<ulLoop)) )
        {
        /*lint -e502*/
            pstSessionEntityPool->ulSessionActiveBitmap
                = (pstSessionEntityPool->ulSessionActiveBitmap & (~(0x1<<ulLoop)));
        /*lint +e502*/

            ulSessionId = pstSessionEntityPool->astLppSessionEntity[ulLoop].ulSessionId;

            NAS_LPP_SessionEntityReInit((VOS_UINT8)ulLoop);

            NAS_LPP_OmSessionRelInd((VOS_UINT8)ulLoop,ulSessionId,pstSessionEntityPool->ulSessionActiveBitmap);
        }
    }
}


/*****************************************************************************
 Function Name   : NAS_LPP_MsgDuplicateDetect
 Description     : LPP ������Ϣ���ظ����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LPP_MsgDuplicateDetect( VOS_UINT32 ulSessionId, VOS_UINT8 ucNewMsgSequenecNum )
{
    NAS_LPP_SESSION_ENTITY_POOL_STRU        *pstSessionEntityPool = NAS_LPP_NULL_PTR;
    VOS_UINT8 ucIndex;

    NAS_LPP_NORM_LOG("NAS_LPP_MsgDuplicateDetect is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_MsgDuplicateDetect_ENUM, LNAS_LPP_MsgDuplicateDetectEnter);
    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    /*����session id������session entity*/
    ucIndex = NAS_LPP_SearchSessionIndx(ulSessionId);

    /*���sessionû�������������ش���ֵ*/
    if ( ucIndex >= NAS_LPP_MAX_SESSION_COUNT )
    {
        NAS_LPP_INFO_LOG1("Fisrt Lpp Msg",ulSessionId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_MsgDuplicateDetect_ENUM, LNAS_LPP_SearchWrongSessionBySessionID, ucIndex);
        return NAS_LPP_SUCCESS;
    }

    /*������sessionû���յ�������LPP��Ϣ*/
    if (PS_FALSE == pstSessionEntityPool->astLppSessionEntity[ucIndex].enRcvedDownMsg)
    {
        pstSessionEntityPool->astLppSessionEntity[ucIndex].enRcvedDownMsg = PS_TRUE;
        return NAS_LPP_SUCCESS;
    }

    /*���sequence number���ظ��ģ������ظ�*/
    if ( ucNewMsgSequenecNum == pstSessionEntityPool->astLppSessionEntity[ucIndex].ucLastDownSequenceNum )
    {
        NAS_LPP_ERR_LOG2("discard duplicate msg,sessionId,newSeqNum",ulSessionId,ucNewMsgSequenecNum);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_MsgDuplicateDetect_ENUM, LNAS_LPP_DuplicateMessageSeqNum, ucNewMsgSequenecNum);
        return NAS_LPP_MSG_DUPLICATE;
    }
    else
    {
        return NAS_LPP_SUCCESS;
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetUpMsgSequenceNum
 Description     : Ϊ��Ҫ���͵�����LPP��Ϣ��ȡһ��sequence number
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_UINT8 NAS_LPP_GetUpMsgSequenceNum( VOS_VOID )
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;
    VOS_UINT8                ucSequencNum;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();

    ucSequencNum = pstLppCtx->ucUpSequenceNumMax;
    pstLppCtx->ucUpSequenceNumMax++;

    return ucSequencNum;
}

/*****************************************************************************
 Function Name   : NAS_LPP_ApplyTransNum
 Description     : ��UE����������һ��transactionʱ����Ҫ����һ��transaction
                   number��
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT8

 History         :
    1.XiaoJun      2015-7-15  Draft Enact

*****************************************************************************/
VOS_UINT8 NAS_LPP_ApplyTransNum( VOS_VOID )
{
    NAS_LPP_ENTITY_STRU     *pstLppCtx;
    VOS_UINT8 ucTransNum;

    pstLppCtx = NAS_LPP_GetLppEntityCtx();
    ucTransNum = pstLppCtx->ucTransNum;
    pstLppCtx->ucTransNum++;

    return ucTransNum;
}


NAS_LPP_MSG_IDENTITY_STRU* NAS_LPP_GetUpLinkMsgIndetity
(
    VOS_UINT32          ulUpBufferIndex
)
{
    return &(NAS_LPP_GetLppUpMsgBuffPool()->astLppUpMsg[ulUpBufferIndex].stLppMsgIdentity);
}

VOS_UINT32 NAS_LPP_GetUpLinkSessionId
(
    VOS_UINT32          ulUpBufferIndex
)
{
    return NAS_LPP_GetUpLinkMsgIndetity(ulUpBufferIndex)->ulSessionId;
}


VOS_UINT32 NAS_LPP_GetUpLinkTransactionNumber
(
    VOS_UINT32          ulUpBufferIndex
)
{
    return NAS_LPP_GetUpLinkMsgIndetity(ulUpBufferIndex)->stTransId.ucTransactionNumber;
}


VOS_UINT32 NAS_LPP_GetUpLinkSequenceNumber
(
    VOS_UINT32          ulUpBufferIndex
)
{
    return NAS_LPP_GetUpLinkMsgIndetity(ulUpBufferIndex)->usSequnceNum;
}


VOS_UINT32 NAS_LPP_GetDownlinkMsgType
(
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    return  (pstLppMsg->stLppMessageBody.u.stC1.ulChoice);
}


LPP_UPLINK_MSG_BUF_STRU* NAS_LPP_FindUpLinkBuffer
(
    VOS_UINT8                           ucSequenceNum,
    VOS_UINT32                          ulSessionId
)
{
    VOS_UINT32                      ulLoop              = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*����1��ʾ��Ӧ��buffer������ʵ��ģ������*/
        if(0 != ((pstUpMsgBuffPool->ulBitMap) & (0x1<<ulLoop)))
        {
            if((NAS_LPP_GetUpLinkSessionId(ulLoop) == ulSessionId)
                && (NAS_LPP_GetUpLinkSequenceNumber(ulLoop) == ucSequenceNum))
            {
                /*����ҵ��ˣ��򷵻ض�Ӧ�����л���buffer*/
                return &(NAS_LPP_GetLppUpMsgBuffPool()->astLppUpMsg[ulLoop]);
            }
        }
    }

    /*����������û���ҵ����򷵻ؿ�*/
    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchUpMsgBuff
 Description     :
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-30  Draft Enact

*****************************************************************************/
LPP_UPLINK_MSG_BUF_STRU*   NAS_LPP_SearchUpMsgBuff
(
    VOS_UINT32             ulSessionId,
    NAS_LPP_TRANS_ID_STRU *pstTransId
)
{
    VOS_UINT32                      ulLoop              = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*����1��ʾ��Ӧ��buffer������ʵ��ģ������*/
        if(0 != ((pstUpMsgBuffPool->ulBitMap) & (0x1<<ulLoop)))
        {
            if( (NAS_LPP_GetUpLinkSessionId(ulLoop) == ulSessionId)
              &&(NAS_LPP_GetUpLinkTransactionNumber(ulLoop) == pstTransId->ucTransactionNumber)
              &&(NAS_LPP_UPLINK_MSG_TYPE_PROCESS == NAS_LPP_GetUpLinkMsgIndetity(ulLoop)->enUplinkMsgType))
            {
                /*����ҵ��ˣ��򷵻ض�Ӧ�����л���buffer*/
                return &(NAS_LPP_GetLppUpMsgBuffPool()->astLppUpMsg[ulLoop]);
            }
        }
    }

    /*����������û���ҵ����򷵻ؿ�*/
    return NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SearchUpMsgBuffByTrnasId
 Description     : ����trans id��Ѱ���еĻ���buffer
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-8-6  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_SearchUpMsgBuffByTrnasId
(
    NAS_LPP_TRANS_ID_STRU                *pstTransId,
    NAS_LPP_UP_MSG_BUFF_SEARCH_RSLT_STRU *pstSearchRslt
)
{
    VOS_UINT32                      ulLoop              = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;
    LPP_UPLINK_MSG_BUF_STRU        *pstLppUpMsgBuf      = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    pstSearchRslt->ucNum = 0;

    for(ulLoop = 0; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++)
    {
        /*����1��ʾ��Ӧ��buffer������ʵ��ģ������*/
        if(0 != ((pstUpMsgBuffPool->ulBitMap) & (0x1<<ulLoop)))
        {
            pstLppUpMsgBuf = &(pstUpMsgBuffPool->astLppUpMsg[ulLoop]);

            if( (pstLppUpMsgBuf->stLppMsgIdentity.stTransId.ucTransactionNumber == pstTransId->ucTransactionNumber)
              &&(pstLppUpMsgBuf->stLppMsgIdentity.stTransId.enInitiator == pstTransId->enInitiator) )
            {
                pstSearchRslt->aucIndex[pstSearchRslt->ucNum] = (VOS_UINT8)ulLoop;
                pstSearchRslt->ucNum++;

                /*���װ���ˣ��˳�*/
                if ( pstSearchRslt->ucNum >= NAS_LPP_MAX_UP_MSG_PER_TRANSACTION)
                {
                    NAS_LPP_ERR_LOG2("search up buffer overflow,transnum,init", pstTransId->ucTransactionNumber,pstTransId->enInitiator);
                    TLPS_PRINT2LAYER_ERROR1(NAS_LPP_SearchUpMsgBuffByTrnasId_ENUM, LNAS_LPP_TransactionUpBufferOverFlow, pstSearchRslt->ucNum);
                    break;
                }

            }
        }
    }


    return;
}



/*****************************************************************************
 Function Name   : NAS_LPP_MallocUpMsgBuffer
 Description     : Ϊ����LPP��Ϣ�����ش��Ļ���buffer
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
LPP_UPLINK_MSG_BUF_STRU  *NAS_LPP_MallocUpMsgBuffer(VOS_UINT8 *pucUplinkBuffIndx)
{
    VOS_UINT32 ulLoop;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU *pstUpMsgBuffPool;
    LPP_UPLINK_MSG_BUF_STRU *pstLppUpMsgBuf = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    *pucUplinkBuffIndx = PS_NULL_UINT8;

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++ )
    {
        if ( 0 == (pstUpMsgBuffPool->ulBitMap & (0x1<<ulLoop)) )
        {
            pstLppUpMsgBuf = &pstUpMsgBuffPool->astLppUpMsg[ulLoop];

            pstUpMsgBuffPool->ulBitMap = pstUpMsgBuffPool->ulBitMap | (0x1<<ulLoop);
            *pucUplinkBuffIndx  = (VOS_UINT8)ulLoop;
            break;
        }
    }

    if (*pucUplinkBuffIndx >= NAS_LPP_MAX_BUFF_MSG_COUNT)
    {
        NAS_LPP_OmUpMsgBuffMallocFailInd(pstUpMsgBuffPool->astUpmsgSeq,pstUpMsgBuffPool->ulBitMap);
    }

    return pstLppUpMsgBuf;
}


NAS_LPP_UP_MSG_SEQUENCE_STRU* NAS_LPP_GetUpLinkMsgBuffSeqByIndex(VOS_UINT8 ucIndex, VOS_UINT8 *pucLoop)
{
    VOS_UINT8                       ucLoop              = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU  *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;
    *pucLoop  = PS_NULL_UINT8;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    for(ucLoop = 0; ucLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ucLoop++)
    {
        if((PS_TRUE == pstUpMsgBuffPool->astUpmsgSeq[ucLoop].ucUsedFlag)
           &&(ucIndex == pstUpMsgBuffPool->astUpmsgSeq[ucLoop].ucUpLinkBuffIndex))
        {
            *pucLoop = ucLoop;
            return &(pstUpMsgBuffPool->astUpmsgSeq[ucLoop]);
        }
    }

    return NAS_LPP_NULL_PTR;
}


VOS_VOID NAS_LPP_ClearUpLinkMsgIndex(VOS_UINT8 ucUpLinkBuffIndex)
{
    NAS_LPP_UP_MSG_SEQUENCE_STRU        *pstUpLinkSeq       = NAS_LPP_NULL_PTR;
    VOS_UINT8                            ucUplinkSeqLoop    = 0;
    VOS_UINT32                           ulLoop             = 0;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU       *pstUpMsgBuffPool    = NAS_LPP_NULL_PTR;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ClearUpLinkMsgIndex_ENUM, LNAS_LPP_Func_Enter);
    pstUpLinkSeq = NAS_LPP_GetUpLinkMsgBuffSeqByIndex(ucUpLinkBuffIndex, &ucUplinkSeqLoop);
    if(NAS_LPP_NULL_PTR == pstUpLinkSeq)
    {
        NAS_LPP_ERR_LOG1("NAS_LPP_ClearUpLinkMsgIndex: Don't find Uplink Seq, UpBuffer Index =", ucUpLinkBuffIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ClearUpLinkMsgIndex_ENUM, LNAS_LPP_SEARCH_UPLINK_BUFFER_FAIL, ucUpLinkBuffIndex);
        return;
    }

    /*�ƶ���ʱ����Ȼ�Ḳ��ԭ��index�߼��� ��ʾ��д�ϣ��������*/
    pstUpLinkSeq->ucUsedFlag = PS_FALSE;
    pstUpLinkSeq->ucUpLinkBuffIndex = PS_NULL_UINT8;

    /*����ɾ���ľ������һ����Ա����ֱ�ӷ��أ������ƶ�*/
    if((NAS_LPP_MAX_BUFF_MSG_COUNT - 1) == ucUplinkSeqLoop)
    {
        return;
    }

    for(ulLoop = ucUplinkSeqLoop; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT - 1; ulLoop++)
    {
        pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag        =
                                    pstUpMsgBuffPool->astUpmsgSeq[ulLoop + 1].ucUsedFlag;
        pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUpLinkBuffIndex =
                                    pstUpMsgBuffPool->astUpmsgSeq[ulLoop + 1].ucUpLinkBuffIndex;
    }

    /*�ƶ���ɺ����һ����Ա��ֵ��û��ʹ�õ�״̬*/
    pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUsedFlag        = PS_FALSE;
    pstUpMsgBuffPool->astUpmsgSeq[ulLoop].ucUpLinkBuffIndex = PS_NULL_UINT8;

    return;
}


/*****************************************************************************
 Function Name   : NAS_LPP_RelUpMsgBuffer
 Description     : �ͷ�����LPP�ش���buffer
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RelUpMsgBuffer( LPP_UPLINK_MSG_BUF_STRU **ppstLppUpMsgBuf )
{
    VOS_UINT32 ulLoop;
    NAS_LPP_UP_MSG_BUFF_POOL_STRU *pstUpMsgBuffPool;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    for ( ulLoop = 0 ; ulLoop < NAS_LPP_MAX_BUFF_MSG_COUNT; ulLoop++ )
    {
        if ( *ppstLppUpMsgBuf == &pstUpMsgBuffPool->astLppUpMsg[ulLoop] )
        {
            TLPS_PRINT2LAYER_INFO1(NAS_LPP_RelUpMsgBuffer_ENUM, LNAS_LPP_SUCC_RELEASE_UPLINK_MSG_BUFFER, ulLoop);
            /*��ջ���buffer��index*/
            NAS_LPP_ClearUpLinkMsgIndex((VOS_UINT8)ulLoop);

            /*lint -e502*/
            pstUpMsgBuffPool->ulBitMap = (pstUpMsgBuffPool->ulBitMap &(~(0x1<<ulLoop)));
            /*lint +e502*/

            NAS_LPP_MEM_SET(*ppstLppUpMsgBuf,0,sizeof(LPP_UPLINK_MSG_BUF_STRU));

            NAS_LPP_OmUpMsgBuffRelInd((VOS_UINT8)ulLoop,pstUpMsgBuffPool->astUpmsgSeq,pstUpMsgBuffPool->ulBitMap);
            break;
        }
    }

    *ppstLppUpMsgBuf = NAS_LPP_NULL_PTR;
}

/*****************************************************************************
 Function Name   : NAS_LPP_RelUpMsgBufferByIndex
 Description     : ����index�ͷ�����msg��buffer
 Input           :VOS_UINT8 ucIndex
 Output          : None
 Return          : VOS_VOID

 History         :
    1.XiaoJun      2015-8-6  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LPP_RelUpMsgBufferByIndex( VOS_UINT8 ucIndex )
{
    NAS_LPP_UP_MSG_BUFF_POOL_STRU *pstUpMsgBuffPool;

    pstUpMsgBuffPool = NAS_LPP_GetLppUpMsgBuffPool();

    if (ucIndex >= NAS_LPP_MAX_BUFF_MSG_COUNT)
    {
        NAS_LPP_ERR_LOG1("wrong index for release up msg", ucIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_RelUpMsgBufferByIndex_ENUM, LNAS_LPP_ERROR_INDEX_FOR_UPLINK_MSG, ucIndex);
        return;
    }

    /*��ջ���buffer��index*/
    NAS_LPP_ClearUpLinkMsgIndex(ucIndex);

    /*lint -e502*/
    pstUpMsgBuffPool->ulBitMap = (pstUpMsgBuffPool->ulBitMap &(~(0x1<<ucIndex)));
    /*lint +e502*/

    NAS_LPP_MEM_SET(&(pstUpMsgBuffPool->astLppUpMsg[ucIndex]),0,sizeof(LPP_UPLINK_MSG_BUF_STRU));

    NAS_LPP_OmUpMsgBuffRelInd(ucIndex,pstUpMsgBuffPool->astUpmsgSeq,pstUpMsgBuffPool->ulBitMap);
    return;
}


/*****************************************************************************
 Function Name   : NAS_LPP_MallocCommCfgInfoElement
 Description     : ��ȡһ�����еĹ������õĵ�Ԫ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
VOS_UINT8  NAS_LPP_MallocCommCfgInfoElementIndex( VOS_UINT8 ucTransIndex )
{
    NAS_LPP_COMM_CONFIG_INFO_POOL_STRU  *pstCommCfgInfoPool;
    VOS_UINT8 ucIndex = PS_NULL_UINT8;
    VOS_UINT8 ucLoop;

    pstCommCfgInfoPool = NAS_LPP_GetCommCfgInfoPool();
    for ( ucLoop = 0 ; ucLoop < NAS_LPP_MAX_POS_TECH; ucLoop++ )
    {
        if ( 0 == (pstCommCfgInfoPool->ulBitmap & (0x1 << ucLoop)) )
        {
            pstCommCfgInfoPool->ulBitmap = (pstCommCfgInfoPool->ulBitmap | (0x1 << ucLoop));
            ucIndex = ucLoop;
            break;
        }
    }

    NAS_LPP_OmCommCfgPoolMallocInd(ucTransIndex,ucIndex,pstCommCfgInfoPool->ulBitmap);

    return ucIndex;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseCommCfgInfoElementByIndex
 Description     : ͨ��index�ͷŹ������õ�Ԫ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseCommCfgInfoElementByIndex( VOS_UINT8 ucTransIndex, VOS_UINT8 ucIndex)
{
    NAS_LPP_COMM_CONFIG_INFO_POOL_STRU  *pstCommCfgInfoPool;

    pstCommCfgInfoPool = NAS_LPP_GetCommCfgInfoPool();
    if ( ucIndex >= NAS_LPP_MAX_POS_TECH )
    {
        NAS_LPP_INFO_LOG1("release wrong comm cfg pool index", ucIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_ReleaseCommCfgInfoElementByIndex_ENUM, LNAS_LPP_SEARCH_WRONG_CFG_INDEX, ucIndex);
        return;
    }
    /*lint -e502*/
    pstCommCfgInfoPool->ulBitmap = (pstCommCfgInfoPool->ulBitmap & (~(0x1 << ucIndex)));
    /*lint +e502*/

    NAS_LPP_MEM_SET( &pstCommCfgInfoPool->astLppCommCfgInfo[ucIndex], 0, sizeof(NAS_LPP_COMM_CONFIG_INFO_STRU) );

    pstCommCfgInfoPool->astLppCommCfgInfo[ucIndex].stReportCriteria.enType = NAS_LPP_REPORT_LOCATION_TYPE_BUTT;

    NAS_LPP_OmCommCfgPoolRelInd( ucTransIndex, ucIndex, pstCommCfgInfoPool->ulBitmap);

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetCommCfgInfoElementByIndex
 Description     : ��ȡcomm cfg info�ĵ�Ԫ�ĵ�ַ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-7  Draft Enact

*****************************************************************************/
NAS_LPP_COMM_CONFIG_INFO_STRU *NAS_LPP_GetCommCfgInfoElementByIndex( VOS_UINT8 ucIndex)
{
    NAS_LPP_COMM_CONFIG_INFO_POOL_STRU  *pstCommCfgInfoPool;
    NAS_LPP_COMM_CONFIG_INFO_STRU       *pstLppCommCfgInfo = NAS_LPP_NULL_PTR;

    pstCommCfgInfoPool = NAS_LPP_GetCommCfgInfoPool();

    if ( ucIndex >= NAS_LPP_MAX_POS_TECH )
    {
        NAS_LPP_ERR_LOG1("get wrong comm cfg pool index", ucIndex);
        TLPS_PRINT2LAYER_ERROR1(NAS_LPP_GetCommCfgInfoElementByIndex_ENUM, LNAS_LPP_SEARCH_WRONG_INDEX_FOR_POSITION_TECH, ucIndex);
        return pstLppCommCfgInfo;
    }

    pstLppCommCfgInfo = &(pstCommCfgInfoPool->astLppCommCfgInfo[ucIndex]);

    return pstLppCommCfgInfo;
}


/*****************************************************************************
 Function Name   : NAS_LPP_LppPlmn2NasPlmn
 Description     : ��LPP�տڵ�PLMN��ʽת�ɵ�ǰNAS��ͨ�ø�ʽ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_LppPlmn2NasPlmn
(
    LPP_MTA_COMMON_PLMN_IDENTITY_STRU   *pstLppPlmnId,
    VOS_UINT8                           *pucNasPlmnId
)
{
    pucNasPlmnId[0] = pstLppPlmnId->aucMcc[0] & 0x0f;
    pucNasPlmnId[0] = pucNasPlmnId[0] | ((VOS_UINT8)( pstLppPlmnId->aucMcc[1] << 4));

    pucNasPlmnId[1] = pstLppPlmnId->aucMcc[2] & 0x0f;

    if ( 3 == pstLppPlmnId->ucMncNum )
    {
        pucNasPlmnId[1] = pucNasPlmnId[1] | ((VOS_UINT8)(pstLppPlmnId->aucMnc[2] << 4));
    }

    pucNasPlmnId[2] = pstLppPlmnId->aucMnc[0] &0x0f;
    pucNasPlmnId[2] = pucNasPlmnId[2] | ((VOS_UINT8)(pstLppPlmnId->aucMnc[1] << 4));
}
/*****************************************************************************
 Function Name   : NAS_LPP_NasPlmn2LppPlmn
 Description     : ��NAS ͨ�õ�PLMNת��LPP�տڵ�PLMN��ʽ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-8-19  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_NasPlmn2LppPlmn
(
    VOS_UINT8                           *pucNasPlmnId,
    LPP_MTA_COMMON_PLMN_IDENTITY_STRU   *pstLppPlmnId
)
{
    /*plmn, ������ MCC0->PLMN0��4�� MCC1->PLMN0��4�� MCC2->PLMN1��4�� MNC0->PLMN2��4,
    MNC1->PLMN2��4�� MNC2->PLMN1 ��4����������FF�����ʾֻ��2������*/
    pstLppPlmnId->aucMcc[0] = pucNasPlmnId[0] & 0x0f;

    pstLppPlmnId->aucMcc[1] = (pucNasPlmnId[0] & 0xf0) >> 4;

    pstLppPlmnId->aucMcc[2] = pucNasPlmnId[1] & 0x0f;

    pstLppPlmnId->aucMnc[0] = pucNasPlmnId[2] & 0x0f;

    pstLppPlmnId->aucMnc[1] = (pucNasPlmnId[2] & 0xf0) >> 4;
    if(0x0f != ((pucNasPlmnId[1] & 0xf0) >> 4))
    {
        pstLppPlmnId->ucMncNum = 3;
        pstLppPlmnId->aucMnc[2] = (pucNasPlmnId[1] & 0xf0) >> 4;
    }
    else
    {
        pstLppPlmnId->ucMncNum = 2;
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_OtdoaAssistDataChng
 Description     : ��ǰ�Ƿ���otdoa��صĸ��������ڽ���provide assist dataʱ
                   �仯�ˣ�
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_BOOL  NAS_LPP_IsOtdoaAssistDataChng( VOS_VOID )
{
    NAS_LPP_CONFIG_PARA_STRU               *pstCfgPara;

    pstCfgPara = NAS_LPP_GetCfgPara();

    /*���otdoa�ĸ��������б仯��1������LRRCǰ��provide location infoʱ���ϱ�otdoa�ģ�2/otdoa��measure ind������*/

    if (NAS_LPP_SLCT == pstCfgPara->bitOtdoaAssisChng)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
/*****************************************************************************
 Function Name   : NAS_LPP_IsGnssAssistDataChng
 Description     : gnss�ĸ��������Ƿ�仯
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.XiaoJun      2015-9-2  Draft Enact

*****************************************************************************/
VOS_BOOL  NAS_LPP_IsGnssAssistDataChng( VOS_VOID )
{
    NAS_LPP_CONFIG_PARA_STRU               *pstCfgPara;

    pstCfgPara = NAS_LPP_GetCfgPara();

    /*���otdoa�ĸ��������б仯��1������LRRCǰ��provide location infoʱ���ϱ�gnss�ģ�2/gnss��measure ind������*/
    if (NAS_LPP_SLCT == pstCfgPara->bitGnssAssisChng)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*lint +e701*/

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
