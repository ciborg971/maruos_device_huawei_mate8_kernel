

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "VosPidDef.h"
#include "v_msg.h"
#include "TafSdcCtx.h"
#include "TafSpmCtx.h"
#include "TafSpmRedial.h"
#include "NasSms.h"
#include "MnMsgApi.h"
#include "TafSpmMntn.h"
#if (FEATURE_IMS == FEATURE_ON)
#include "SpmImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_REDIAL_C

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 ��������
*****************************************************************************/


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
  6 ����ʵ��
*****************************************************************************/

VOS_UINT8 TAF_SPM_IsCallRedialCauseFromImsToCs(TAF_CS_CAUSE_ENUM_UINT32 enCause)
{

    VOS_UINT16                                               usIndex;
    TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU       *pstImsToCsRedialCauseCfg;
    pstImsToCsRedialCauseCfg  = TAF_SDC_GetImsToCsRedialCauseConfig();

    /* ���ԭ��ֵenCause�Ƿ���IMS�ز�ԭ��ֵ�б����� */
    for (usIndex = 0; usIndex < pstImsToCsRedialCauseCfg->ucImsRedialCauseNum; usIndex++)
    {
        if (enCause == pstImsToCsRedialCauseCfg->ausImsRedialCause[usIndex] + TAF_CS_CAUSE_IMS_BEGIN )
        {
            return VOS_TRUE;
        }
    }

    /* ���ԭ��ֵenCause�Ƿ���IMSA�ز�ԭ��ֵ�б����� */
    for (usIndex = 0; usIndex < pstImsToCsRedialCauseCfg->ucImsaRedialCauseNum; usIndex++)
    {
        if (enCause == pstImsToCsRedialCauseCfg->ausImsaRedialCause[usIndex] + TAF_CS_CAUSE_IMSA_BEGIN )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT8 TAF_SPM_IsCsCallRedialAllowed(MN_CALL_INFO_STRU *pstCallInfo)
{

    IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU                    stCallInfoInd;


    PS_MEM_SET(&stCallInfoInd, 0, sizeof(IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU));

    /* ���л����ز����ܹرգ�����Ҫ����CS�� */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return VOS_FALSE;
    }

    /* ����ú��в���MO������ */
    if (MN_CALL_DIR_MO != pstCallInfo->enCallDir)
    {
        return VOS_FALSE;
    }

    /* ����IMSA�ṩ��API��ѯ��ǰ��·ͨ������Ϣ������Ѿ���IMS��ͨ����
        �ڶ�·ͨ����������ͨ���л��ǽ����������������ز� */
    (VOS_VOID)IMSA_SpmGetCallInfo(&stCallInfoInd);

    TAF_SPM_LogRedialCallInfo(&stCallInfoInd);

    if (0 < stCallInfoInd.ucNumOfCalls)
    {
        return VOS_FALSE;
    }


    /* �����ͻ�����º����ز������Ѿ���������ز�����Ϊ�գ�����Ҫ���� */
    if (VOS_TRUE == TAF_SPM_IsCallRedialBufferEmpty())
    {
        return VOS_FALSE;
    }

    /* �������Ƶ���У�����Ҫ����CS�� */
    if (TAF_SPM_IS_VIDEO_CALL(pstCallInfo->enCallType))
    {
        return VOS_FALSE;
    }

    /* ����ǽ������������������ز� */
    if (MN_CALL_TYPE_EMERGENCY == pstCallInfo->enCallType)
    {
        return VOS_TRUE;
    }

    /* ԭ��ֵ��Ϊ�ز�causeֵ������Ҫ����CS�� */
    if (VOS_FALSE == TAF_SPM_IsCallRedialCauseFromImsToCs(pstCallInfo->enCause))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetCallRedialBufferWithCallId(MN_CALL_ID_T ucCallId)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg   = VOS_NULL_PTR;

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (ucCallId == pstAppMsg->callId)
        {
            return pstCacheMsg;
        }
    }

    return VOS_NULL_PTR;
}


VOS_VOID TAF_SPM_FreeCallRedialBufferWithClientId(MN_CLIENT_ID_T usClientId)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg   = VOS_NULL_PTR;

    /* �����ز�δ�򿪣�ֱ�ӷ��� */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return;
    }

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (usClientId == pstAppMsg->clientId)
        {
            TAF_SPM_FreeSpecificedIndexCallRedialBuffer(i);
            break;
        }
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();
}
VOS_VOID TAF_SPM_FreeCallRedialBufferWithCallId(MN_CALL_ID_T ucCallId)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg   = VOS_NULL_PTR;

    /* �����ز�δ�򿪣�ֱ�ӷ��� */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return;
    }

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (ucCallId == pstAppMsg->callId)
        {
            TAF_SPM_FreeSpecificedIndexCallRedialBuffer(i);
            break;
        }
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();
}
VOS_VOID TAF_SPM_UpdateCallRedialBufferMsgWithCallId(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_ID_T                        ucCallId
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAtMsg    = VOS_NULL_PTR;

    /* �����ز�δ�򿪣�ֱ�ӷ��� */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return;
    }

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAtMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (usClientId == pstAtMsg->clientId)
        {
            /* ����call Id */
            pstAtMsg->callId = ucCallId;
            break;
        }
    }
}



VOS_VOID TAF_SPM_UpdateCallRedialBufferMsgWithCallType(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_TYPE_ENUM_U8                enDestCallType,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmcCat
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAtMsg    = VOS_NULL_PTR;

    /* �����ز�δ�򿪣�ֱ�ӷ��� */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return;
    }

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAtMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (usClientId == pstAtMsg->clientId)
        {
            /* ����call Id */
            pstAtMsg->unParm.stOrig.enCallType  = enDestCallType;

            /* ������������ͨ���б�Ϊ��������ʱ��������������ҲҪ���� */
            if (MN_CALL_TYPE_EMERGENCY == enDestCallType)
            {
                PS_MEM_CPY(&(pstAtMsg->unParm.stOrig.stEmergencyCat), pstEmcCat, sizeof(MN_CALL_EMERGENCY_CAT_STRU));
            }
            break;
        }
    }
}
VOS_UINT8 TAF_SPM_StoreMsgIntoCallRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucStoreRlst;

    ucStoreRlst = VOS_FALSE;

    if (VOS_FALSE == TAF_SPM_IsCallRedialBufferFull())
    {
        /* ����Ϣ������ */
        ucStoreRlst = (VOS_UINT8)TAF_SPM_PutMsgIntoCallRedialBuffer(ulEventType, pstMsg);
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();

    return ucStoreRlst;
}
VOS_UINT8 TAF_MSG_IsSmsRedialCauseValueFromImsDomain(SMR_SMT_ERROR_ENUM_UINT32 enCause)
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT8                           ucRslt;
    MN_MSG_IMS_CAUSE_ENUM_UINT8         enImsCause;
    MN_MSG_IMSA_CAUSE_ENUM_UINT8        enImsaCause;
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause;

    ucRslt = VOS_FALSE;

    if (SMR_SMT_ERROR_IMS_ERROR_BEGIN == (SMR_SMT_ERROR_IMS_ERROR_BEGIN & enCause))
    {
        enImsCause = (MN_MSG_IMS_CAUSE_ENUM_UINT8)(enCause & (~SMR_SMT_ERROR_IMS_ERROR_BEGIN));

        switch (enImsCause)
        {
            case MN_MSG_IMS_CAUSE_INNER_ERROR:
            case MN_MSG_IMS_CAUSE_SMS_INCAPABILITY:
            case MN_MSG_IMS_CAUSE_SMS_NO_SMSC:
            case MN_MSG_IMS_CAUSE_SMS_NO_IPSMGW:
                ucRslt = VOS_TRUE;
                break;

            default:
                break;
        }
    }
    else if (SMR_SMT_ERROR_IMSA_ERROR_BEGIN == (SMR_SMT_ERROR_IMSA_ERROR_BEGIN & enCause))
    {
        enImsaCause = (MN_MSG_IMSA_CAUSE_ENUM_UINT8) (enCause & (~SMR_SMT_ERROR_IMSA_ERROR_BEGIN));

        switch (enImsaCause)
        {
            case MN_MSG_IMSA_CAUSE_NO_SERVICE:
                ucRslt = VOS_TRUE;
                break;

            default:
                break;
        }
    }
    else if (SMR_SMT_ERROR_RP_ERROR_BEGIN == (SMR_SMT_ERROR_RP_ERROR_BEGIN & enCause))
    {
        enRpCause = (MN_MSG_RP_CAUSE_ENUM_U8) (enCause & (~SMR_SMT_ERROR_RP_ERROR_BEGIN));

        switch (enRpCause)
        {
            /* ����RP cause�µ��ز�����������������ȷ��Ŀǰ����������cause */
            case MN_MSG_RP_CAUSE_NETWORK_OUT_OF_ORDER:                              /* 38 */
            case MN_MSG_RP_CAUSE_TEMPORARY_FAILURE:                                 /* 41 */
            case MN_MSG_RP_CAUSE_CONGESTION:                                        /* 42 */
            case MN_MSG_RP_CAUSE_RESOURCES_UNAVAILABLE_UNSPECIFIED:                 /* 47 */
            case MN_MSG_RP_CAUSE_REQUESTED_FACILITY_NOT_IMPLEMENTED:                /* 69 */
                ucRslt = VOS_TRUE;
                break;

            default:
                break;
        }
    }
    else
    {
        /* �ڲ�������Ҫ�ط��ĳ��� */
        switch (enCause)
        {
            case SMR_SMT_ERROR_TR1M_TIMEOUT:
                ucRslt = VOS_TRUE;
                break;

            default:
                break;
        }
    }

    return ucRslt;

#else
    /* SMR_SMT_ERROR_IMS_ERROR_BEGIN���ڵ�ԭ��ֵ����������ö���ж����ֵ����Ҫ�޸ĳ�UINT32
       ��������ȷ����mate7���Ȳ�����ԭ��ֵȫ�������ز�����austin�汾������ϸ���� */
    if (SMR_SMT_ERROR_NO_ERROR == enCause)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

#endif
}


TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSmsRedialBufferWithClientId(
    VOS_UINT8                          *pucIndex,
    MN_CLIENT_ID_T                      usClientId
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstRedialMsg = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg    = VOS_NULL_PTR;

    ucNum = TAF_SPM_GetNumberOfSmsRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM); i++)
    {
        pstRedialMsg = TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(i);

        pstAppMsg = (MN_APP_REQ_MSG_STRU *)(pstRedialMsg->aucEntryMsgBuffer);

        if (usClientId == pstAppMsg->clientId)
        {
            *pucIndex = i;

            return pstRedialMsg;
        }
    }

    return VOS_NULL_PTR;
}


VOS_UINT8 TAF_SPM_StoreMsgIntoSmsRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucStoreRlst;

    ucStoreRlst = VOS_FALSE;

    if (VOS_FALSE == TAF_SPM_IsSmsRedialBufferFull())
    {
        /* ����Ϣ������ */
        ucStoreRlst = (VOS_UINT8)TAF_SPM_PutMsgIntoSmsRedialBuffer(ulEventType, pstMsg);
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();

    return ucStoreRlst;
}

/*lint -restore */


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

