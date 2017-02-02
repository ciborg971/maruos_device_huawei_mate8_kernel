


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Ps.h"

#include "Taf_Common.h"
#include "Taf_Ssa_DecodeDef.h"
#include "TafAppSsa.h"
#include "MnErrorCode.h"
#include "NasComm.h"
#include "TafSdcCtx.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_DECODE_C



/*lint -save -e958 */

/******************************************************************************
 Prototype      : SSA_DecodeComponent
 Description    : ����component type�����з��ദ��
 Input          : *pEvent - �ϱ���APP�Ĳ���
                  *pucSrc   - ���յ����ִ�
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*******************************************************************************/
VOS_UINT32 SSA_DecodeComponent(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 *pucSrc)
{
    VOS_UINT32      ulRslt = SSA_SUCCESS;

    /*����component type���ͣ�������Ӧ���룬����:INVOKE, return result, return error, reject*/
    /*��component type ����״̬����*/
    /* pEvent->ComponentType = *pucSrc; */
    gastSsaStatetable[gucCurrentTi].uComponenttype = *pucSrc;

    switch (*pucSrc)
    {
        case TAF_SS_COMPONENT_TYPE_INVOKE:
            ulRslt = SSA_DecodeInvoke(pEvent, &pucSrc);
            break;

        case TAF_SS_COMPONENT_TYPE_RTRNRSLT:
            ulRslt = SSA_DecodeRtrnRslt(pEvent, &pucSrc);
            break;

        case TAF_SS_COMPONENT_TYPE_RTRNERR:
            ulRslt = SSA_DecodeRtrnErr(pEvent, &pucSrc);
            break;

        case TAF_SS_COMPONENT_TYPE_REJECT:
            ulRslt = SSA_DecodeReject(pEvent, &pucSrc);
            break;

        default:
            SSA_LOG(WARNING_PRINT, "SSA_DecodeComponent:WARNING: Component Type Unrecognized");
            return TAF_SS_REJ_UNRECOGNIZED_COMPONENT;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeInvoke(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8       ucOperationCode;
    /* VOS_UINT8      *pucEndLocation; */
    VOS_UINT32      ulRslt = SSA_SUCCESS;
    VOS_UINT8       ucTmpLen;

    /* ����tag�ֽ� */
    (*ppucSrc)++;

    /*��ȡcomponent����, TLV��ʽ��ͬʱָ����λ��V��ȷ������λ��*/
    ulRslt = SSA_DecodeLength(ppucSrc, &ucTmpLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Length Value Error");
    }
    gpucSsParaEndLocation = *ppucSrc + ucTmpLen;

    /*���INVOKE ID*/
    if (INVOKE_ID_TAG == **ppucSrc)
    {
        #if 0
        /*���INVOKE ID�ĺ����ԣ���Ӧ����,������ظ��ģ����������¼����*/
        if (SSA_SUCCESS != SSA_CheckInvokeId(gucCurrentTi, *(*ppucSrc + 2)))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Invoke Id Wrong");
            return TAF_SS_REJ_DUPLICATE_INVOKE_ID;
        }
        #endif

        gastSsaStatetable[gucCurrentTi].ucInvokeId = *(*ppucSrc + 2);
        gucSsCurInvokeId = *(*ppucSrc + 2);

        *ppucSrc = *ppucSrc + 3;

    }
    else
    {
        /*ȱ��Invoke Id,������Ϣ�������*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Invoke Id not exist");
        return TAF_SS_REJ_INVALID_MANDATORY_IE;
    }

    /*�鿴�Ƿ���LINKED_ID*/
    if (LINKED_ID_TAG == **ppucSrc)
    {
        /*��LINKED_ID_TAG����Ӧ�Ĵ���*/
        gastSsaStatetable[gucCurrentTi].ucLinkId = *(*ppucSrc + 2);
        *ppucSrc = *ppucSrc + 3;

    }

    /*�鿴������*/
   ucOperationCode = *(*ppucSrc + 2);
    if (OPERATION_CODE_TAG == **ppucSrc)
    {
        /*�����ǰoperation codeֵ��ȷ*/
        if (SSA_SUCCESS == SSA_CheckOperationCode(gucCurrentTi, ucOperationCode))
        {
            /*��¼operationcode,��ת������Ӧ���ϱ��¼�*/
            if (TAF_SS_MSG_TYPE_REGISTER == gastSsaStatetable[gucCurrentTi].ucMsgType)
            {
                gastSsaStatetable[gucCurrentTi].ucOperationCode = ucOperationCode;
            }
            pEvent->SsEvent = SSA_GetRepEvtFromOpCode(ucOperationCode);
            if (TAF_SS_EVT_ERROR == pEvent->SsEvent)
            {
                /*�������ֵΪSSA_FAILURE��˵�����������󣬷���*/
                return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
            }

            *ppucSrc = *ppucSrc + 3;
        }
        else
        {
            /*������������,������Ϣ�������*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Operation Unrecognized");
            return  TAF_SS_REJ_UNRECOGNIZED_OPERATION;
        }
    }
    else
    {
        /*ȱ��operation code��������Ϣ�������*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Operation Id not exist");
        return TAF_SS_REJ_INVALID_MANDATORY_IE;
    }

    /*���ݲ����룬�����component����������Ӧ�Ľ��봦��*/
    if (*ppucSrc < gpucSsParaEndLocation)
    {
        switch(ucOperationCode)
        {
            case TAF_SS_USS_REQ:
                /*�Ե�ǰ״̬�����ж�,�Ƿ���Խ���USSD����(�Ƿ����ͨ��״̬,�Ƿ��������Ĳ���ҵ��
                ����)*/
                if ((SSA_IDLE == SSA_TiIdle())||(gastSsaStatetable[gucCurrentTi].ucMsgType == TAF_SS_MSG_TYPE_FACILITY))
                {
                    ulRslt = SSA_DecodeUntructuredSSInd(pEvent, ppucSrc);
                }
                else
                {
                    SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: USS_REQ Busy");
                    return TAF_ERR_SS_USSD_BUSY;
                }
                break;
            case TAF_SS_USS_NOTIFY:
                /*�Ե�ǰ״̬�����ж�,�Ƿ���Խ���USSD����*/
                if ((SSA_IDLE == SSA_TiIdle())||(gastSsaStatetable[gucCurrentTi].ucMsgType == TAF_SS_MSG_TYPE_FACILITY))
                {
                    ulRslt = SSA_DecodeUntructuredSSNotifyInd(pEvent, ppucSrc);
                }
                else
                {
                    SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: USS_NOTIFY Busy");
                    return TAF_ERR_SS_USSD_BUSY;
                }
                break;
            case TAF_SS_GETPASSWORD:
                ulRslt = SSA_DecodeGetPwdInd(pEvent, ppucSrc);
                break;
            #if 0
            case TAF_SS_FORWARDCHECKSS_INDICATION:
                /*������,����������¼�ϱ�����Ϣ*/
                break;
            #endif
            default:
                SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: Wrong Operation Code");
                return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
    }

   /* if ((*pucSrc != pucEndLocation)&&(SSA_SUCCESS == ulRslt)) */
   /* { */
   /*     SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke: BADLY_STRUCTURED_COMPONENT"); */
   /*     return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT; */
   /* } */
    return ulRslt;
}
VOS_UINT32 SSA_DecodeRtrnRslt(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8       ucOperationCode;
    /* VOS_UINT8      *pucEndLocation; */
    VOS_UINT32      ulRslt = SSA_SUCCESS;
    VOS_UINT8       ucTmpLen;

    /* ����tag�ֽ� */
    (*ppucSrc)++;

    /*��ȡcomponent����, TLV��ʽ��ͬʱָ����λ��V��ȷ������λ��*/
    ulRslt = SSA_DecodeLength(ppucSrc, &ucTmpLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Length Value Error");
    }

    gpucSsParaEndLocation = *ppucSrc + ucTmpLen;

    /*������INVOKE ID*/
    if (INVOKE_ID_TAG == **ppucSrc)
    {
        /*����Invoke Id��ֵ*/
        if ((gucSsCurInvokeId < 255)&&(gucSsCurInvokeId <*(*ppucSrc + 2)))
        {
           gucSsCurInvokeId = *(*ppucSrc + 2);
           gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else if ((gucSsCurInvokeId == 255) && (0 == *(*ppucSrc + 2)))
        {
            gucSsCurInvokeId = 0;
            gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else
        {
            ;
        }

        *ppucSrc = *ppucSrc + 3;
    }
    else
    {
        if (gastSsaStatetable[gucCurrentTi].ucMsgType != TAF_SS_MSG_TYPE_RLCOMPLETE)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Invoke Id not exist");
            return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
        }
    }

    /*�ж��Ƿ��в���Sequence Tag,Ŀǰ����������*/
    if (*ppucSrc < gpucSsParaEndLocation)
    {
        if ((TAG_SS_OF_SEQUENCE == **ppucSrc)||(TAG_SS_OF_SET == **ppucSrc))
        {

            /* ����tag�ֽ� */
            (*ppucSrc)++;

            /*��ȡcomponent����, TLV��ʽ��ͬʱָ����λ��V��ȷ������λ��*/
            ulRslt = SSA_DecodeLength(ppucSrc, &ucTmpLen);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Length Value Error");
            }
        }
    }

    /*�ж��Ƿ��в���operation code,�еĻ�����¼,û������(��ѡ��)*/
    ucOperationCode = *(*ppucSrc + 2);
    if (*ppucSrc < gpucSsParaEndLocation)
    {
        if (OPERATION_CODE_TAG == **ppucSrc)
        {
            /*�����ǰoperation codeֵ��ȷ,��¼operationcode,ת������Ӧ���ϱ��¼�,ƫ��*/
            if (SSA_SUCCESS == SSA_CheckOperationCode(gucCurrentTi, ucOperationCode))
            {
                gastSsaStatetable[gucCurrentTi].ucOperationCode = ucOperationCode;
                pEvent->SsEvent = SSA_GetRepEvtFromOpCode(ucOperationCode);
                #if 0
                if (TAF_SS_EVT_ERROR == pEvent->SsEvent)
                {
                    /*�������ֵΪSSA_FAILURE��˵�����������󣬷���*/
                    return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
                }
                #endif

                *ppucSrc = *ppucSrc + 3;
            }
            else
            {
                /*������������,�����ӡ��Ϣ,����*/
                SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Operation Unrecognized");
                return  TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
            }
        }
    }
    else
    {
        pEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);
        pEvent->OpId = gastSsaStatetable[gucCurrentTi].OpId;
        pEvent->ClientId = gastSsaStatetable[gucCurrentTi].ClientId;
        return SSA_SUCCESS;
    }

    /*����operation code,�����component����������Ӧ�Ĳ����Ľ���*/
    if (*ppucSrc < gpucSsParaEndLocation)
    {
        pEvent->OP_UnParsePara = 1;
        pEvent->UnParsePara.ucCnt = (VOS_UINT8)(gpucSsParaEndLocation - *ppucSrc);
        PS_MEM_CPY(pEvent->UnParsePara.aucUnParsePara, *ppucSrc, pEvent->UnParsePara.ucCnt);
        switch(ucOperationCode)
        {
            case TAF_SS_REGISTERSS:
                ulRslt = SSA_DecodeRegisterSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_ERASESS:
                ulRslt = SSA_DecodeEraseSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_ACTIVATESS:
                ulRslt = SSA_DecodeActivateSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_DEACTIVATESS:
                ulRslt = SSA_DecodeDeactivateSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_INTERROGATESS:
                ulRslt = SSA_DecodeInterrogateSsCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_PROCESS_USS_REQ:
                ulRslt = SSA_DecodeProcessUnstructuredSSCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_REGISTERPASSWORD:
                ulRslt = SSA_DecodeRegPwdCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_ERASECC_ENTRY:
                ulRslt = SSA_DecodeEraseCCEntryCnf(pEvent, ppucSrc);
                break;
            case TAF_SS_PROCESS_USS_DATA:
                ulRslt = SSA_DecodeProcessUSSDataCnf(pEvent, ppucSrc);
                break;
            default:
                SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnRslt:WARNING: Wrong Operation Code");
                return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
        }
    }

/*    if (*ppucSrc != gpucSsParaEndLocation) */
/*    { */
/*        SSA_LOG(WARNING_PRINT, "SSA_DecodeInvoke:WARNING: BADLY_STRUCTURED_COMPONENT"); */
/*        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT; */
/*    } */

    return ulRslt;
}



VOS_UINT32 SSA_DecodeRtrnErr(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 **ppucSrc)
{
    VOS_UINT16       usErrCode;

    *ppucSrc = *ppucSrc + 2;

    /*������INVOKE Id�Ƿ����*/
    if (INVOKE_ID_TAG == **ppucSrc)
    {
        /*����Invoke Id��ֵ*/
        if ((gucSsCurInvokeId < 255)&&(gucSsCurInvokeId <*(*ppucSrc + 2)))
        {
           gucSsCurInvokeId = *(*ppucSrc + 2);
           gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else if ((gucSsCurInvokeId == 255) && (0 == *(*ppucSrc + 2)))
        {
            gucSsCurInvokeId = 0;
            gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else
        {
            ;
        }
        *ppucSrc = *ppucSrc + 3;

    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnErr:WARNING: Invoke Id not exist");
        return TAF_SS_REJ_RETURN_ERROR_MISTYPED_PARAMETER;
    }

    /*������error code�Ƿ����,���ڵĻ����м�¼,��ǰ�Ĵ�������Ѿ�������ƫ����*/
    usErrCode = *(*ppucSrc + 2) + TAF_SS_ERRCODE_OFFSET;
    if (ERROR_CODE_TAG == **ppucSrc)
    {
        /*��¼error code����Ӧ�������ϱ��¼�*/
        pEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);
        pEvent->OP_Error = SSA_FIELD_EXIST;
        pEvent->ErrorCode = usErrCode;
        *ppucSrc = *ppucSrc + 3;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRtrnErr:WARNING: Error Code not exist");
        return TAF_SS_REJ_RETURN_ERROR_MISTYPED_PARAMETER;
    }

    /* ����SS Status��������Event */
    if (OCTETSTRING_TAG == **ppucSrc)
    {
        pEvent->OP_SsStatus = SSA_FIELD_EXIST;

        /* ƫ�Ƶ�TAG���� */
        (*ppucSrc)++;

        /* ƫ�Ƶ�Length���� */
        (*ppucSrc)++;

        pEvent->SsStatus    = **ppucSrc;
    }

    return SSA_SUCCESS;

}


VOS_UINT32 SSA_DecodeReject(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8         ucTmpLen;
    VOS_UINT8         ucProblemCode;
    VOS_UINT8         ucProblemTag;
    /* VOS_UINT8      *pucEndLocation; */

    /* pucEndLocation = *ppucSrc + *(*ppucSrc + 1); */
    *ppucSrc = *ppucSrc + 2;

    /*������INVOKE ID�Ƿ����*/
    if (INVOKE_ID_TAG == **ppucSrc)
    {
        /*����Invoke Id��ֵ*/
        if ((gucSsCurInvokeId < 255)&&(gucSsCurInvokeId <*(*ppucSrc + 2)))
        {
           gucSsCurInvokeId = *(*ppucSrc + 2);
           gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else if ((gucSsCurInvokeId == 255) && (0 == *(*ppucSrc + 2)))
        {
            gucSsCurInvokeId = 0;
            gastSsaStatetable[gucCurrentTi].ucInvokeId = gucSsCurInvokeId;
        }
        else
        {
            ;
        }

        *ppucSrc = *ppucSrc + 3;
    }
    else if (SSA_NULL_TAG == **ppucSrc)
    {
        /*��ʱInvoke Id������*/
        *ppucSrc = *ppucSrc + 2;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeReject:WARNING: Invoke Id not exist");
        return TAF_SS_REJ_MISTYPED_COMPONENT;
    }

    /*������problem code*/
    if ((GENERAL_PROBLEM_TAG == **ppucSrc)||(INVOKE_PROBLEM_TAG == **ppucSrc)
        ||(RETURN_RESULT_PROBLEM_TAG == **ppucSrc)||(RETURN_ERROR_PROBLEM_TAG == **ppucSrc))
    {
        /*��¼problem code,Ŀǰ��������ʧ��,ͳһ�ϱ�*/
        pEvent->SsEvent = TAF_SS_EVT_PROBLEM;
        pEvent->OP_ProblemCode = SSA_FIELD_EXIST;

        ucProblemTag = **ppucSrc;
        (*ppucSrc)++;

        if (VOS_OK != SSA_DecodeLength(ppucSrc, &ucTmpLen))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeReject:WARNING: SSA_DecodeLength fail");
        }

        ucProblemCode = **ppucSrc;
        pEvent->ProblemCode = ucProblemCode;

        (*ppucSrc)++;

        if (INVOKE_PROBLEM_TAG == ucProblemTag)
        {
            return ucProblemCode|0x20;
        }

    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeReject:WARNING: Invoke Id not exist");
        return TAF_SS_REJ_MISTYPED_COMPONENT;
    }

    return SSA_SUCCESS;
}



/*****************************************************************************
 Prototype      : SSA_DecodeRegisterSSCnf
 Description    : ���������ظ���RegisterSS����Ӧ��Return result��
 Input          : **ppucSrc--������ִ�
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeRegisterSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8  **ppucSrc)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8      *pucEndLocation;

    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegisterSSCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegisterSSCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*�Ա�ǩֵ�����ж�,����24��080��������ֵֻ����ʱ0��1��3*/
    /*����Ӧ�Ĳ������н��룬��������ο�24.080 Annex A, RegisterSS�����Ĳ���*/
    switch (gSsTagValue.iNumber)
    {
        /*����:forwardingInfo�����н���*/
        case 0:
            ulRslt = SSA_DecodeForwardingInfo(&(para->FwdInfo), ppucSrc, IMPLICIT_MODE);
            para->OP_FwdInfo = 1;
            break;

        /*����:callBarringInfo�����н���*/
        case 1:
            ulRslt = SSA_DecodeCallBarringInfo(&(para->CallBarInfo), ppucSrc, IMPLICIT_MODE);
            para->OP_CallBarInfo = 1;
            break;

        /*����:ss-Data, ���н���*/
        case 3:
            ulRslt = SSA_DecodeSSData(&(para->SsData), ppucSrc, IMPLICIT_MODE);
            para->OP_SsData = 1;
            break;
        default:
            SSA_LOG(WARNING_PRINT, "SSA_DecodeRegisterSSCnf:WARNING: TagNumber is Error");
            return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegisterSSCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}


/*****************************************************************************
 Prototype      : SSA_DecodeEraseSSCnf
 Description    : ���������ظ���EraseSS����Ӧ��Return result��
 Input          : **ppucSrc--������ִ�   ulLen-- �Ӵ����ִ�
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeEraseSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8   **ppucSrc)
{
    VOS_UINT32       ulRslt;

    /*EraseSS�����Ĳ���������RegiserSS�Ĳ�������һ��*/
    ulRslt = SSA_DecodeRegisterSSCnf(para, ppucSrc);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseSSCnf:WARNING: DeCode EraseSS fail");
    }


    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeActivateSSCnf
 Description    : ���������ظ���AtcivateSS����Ӧ��Return result��
 Input          : **ppucSrc--������ִ�   ulLen-- �Ӵ����ִ�
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeActivateSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8   **ppucSrc)
{
    VOS_UINT32       ulRslt;

    /*ActivateSS�����Ĳ���������RegiserSS�Ĳ�������һ��*/
    ulRslt = SSA_DecodeRegisterSSCnf(para, ppucSrc);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeActivateSSCnf:WARNING: DeCode ActivateSS fail");
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeDeactivateSSCnf
 Description    : ���������ظ���DeatcivateSS����Ӧ��Return result��
 Input          : **ppucSrc--������ִ�   ulLen-- �Ӵ����ִ�
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeDeactivateSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8  **ppucSrc)
{
    VOS_UINT32       ulRslt;

    /*DeactivateSS�����Ĳ���������RegiserSS�Ĳ�������һ��*/
    ulRslt = SSA_DecodeRegisterSSCnf(para, ppucSrc);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeDeactivateSSCnf:WARNING: DeCode DeactivateSS fail");
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeInterrogateSsCnf
 Description    : ���������ظ���InterrogateSS����Ӧ��Return result��
 Input          : **ppucSrc--������ִ�   ulLen--�ִ��ĳ���
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeInterrogateSsCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8      *pucEndLocation;


    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInterrogateSsCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInterrogateSsCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*�Ա�ǩֵ�����ж�,����24��080��������ֵֻ����ʱ0,2,3, 4*/
    /*����Ӧ�Ĳ������н��룬��������ο�24.080 Annex A, InterrogateSS�����Ĳ���*/
    switch (gSsTagValue.iNumber)
    {
        /*����:ss-Status�����н���*/
        case 0:
            ulRslt = SSA_DecodeSsStatus(&(para->SsStatus), ppucSrc, IMPLICIT_MODE);
            para->OP_SsStatus = 1;
            break;

        /*����:basicServiceGroupList�����н���*/
        case 2:
            ulRslt = SSA_DecodeBasicServiceGroupList(&(para->BsServGroupList), ppucSrc, IMPLICIT_MODE);
            para->OP_BsServGroupList = 1;
            break;

        /*����:forwardingFeatureList, ���н���*/
        case 3:
            ulRslt = SSA_DecodeForwardingFeatureList(&(para->FwdFeaturelist), ppucSrc, IMPLICIT_MODE);
            para->OP_FwdFeaturelist = 1;
            break;

        /*����:genericServiceInfo, ���н���*/
        case 4:
            ulRslt = SSA_DecodeGenericServiceInfo(&(para->GenericServiceInfo), ppucSrc, IMPLICIT_MODE);
            para->OP_GenericServiceInfo = 1;
            break;
        default:
            SSA_LOG(WARNING_PRINT, "SSA_DecodeInterrogateSsCnf:WARNING: TagNumber is Error");
            return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInterrogateSsCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;

}

/*****************************************************************************
 Prototype      : SSA_DecodeRegPwdCnf
 Description    : ���������ظ���RegisterPassword����Ӧ��Return result��
 Input          : **ppucSrc--������ִ�   ulLen--�ִ��ĳ���
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeRegPwdCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8       ucTmp;
    VOS_UINT8      *pucEndLocation;

    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*�ж��Ƿ�ʱNumericString���ͣ��ǵĻ����н���*/
    if (NUMERICSTRING_TAG == gSsTagValue.iNumber)
    {
        gulCurStrMaxLen = 4;
        ulRslt = SSA_DecodeNumericString(para->aucPassWord, &ucTmp, ppucSrc, IMPLICIT_MODE);
        para->OP_PassWord = 1;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: TagNumber is Error");
        return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeGetPwdInd
 Description    : ��������෢���ĵ�GetPassword�Ĳ�����Invoke��
 Input          : **ppucSrc--������ִ�   ulLen--�ִ��ĳ���
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeGetPwdInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32      ulRslt;
    VOS_UINT8      *pucEndLocation;


    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeGetPwdInd:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeGetPwdInd:WARNING: Length Value Error");
        return ulRslt;
    }

    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*�ж��Ƿ���Enumerated���ͣ��ǵĻ����н���*/
    if (ENUMERATED_TAG == gSsTagValue.iNumber)
    {
        ulRslt = SSA_DecodeGuidanceInfo(&(para->GuidanceInfo), ppucSrc, IMPLICIT_MODE);
        para->OP_GuidanceInfo = 1;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeGetPwdInd:WARNING: TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeRegPwdCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}
VOS_UINT32  SSA_DecodeProcessUnstructuredSSCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32      ulRslt = SSA_SUCCESS;
    VOS_UINT8      *pucEndLocation;


    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: Length Value Error");
        return ulRslt;
    }

    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��ussd-DataCodingScheme���н���, ����ʧ���򷵻�*/
    ulRslt = SSA_DecodeUssdDataCodingScheme(&(para->DataCodingScheme), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: SSA_DecodeUssdDataCodingScheme Failure");
        return ulRslt;
    }
    para->OP_DataCodingScheme = 1;

    /*��ussd-String���н���,����ʧ���򷵻�*/
    ulRslt = SSA_DecodeUssdString(&(para->UssdString), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: SSA_DecodeUssdString Failure");
        return ulRslt;
    }

    /*��ĳЩ���뷽����,��Ҫ�����ٽ���,���8bit���뷽ʽ*/
    if(AT_USSD_NON_TRAN_MODE == SSA_GetUssdTransMode())
    {

       /*�жϱ��뷽���Ƿ�֧��,֧�ֵı��뷽��Ϊ0x0f��01xx xxxx�ı���(bit3��bit2Ϊ0��7bit���벻֧��)*/
        if ((para->DataCodingScheme == TAF_SS_8bit)
         || ((para->DataCodingScheme != TAF_SS_UCS2)
         && (0x00 != (para->DataCodingScheme>> 4))
         && (para->DataCodingScheme != TAF_SS_7BIT_DATA_CODING)))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: UNKNOWNALPHABET");
            return TAF_ERR_SS_UNKNOWN_ALPHABET;
        }

        if ((0x00 == (para->DataCodingScheme>> 4))
            ||(TAF_SS_7BIT_DATA_CODING == para->DataCodingScheme))
        {
            ulRslt = SSA_DecodeUssdMessage(&(para->UssdString), para->DataCodingScheme);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: SSA_DecodeUssdMessage decode Failure");
                return ulRslt;
            }
            else
            {
                para->DataCodingScheme = TAF_SS_8bit;
            }
        }

    }
    para->OP_UssdString = 1;

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}


VOS_UINT32  SSA_DecodeUntructuredSSInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT32       ulRslt = SSA_SUCCESS;
    VOS_UINT8       *pucEndLocation;
    VOS_UINT8       *pucCurLocation;

    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��ussd-DataCodingScheme���н���,����ʧ���򷵻�*/
    ulRslt = SSA_DecodeUssdDataCodingScheme(&(para->DataCodingScheme), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: SSA_DecodeUssdDataCodingScheme deocde Failure");
        return ulRslt;
    }
    para->OP_DataCodingScheme = 1;

    /*��ussd-String���н���,����ʧ���򷵻�*/
    ulRslt = SSA_DecodeUssdString(&(para->UssdString), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: SSA_DecodeUssdString decode Failure");
        return ulRslt;
    }

    /*��ĳЩ���뷽����,��Ҫ�����ٽ���,���8bit���뷽ʽ*/
    if(AT_USSD_NON_TRAN_MODE == SSA_GetUssdTransMode())
    {

       /*�жϱ��뷽���Ƿ�֧��,֧�ֵı��뷽��Ϊ0x0f��01xx xxxx�ı���(bit3��bit2Ϊ0��7bit���벻֧��)*/
        if ((para->DataCodingScheme == TAF_SS_8bit)
         || ((para->DataCodingScheme != TAF_SS_UCS2)
         && (0x00 != (para->DataCodingScheme>> 4))
         && (para->DataCodingScheme != TAF_SS_7BIT_DATA_CODING)))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: UNKNOWNALPHABET");
            return TAF_ERR_SS_UNKNOWN_ALPHABET;
        }

        if ((0x00 == (para->DataCodingScheme>> 4))
          ||(TAF_SS_7BIT_DATA_CODING == para->DataCodingScheme))
        {
            ulRslt = SSA_DecodeUssdMessage(&(para->UssdString), para->DataCodingScheme);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUnstructuredSSCnf:WARNING: SSA_DecodeUssdMessage decode Failure");
                return ulRslt;
            }
            else
            {
                para->DataCodingScheme = TAF_SS_8bit;
            }
        }

    }
    para->OP_UssdString = 1;

    /*�ж���û��alertingPattern�������,û�еĻ�,����*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*����TLV�е�T��L*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�жϱ�ǩ���ͺͱ�ǩֵ�����жϽ���λ��*/
        if ((OCTETSTRING_TAG == gSsTagValue.iNumber) && (UNIVERSAL_TAG_TYPE == gSsTagValue.ucClass) && (*ppucSrc < pucEndLocation))
        {
            /*����alertingpattern������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeAlertingPattern(&(para->AlertingPattern), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: SSA_DecodeAlertingPattern Failure");
                return ulRslt;
            }
            para->OP_AlertingPattern = 1;
        }
        else
        {
            /*������alertingpattern��*/
            *ppucSrc = pucCurLocation;
            para->OP_AlertingPattern = 0;
        }
    }
    else
    {
        /*������alertingpattern������*/
        para->OP_AlertingPattern = 0;
    }

#if 0
    /*�ж���û��msisdn�������������еĻ����н��룬û�еĻ�������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*����TLV�е�T��L*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Length Value Error");
            return ulRslt;
        }

        /*ȷ���Ƿ����msisdn������*/
        if ((0 == gSsTagValue.iNumber) && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass) && (*ppucSrc < pucEndLocation))
        {
            /*����Msisdn������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeMsisdn(para->aucMsisdn, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: SSA_DecodeMsisdn Failure");
                return ulRslt;
            }
            para->OP_Msisdn = 1;
        }
        else
        {
            /*���һ����������ǩֵ������Ϊ�����������������������Ϊ����*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: Unknow Parameter");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
    }
    else
    {
        /*������alertingpattern������*/
        para->OP_Msisdn= 0;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSInd:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }
#endif

    return  ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeUntructuredSSNotifyInd
 Description    : ��������෢���ĵ�UntructuredSSNotify�Ĳ�����Invoke��
 Input          : **ppucSrc--������ִ�   ulLen--�ִ��ĳ���
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeUntructuredSSNotifyInd(TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *para, VOS_UINT8 **ppucSrc)
{
  VOS_UINT32       ulRslt;

    /*unstructuredSS-Notify�����Ĳ���������unstructuredSS-Request�Ĳ�������һ��*/
    ulRslt = SSA_DecodeUntructuredSSInd(para, ppucSrc);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUntructuredSSNotifyInd:WARNING: DeCode UntructuredSSNotify fail");
    }


    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeEraseCCEntryCnf
 Description    : ��������෢���ĵ�EraseCCEntry�Ĳ�����Return Result��
 Input          : **ppucSrc--������ִ�   ulLen--�ִ��ĳ���
 Output         : *para--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeEraseCCEntryCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��ss-Code���н���*/
    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Length Value Error");
        return ulRslt;
    }

    /*�жϱ�ǩֵ����ȷ��*/
    if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
    {
        /*����ss-Code������,�������ʧ��,�򷵻�*/
        ulRslt = SSA_DecodeSsCode(&(para->SsCode), ppucSrc, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: SSA_DecodeSsCode decode Failure");
            return ulRslt;
        }
        para->OP_SsCode = 1;
    }
    else
    {
        /*��ǩֵ����ss-Code�ı�ǩֵ,ʧ�ܷ���*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*�ж��Ƿ���ss-Status, �еĻ�����,û������*/
    if (*ppucSrc < pucEndLocation)
    {
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Length Value Error");
            return ulRslt;
        }
        if ((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass))
        {
            /*����ss-Status������,�������ʧ��,�򷵻�*/
            /*�жϱ�ǩֵ����ȷ��*/
            ulRslt = SSA_DecodeSsStatus(&(para->SsStatus), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: SSA_DecodeSsCode decode Failure");
                return ulRslt;
            }
            para->OP_SsStatus = 1;
            /*�Է���ֵ�����ж������������*/
        }
        else
        {
            /*���һ����������ǩֵ������Ϊ�����������������������Ϊ����*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: Unknow Parameter");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
    }
    else
    {
        /*û��Ss-Status������*/
        para->OP_SsStatus = 0;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEraseCCEntryCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt ;
}
VOS_UINT32  SSA_DecodeProcessUSSDataCnf(TAF_SS_CALL_INDEPENDENT_EVENT_STRU *para, VOS_UINT8 **ppucSrc)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt;

    /*����TLV�е�T��L,ȷ������λ��*/
    ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: Tag Value Wrong");
        return ulRslt;
    }
    ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: Length Value Error");
        return ulRslt;
    }
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*�����IA5String����,������Ӧ�Ľ���*/
    if (IA5STRING_TAG== gSsTagValue.iNumber)
    {
        gulCurStrMaxLen = 200;
        ulRslt = SSA_DecodeIA5String(para->UssdString.aucUssdStr,
                                    (VOS_UINT8*)&para->UssdString.usCnt, ppucSrc, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: SSA_DecodeUssdString Failure");
            return ulRslt;
        }
        para->OP_USSData = 1;
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: Unknow Parameter");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeProcessUSSDataCnf:WARNING: length not consistent");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    para->OP_DataCodingScheme = 1;
    para->DataCodingScheme    = TAF_SS_8bit;

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeSsCode
 Description    : �������ss-Code,ASN.1�������μ�24.080��Annex A
 Input          : **ppucSrc--������ִ� ,ucTagMode -- ��ǩģʽ
 Output         : *ucSscode -- ������Sscode��ֵ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeSsCode(TAF_SS_CODE *ucSscode, VOS_UINT8  **ppucSrc, TAG_MODE ucTagmode)
{
    VOS_UINT8       ucStrLen;

    /* ���룬���ؽ��뺯���Ĳ������ */
    gulCurStrMaxLen = 1;
    return SSA_DecodeString(ucSscode, &ucStrLen, ppucSrc, ucTagmode);
}

/*****************************************************************************
 Prototype      : SSA_DecodeBasicServiceCode
 Description    : �������basic service Code,ASN.1�������μ�24.080��Annex A
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *ucBsCode -- ������UINT8���͵ķ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeBasicServiceCode(TAF_BASIC_SERVICE_CODE *ucBsCode, VOS_UINT8  **ppucSrc, TAG_MODE ucTagmode)
{
    VOS_UINT8       ucStrLen;

    /* ���룬���ؽ��뺯���Ĳ������ */
    gulCurStrMaxLen = 1;
    return SSA_DecodeString(ucBsCode, &ucStrLen, ppucSrc, ucTagmode);
}


/*****************************************************************************
 Prototype      : SSA_DecodeSsStatus
 Description    : �������ss-Status,ASN.1�������μ�24.080��Annex A
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeSsStatus(TAF_SS_STATUS *ucSsStatus, VOS_UINT8  **ppucSrc, TAG_MODE ucTagmode)
{
    VOS_UINT8       ucStrLen;

    /* ���룬���ؽ��뺯���Ĳ������ */
    gulCurStrMaxLen = 1;
    return SSA_DecodeString(ucSsStatus, &ucStrLen, ppucSrc, ucTagmode);
}

/*****************************************************************************
 Prototype      : SSA_DecodeMsisdn
 Description    : �������Msisdn,ASN.1�������μ�24.080��Annex A
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeMsisdn(VOS_UINT8 *pucDest, VOS_UINT8  **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;

    /* ���룬���ؽ��뺯���Ĳ������,�����ִ��Ľ�β������'\0'*/
    gulCurStrMaxLen = 20;
    ulRslt = SSA_DecodeString(pucDest, &ucStrLen, ppucSrc, ucTagMode);
    if (ulRslt != SSA_SUCCESS)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeMsisdn:WARNING: Decode Msisdn Error!");
        return ulRslt;
    }

    pucDest[ucStrLen]='\0';

    return ulRslt;
}


/*****************************************************************************
 Prototype      : SSA_DecodeAlertingPattern
 Description    : �������alertingPattern,ASN.1�������μ�24.080��Annex A
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeAlertingPattern(VOS_UINT8 *pucDest, VOS_UINT8  **ppucSrc, TAG_MODE ucTagmode)
{
    VOS_UINT8       ucStrLen;

    /* ���룬���ؽ��뺯���Ĳ������ */
    gulCurStrMaxLen = 1;
    return  SSA_DecodeString(pucDest, &ucStrLen, ppucSrc, ucTagmode);
}

/*****************************************************************************
 Prototype      : SSA_DecodeBasicService
 Description    : �������basicService,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeBasicService(TAF_SS_BASIC_SERVICE_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicService:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicService:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*ȷ����������*/
    pDest->BsType = (VOS_UINT8)gSsTagValue.iNumber;
    switch (gSsTagValue.iNumber)
    {
        /*ȷ��service code*/
        case TAF_SS_BEARER_SERVICE:
        case TAF_SS_TELE_SERVICE:
            ulRslt = SSA_DecodeBasicServiceCode(&(pDest->BsServiceCode), ppucSrc, IMPLICIT_MODE);
            break;
        default:
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicService:WARNING: TagNumber is Error");
            return TAF_SS_REJ_RETURN_RESULT_MISTYPED_PARAMETER;
    }

    return ulRslt;
}


VOS_UINT32 SSA_DecodeForwardedToNumber(TAF_SS_NUMTYPE *pucNumType, VOS_UINT8 *pucFwdToNum,VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucDest[21];

    /* ���룬���ؽ��뺯���Ĳ������,�����ִ��Ľ�β������'\0'*/
    gulCurStrMaxLen = 20;

    PS_MEM_SET(aucDest, 0, sizeof(aucDest));

    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardedToNumber:WARNING: SSA_DecodeForwardedToSubaddress Decode Failure");
        return ulRslt;
    }

    *pucNumType = aucDest[0];
    SSA_BcdNumToAsciiNum(pucFwdToNum, aucDest + 1, ucStrLen-1, *pucNumType);

    return ulRslt;
}
VOS_UINT32 SSA_DecodeForwardedToSubaddress(TAF_SS_SUBADDRTYPE *pucSubAddrType, VOS_UINT8 *pucSubAddr,VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucDest[21];

    /* ���룬���ؽ��뺯���Ĳ������,�����ִ��Ľ�β������'\0'*/
    gulCurStrMaxLen = 21;

    PS_MEM_SET(aucDest, 0, sizeof(aucDest));

    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardedToSubaddress:WARNING: SSA_DecodeForwardedToSubaddress Decode Failure");
        return ulRslt;
    }
    *pucSubAddrType = aucDest[0];

    PS_MEM_CPY(pucSubAddr, aucDest + 1, ucStrLen-1);

    *(pucSubAddr + ucStrLen) = '\0';

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeForwardingInfo
 Description    : �������ForwardingInfo,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardingInfo(TAF_SS_FORWARDINGINFO_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32      ulRslt = SSA_SUCCESS;
    VOS_UINT8      *pucEndLocation;
    VOS_UINT8      *pucCurLocation;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�Ӵ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*�ж��Ƿ���ss-Code������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���ss-Code�������Tagֵ:OCTETSTRING_TAG*/
        if ((OCTETSTRING_TAG == gSsTagValue.iNumber)&&(*ppucSrc < pucEndLocation))
        {
            /*����ss-Code������,�������ʧ��,�򷵻�*/
            ulRslt = SSA_DecodeSsCode(&(pDest->SsCode), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: SSA_DecodeSsCode Decode Failure");
                return ulRslt;
            }
            pDest->OP_SsCode = 1;
        }
        else
        {
            *ppucSrc = pucCurLocation;
            pDest->OP_SsCode = 0;
        }
    }
    else
    {
        /*���κβ���,ʧ�ܷ��أ�forwardingFeatureListΪ����ѡ��*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Para Error");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    /*ȷ�ϵ�ǰ��forwardingFeatureList,���򷵻ش�����Ϣ*/
    if (*ppucSrc < pucEndLocation)
    {
        /*��forwardingFeatureList��T��L����н���*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���forwardingFeatureList������,����ʧ���򷵻�*/
        if ( (SEQUENCE_TAG == gSsTagValue.iNumber) && (*ppucSrc < pucEndLocation) )
        {
            ulRslt = SSA_DecodeForwardingFeatureList(&(pDest->FwdFeaTurelist), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: SSA_DecodeForwardingFeatureList Decode Failure");
                return ulRslt;
            }
        }
        else
        {
            /*��ǩֵ����ȷ,ʧ�ܷ���*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: forwardingFeatureList Error");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }
    }
    else
    {
        /*��forwardingFeatureList��,ʧ�ܷ���*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingInfo:WARNING: forwardingFeatureList Error");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeForwardingFeatureList
 Description    : �������ForwardingFeatureList,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardingFeatureList(TAF_SS_FWDFEATURELIST_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8      *pucEndLocation;
    VOS_UINT32      ulRslt = SSA_SUCCESS;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeatureList:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeatureList:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*����ѭ������ķ�ʽ������ṹ�����͵�����*/
    pDest->ucCnt = 0;
    while (*ppucSrc < pucEndLocation)
    {
        /*�ж��Ƿ��������Խ��*/
        if (pDest->ucCnt == TAF_SS_MAX_NUM_OF_FW_FEATURES)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeatureList:WARNING: ForwardingFeature Num too large\r");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }

        /*���ForwardingFeature����ʧ�ܣ�����*/
        ulRslt = SSA_DecodeForwardingFeature(&(pDest->astFwdFtr[pDest->ucCnt]), ppucSrc, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeatureList:WARNING: SSA_DecodeForwardingFeatureList Decode Failure");
            return ulRslt;
         }

        pDest->ucCnt += 1;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeForwardingOptions
 Description    : �������forwardingOptions,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeForwardingOptions(VOS_UINT8 *pucDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8     ucStrLen;

    /* ���룬���ؽ��뺯���Ĳ������ */
    gulCurStrMaxLen = 1;
    return SSA_DecodeString(pucDest, &ucStrLen, ppucSrc, ucTagMode);
}
VOS_UINT32 SSA_DecodeLongForwardedToNumber(TAF_SS_NUMTYPE *pucLongFwdNumType, VOS_UINT8 *pucLongFwdToNum,VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8     ucStrLen;
    VOS_UINT32    ulRslt;
    VOS_UINT8     aucDest[21];

    /*���룬ͬʱ�����һ���ַ���������ַ���������'\0'*/
    gulCurStrMaxLen = 20;

    PS_MEM_SET(aucDest, 0, sizeof(aucDest));

    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeLongForwardedToNumber:WARNING: SSA_DecodeForwardedToSubaddress Decode Failure");
        return ulRslt;
    }

    *pucLongFwdNumType = aucDest[0];

    SSA_BcdNumToAsciiNum(pucLongFwdToNum, aucDest + 1, ucStrLen-1, *pucLongFwdNumType);

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeCallBarringInfo
 Description    : �������callBarringInfo,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeCallBarringInfo(TAF_SS_CALLBRARINGINFO_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT8       *pucCurLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;


    /*�ж��Ƿ���ss-Code������,�еĻ�����,û������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���ss-Code�������Tagֵ:OCTETSTRING_TAG*/
        if ((OCTETSTRING_TAG == gSsTagValue.iNumber)&&(*ppucSrc < pucEndLocation))
        {
            /*����ss-Code���������ʧ���򷵻�*/
            ulRslt = SSA_DecodeSsCode(&(pDest->SsCode), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeature:WARNING: SSA_DecodeNoReplyConditionTime Decode Failure");
                return ulRslt;
            }
            pDest->OP_SsCode = 1;
        }
        else
        {
            *ppucSrc = pucCurLocation;
            pDest->OP_SsCode = 0;
        }
    }
    else
    {
        /*���κβ���,ʧ�ܷ��أ� callBarringFeatureListΪ����ѡ��*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Para Error");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    if (*ppucSrc < pucEndLocation)
    {
        /*��callBarringFeatureList��T��L����н���*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���callBarringFeatureList������,�еĻ�����,û������*/
        if (SEQUENCE_TAG == gSsTagValue.iNumber)
        {
            ulRslt = SSA_DecodeCallBarringFeatureList(&(pDest->CallBarFtrList), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: SSA_DecodeCallBarringFeatureList Decode Failure");
                return ulRslt;
            }
        }
        else
        {
            /*��ǩֵ����ȷ,ʧ�ܷ���*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: callBarringFeatureList Error");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }
    }
    else
    {
        /*��callBarringFeatureList��,ʧ�ܷ���*/
        SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringInfo:WARNING: callBarringFeatureList Error");
        return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
    }

    return ulRslt;
}


/*****************************************************************************
 Prototype      : SSA_DecodeCallBarringFeatureList
 Description    : �������CallBarringFeatureList,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeCallBarringFeatureList(TAF_SS_CALLBARFEATURELIST_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeatureList:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeatureList:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*����ѭ������ķ�ʽ������ṹ�����͵�����*/
    pDest->ucCnt = 0;
    while (*ppucSrc < pucEndLocation)
    {
        /*�ж��Ƿ��������Խ��*/
        if (pDest->ucCnt == TAF_SS_MAX_NUM_OF_CallBarring_FEATURES)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeatureList:WARNING: callBarringFeature Num too large");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }

        /*CallBarringFeature���룬����ʧ���򷵻�*/
        ulRslt = SSA_DecodeCallBarringFeature(&(pDest->astCallBarFtr[pDest->ucCnt]), ppucSrc, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeatureList:WARNING: SSA_DecodeCallBarringFeature Decode Failure");
            return ulRslt;
         }

        pDest->ucCnt += 1;

        #if 0
        while ((**ppucSrc == 0) && (*(*ppucSrc + 1) == 0) && (*ppucSrc < pucEndLocation))
        {
            *ppucSrc = *ppucSrc + 2;
        }
        #endif
    }

    return ulRslt;
}


/*lint -e438 -e830*/

/*****************************************************************************
 Prototype      : SSA_DecodeCallBarringFeature
 Description    : �������callBarringFeature,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeCallBarringFeature(TAF_SS_CALLBARRINGFEATURE_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{

    VOS_UINT8       *pucEndLocation;
    VOS_UINT8       *pucCurLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*�ж��Ƿ��в�����basicService,�еĻ�����,û������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���basicService�������Tagֵ:0x82����0x83*/
        if (((2 == gSsTagValue.iNumber)||(3 == gSsTagValue.iNumber))&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*����basicService������,����ʧ���򷵻�*/
            ulRslt = SSA_DecodeBasicService(&(pDest->BsService), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: SSA_DecodeBasicService Decode Failure");
                return ulRslt;
            }
            pDest->OP_BsService= 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc = pucCurLocation;
            pDest->OP_BsService= 0;
        }
    }
    else
    {
        /*����û��basicService������*/
        pDest->OP_BsService= 0;
    }

    /*�ж��Ƿ��в�����ss-Status,�еĻ�����,û������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���ss-Status�������Tagֵ:0x84*/
        if ((4 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*����ss-Status���������ʧ���򷵻�*/
            ulRslt = SSA_DecodeSsStatus(&(pDest->SsStatus), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: SSA_DecodeSsStatus Decode Failure");
                return ulRslt;
            }
            pDest->OP_SsStatus= 1;
        }
        else
        {
            /*���һ����������ǩֵ������Ϊ�����������������������Ϊ����*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCallBarringFeature:WARNING: SSA_DecodeSsStatus Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }
    }
    else
    {
        /*����û��ss-Status������*/
        pDest->OP_SsStatus= 0;
    }

    return ulRslt;
}
/*lint +e438 +e830*/

/*****************************************************************************
 Prototype      : SSA_DecodeBasicServiceGroupList
 Description    : �������basicServiceGroupList,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeBasicServiceGroupList(TAF_SS_BS_SERV_GROUPLIST_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE  ucTagMode)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeSSData:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeSSData:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*����ָʾ��0*/
    pDest->ucCnt = 0;
    while (*ppucSrc < pucEndLocation)
    {
        /*�ж��Ƿ��������Խ��*/
        if (pDest->ucCnt == TAF_SS_MAX_NUM_OF_BASIC_SERVICES)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicServiceGroupList:WARNING: basicServiceGroup Num too large");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }

        /*����basicService������,����ʧ���򷵻�*/
        ulRslt = SSA_DecodeBasicService(&(pDest->astBsService[pDest->ucCnt]), ppucSrc, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeBasicServiceGroupList:WARNING: SSA_DecodeCallBarringFeature Decode Failure");
            return ulRslt;
        }

        /*���ȼ�����1*/
        pDest->ucCnt += 1;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeCcbsFeatureList(TAF_SS_CCBS_FEATURELIST_STRU *pDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       *pucEndLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeatureList:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeatureList:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*��ȡ�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*����ѭ������ķ�ʽ������ṹ�����͵�����*/
    pDest->ucCnt = 0;
    while (*ppucSrc < pucEndLocation)
    {
        /*�ж��Ƿ��������Խ��*/
        if (pDest->ucCnt == TAF_SS_MAX_NUM_OF_CCBS_FEATURE)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeatureList:WARNING: CcbsFeature Num too large");
            return TAF_SS_REJ_BADLY_STRUCTURED_COMPONENT;
        }

        /*����CcbsFeatur,����ʧ�����˳�*/
        ulRslt = SSA_DecodeCcbsFeature(&(pDest->astCcBsFeature[pDest->ucCnt]), ppucSrc, EXPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeatureList:WARNING: SSA_DecodeCcbsFeature Decode Failure");
            return ulRslt;
        }

        pDest->ucCnt += 1;

        #if 0
        while ((**ppucSrc == 0) && (*(*ppucSrc + 1) == 0) && (*ppucSrc < pucEndLocation))
        {
            *ppucSrc = *ppucSrc + 2;
        }
        #endif
    }

    return ulRslt;

}

/*lint -e438 -e830*/

/*****************************************************************************
 Prototype      : SSA_DecodeCcbsFeature
 Description    : �������ccbs-Feature,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pCcBsFeature--���������ݽṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeCcbsFeature(TAF_SS_CCBS_FEATURE_STRU *pCcBsFeature, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{

    VOS_UINT8       *pucEndLocation;
    VOS_UINT8       *pucCurLocation;
    VOS_UINT32       ulRslt = SSA_SUCCESS;
    VOS_INT32          iTmp;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*�ж��Ƿ��в�����ccbs-Index,�еĻ�����,û������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���ccbs-Index�������Tagֵ:0x80*/
        if ((0 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*����ccbs-Index������*/
            ulRslt = SSA_DecodeCcbsIndex(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeCcbsIndex Decode Failure");
                return ulRslt;
            }
            pCcBsFeature->CcbsIndex = (VOS_UINT8)iTmp;
            pCcBsFeature->OP_CcbsIndex= 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc = pucCurLocation;
            pCcBsFeature->OP_CcbsIndex= 0;
        }
    }
    else
    {
            /*����û��ccbs-Index������*/
            pCcBsFeature->OP_CcbsIndex= 0;
    }

    /*�ж��Ƿ��в�����b-subscriberNumber,�еĻ�����,û������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���b-subscriberNumber�������Tagֵ:0x81*/
        if ((1 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*����b-subscriberNumber������*/
            ulRslt = SSA_DecodeBSubscriberNum(&(pCcBsFeature->NumType), pCcBsFeature->aucBSubscriberNum, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeBSubscriberNum Decode Failure");
                return ulRslt;
            }
            pCcBsFeature->OP_BSubscriberNum = 1;
            pCcBsFeature->OP_NumType = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc = pucCurLocation;
            pCcBsFeature->OP_BSubscriberNum = 0;
            pCcBsFeature->OP_NumType = 0;
        }
    }
    else
    {
        /*����û��b-subscriberNumber������*/
        pCcBsFeature->OP_BSubscriberNum = 0;
        pCcBsFeature->OP_NumType = 0;
    }

    /*�ж��Ƿ��в�����b-subscriberSubaddress,�еĻ�����,û������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���b-subscriberSubaddress�������Tagֵ:0x82*/
        if ((2 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*����b-subscriberSubaddress������*/
            ulRslt = SSA_DecodeBSubscriberSubAddress(&(pCcBsFeature->SubAddrType), pCcBsFeature->aucBSubscriberSubAddr, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeBSubscriberSubAddress Decode Failure");
                return ulRslt;
            }
            pCcBsFeature->OP_BSubscriberSubAddr = 1;
            pCcBsFeature->OP_SubAddrType = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc = pucCurLocation;
            pCcBsFeature->OP_BSubscriberSubAddr = 0;
            pCcBsFeature->OP_SubAddrType = 0;
        }
    }
    else
    {
        /*����û��b-subscriberSubaddress������*/
        pCcBsFeature->OP_BSubscriberSubAddr = 0;
        pCcBsFeature->OP_SubAddrType = 0;
    }

    /*�ж��Ƿ��в�����basicServiceGroup,�еĻ�����,û������*/
    pucCurLocation = *ppucSrc;
    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value Error");
            return ulRslt;
        }

        /*�ж��Ƿ���basicServiceGroup�������Tagֵ:0x83*/
        if ((3 == gSsTagValue.iNumber)&&(CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)&&(*ppucSrc < pucEndLocation))
        {
            /*����basicServiceGroup������*/
            ulRslt = SSA_DecodeBasicServiceGroupList(&(pCcBsFeature->BsServGroupList), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeBasicService Decode Failure");
                return ulRslt;
            }
            pCcBsFeature->OP_BsService= 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: SSA_DecodeBasicService Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }
    }
    else
    {
        /*����û��basicServiceGroup������*/
        pCcBsFeature->OP_BsService= 0;
    }

    /*�жϵ�ǰָ���λ�ú��Ƿ�ͱ�ǩ����һ��*/
    if (pucEndLocation != *ppucSrc)
    {
		SSA_LOG(WARNING_PRINT, "SSA_DecodeCcbsFeature:WARNING: Length Value not equal with actual length");

        return VOS_ERR;
    }
    return SSA_SUCCESS;
}
/*lint +e438 +e830*/

VOS_UINT32 SSA_DecodeBSubscriberNum(TAF_SS_NUMTYPE *pucNumType, VOS_UINT8 *pucBSubscriberNum, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucDest[21];


    ucStrLen = 0;
    PS_MEM_SET(aucDest, 0x00, sizeof(aucDest));


    /* ���룬���ؽ��뺯���Ĳ������,�����ִ��Ľ�β������'\0'*/
    gulCurStrMaxLen = 20;
    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);

    *pucNumType = aucDest[0];

    SSA_BcdNumToAsciiNum(pucBSubscriberNum, aucDest + 1, ucStrLen-1, *pucNumType);

    return ulRslt;
}
VOS_UINT32 SSA_DecodeBSubscriberSubAddress(TAF_SS_SUBADDRTYPE *pucSubAddrType, VOS_UINT8 *pucBSubscriberSubAddr, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucStrLen;
    VOS_UINT32      ulRslt;
    VOS_UINT8       aucDest[21];


    ucStrLen = 0;
    PS_MEM_SET(aucDest, 0x00, sizeof(aucDest));


    /* ���룬���ؽ��뺯���Ĳ������,�����ִ��Ľ�β������'\0'*/
    gulCurStrMaxLen = 21;
    ulRslt = SSA_DecodeString(aucDest, &ucStrLen, ppucSrc, ucTagMode);

    *pucSubAddrType = aucDest[0];

    PS_MEM_CPY(pucBSubscriberSubAddr, aucDest + 1, ucStrLen-1);

    *(pucBSubscriberSubAddr + ucStrLen) = '\0';

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeUssdDataCodeScheme
 Description    : �������ussd-DataCodingScheme,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pCodingScheme--�����ı��뷽��
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeUssdDataCodingScheme(TAF_SS_DATA_CODING_SCHEME *pCodingScheme, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    /* VOS_UINT8       *pucEndLocation; */
    VOS_UINT8        ucStrLen;
    VOS_UINT32       ulRslt = SSA_SUCCESS;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdDataCodingScheme:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdDataCodingScheme:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /* pucEndLocation = *ppucSrc + gucSsCurLen; */

    /*�����ǩֵ������Բ���ussd-DataCodingScheme���н���*/
    if ( OCTETSTRING_TAG == gSsTagValue.iNumber)
    {
        /*������ussd-DataCodingScheme����,ʧ���򷵻�*/
        gulCurStrMaxLen = 1;
        ulRslt = SSA_DecodeString(pCodingScheme, &ucStrLen, ppucSrc, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdDataCodingScheme:WARNING: SSA_DecodeString Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdDataCodingScheme:WARNING: TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    return ulRslt;
}

/*****************************************************************************
 Prototype      : SSA_DecodeUssdString
 Description    : �������ussd-String,�μ�24.080��Annex A��ASN.1������
 Input          : **ppucSrc--������ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pUssdStr--������USSD�ִ�
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeUssdString(TAF_SS_USSD_STRING_STRU *pUssdStr, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT32       ulRslt;
    /* VOS_UINT8        ucStrLen; */
    /* VOS_UINT8       *pucEndLocation; */

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdString:WARNING: Tag Value Wrong");
            return ulRslt;
        }
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdString:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /* pucEndLocation = *ppucSrc + gucSsCurLen; */

    /*�����ǩֵ������Բ���ussd-String���н���*/
    if ( OCTETSTRING_TAG == gSsTagValue.iNumber)
    {
        gulCurStrMaxLen = 160;
        ulRslt = SSA_DecodeString(pUssdStr->aucUssdStr, (VOS_UINT8*)&(pUssdStr->usCnt), ppucSrc, IMPLICIT_MODE);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdString:WARNING: SSA_DecodeString Decode Failure");
            return ulRslt;
        }
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdString:WARNING: TagNumber is Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    return SSA_SUCCESS;

}

/*******************************************************************************
  Function      :SSA_BcdNumToAsciiNum
  Description   :��BCD����ת����Ascii��
  Input         :*pucBcdNum --- �����BCD������ִ�
				  ucBcdNumLen --- BCD�����ִ��ĳ���
  Return        : SSA_SUCCESS --- �ɹ�
  				  SSA_ERROR---ʧ��
  Output        :*pucAsciiNum --- Ascii���ַ���
  Invoke        : --
  Invoked By    : --
  History       : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
********************************************************************************/
VOS_VOID SSA_BcdNumToAsciiNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucBcdNum,
                              VOS_UINT8 ucBcdNumLen, VOS_UINT8 ucNumType)
{
    VOS_UINT32      ulTmp;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    if (SSA_NUM_TYPE_INT_E164 == ucNumType) /*<==A32D10708*/
    {
        *pucAsciiNum = '+';
        pucAsciiNum++;
    }

    for (ulTmp = 0; ulTmp < ucBcdNumLen; ulTmp++)
    {
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + ulTmp)) & 0x0f);             /*low four bits*/
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + ulTmp)) >> 4) & 0x0f);   /*high four bits*/
        if(ucFirstNumber <= 9)
        {
            *pucAsciiNum = ucFirstNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucFirstNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucFirstNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucFirstNumber + 0x55;
            pucAsciiNum++;
        }

        /* the following proceed the second number */
        if(0xf == ucSecondNumber)
        {
            break;
        }
        if(ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucSecondNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucSecondNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucSecondNumber + 0x55;
            pucAsciiNum++;
        }
    }
    *pucAsciiNum = '\0';
}

/*****************************************************************************
*  Prototype       : SSA_Get7bits
*  Description     : ��7bit����Ķν��н��벢ת��Ϊ�ֽ�
*  Input           : pucEncodedMsg --- ָ��������7bit�ַ�����ָ��
*                    ulBitAddress  --- ��7Ϊ������bit���ĳ���ֵ
*  Output          : pucChar       --- ָ���������ɵ��ֽڵ�ָ��
*  Return Value    : SMT_FALSE     --- ʧ��
*                    SMT_TRUE      --- �ɹ�
*  Calls           :
*  Called By       : Smt_DecodeMessage
*  History         :
*  1. Date         : 2005-10-30
*     Author       : ۬����
*     Modification : Created function
*****************************************************************************/
VOS_VOID SSA_Get7bits( VOS_UINT8 *pucChar,
                   VOS_UINT8 const *pucEncodedMsg,
                   VOS_UINT32 ulBitAddress )
{
    VOS_UINT32   ulAddress;      /*����ֽڵ�ַ*/
    VOS_UINT32   ulOffset;       /*���λƫ��*/

    /*������ֽڵ�ַ��λƫ��*/
    ulAddress = ulBitAddress / 8;
    ulOffset  = ulBitAddress % 8;

    /*����������ַ��������֣��ֱ�����ڵ������ֽڶ�����*/
    /*������һ���ֵ�����*/
    *pucChar = ( pucEncodedMsg[ulAddress] >> ulOffset ) & 0x7F;
    /*���λƫ��С��2����û�еڶ����ֵ����ݣ�ֱ�ӷ���*/
    if ( ulOffset < 2 )
    {
        return;
    }
    /*���������ڶ����ֵ�����*/
    /*lint -e701*/
    *pucChar |= ( ( pucEncodedMsg[ulAddress + 1] << ( 8 - ulOffset ) ) & 0x7F );
    /*lint +e701*/
}
VOS_VOID SSA_Decode7bit (TAF_SS_USSD_STRING_STRU   *para, VOS_UINT8  ucCodingScheme)
{
    VOS_UINT8      aucTmp[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32     ulLoop;
    VOS_UINT32     ulBitAddress;
    VOS_UINT8      ucDecodeLen;

    ulLoop        = 0;
    ulBitAddress  = 0;


    /*�ж��Ƿ���7bit����,���ݲ�Ʒ������ֻ֧��0000 XXXX��7bit���룬
     ������ʽ��7bit����ֱ�Ӷ�����������error */

    if (0 == para->usCnt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_Decode7bit:WARNING: string size 0");
        return;
    }

    if ((0x00 == (ucCodingScheme >> 4 ))
        || (TAF_SS_7BIT_DATA_CODING == ucCodingScheme))
    {
        PS_MEM_SET(aucTmp, 0, TAF_SS_MAX_UNPARSE_PARA_LEN);

        /*���ȳ���182���ַ�����*/
        if (para->usCnt > TAF_SS_MAX_USS_CHAR)
        {
            SSA_LOG(WARNING_PRINT, "SSA_Decode7bit:WARNING: string too long");
            return;
        }

        /*����7bit�ַ���*/
        ucDecodeLen = (VOS_UINT8)((para->usCnt * 8) / 7);
        if (0 == ((para->usCnt * 8) % 7))
        {
            /*���ֽ���Ϊ8(n-1)ʱ,ȷ�����һ���ֽڵĸ�7λ�ǲ���Ϊ0001101,
            �ǵĻ�,��Ϊ�ǻس�,�����ַ�*/
            if (0x0d == (para->aucUssdStr[para->usCnt-1]>>1))
            {
                ucDecodeLen--;
            }
        }

        /*ѭ���ṹ,ת����7bit���뷽ʽ*/
        for ( ulLoop = 0; ulLoop < ucDecodeLen; ulLoop++ )
        {
            SSA_Get7bits(&aucTmp[ulLoop], para->aucUssdStr, ulBitAddress);

            /*��һ���ַ��ĵ�ַ*/
            ulBitAddress += 7;
        }

        /*��ֵ,�������������ַ���*/
        para->usCnt = ucDecodeLen;
        PS_MEM_CPY(para->aucUssdStr, aucTmp, para->usCnt);
    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_Decode7bit:WARNING: CodingScheme is not suport");
        return;
    }
    return;
}
VOS_UINT32 SSA_DecodeUssdMessage (TAF_SS_USSD_STRING_STRU   *para, VOS_UINT8  ucCodingScheme)
{
    VOS_UINT8      aucTmp[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32     ulLoop;
    VOS_UINT32     ulBitAddress;
    VOS_UINT8      ucDecodeLen;
    VOS_UINT8      aucAscii_String[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32     n;
    VOS_UINT8      *pucCurTransTbl= VOS_NULL_PTR;

    ulLoop        = 0;
    ulBitAddress  = 0;
    n             = 0;

    PS_MEM_SET(aucAscii_String, 0, TAF_SS_MAX_UNPARSE_PARA_LEN);

    if (0 == para->usCnt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdMessage:WARNING: string usCnt 0");
        return SSA_FAILURE;
    }

    /*�ж��Ƿ���7bit����,���ݲ�Ʒ������ֻ֧��0000 XXXX��7bit���룬
     ������ʽ��7bit����ֱ�Ӷ�����������error
    */
    if ((0x00 == (ucCodingScheme >> 4 ))
        || (TAF_SS_7BIT_DATA_CODING == ucCodingScheme))
    {
        PS_MEM_SET(aucTmp, 0, TAF_SS_MAX_UNPARSE_PARA_LEN);

        /*���ȳ���182���ַ�����*/
        if (para->usCnt > TAF_SS_MAX_USS_CHAR)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdMessage:WARNING: string too long");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }

        /*����7bit�ַ���*/
        ucDecodeLen = (VOS_UINT8)((para->usCnt * 8) / 7);
        if (0 == ((para->usCnt * 8) % 7))
        {
            /*���ֽ���Ϊ8(n-1)ʱ,ȷ�����һ���ֽڵĸ�7λ�ǲ���Ϊ0001101,
            �ǵĻ�,��Ϊ�ǻس�,�����ַ�*/
            if (0x0d == (para->aucUssdStr[para->usCnt-1]>>1))
            {
                ucDecodeLen--;
            }
        }

        /*ѭ���ṹ,ת����7bit���뷽ʽ*/
        for ( ulLoop = 0; ulLoop < ucDecodeLen; ulLoop++ )
        {
            SSA_Get7bits(&aucTmp[ulLoop], para->aucUssdStr, ulBitAddress);

            /*��һ���ַ��ĵ�ַ*/
            ulBitAddress += 7;
        }

        /*now convert from default alphabet coding into ascii coding*/
        pucCurTransTbl = TAF_SDC_GetCurr7BitToAsciiTableAddr();
        for( n = 0; n < ucDecodeLen; n++ )
        {
            aucAscii_String[n] = pucCurTransTbl[aucTmp[n]];
        }

        /*��ֵ,�������������ַ���*/
        para->usCnt = ucDecodeLen;
        PS_MEM_CPY(para->aucUssdStr, aucAscii_String, para->usCnt);

    }
    else
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeUssdMessage:WARNING: CodingScheme is not suport");
        return SSA_FAILURE;
    }
    return SSA_SUCCESS;
}


/*****************************************************************************
 Prototype      : SSA_DecodeInt
 Description    : ��BER������ֵ���н���
 Input          : **ppucSrc--����ǰ���ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pDest--������ֵ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeInt(VOS_INT32 *piDest, VOS_INT32 iMaxNum, VOS_UINT8 **ppucSrc, TAG_MODE usTagMode)
{
    VOS_UINT8    ucTmpValue;
    VOS_INT8     cTempLen;
    VOS_INT8     cTmpBuffer[sizeof(VOS_INT32)];
    /*VOS_UINT8    ucFillChar1 = 0; ucFillChar2 = 0xff;*/
    VOS_INT32      Tmpsize,i;

    PS_MEM_SET(cTmpBuffer, 0, sizeof(VOS_INT32));
    /*�����explicitģʽ*/
    if (EXPLICIT_MODE  == usTagMode)
    {
        ucTmpValue = (VOS_UINT8)(**ppucSrc & 0x1f);
        if (ucTmpValue != INTEGER_TAG)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeInt:WARNING: Tag Number Error");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
        *ppucSrc = *ppucSrc + 2;  /*����2���ֽ�,��ȡֵ*/
    }


    /*��ȡ���͵ĳ���*/
    cTempLen = (VOS_INT8)(*(*ppucSrc - 1));
    if ((cTempLen > 4) || (cTempLen <= 0)||(cTempLen > (VOS_INT32)sizeof(VOS_INT32)))
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInt:WARNING: Int length Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*�ж��Ƿ���0���ǵĻ�����ֵ����*/
    if ((*(*ppucSrc-1) == 1)&&(**ppucSrc == 0))
    {
        *piDest = 0;
        *ppucSrc = *ppucSrc + 1;
        return SSA_SUCCESS;
    }

    /*��һ���ֽں͵ڶ����ֽڵ����λ����ͬʱΪ0��1*/
    if (((**ppucSrc == 0) && ((*(*ppucSrc+1)&0x80) == 0)) ||
         ((**ppucSrc == 0xff) && ((*(*ppucSrc+1)&0x80) == 0x80)) )
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInt:WARNING: para value Error");
        return TAF_ERR_SS_UNEXPECTED_DATA_VALUE;
    }

    /*��¼��߱������ڵ��ֽڵ�ֵ*/
    ucTmpValue = **ppucSrc;

    /*���и�ֵ*/
    *piDest = 0;
    for (i = 0 ; i < cTempLen ; i++)
    {
        /* cTmpBuffer[(cTemLen - i) - 1] = (char)**ppucSrc ; */
        /* *ppucSrc = *ppucSrc + 1 ; */
        *piDest = (VOS_INT32)(((VOS_UINT32)*piDest << 8) + **ppucSrc);
        *ppucSrc = *ppucSrc + 1;
    }

    /*�������ff*/
    Tmpsize = (VOS_INT8)sizeof(VOS_INT32);
    /*lint -e961*/
    if ((ucTmpValue & 0x80) && (Tmpsize != cTempLen))
    /*lint +e961*/
    {
        *piDest =(VOS_INT32)((0xffffffff << ((Tmpsize - cTempLen)*8)) | *piDest);
    }

    /*�����趨�����ֵ,�򱨴���*/
    if (*piDest > iMaxNum)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeInt:WARNING: Value too large");
        return TAF_ERR_SS_UNEXPECTED_DATA_VALUE;
    }

    return SSA_SUCCESS;
}



/*****************************************************************************
 Prototype      : SSA_DecodeString
 Description    : ��Octet String���͵��ִ��������ͨ���ַ���
 Input          : **ppucSrc--����ǰ���ִ�
 Output         : *pucDest--�������ִ�   *pDestLen--�������ִ�����
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeString(VOS_UINT8 *pucDest, VOS_UINT8 *pucDestLen, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    /* VOS_UINT8            ucCurLen; */
    VOS_UINT32           ulRslt;
    /* SSA_TAG_STRU         stTagStru; */

    /*�����explicitģʽ*/
    if (EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����Ļ�return*/
        ulRslt = SSA_DecodeTag(ppucSrc, &gSsTagValue);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeString:WARNING: Tag Value Error");
            return ulRslt;
        }

        /*�Գ��Ƚ��н��룬ʧ���򷵻�*/
        ulRslt = SSA_DecodeLength(ppucSrc, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeString:WARNING: Length Value Error");
            return ulRslt;
        }
    }

    /*����ǳ���ȷ���͵�����*/
    /* if (gucSsCurLen != INDEFINITE_LEN) ����ȷ����*/
    /*{ */
    /*�Է��صĳ��Ƚ��м��*/
    if ((gucSsCurLen == 0)||(gucSsCurLen > gulCurStrMaxLen))
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeString:WARNING: Length Error");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*���ݽ���������ַ��������������ڴ濽��*/
    PS_MEM_CPY(pucDest, *ppucSrc, gucSsCurLen);

    *pucDestLen = gucSsCurLen;

    *ppucSrc = *ppucSrc + gucSsCurLen;

    return SSA_SUCCESS ;
   /* } */

    #if 0
    /*����Ƿ�ȷ����������,������ȫ0�ֽڼ����˱�����Value�ֶκ���*/
    *pucDestLen = 0;
    while ((**ppucSrc != 0) && (*(*ppucSrc + 1) != 0))
    {
        /*����Tag����*/
        SSA_DecodeTag(ppucSrc, stTagStru);

        /*�Գ��Ƚ��н���,��ȡ��ǰ����*/
        ulRslt = SSA_DecodeLength(ppucSrc, &ucCurLen);
        /*��鷵�صĲ���, ����Ļ�return*/

        /*��ȡ����ǰ���ִ��ܳ�*/
        *pucDestLen = *pucDestLen + ucCurLen;

        /*���ݽ���������ַ��������������ڴ濽��*/
        VOS_MemCpy(pucDest + *pucDestLen, *ppucSrc, ucCurLen);

        /*Դ�ִ���ָ����λ*/
        *ppucSrc = *ppucSrc + ucCurLen;
    }
    #endif
}


/*****************************************************************************
 Prototype      : SSA_DecodeEnum
 Description    : BER�����ö��ֵת����VOS_UINT8��
 Input          : **ppucSrc--����ǰ���ִ�, ucTagMode -- ��ǩģʽ
 Output         : *pucDest--������ֵ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeEnum( VOS_UINT8 *pucDest, VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8       ucTagNum;

    /*�����explicitģʽ*/
    if (EXPLICIT_MODE == ucTagMode)
    {
        /*��ȡTag��ֵ*/
        ucTagNum = (VOS_UINT8)(**ppucSrc & 0x1f);

        /*�Ա�ǩֵ�����ж�*/
        if (ucTagNum != ENUMERATED_TAG)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeEnum:WARNING: Enum Tag Num Wrong");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }

        /*ָ��TLV��V��ָ��ĵ�ַ*/
        *ppucSrc = *ppucSrc + 2;
    }

    /*�ж�TLV��L��ֵ*/
    if (*(*ppucSrc - 1) != 1)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeEnum:WARNING: Enum Tag Num Wrong");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    /*���и�ֵ����ƫ��ָ��*/
    *pucDest = **ppucSrc;
    *ppucSrc = *ppucSrc + 1;

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_DecodeLength
 Description    : ����BER����ĳ��ȷ��������Ϣ�еĳ����ֶΣ�
                  ��һ������: �����Ͳ�����
                  �ڶ�������: �������ķ�Ϊ����ʽ�Ͷ̸�ʽ
 Input          : **ppucSrc--����ǰ���ִ�
 Output         : *pucLen--�����ĳ���
 Return Value   : Tag�����
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  SSA_DecodeLength(VOS_UINT8 **ppucSrc, VOS_UINT8 *pucLen)
{
    VOS_UINT8    ucTmpLen;

    *pucLen = 0;
    ucTmpLen = **ppucSrc;

    *ppucSrc = *ppucSrc + 1;

    /* ����Ƕ̸�ʽģʽ����ȷ���ȣ����㳤�� */
    if (ucTmpLen < 128)
    {
        *pucLen = ucTmpLen;
        return SSA_SUCCESS;
    }

    switch (ucTmpLen)
    {
        case 128:   /*�������ȵļ��㴦��*/
            /*������SS��para���ܳ����ǿ�֪�ģ����Բ�Ӧ�ó���ֱ�Ӵ������ݶ���������������ݵĳ���*/
            /* SSA_LOG(WARNING_PRINT, "SSA_DecodeLength:WARNING: Length 128 Wrong"); */
            if (SSA_SUCCESS != SSA_DecodeIndefLen(*ppucSrc, pucLen))
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeLength:WARNING: Indefine Len Error");
                return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
            }
            break;
        case 129:   /*����ʽ�����ֽڣ�*/
            *pucLen = **ppucSrc;
            *ppucSrc = *ppucSrc + 1;
            break;
        default:
            /*
            ����129����������ڳ��Ȳ��ᳬ��һ���ֽڣ���ʹ�ö��ֽڱ�ʾʱ�����ᳬ��һ���ֽ�
            ���������������
            */
            SSA_LOG(WARNING_PRINT, "SSA_DecodeLength:WARNING: length too long");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    return SSA_SUCCESS;

}


VOS_UINT32 SSA_DecodeIndefLen(VOS_UINT8 *pucSrc, VOS_UINT8 *pucLen)
{
    VOS_UINT8                           ucCheckLength;
    VOS_UINT8                           aucEndFlag[] = {0,0};
    VOS_UINT8                           ucEndFlagLength;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucLength;
    VOS_UINT8                           ucLengthBytes;
    VOS_UINT32                          ulRet;

    /* ��ȡLEN��ʵ�ʳ��ȣ� */
    /* ���¿ɱ䳤���ֶ�Ϊʵ�ʳ��ȣ��������ܳ��ȱ��Ϊ�ɱ䳤�ȵ�ʵ�ʳ��ȵĽ���λ�ã�*/
    /* ֱ������鳤����TLV�ֶε�Lһ�½��� */
    ucCheckLength   = SSA_MAX_COMPONENT_LENGTH;
    ucEndFlagLength = sizeof(aucEndFlag);
    ulLoop          = 0;

    while (ulLoop < SSA_MAX_COMPONENT_LENGTH)
    {
        if (0 == PS_MEM_CMP(pucSrc, aucEndFlag, ucEndFlagLength))
        {
            *pucLen = (VOS_UINT8)ulLoop;
            return SSA_SUCCESS;
        }

        /* TAG */
        pucSrc++;
        ulLoop++;

        /* LENGTH */
        ucLength    = *pucSrc;
        pucSrc++;
        ulLoop++;

        /* ��������ʽ:Length���ڰ�λ��̶�����Ϊ0x80��Value���������������0x00��β��*/
        if (SSA_FALSE_LENGTH_FLAG == ucLength)
        {
            ucLength = ucCheckLength - (VOS_UINT8)ulLoop;
            ulRet = SSA_DecodeIndefLen(pucSrc, &ucLength);
            if (SSA_SUCCESS != ulRet)
            {
                return ulRet;
            }

            pucSrc  += ucLength;
            ulLoop  += ucLength;
        }
        else
        {
            if (SSA_FALSE_LENGTH_FLAG == (ucLength & SSA_FALSE_LENGTH_FLAG))
            {
                /* ������ʽ����ʽ: ��һ����λ��ĵ���λָ������L��ռ�õİ�λ�������������λ���ʾV�ĳ��� */
                /* SS��֧�ֳ���Ϊ1�ֽڵĳ��� */
                ucLengthBytes = ucLength & SSA_LONG_LENGTH_FORMAT_MASK;
                if (ucLengthBytes > sizeof(VOS_UINT8))
                {
                    SSA_LOG(WARNING_PRINT, "SSA_DecodeLength:WARNING: length too long");
                    return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
                }

                /* LENGTH */
                ucLength    = *pucSrc;
                pucSrc++;
                ulLoop++;

                pucSrc  += ucLength;
                ulLoop  += ucLength;
            }
            else
            {
                /* ������ʽ�̸�ʽ */
                pucSrc  += ucLength;
                ulLoop  += ucLength;
            }
        }

    }

    return SSA_FAILURE;
}

/*****************************************************************************
 Prototype      : SSA_DecodeTag
 Description    : ��BER�����Tag��ֵ���н���
 Input          : **ppucSrc -- ����ǰ���ִ�
 Output         : *pstTagStru -- ��ǩ�Ľṹ
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeTag(VOS_UINT8 **ppucSrc , SSA_TAG_STRU *pstTagStru)
{
    VOS_UINT8       ucCounter = 0;
    VOS_UINT8       ucTmp;

    ucTmp = **ppucSrc;

    /*��ȡ��ǩ���ͺͽṹ*/
    pstTagStru->ucClass = (VOS_UINT8)(ucTmp >> 6);
    pstTagStru->ucStructed = (VOS_UINT8)(((ucTmp & 0x20) == PRIMITIVE_TAG) ? PRIMITIVE_TAG : CONSTRUCTED_TAG);

    /*��ȡ��ǩֵ*/
    ucTmp = (VOS_UINT8)(ucTmp & 0x1f);
    if (ucTmp != 0x1f)          /*���ֽڸ�ʽ*/
    {
        pstTagStru->iNumber = ucTmp;
        *ppucSrc = *ppucSrc + 1;
        return SSA_SUCCESS;
    }

    /*���ֽڸ�ʽʱ,��ȡ��ǩֵ,���λΪ1ʱ,��ʾ�к����ֽ�*/
    /*�Ѻ����ֽڵĵ�һ���ֽڵ����һ���ֽڵĵ�7λ����һλ���������Ǳ�ǩ��ֵ*/
    pstTagStru->iNumber = 0;
    do
    {
        /*����ѭ��������int�͵ĳ������*/
        if (ucCounter > sizeof(pstTagStru->iNumber))
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeTag:WARNING: Tag Num wrong");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
        }
        ucCounter ++;
        *ppucSrc = *ppucSrc + 1;
        ucTmp = **ppucSrc;
        pstTagStru->iNumber = (VOS_INT32)(((VOS_UINT32)pstTagStru->iNumber << 7) + (ucTmp & 0x7f));
    }while(ucTmp >= 128);

    *ppucSrc = *ppucSrc + 1;

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_DecodeSsNull
 Description    : ��������NULL����,���Ͷ���μ�24.080,��¼
 Input          : **ppucSrc--����ǰ���ִ�, ucTagMode -- ��ǩģʽ
 Output         : --
 Return Value   : �������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-01-21
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 SSA_DecodeSsNull(VOS_UINT8 **ppucSrc, TAG_MODE ucTagMode)
{
    VOS_UINT8    ucTmp;

    /*�������ʽģʽ�������tag*/
    if (ucTagMode == EXPLICIT_MODE)
    {
        ucTmp = (**ppucSrc & 0x1F) ;
        if (ucTmp != NULL_TAG)
        {
            SSA_LOG(WARNING_PRINT, "SSA_DecodeSsNull:WARNING: Null Tag Value Err");
            return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER ;
        }

        gucSsCurLen = *(*ppucSrc + 1);
        *ppucSrc = *ppucSrc + 2 ;
    }

    /*NULLģʽ�£����ȱ�Ȼ��0*/
    if (gucSsCurLen != 0)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeSsNull:WARNING: Null Type Length Value Err");
        return TAF_SS_REJ_INVOKE_MISTYPED_PARAMETER;
    }

    return SSA_SUCCESS;
}



VOS_UINT32 SSA_DecodeTL(
    VOS_UINT8                           **ppucSrc,
    SSA_TAG_STRU                        *pstTagStru,
    VOS_UINT8                           *pucLen
)
{
    VOS_UINT32                          ulRslt;

    /* �Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ�� */
    ulRslt = SSA_DecodeTag(ppucSrc, pstTagStru);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeTL:WARNING: Tag Value Wrong");
        return ulRslt;
    }

    ulRslt = SSA_DecodeLength(ppucSrc, pucLen);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeTL:WARNING: Length Value Error");
        return ulRslt;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeSSDataSsCode(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                              ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���ss-Code�������Tagֵ:OCTETSTRING_TAG*/
        if ((OCTETSTRING_TAG == gSsTagValue.iNumber)
         && (*ppucSrc < pucEndLocation)
           )
        {
            /*����ss-Code������,����ʧ���򷵻�*/
            ulRslt = SSA_DecodeSsCode(&(pstDest->SsCode), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataSsCode:WARNING: SSA_DecodeSsCode Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsCode    = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc              = pucCurLocation;
            pstDest->OP_SsCode    = 0;
        }
    }
    else
    {
        /*����û�в�����ss-Code*/
        pstDest->OP_SsCode    = 0;
        ulRslt                = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeSSDataSsStatus(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���ss-Status�������Tagֵ:OCTETSTRING_TAG*/
        if ((4 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����SsStatus������*/
            ulRslt = SSA_DecodeSsStatus(&(pstDest->SsStatus), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataSsStatus:WARNING: SSA_DecodeSsStatus Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsStatus        = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_SsStatus        = 0;
        }
    }
    else
    {
        /*����û�в�����ss-status*/
        pstDest->OP_SsStatus     = 0;
        ulRslt                   = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeSSDataSsSubScriptionOp(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���ss-SubscriptionOption�������Tagֵ:OCTETSTRING_TAG*/
        if (((2 == gSsTagValue.iNumber) || (1 == gSsTagValue.iNumber))
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����ss-SubscriptionOption������*/
            pstDest->SsSubScriptionOp.SubScriptionOptionChoice = (VOS_UINT8)gSsTagValue.iNumber;
            ulRslt = SSA_DecodeEnum(&(pstDest->SsSubScriptionOp.SubScriptionOptionValue), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataSsSubScriptionOp:WARNING: ss-SubscriptionOption Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsSubscriptionOp    = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                        = pucCurLocation;
            pstDest->OP_SsSubscriptionOp    = 0;
        }
    }
    else
    {
        /*����û�в�����ss-SubscriptionOption*/
        pstDest->OP_SsSubscriptionOp    = 0;
        ulRslt                          = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeSSDataBasicServiceGroupList(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���basicServiceGroupList�������Tagֵ:SEQUENCE_TAG*/
        if ((SEQUENCE_TAG == gSsTagValue.iNumber)
         && (*ppucSrc < pucEndLocation))
        {
            /*����basicServiceGroupList������*/
            ulRslt = SSA_DecodeBasicServiceGroupList(&(pstDest->BsServGroupList), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataBasicServiceGroupList:WARNING: SSA_DecodeBasicServiceGroupList Decode Failure");
                return ulRslt;
            }
            pstDest->OP_BsServGroupList     = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                        = pucCurLocation;
            pstDest->OP_BsServGroupList     = 0;
        }
    }
    else
    {
        /*����û�в�����basicServiceGroupList*/
        pstDest->OP_BsServGroupList     = 0;
        ulRslt                          = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeSSDataDefaultPriority(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

         /*�ж��Ƿ���defaultPriority �������Tagֵ:INTEGER_TAG*/
        if ((INTEGER_TAG == gSsTagValue.iNumber)
         && (*ppucSrc < pucEndLocation))
        {

            /*����defaultPriority������*/
            ulRslt = SSA_DecodeDefaultPriority(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataDefaultPriority:WARNING: SSA_DecodeBasicServiceGroupList Decode Failure");
                return ulRslt;
            }
            pstDest->DefaultPrio        = (VOS_UINT8)iTmp;
            pstDest->OP_DefaultPrio     = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_DefaultPrio     = 0;
        }
    }
    else
    {
        /*����û�в�����defaultPriority*/
         pstDest->OP_DefaultPrio    = 0;
         ulRslt                     = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeSSDataNbrUser(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

         /*�ж��Ƿ���nbrUser�������Tagֵ:INTEGER_TAG*/
        if ((5 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����nbrUser������*/
            ulRslt = SSA_DecodeNbrUser(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataNbrUser:WARNING: SSA_DecodeNbrUser Decode Failure");
                return ulRslt;
            }
            pstDest->NbrUser            = (VOS_UINT8)iTmp;
            pstDest->OP_NbrUser         = 1;
        }
        else
        {
            /*���һ����������ǩֵ������Ϊ�����������������������Ϊ����*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeSSDataNbrUser:WARNING: SSA_DecodeNbrUser Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }
    }
    else
    {
        /*����û�в�����nbrUser*/
        pstDest->OP_NbrUser     = 0;
        ulRslt                  = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeFwdFeatureBasicService(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���basicService�������Tagֵ:0x82, 0x83*/
        if (((2 == gSsTagValue.iNumber)||(3 == gSsTagValue.iNumber))
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����basicService������,����ʧ���򷵻�*/
            ulRslt = SSA_DecodeBasicService(&(pstDest->BsService), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureBasicService:WARNING: SSA_DecodeBasicService Decode Failure");
                return ulRslt;
            }
            pstDest->OP_BsService         = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                      = pucCurLocation;
            pstDest->OP_BsService         = 0;
        }
    }
    else
    {
        /*����û��basicService������*/
        pstDest->OP_BsService         = 0;
        ulRslt                        = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeFwdFeatureSsStatus(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���ss-Status�������Tagֵ:0x84*/
        if ((4 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����ss-Status������,����ʧ���򷵻�*/
            ulRslt = SSA_DecodeSsStatus(&(pstDest->SsStatus), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureSsStatus:WARNING: SSA_DecodeSsStatus Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SsStatus        = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_SsStatus        = 0;
        }
    }
    else
    {
        /*����û�в�����ss-status*/
        pstDest->OP_SsStatus        = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeFwdFeatureForwardedToNumber(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���forwardedToNumber�������Tagֵ:0x85*/
        if ((5 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����forwardedToNumber���������ʧ���򷵻�*/
            ulRslt = SSA_DecodeForwardedToNumber(&(pstDest->NumType), pstDest->aucFwdToNum, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureForwardedToNumber:WARNING: SSA_DecodeForwardedToNumber Decode Failure");
                return ulRslt;
            }
            pstDest->OP_NumType         = 1;
            pstDest->OP_FwdToNum        = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_NumType         = 0;
            pstDest->OP_FwdToNum        = 0;
        }
    }
    else
    {
        /*����û��forwardedToNumber������*/
        pstDest->OP_NumType         = 0;
        pstDest->OP_FwdToNum        = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeFwdFeatureForwardedToSubaddress(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���forwardedToSubaddress�������Tagֵ:0x88*/
        if ((8 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����forwardedToSubaddress������,����ʧ���򷵻�*/
            ulRslt = SSA_DecodeForwardedToSubaddress(&(pstDest->SubAddrType), pstDest->aucFwdToSubAddr, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureForwardedToSubaddress:WARNING: SSA_DecodeForwardedToSubaddress Decode Failure");
                return ulRslt;
            }
            pstDest->OP_SubAddrType       = 1;
            pstDest->OP_FwdToSubAddr      = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                      = pucCurLocation;
            pstDest->OP_SubAddrType       = 0;
            pstDest->OP_FwdToSubAddr      = 0;
        }
    }
    else
    {
        /*����û��forwardedToSubaddress������*/
        pstDest->OP_SubAddrType       = 0;
        pstDest->OP_FwdToSubAddr      = 0;
        ulRslt = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeFwdFeatureForwardingOptions(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���forwardingOptions�������Tagֵ:0x86*/
        if ((6 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����forwardingOptions������,����ʧ���򷵻�*/
            ulRslt = SSA_DecodeForwardingOptions(&(pstDest->FwdOption), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeForwardingFeature:WARNING: SSA_DecodeForwardingOptions Decode Failure");
                return ulRslt;
            }
            pstDest->OP_FwdOption       = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_FwdOption       = 0;
        }
    }
    else
    {
        /*����û��forwardingOptions������*/
        pstDest->OP_FwdOption       = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeFwdFeatureNoReplyConditionTime(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

       /*�ж��Ƿ���noReplyConditionTime�������Tagֵ:0x87*/
        if ((7 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����noReplyConditionTime�����ʧ���򷵻�*/
            ulRslt = SSA_DecodeNoReplyConditionTime(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureNoReplyConditionTime:WARNING: SSA_DecodeNoReplyConditionTime Decode Failure");
                return ulRslt;
            }
            pstDest->NoRepCondTime      = (VOS_UINT8)iTmp;
            pstDest->OP_NoRepCondTime   = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_NoRepCondTime   = 0;
        }
    }
    else
    {
        /*����û��noReplyConditionTime������*/
        pstDest->OP_NoRepCondTime   = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeFwdFeatureLongForwardedToNumber(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

         /*�ж��Ƿ���longForwardedToNumber�������Tagֵ:0x89*/
        if ((9 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����longForwardedToNumber������,����ʧ���򷵻�*/
            ulRslt = SSA_DecodeLongForwardedToNumber(&(pstDest->LongFwdNumType), pstDest->aucLongFwdToNum, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureLongForwardedToNumber:WARNING: SSA_DecodeNoReplyConditionTime Decode Failure");
                return ulRslt;
            }
            pstDest->OP_LongFwdNumType  = 1;
            pstDest->OP_LongFwdToNum    = 1;
        }
        else
        {
            /*���һ����������ǩֵ������Ϊ�����������������������Ϊ����*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeFwdFeatureLongForwardedToNumber:WARNING: NoReplyConditionTime Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }
    }
    else
    {
        /*����û��longForwardedToNumber������*/
        pstDest->OP_LongFwdNumType  = 0;
        pstDest->OP_LongFwdToNum    = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeGenericCliRestrictionOption(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���cliRestrictionOption�������Tagֵ:ENUMERATED_TAG*/
        if ((ENUMERATED_TAG == gSsTagValue.iNumber)
         && (*ppucSrc < pucEndLocation))
        {
            /*����cliRestrictionOption������,����ʧ�����򷵻�*/
            ulRslt = SSA_DecodeCliRestrictionOption(&(pstDest->CliRestrictionOp), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericServiceInfo:WARNING: SSA_DecodeCliRestrictionOption Decode Failure");
                return ulRslt;
            }
            pstDest->OP_CliStrictOp     = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_CliStrictOp     = 0;
        }
    }
    else
    {
        /*����û��cliRestrictionOption������*/
        pstDest->OP_CliStrictOp     = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeGenericMaxEntitledPriority(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���maximumEntitledPriority�������Tagֵ:80*/
        if ((0 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����maximumEntitledPriority������*/
            ulRslt = SSA_DecodeMaxEntitledPriority(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericMaxEntitledPriority:WARNING: SSA_DecodeMaxEntitledPriority Decode Failure");
                return ulRslt;
            }
            pstDest->MaxEntitledPrio    = (VOS_UINT8)iTmp;
            pstDest->OP_MaxEntiledPrio  = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_MaxEntiledPrio  = 0;
        }

    }
    else
    {
        /*����û��maximumEntitledPriority������*/
        pstDest->OP_MaxEntiledPrio  = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeGenericDefaultPriority(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���defaultPriority�������Tagֵ:81*/
        if ((1 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����defaultPriority������,����ʧ�����˳�*/
            ulRslt = SSA_DecodeDefaultPriority(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericDefaultPriority:WARNING: SSA_DecodeDefaultPriority Decode Failure");
                return ulRslt;
            }
            pstDest->DefaultPrio        = (VOS_UINT8)iTmp;
            pstDest->OP_DefaultPrio     = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_DefaultPrio     = 0;
        }
    }
    else
    {
        /*����û��defaultPriority������*/
        pstDest->OP_DefaultPrio     = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeGenericCcbsFeatureList(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���ccbs-FeatureList�������Tagֵ:0x82*/
        if ((2 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����ccbs-FeatureList������,����ʧ�����˳�*/
            ulRslt = SSA_DecodeCcbsFeatureList(&(pstDest->CcbsFeatureList), ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericCcbsFeatureList:WARNING: SSA_DecodeCcbsFeatureList Decode Failure");
                return ulRslt;
            }
            pstDest->OP_CcbsFeatureList = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc = pucCurLocation;
            pstDest->OP_CcbsFeatureList = 0;
        }
    }
    else
    {
        /*����û��ccbs-FeatureList������*/
        pstDest->OP_CcbsFeatureList = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeGenericNbrSB(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���nbrSB�������Tagֵ:0x83*/
        if ((3 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����nbrSB������,����ʧ�����˳�*/
            ulRslt = SSA_DecodeNbrSB(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericNbrSB:WARNING: SSA_DecodeNbrSB Decode Failure");
                return ulRslt;
            }
            pstDest->NbrSb              = (VOS_UINT8)iTmp;
            pstDest->OP_NbrSb           = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pstDest->OP_NbrSb           = 0;
        }
    }
    else
    {
        /*����û��nbrSB������*/
        pstDest->OP_NbrSb           = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeGenericNbrUser(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���nbrUser�������Tagֵ:0x84*/
        if ((4 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����nbrUser������,����ʧ�����˳�*/
            ulRslt = SSA_DecodeNbrUser(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericNbrUser:WARNING: SSA_DecodeNbrUser Decode Failure");
                return ulRslt;
            }
            pDest->NbrUser              = (VOS_UINT8)iTmp;
            pDest->OP_NbrUser           = 1;
        }
        else
        {
            /*���û�У����ûؽ���ǰλ�ã���ز������λ����0*/
            *ppucSrc                    = pucCurLocation;
            pDest->OP_NbrUser           = 0;
        }

    }
    else
    {
        /*����û��nbrUser������*/
        pDest->OP_NbrUser           = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeGenericNbrSN(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pDest,
    VOS_UINT8                           **ppucSrc,
    VOS_UINT8                           *pucCurLocation,
    VOS_UINT8                           *pucEndLocation
)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           iTmp;

    if (*ppucSrc < pucEndLocation)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }

        /*�ж��Ƿ���nbrSN�������Tagֵ:0x85*/
        if ((5 == gSsTagValue.iNumber)
         && (CONTEXT_SPECIFIC_TAG_TYPE == gSsTagValue.ucClass)
         && (*ppucSrc < pucEndLocation))
        {
            /*����nbrUser������,����ʧ�����˳�*/
            ulRslt = SSA_DecodeNbrSN(&iTmp, ppucSrc, IMPLICIT_MODE);
            if (SSA_SUCCESS != ulRslt)
            {
                SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericNbrSN:WARNING: SSA_DecodeNbrSN Decode Failure");
                return ulRslt;
            }
            pDest->NbrSn                = (VOS_UINT8)iTmp;
            pDest->OP_NbrSn             = 1;
        }
        else
        {
            /*���һ����������ǩֵ������Ϊ�����������������������Ϊ����*/
            SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericNbrSN:WARNING: nbrSN Tag Number Error");
            return TAF_SS_REJ_MISTYPED_COMPONENT;
        }

    }
    else
    {
        /*����û��nbrSN������*/
        pDest->OP_NbrSn             = 0;
        ulRslt                      = SSA_SUCCESS;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeSSData(
    TAF_SS_SSDATA_STRU                  *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT8                           *pucCurLocation;
    VOS_UINT32                          ulRslt;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if (EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������SsCode*/
    ulRslt = SSA_DecodeSSDataSsCode(pstDest,
                                    ppucSrc,
                                    pucCurLocation,
                                    pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������SsStatus*/
    ulRslt = SSA_DecodeSSDataSsStatus(pstDest,
                                      ppucSrc,
                                      pucCurLocation,
                                      pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������SsSubScriptionOp*/
    ulRslt = SSA_DecodeSSDataSsSubScriptionOp(pstDest,
                                              ppucSrc,
                                              pucCurLocation,
                                              pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������basicServiceGroupList*/
    ulRslt = SSA_DecodeSSDataBasicServiceGroupList(pstDest,
                                                   ppucSrc,
                                                   pucCurLocation,
                                                   pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������defaultPriority*/
    ulRslt = SSA_DecodeSSDataDefaultPriority(pstDest,
                                             ppucSrc,
                                             pucCurLocation,
                                             pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }


    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������nbrUser*/
    ulRslt = SSA_DecodeSSDataNbrUser(pstDest,
                                     ppucSrc,
                                     pucCurLocation,
                                     pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeForwardingFeature(
    TAF_SS_FWDFEATURE_STRU              *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT8                           *pucCurLocation;
    VOS_UINT32                          ulRslt;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTL(ppucSrc, &gSsTagValue, &gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }
    }

    /*�ִ�������ĵ�ַ*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������SsCode*/
    ulRslt = SSA_DecodeFwdFeatureBasicService(pstDest,
                                              ppucSrc,
                                              pucCurLocation,
                                              pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������SsStatus*/
    ulRslt = SSA_DecodeFwdFeatureSsStatus(pstDest,
                                          ppucSrc,
                                          pucCurLocation,
                                          pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������forwardedToNumber*/
    ulRslt = SSA_DecodeFwdFeatureForwardedToNumber(pstDest,
                                                   ppucSrc,
                                                   pucCurLocation,
                                                   pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������forwardedToSubaddress*/
    ulRslt = SSA_DecodeFwdFeatureForwardedToSubaddress(pstDest,
                                                       ppucSrc,
                                                       pucCurLocation,
                                                       pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������forwardingOptions*/
    ulRslt = SSA_DecodeFwdFeatureForwardingOptions(pstDest,
                                                   ppucSrc,
                                                   pucCurLocation,
                                                   pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������noReplyConditionTime*/
    ulRslt = SSA_DecodeFwdFeatureNoReplyConditionTime(pstDest,
                                                      ppucSrc,
                                                      pucCurLocation,
                                                      pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������longForwardedToNumber*/
    ulRslt = SSA_DecodeFwdFeatureLongForwardedToNumber(pstDest,
                                                       ppucSrc,
                                                       pucCurLocation,
                                                       pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    return ulRslt;
}
VOS_UINT32 SSA_DecodeGenericServiceInfo(
    TAF_SS_GENERIC_SERV_INFO_STRU       *pstDest,
    VOS_UINT8                           **ppucSrc,
    TAG_MODE                            ucTagMode
)
{
    VOS_UINT8                           *pucEndLocation;
    VOS_UINT8                           *pucCurLocation;
    VOS_UINT32                          ulRslt;

    /*���TAG_MODEΪEXPLICITģʽ*/
    if(EXPLICIT_MODE == ucTagMode)
    {
        /*�Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ��*/
        ulRslt = SSA_DecodeTL(ppucSrc,&gSsTagValue,&gucSsCurLen);
        if (SSA_SUCCESS != ulRslt)
        {
            return ulRslt;
        }
    }

    /*ȷ���ִ�����λ��*/
    pucEndLocation = *ppucSrc + gucSsCurLen;

    /*��ss-Status���н���,����ʧ���򷵻�*/
    ulRslt = SSA_DecodeSsStatus(&(pstDest->SsStatus), ppucSrc, EXPLICIT_MODE);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_DecodeGenericServiceInfo:WARNING: SSA_DecodeSsStatus Decode Failure");
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������cliRestrictionOption*/
    ulRslt = SSA_DecodeGenericCliRestrictionOption(pstDest,
                                                   ppucSrc,
                                                   pucCurLocation,
                                                   pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������maximumEntitledPriority*/
    ulRslt = SSA_DecodeGenericMaxEntitledPriority(pstDest,
                                                  ppucSrc,
                                                  pucCurLocation,
                                                  pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������defaultPriority*/
    ulRslt = SSA_DecodeGenericDefaultPriority(pstDest,
                                              ppucSrc,
                                              pucCurLocation,
                                              pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������ccbs-FeatureList*/
    ulRslt = SSA_DecodeGenericCcbsFeatureList(pstDest,
                                              ppucSrc,
                                              pucCurLocation,
                                              pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������nbrSB*/
    ulRslt = SSA_DecodeGenericNbrSB(pstDest,
                                    ppucSrc,
                                    pucCurLocation,
                                    pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������nbrUser*/
    ulRslt = SSA_DecodeGenericNbrUser(pstDest,
                                      ppucSrc,
                                      pucCurLocation,
                                      pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    /*��ǽ���ָ�뵱ǰλ��*/
    pucCurLocation = *ppucSrc;

    /*�������nbrSN*/
    ulRslt = SSA_DecodeGenericNbrSN(pstDest,
                                    ppucSrc,
                                    pucCurLocation,
                                    pucEndLocation);
    if (SSA_SUCCESS != ulRslt)
    {
        return ulRslt;
    }

    return ulRslt;
}



/* Deleted SSA_GetDcsMsgCoding */

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
