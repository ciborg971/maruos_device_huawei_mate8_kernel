

#include "vos.h"
#include "Ps.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Common.h"
#include "Ssa_Define.h"
#include "Taf_Ssa_EncodeDef.h"
#include "SsDef.h"
#include "Taf_Tafm_Local.h"
#include "TafClientApi.h"
#include "PsNvId.h"
#include "NVIM_Interface.h"
#include "TafSdcLib.h"

#include "NasUsimmApi.h"
#include "NasComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_COMMON_C

SSA_TAG_STRU      gSsTagValue;

VOS_UINT8                  *gpucSsEncodeEndLocation;  /*�ִ�����λ��*/
VOS_UINT8                   gucSsCurLen;              /*��ǰ�ִ��ĳ���*/
VOS_UINT8                   gucSsCurInvokeId;         /*��ǰ��ʹ�õ�Invoke ID��ֵ*/
VOS_UINT8                  *gpucSsParaEndLocation;    /*��ǰSs����para���ֵĽ���λ��*/

/*SSA״̬��*/
SSA_STATE_TABLE_STRU        gastSsaStatetable[TAF_MAX_SSA_TI + 1];

ST_SSP_IES_SSPVERSION       gstSsVersion;

VOS_UINT8                   gucCurrentTi;

VOS_UINT32                  gulCurStrMaxLen;                                /*��ǰ�ִ�����󳤶�*/

/* USSD�Ĵ���ģʽ, Ĭ��ֵ��͸��ģʽ */
VOS_UINT16                  g_usTafSsaUssdTransMode   = AT_USSD_TRAN_MODE;

TAF_SSA_RETRY_CFG_STRU     g_stSsaRetryCfgInfo;

/* Added by n00355355 for User_Exp_Improve, 2015-8-25, begin */
/*****************************************************************************
 �� �� ��  : TAF_SSA_GetSsaRetryCfgInfo
 ��������  : ��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : g_stSsaRetryCfgInfo�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��25��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SSA_RETRY_CFG_STRU* TAF_SSA_GetSsaRetryCfgInfo(VOS_VOID)
{
    return  &g_stSsaRetryCfgInfo;
}
/* Added by n00355355 for User_Exp_Improve, 2015-8-25, end */

/*lint -save -e958 */


VOS_VOID  SSA_Init(VOS_VOID)
{

    VOS_UINT32                          ulIndex;

    /*������ȫ�ֱ�����ʼ��*/
    PS_MEM_SET(&gSsTagValue, 0, sizeof(SSA_TAG_STRU));
    PS_MEM_SET(gastSsaStatetable, 0, (TAF_MAX_SSA_TI + 1)*sizeof(SSA_STATE_TABLE_STRU));

    for (ulIndex = 0; ulIndex < (TAF_MAX_SSA_TI + 1); ulIndex++)
    {
        TAF_SSA_InitAllTimers(gastSsaStatetable[ulIndex].astSsaTimerCtx);
    }

    TAF_SSA_ReadSsRetryCfgNvim();

    /* Added by n00355355 for User_Exp_Improve, 2015-8-24, begin */
    TAF_SSA_ReadSsRetryCmSrvRejCfgNvim();
    /* Added by n00355355 for User_Exp_Improve, 2015-8-24, end */

    gucCurrentTi     = 0;
    gucSsCurInvokeId = 0;
    PS_MEM_SET(&gstSsVersion, 0, sizeof(ST_SSP_IES_SSPVERSION));



}
VOS_VOID  SSA_PowerOff(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        TAF_SSA_StopAllTimer(i);
    }
    SSA_Init();

#ifdef DMT
    Ss_TaskInit();
#endif

}

/*****************************************************************************
 Prototype      : SSA_PackMsgHeader
 Description    : ��COMPONENT��Parameter����֮���ͷ�����з�װ(operationcode, InvokeId,
                  ComponetType)
 Input          : ucOperationcode -- ������, ucMsgType -- ��Ϣ����,
                  ucTi -- ʹ�õ�Tiֵ
 Output         : *stFacility -- facility������
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_PackMsgHeader(ST_SSP_IES_FACILITY  *pstFacility, TAF_SS_OPERATION ucOperationcode,
                           TAF_SS_MSGTYPE ucMsgType, VOS_UINT8 ucTi, TAF_SS_ERROR usErrCode,
                           TAF_SS_REJECT ucProblemCode/*, TAF_SS_COMPONENTTYPE ucCmpNntType*/)
{
    VOS_UINT8               ucInvokeId;
    TAF_SS_COMPONENTTYPE    ucCmpNntType;

    /*��ȡINVOKE ID*/
    ucInvokeId = SSA_GetInvokeId(ucTi);

    /*�����REGISTER����,ΪINVOKE����*/
    if (TAF_SS_MSG_TYPE_REGISTER == ucMsgType)
    {
        gastSsaStatetable[ucTi].ucInvokeId = ucInvokeId;
        ucCmpNntType = TAF_SS_COMPONENT_TYPE_INVOKE;
    }
    /*������ʱ��Ϊ��return result����,������������������,���ó���Ӧ������*/
    else
    {
        ucCmpNntType = TAF_SS_COMPONENT_TYPE_RTRNRSLT;
    }

    /*��װoperation code*/
    if (VOS_NULL != ucOperationcode)
    {
        SSA_EncodeOperationCode(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), ucOperationcode);
        /*�����������USSD����ʱʱ����Ҫ�趨Sequence Tag*/
        if ((ucOperationcode == TAF_SS_GETPASSWORD) || (ucOperationcode == TAF_SS_USS_REQ))
        {
            SSA_EncodeSequenceTag(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt));
        }
    }
    /*��error code��ʱ��,Ϊretrun error����,��װerror code*/
    else if (VOS_NULL != usErrCode)
    {
        SSA_EncodeErrorCode(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), usErrCode);
        ucCmpNntType = TAF_SS_COMPONENT_TYPE_RTRNERR;
    }
    /*��problem code��ʱ��,Ϊreject����,��װ*/
    else if (VOS_NULL != ucProblemCode)
    {
        SSA_EncodeProblemCode(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), ucProblemCode);
        ucCmpNntType = TAF_SS_COMPONENT_TYPE_REJECT;
    }
    else
    {
        ;
    }


    /*ͷ����װINVOKE ID*/
    SSA_EncodeInvokeId(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), ucInvokeId);

    /*ͷ����װcomponent type*/
    SSA_EncodeComponentType(pstFacility->Facility, (VOS_UINT8*)&(pstFacility->ulCnt), ucCmpNntType);

    return SSA_SUCCESS;
}

VOS_VOID TAF_SSA_WaitNetworkRspTimerExpired(VOS_UINT8 ucTi)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU      *pstSsEvent;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "SSA_TimeoutProc:ERROR: Alloc Mem Fail");
        return;
    }


    /*�쿴״̬���е�ǰTi����ز���,ȷ��Ti�Ĳ����Ƿ�����*/
    if (SSA_IDLE == gastSsaStatetable[ucTi].ucState)
    {
        /*��ӡ�쳣��Ϣ*/
        SSA_LOG(WARNING_PRINT, "SSA_TimeoutProc:WARNING: Timer out,but Ti not exist");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    /*������෢��Release Complete��Ϣ,����֪ԭ��,��UE 1.5�ĳ�ʱ
    ��������, ��APP�����¼��ϱ�*/
    PS_MEM_SET(pstSsEvent, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
    pstSsEvent->OP_Error = 1;
    pstSsEvent->ClientId = gastSsaStatetable[ucTi].ClientId;
    pstSsEvent->OpId = gastSsaStatetable[ucTi].OpId;

    /* ��дErrorCode�������ǰ��UE������������ӣ��������糬ʱ��ErrorCode��Ҫ��������ԭ��ֵ
        AT�ϱ�+CUSD: 5ʱ���õ������������ErrorCodeΪTAF_ERR_TIME_OUT */
    if (TAF_SSA_USSD_MO_CONN_STATE == gastSsaStatetable[ucTi].ucUssdFlag)
    {
        pstSsEvent->ErrorCode = TAF_ERR_USSD_NET_TIMEOUT;
    }
    else
    {
        pstSsEvent->ErrorCode = TAF_ERR_TIME_OUT;
    }


    TAF_SsEventReport(pstSsEvent);
    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);

    SSA_ReturnError(0, ucTi, TAF_SS_MSG_TYPE_RLCOMPLETE,SS_CAUSE_RECOVERY_TIMER_EXPIRY);
}

/*****************************************************************************
 �� �� ��  : TAF_SSA_WaitAppRspTimerExpired
 ��������  : TI_TAF_SSA_WAIT_APP_RSP_TIMER��ʱ����ʱ�Ĵ���
 �������  : ucTi - transaction id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��15��
    ��    ��   : z001617
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SSA_WaitAppRspTimerExpired(VOS_UINT8  ucTi)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU      *pstSsEvent;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "TAF_SSA_WaitAppRspTimerExpired:ERROR: Alloc Mem Fail");
        return;
    }


    /*�쿴״̬���е�ǰTi����ز���,ȷ��Ti�Ĳ����Ƿ�����*/
    if (SSA_IDLE == gastSsaStatetable[ucTi].ucState)
    {
        /*��ӡ�쳣��Ϣ*/
        SSA_LOG(WARNING_PRINT, "TAF_SSA_WaitAppRspTimerExpired:WARNING: Timer out,but Ti not exist");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    /*������෢��Release Complete��Ϣ,����֪ԭ��,��UE 1.5�ĳ�ʱ
    ��������, ��APP�����¼��ϱ�*/
    PS_MEM_SET(pstSsEvent, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
    pstSsEvent->OP_Error = 1;
    pstSsEvent->ClientId = gastSsaStatetable[ucTi].ClientId;
    pstSsEvent->OpId = gastSsaStatetable[ucTi].OpId;

    /* ��дErrorCode�������ǰ��UE������������ӣ��������糬ʱ��ErrorCode��Ҫ��������ԭ��ֵ
        AT�ϱ�+CUSD: 5ʱ���õ������������ErrorCodeΪTAF_ERR_TIME_OUT */
    if (TAF_SSA_USSD_MT_CONN_STATE == gastSsaStatetable[ucTi].ucUssdFlag)
    {
        pstSsEvent->ErrorCode = TAF_ERR_USSD_USER_TIMEOUT;
    }
    else
    {
        pstSsEvent->ErrorCode = TAF_ERR_TIME_OUT;
    }


    TAF_SsEventReport(pstSsEvent);
    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);

    SSA_ReturnError(0, ucTi, TAF_SS_MSG_TYPE_RLCOMPLETE,SS_CAUSE_RECOVERY_TIMER_EXPIRY);
}



/*****************************************************************************
 Prototype      : SSA_CheckInvokeId
 Description    : �ж�Invoke ID��ֵ�Ƿ��쳣
 Input          : ucTi--Ti��ֵ  ucInvokeId--Invoke Id��ֵ
 Output         : ��
 Return Value   : ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_CheckInvokeId(VOS_UINT8 ucTi, VOS_UINT8  ucInvokeId)
{
    VOS_UINT32     i;

    /*�����ǰTi״̬������,���Һ�֮ǰ��Invoke Idֵ��ͬ,�򷵻�ʧ��*/
    for (i = 0; i < TAF_MAX_SSA_TI; i++)
    {
        if ((gastSsaStatetable[i].ucState == SSA_USED)
            &&(gastSsaStatetable[i].ucInvokeId == ucInvokeId))
        {
            return  SSA_FAILURE;
        }
    }
    return SSA_SUCCESS;

}


/*****************************************************************************
 Prototype      : SSA_GetInvokeId
 Description    : ��ȡ��ǰ���õ�Invoke Id(Invoke Id��һ��ѭ�������ķ�ʽ,��Χ��0~255)
 Input          : ucTi--Ti��ֵ
 Output         : ��
 Return Value   : Invoke Id��ֵ
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT8 SSA_GetInvokeId(VOS_UINT8 ucTi)
{
    VOS_UINT32    ulTmp;

    /*��ѯ��ǰTi��״̬��������е�Ti���Ѿ�ʹ�ã��򷵻ظ����Invoke IDֵ�����
    û�У�����ѡһ���µ�Invoke Idֵ(ѭ��������ʽ)*/
    if (gastSsaStatetable[ucTi].ucState == SSA_USED)
    {
        return gastSsaStatetable[ucTi].ucInvokeId;
    }
    else
    {
        gucSsCurInvokeId += 1;

        for (ulTmp = 0; ulTmp < TAF_MAX_SSA_TI; ulTmp ++)
        {
            if ((gastSsaStatetable[ulTmp].ucState == SSA_USED)
                &&(gastSsaStatetable[ulTmp].ucInvokeId == gucSsCurInvokeId))
            {
                gucSsCurInvokeId += 1;
                ulTmp = 0;
            }
        }

        return gucSsCurInvokeId;
    }
}


/*****************************************************************************
 Prototype      : SSA_GetPassWord
 Description    : �쿴��ǰ�Ƿ񱣴��иò������������
 Input          : *ucTi --  ��ǰ������Ti
 Output         : ��
 Return Value   : ���ҽ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_CheckPassWord(VOS_UINT8 ucTi)
{
    /*�����ǰTi״̬�����,����������Ч*/
    if ((gastSsaStatetable[ucTi].ucState == SSA_USED)
        &&(gastSsaStatetable[ucTi].ucPwdFlag == SSA_PASSWORD_VALID))
    {
        return  SSA_SUCCESS;
    }

    return SSA_FAILURE;
}
VOS_UINT32 SSA_CheckOperationCode(VOS_UINT8 ucTi, VOS_UINT8  ucOperationCode)
{
    switch (ucOperationCode)
    {
        case TAF_SS_REGISTERSS:
        case TAF_SS_ERASESS:
        case TAF_SS_ACTIVATESS:
        case TAF_SS_DEACTIVATESS:
        case TAF_SS_INTERROGATESS:
        case TAF_SS_PROCESS_USS_DATA:
        case TAF_SS_PROCESS_USS_REQ:
        case TAF_SS_USS_REQ:
        case TAF_SS_USS_NOTIFY:
        case TAF_SS_REGISTERPASSWORD:
        case TAF_SS_GETPASSWORD:
        case TAF_SS_ERASECC_ENTRY:
        /*case TAF_SS_FORWARDCHECKSS_INDICATION:*/
            return SSA_SUCCESS;
        default:
            return TAF_ERR_PARA_ERROR;
    }
}

/*****************************************************************************
 Prototype      : SSA_GetIdByTi
 Description    : ����Tiֵ����ȡClientId��OpId
 Input          : ucTi    -   �����Ti
 Output         : *pClientId -   APP/AT�ͻ��˱�ʶ
                  *pOpId       -   ������ʶ
 Return Value   : �������
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_GetIdByTi(VOS_UINT16 *pClientId, VOS_UINT8 *pOpId, VOS_UINT8 ucTi)
{

    /*TI��Ч��Χ��0-6,8-14*/
    if ((ucTi > TAF_MAX_SSA_TI) || (ucTi == TAF_MIDDLE_SSA_TI))
    {
        return SSA_FAILURE;
    }

    /* �ж�g_SsaStatetable[ucTi].ucState�Ƿ��Ѿ���ʹ��*/
    if ( gastSsaStatetable[ucTi].ucState == SSA_USED)
    {
        *pClientId = gastSsaStatetable[ucTi].ClientId;
        *pOpId = gastSsaStatetable[ucTi].OpId;
        return SSA_SUCCESS;
    }

    return SSA_FAILURE;

}

/* ɾ������SSA_GetTi()�����еĵ���ʹ��TAF_SSA_GetUssdTi()�滻 */

VOS_UINT32 TAF_SSA_GetUssdTi(VOS_UINT8 *pucTi)
{
    VOS_UINT8                           i;

    /* TI��Ч��Χ��0-6,8-14 */
    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        /* index=7ʱ���� */
        if (i != TAF_MIDDLE_SSA_TI)
        {
            if ( (SSA_USED == gastSsaStatetable[i].ucState)
              && ( (TAF_SSA_USSD_MO_CONN_STATE == gastSsaStatetable[i].ucUssdFlag)
                || (TAF_SSA_USSD_MT_CONN_STATE == gastSsaStatetable[i].ucUssdFlag) ) )
            {
                *pucTi = i;
                return SSA_SUCCESS;
            }
        }
     }

    /* δ�ҵ�ƥ��� */
    return SSA_FAILURE;

}
VOS_UINT32 SSA_TiAlloc(VOS_UINT16 ClientId, VOS_UINT8 OpId, VOS_UINT8 *pucTi)
{
    VOS_UINT8     ucAllocTi = TAF_MIDDLE_SSA_TI;
    VOS_UINT32    i = 0;

    for (i = 0; i < TAF_MIDDLE_SSA_TI; i++)
    {
        /*MOʱTI��Χ��0-6*/
        if (SSA_IDLE == gastSsaStatetable[i].ucState)
        {   /*�п���TI*/
            ucAllocTi = (VOS_UINT8)i;
        }
        /*���з�������APPʱ����������ͬClientId��OpIdͬʱ������������*/
        else if ((gastSsaStatetable[i].ClientId == ClientId)
                  &&(gastSsaStatetable[i].OpId == OpId))
        {
            return SSA_FAILURE;   /*�Ƿ�Ӧ�ø�֪APP�䷢�������clientid��Opid��ֵ����*/
        }
        else
        {
            ;
        }
    }

    if (ucAllocTi < TAF_MIDDLE_SSA_TI)
    {
        /*TI����ɹ�*/
        gastSsaStatetable[ucAllocTi].ClientId = ClientId;
        gastSsaStatetable[ucAllocTi].OpId = OpId;
        gastSsaStatetable[ucAllocTi].ucState = SSA_USED;
        gastSsaStatetable[ucAllocTi].ucPwdFlag = SSA_PASSWORD_INVALID;
        *pucTi = ucAllocTi;

        /* TI����ɹ�֮����һ��CS���SSҵ���Ƿ���ڵı�־ */
        TAF_SDC_SetCsSsSrvExistFlg(VOS_TRUE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
        TAF_SendMtcCsSrvInfoInd();
#endif

        return SSA_SUCCESS;
    }
    else
    {
        /*û�п���TI*/
        return SSA_FAILURE;
    }
}

/*****************************************************************************
 Prototype      : Taf_SsaTiFree
 Description    : Ssaģ���ͷ�Ti
 Input          : ucTi -- �����Ti
 Output         :
 Return Value   : �������
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: UE 1.5d function
*****************************************************************************/
VOS_UINT32 SSA_TiIdle(VOS_VOID)
{
    VOS_UINT32  i;

    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        /*index=7ʱ����*/
        if (i != TAF_MIDDLE_SSA_TI)
        {
            /*�����ǰ��ClientId��OpId��״̬���е�CliendId��OpId��ͬ��ɹ���ȡTi,
            ���������֮ǰ�㲥�ϱ���Ti,���滻ԭ�е�CliendId��OpId*/
            if (gastSsaStatetable[i].ucState == SSA_USED)
            {
                return SSA_USED;
            }
        }
    }

    return   SSA_IDLE;
}


VOS_VOID SSA_TiFree(VOS_UINT8 ucTi)
{
    if ((ucTi > TAF_MAX_SSA_TI) || (ucTi == TAF_MIDDLE_SSA_TI))
    {
        SSA_LOG1(WARNING_PRINT, "SSA_TiFree:WARNING: Ti Value is Wrong, ucTi:", ucTi);
        return;
    }

    if (VOS_NULL_PTR != gastSsaStatetable[ucTi].pstUssdBuf)
    {
        PS_MEM_FREE(WUEPS_PID_SS, gastSsaStatetable[ucTi].pstUssdBuf);
        gastSsaStatetable[ucTi].pstUssdBuf = VOS_NULL_PTR;
    }

    PS_MEM_SET(&gastSsaStatetable[ucTi], 0, sizeof(SSA_STATE_TABLE_STRU));

    /* ��ǰTi�ͷ�����֮���ж�һ���Ƿ����е�TI���ͷ��ˣ�
        ������е�TI���ͷ��ˣ���һ��CS���SSҵ�񲻴��ڵı�־ */
    if (SSA_IDLE == SSA_TiIdle())
    {
        TAF_SDC_SetCsSsSrvExistFlg(VOS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
        TAF_SendMtcCsSrvInfoInd();
#endif
    }

    return ;
}
VOS_UINT8 SSA_GetRepEvtFromOpCode(VOS_UINT8  ucOprationCode)
{
    switch (ucOprationCode)
    {
        case TAF_SS_REGISTERSS:
            return TAF_SS_EVT_REGISTERSS_CNF;

        case TAF_SS_ERASESS:
            return TAF_SS_EVT_ERASESS_CNF;

        case TAF_SS_ACTIVATESS:
            return TAF_SS_EVT_ACTIVATESS_CNF;

        case TAF_SS_DEACTIVATESS:
            return TAF_SS_EVT_DEACTIVATESS_CNF;

        case TAF_SS_INTERROGATESS:
            return TAF_SS_EVT_INTERROGATESS_CNF;

        case TAF_SS_PROCESS_USS_DATA:
            return TAF_SS_EVT_PROCESS_USS_REQ_CNF;

        case TAF_SS_PROCESS_USS_REQ:
            return TAF_SS_EVT_PROCESS_USS_REQ_CNF;

        case TAF_SS_USS_REQ:
            return TAF_SS_EVT_USS_REQ_IND;

        case TAF_SS_USS_NOTIFY:
            return TAF_SS_EVT_USS_NOTIFY_IND;

        case TAF_SS_REGISTERPASSWORD:
            return TAF_SS_EVT_REG_PASSWORD_CNF;

        case TAF_SS_GETPASSWORD:
            return TAF_SS_EVT_GET_PASSWORD_IND;

        case TAF_SS_ERASECC_ENTRY:
            return TAF_SS_EVT_ERASE_CC_ENTRY_CNF;

        /* case TAF_SS_FORWARDCHECKSS_INDICATION: */
        /* return TAF_SS_EVT_FORWARDCHECKSS_INDICATION; */

        default:
            return TAF_SS_EVT_ERROR;
    }
}


VOS_UINT16  SSA_GetUssdTransMode(VOS_VOID)
{
    /* ��g_usTafSsaUssdTransMode�Ƿ����򷵻�AT_USSD_TRAN_MODE */
    if ((AT_USSD_NON_TRAN_MODE != g_usTafSsaUssdTransMode)
     && (AT_USSD_TRAN_MODE != g_usTafSsaUssdTransMode))
    {
        SSA_LOG(WARNING_PRINT, "SSA_GetUssdTransMode: usUssdTransMode is Abnormal!");

        return AT_USSD_TRAN_MODE;
    }

    /* g_usTafSsaUssdTransModeֵ�Ϸ� */
    return g_usTafSsaUssdTransMode;
}


VOS_VOID  TAF_SSA_UpdateUssdRptStatus(
    TAF_SS_PROCESS_USS_REQ_STRU        *pstSsReqMsg
)
{
    VOS_UINT32                               ulRptCmdStatus;

    ulRptCmdStatus  = VOS_TRUE;

    /* ����CUSD��Ӧ��SDCȫ�ֱ��� */
    if (TAF_SS_CUSD_TYPE_ENABLE == pstSsReqMsg->enCusdType)
    {
        ulRptCmdStatus = VOS_TRUE;
    }
    else
    {
        ulRptCmdStatus = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, ulRptCmdStatus);

    return;
}
VOS_UINT32 TAF_SSA_IsUssdStateIdle(VOS_VOID)
{
    VOS_UINT32  i;

    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        /*index=7ʱ����*/
        if (i != TAF_MIDDLE_SSA_TI)
        {
            /*�����ǰ��ClientId��OpId��״̬���е�CliendId��OpId��ͬ��ɹ���ȡTi,
            ���������֮ǰ�㲥�ϱ���Ti,���滻ԭ�е�CliendId��OpId*/
            if ( (TAF_SSA_USSD_MO_CONN_STATE == gastSsaStatetable[i].ucUssdFlag)
              || (TAF_SSA_USSD_MT_CONN_STATE == gastSsaStatetable[i].ucUssdFlag) )
            {
                return VOS_FALSE;
            }
        }
    }

    return   VOS_TRUE;
}


VOS_UINT8 TAF_SSA_GetSsRetrySupportFlg(VOS_VOID)
{
    return g_stSsaRetryCfgInfo.ucIsSsRetrySupportFlg;
}


VOS_VOID TAF_SSA_SetSsRetrySupportFlg(VOS_UINT8 ucIsSsRetrySupportFlg)
{
    g_stSsaRetryCfgInfo.ucIsSsRetrySupportFlg = ucIsSsRetrySupportFlg;
}


VOS_UINT32 TAF_SSA_GetSsRetryIntervalTimerLen(VOS_VOID)
{
    return g_stSsaRetryCfgInfo.ulSsRetryInterval;
}


VOS_VOID TAF_SSA_SetSsRetryIntervalTimerLen(VOS_UINT32 ulSsRetryInterval)
{
    g_stSsaRetryCfgInfo.ulSsRetryInterval = ulSsRetryInterval;
}


VOS_UINT32 TAF_SSA_GetSsRetryPeriodTimerLen(VOS_VOID)
{
    return g_stSsaRetryCfgInfo.ulSsRetryPeriod;
}


VOS_VOID TAF_SSA_SetSsRetryPeriodTimerLen(VOS_UINT32 ulSsRetryPeriod)
{
    g_stSsaRetryCfgInfo.ulSsRetryPeriod = ulSsRetryPeriod;
}


VOS_VOID  TAF_SSA_ReadSsRetryCfgNvim( VOS_VOID )
{
    TAF_SSA_NVIM_RETRY_CFG_STRU         stSsaRetryCfg;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    /* GCF����,ss�ط�������Ҫ�ر� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        TAF_SSA_SetSsRetrySupportFlg(VOS_FALSE);
        TAF_SSA_SetSsRetryIntervalTimerLen(0);
        TAF_SSA_SetSsRetryPeriodTimerLen(0);

        return;
    }

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_SS_Retry_CFG, &ulLength);

    PS_MEM_SET(&stSsaRetryCfg, 0x0, sizeof(TAF_SSA_NVIM_RETRY_CFG_STRU));

    if (ulLength > sizeof(TAF_SSA_NVIM_RETRY_CFG_STRU))
    {
        MN_WARN_LOG("TAF_SS_ReadSsaRetryCfgNvim():WARNING: en_NV_Item_SS_Retry_CFG length Error");

        TAF_SSA_SetSsRetrySupportFlg(VOS_FALSE);
        TAF_SSA_SetSsRetryIntervalTimerLen(0);
        TAF_SSA_SetSsRetryPeriodTimerLen(0);

        return;
    }

    /* ���NV��ȡʧ�ܣ�������Ϊ������ */
    if (NV_OK != NV_Read(en_NV_Item_SS_Retry_CFG,
                         &stSsaRetryCfg, ulLength))
    {
        MN_WARN_LOG("TAF_SS_ReadSsaRetryCfgNvim():WARNING: en_NV_Item_SS_Retry_CFG Error");
        TAF_SSA_SetSsRetrySupportFlg(VOS_FALSE);
        TAF_SSA_SetSsRetryIntervalTimerLen(0);
        TAF_SSA_SetSsRetryPeriodTimerLen(0);

        return;
    }

    if (VOS_TRUE == stSsaRetryCfg.ucIsSsRetrySupportFlg)
    {
        TAF_SSA_SetSsRetrySupportFlg(VOS_TRUE);

        /* nv�д��ʱ��Ϊ�룬��Ҫת��Ϊ���� */
        TAF_SSA_SetSsRetryPeriodTimerLen(TAF_SSA_ONE_THOUSAND_MILLISECOND * stSsaRetryCfg.ulSsRetryPeriod);
        TAF_SSA_SetSsRetryIntervalTimerLen(TAF_SSA_ONE_THOUSAND_MILLISECOND * stSsaRetryCfg.ulSsRetryInterval);
    }
    else
    {
        TAF_SSA_SetSsRetrySupportFlg(VOS_FALSE);
        TAF_SSA_SetSsRetryIntervalTimerLen(0);
        TAF_SSA_SetSsRetryPeriodTimerLen(0);

    }

    return;
}

/* Added by n00355355 for User_Exp_Improve, 2015-8-24, begin */
/*****************************************************************************
 �� �� ��  : TAF_SSA_ReadSsRetryCmSrvRejCfgNvim
 ��������  : ��ȡNVIM�е�en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SSA_ReadSsRetryCmSrvRejCfgNvim( VOS_VOID )
{
    TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU      stSsRetryCmSrvRejCfg;
    VOS_UINT32                                  ulLength;

    ulLength = 0;

    /* GCF����,ss�ط�������Ҫ�ر� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        g_stSsaRetryCfgInfo.ucSsRetryCmSrvRejCauseNum = 0;
        return;
    }

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG, &ulLength);

    PS_MEM_SET(&stSsRetryCmSrvRejCfg, 0x0, sizeof(TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU));

    if (ulLength > sizeof(TAF_SSA_NVIM_RETRY_CM_SRV_REJ_CFG_STRU))
    {
        MN_WARN_LOG("TAF_SSA_ReadSsRetryCmSrvRejCfgNvim():WARNING: en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG length Error");

        g_stSsaRetryCfgInfo.ucSsRetryCmSrvRejCauseNum = 0;
        return;
    }

    /* ���NV��ȡʧ�ܣ�������Ϊ������ */
    if (NV_OK != NV_Read(en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG,
                         &stSsRetryCmSrvRejCfg, ulLength))
    {
        MN_WARN_LOG("TAF_SSA_ReadSsRetryCmSrvRejCfgNvim():WARNING: en_NV_Item_SS_RETRY_CM_SRV_REJ_CAUSE_CFG Error");
        g_stSsaRetryCfgInfo.ucSsRetryCmSrvRejCauseNum = 0;
        return;
    }

    if (stSsRetryCmSrvRejCfg.ucSsRetryCmSrvRejCauseNum > TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM)
    {
        stSsRetryCmSrvRejCfg.ucSsRetryCmSrvRejCauseNum = TAF_NVIM_SS_RETRY_CAUSE_MAX_NUM;
    }

    g_stSsaRetryCfgInfo.ucSsRetryCmSrvRejCauseNum = stSsRetryCmSrvRejCfg.ucSsRetryCmSrvRejCauseNum;
    PS_MEM_CPY(g_stSsaRetryCfgInfo.aucSsRetryCmSrvRejCause,
               stSsRetryCmSrvRejCfg.aucSsRetryCmSrvRejCause,
               stSsRetryCmSrvRejCfg.ucSsRetryCmSrvRejCauseNum);
    return;
}

/* Added by n00355355 for User_Exp_Improve, 2015-8-24, end */


VOS_VOID TAF_SSA_ClearBufferedMsg(VOS_UINT8 ucTi)
{
    PS_MEM_SET(&gastSsaStatetable[ucTi].stSsaBufferedMsg, 0x0, sizeof(TAF_SSA_MSG_BUFF_STRU));
    return;
}


TAF_SSA_MSG_BUFF_STRU*  TAF_SSA_GetBufferedMsg( VOS_UINT8 ucTi )
{
    return &(gastSsaStatetable[ucTi].stSsaBufferedMsg);
}


VOS_UINT32  TAF_SSA_GetTimerRemainLen(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
)
{
    VOS_UINT32                          ulTick;
    TAF_SSA_TIMER_CXT_STRU             *pstSsaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    ulTick         = 0;

    /*TI��Ч��Χ��0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_GetTimerRemainLen: Ti invalid!");
        return ulTick;
    }

    pstSsaTimerCtx = gastSsaStatetable[ucTi].astSsaTimerCtx;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_SSA_TIMER_STATUS_RUNING  == pstSsaTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstSsaTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if (i >= TAF_SSA_MAX_TIMER_NUM)
    {
        /* ������˵���˶�ʱ���ѳ�ʱ��ֹͣ */
        ulTick = 0;
        return ulTick;
    }

    /* ���Ϊ��ʱ��˵���˶�ʱ���ѳ�ʱ��ֹͣ */
    if (VOS_NULL_PTR != pstSsaTimerCtx[i].hTimer)
    {
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstSsaTimerCtx[i].hTimer), &ulTick))
        {
            ulTick = 0;
        }
    }

    /* tickֵ����10ת��Ϊ���� */
    return ulTick * TAF_SSA_TIMER_TICK;
}



TAF_SSA_TIMER_STATUS_ENUM_UINT8  TAF_SSA_GetTimerStatus(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
)
{
    TAF_SSA_TIMER_CXT_STRU             *pstSsaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /*TI��Ч��Χ��0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_GetTimerStatus: Ti invalid!");
        return TAF_SSA_TIMER_STATUS_STOP;
    }

    pstSsaTimerCtx = gastSsaStatetable[ucTi].astSsaTimerCtx;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_SSA_TIMER_STATUS_RUNING  == pstSsaTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstSsaTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= TAF_SSA_MAX_TIMER_NUM)
    {
        return TAF_SSA_TIMER_STATUS_STOP;
    }

    return TAF_SSA_TIMER_STATUS_RUNING;

}
VOS_UINT32  TAF_SSA_StartTimer(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucTi
)
{
    TAF_SSA_TIMER_CXT_STRU             *pstSsaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;
    NAS_TIMER_OPERATION_STRU            stTimer;

    /*TI��Ч��Χ��0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StopTimer: Ti invalid!");
        return VOS_FALSE;
    }

    pstSsaTimerCtx   =  gastSsaStatetable[ucTi].astSsaTimerCtx;

    if (0 == ulLen)
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StartTimer: timer len is zero!");
        return VOS_FALSE;
    }

    /* ����ö�ʱ���Ѿ�������ֱ�ӷ��� */
    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_SSA_TIMER_STATUS_RUNING == pstSsaTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstSsaTimerCtx[i].enTimerId))
        {
            SSA_LOG1(WARNING_PRINT, "TAF_SSA_StartTimer:timer is running", enTimerId);
            return VOS_FALSE;
        }
    }

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( TAF_SSA_TIMER_STATUS_STOP == pstSsaTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if ( i >= TAF_SSA_MAX_TIMER_NUM)
    {
        SSA_LOG1(WARNING_PRINT, "TAF_SSA_StartTimer:too many timer", enTimerId);

        return VOS_FALSE;
    }

    if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    ulPrecision = NAS_GetTimerPrecision(WUEPS_PID_SS, enTimerId);

    ulRet = VOS_StartRelTimer(&(pstSsaTimerCtx[i].hTimer),
                              WUEPS_PID_SS,
                              ulLen,
                              enTimerId,
                              ucTi,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);

    if ( VOS_OK != ulRet)
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StartTimer: start timer failed!");

        return VOS_FALSE;
    }

    pstSsaTimerCtx[i].enTimerId     = enTimerId;
    pstSsaTimerCtx[i].enTimerStatus = TAF_SSA_TIMER_STATUS_RUNING;


    /* ��ʱ��״̬�������� */
    stTimer.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulSenderPid      = WUEPS_PID_SS;
    stTimer.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stTimer.MsgHeader.ulReceiverPid    = VOS_PID_TIMER;
    stTimer.MsgHeader.ulLength         = sizeof(NAS_TIMER_OPERATION_STRU) - VOS_MSG_HEAD_LENGTH;
    stTimer.MsgHeader.ulMsgName        = enTimerId;
    stTimer.ulTimeAction               = NAS_TIMER_OPERATION_START;
    stTimer.ulTimeLen                  = ulLen;

    DIAG_TraceReport(&stTimer);

    NAS_TIMER_EventReport(stTimer.MsgHeader.ulMsgName, WUEPS_PID_SS, NAS_OM_EVENT_TIMER_OPERATION_START);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SSA_StopTimer
 ��������  : ָֹͣ����SSA��ʱ��
 �������  : enTimerId - ��Ҫֹͣ�Ķ�ʱ��ID
             ucTi      - transaction id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��10��
    ��    ��   : z001617
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SSA_StopTimer(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
)
{
    TAF_SSA_TIMER_CXT_STRU             *pstSsTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /*TI��Ч��Χ��0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StopTimer: Ti invalid!");
        return;
    }

    pstSsTimerCtx = gastSsaStatetable[ucTi].astSsaTimerCtx;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( (TAF_SSA_TIMER_STATUS_RUNING  == pstSsTimerCtx[i].enTimerStatus )
          && (enTimerId                    == pstSsTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= TAF_SSA_MAX_TIMER_NUM)
    {
        SSA_LOG1(WARNING_PRINT, "TAF_SSA_StopTimer:too many timer", enTimerId);
        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstSsTimerCtx[i].hTimer)
    {
        (VOS_VOID)NAS_StopRelTimer(WUEPS_PID_SS, enTimerId, &pstSsTimerCtx[i].hTimer);
    }

    pstSsTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstSsTimerCtx[i].enTimerId     = TI_TAF_SSA_TIMER_BUTT;
    pstSsTimerCtx[i].enTimerStatus = TAF_SSA_TIMER_STATUS_STOP;

    return;
}


VOS_VOID  TAF_SSA_StopAllTimer(VOS_UINT8 ucTi)
{

    TAF_SSA_TIMER_CXT_STRU             *pstSsaTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /*TI��Ч��Χ��0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_StopTimer: Ti invalid!");
        return;
    }

    pstSsaTimerCtx =  gastSsaStatetable[ucTi].astSsaTimerCtx;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        if ( TAF_SSA_TIMER_STATUS_RUNING  == pstSsaTimerCtx[i].enTimerStatus )
        {
            TAF_SSA_StopTimer(pstSsaTimerCtx[i].enTimerId, ucTi);

            pstSsaTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstSsaTimerCtx[i].enTimerId     = TI_TAF_SSA_TIMER_BUTT;
            pstSsaTimerCtx[i].enTimerStatus = TAF_SSA_TIMER_STATUS_STOP;
        }
    }
}


/*****************************************************************************
 �� �� ��  : TAF_SSA_RetryPeriodTimerExpired
 ��������  : TI_TAF_SSA_RETRY_PERIOD_TIMER��ʱ����ʱ����
 �������  : ucTi - transaction id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��12��
    ��    ��   : z001617
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SSA_RetryPeriodTimerExpired(VOS_UINT8 ucTi)
{
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SSA_RetryIntervalTimerExpired
 ��������  : TI_TAF_SSA_RETRY_INTERVAL_TIMER��ʱ����ʱ����
 �������  : ucTi - transaction id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��12��
    ��    ��   : z001617
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SSA_RetryIntervalTimerExpired(VOS_UINT8 ucTi)
{
    TAF_SSA_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg  = TAF_SSA_GetBufferedMsg(ucTi);


    if (TAF_SSA_STATE_CONN_PENDING != gastSsaStatetable[ucTi].enSsaState)
    {
        SSA_LOG(INFO_PRINT, "TAF_SSA_RetryIntervalTimerExpired: ssa state is invalid.");
        TAF_SSA_ClearBufferedMsg(ucTi);
        TAF_SSA_StopTimer(TI_TAF_SSA_RETRY_PERIOD_TIMER, ucTi);
        return;
    }

    /* ȡ������Ϣ */
    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedBeginReqMsg)
    {
        Taf_SSA_ProcBufferedBeginReqMsg(&pstBufferdMsg->stBufferedBeginReqMsg);
        return;
    }

    SSA_LOG(INFO_PRINT, "TAF_SSA_RetryIntervalTimerExpired: buffered begin req msg is null!");
    TAF_SSA_StopTimer(TI_TAF_SSA_RETRY_PERIOD_TIMER, ucTi);

    return;

}


/*****************************************************************************
 �� �� ��  : TAF_SSA_RcvTimerExpired
 ��������  : SSA��ʱ����ʱ
 �������  : enTimerId - ��ʱ�Ķ�ʱ��ID
             ucTi      - transaction id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��12��
    ��    ��   : z001617
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SSA_RcvTimerExpired(
    TAF_SSA_TIMER_ID_ENUM_UINT8         enTimerId,
    VOS_UINT8                           ucTi
)
{
    /*TI��Ч��Χ��0-6,8-14*/
    if (VOS_FALSE == TAF_SSA_IsTiValid(ucTi))
    {
        SSA_LOG(WARNING_PRINT, "TAF_SSA_RcvTimerExpired: Ti invalid!");
        return;
    }

    TAF_SSA_StopTimer(enTimerId, ucTi);

    switch (enTimerId)
    {
        case TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER:
            TAF_SSA_WaitNetworkRspTimerExpired(ucTi);
            break;

        case TI_TAF_SSA_WAIT_APP_RSP_TIMER:
            TAF_SSA_WaitAppRspTimerExpired(ucTi);
            break;

        case TI_TAF_SSA_RETRY_PERIOD_TIMER:
            /*lint -e522*/
            TAF_SSA_RetryPeriodTimerExpired(ucTi);
            /*lint +e522*/
            break;

        case TI_TAF_SSA_RETRY_INTERVAL_TIMER:
            TAF_SSA_RetryIntervalTimerExpired(ucTi);
            break;

        default:
            SSA_LOG(WARNING_PRINT, "TAF_SSA_RcvTimerExpired: timer id is invalid!");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SSA_InitAllTimers
 ��������  : ��ʼ��ssa��ʱ��
 �������  : pstSsaTimerCtx - ��ʱ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��15��
    ��    ��   : z001617
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_SSA_InitAllTimers(
    TAF_SSA_TIMER_CXT_STRU              *pstSsaTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < TAF_SSA_MAX_TIMER_NUM ; i++ )
    {
        pstSsaTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstSsaTimerCtx[i].enTimerId     = TI_TAF_SSA_TIMER_BUTT;
        pstSsaTimerCtx[i].enTimerStatus = TAF_SSA_TIMER_STATUS_STOP;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_SSA_IsTiValid
 ��������  : �ж�ti�Ƿ�Ϸ�
 �������  : ucTi - Transaction id
 �������  : ��
 �� �� ֵ  : VOS_TRUE:ti�Ϸ�
             VOS_FALSE: ti�Ƿ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��15��
    ��    ��   : z001617
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_SSA_IsTiValid(
    VOS_UINT8                           ucTi
)
{
    /*TI��Ч��Χ��0-6,8-14*/
    if ((ucTi > TAF_MAX_SSA_TI)
     || (TAF_MIDDLE_SSA_TI == ucTi))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
