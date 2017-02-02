


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallProcTaf.h"
#include "MnCallMgmt.h"
#include "TafSdcCtx.h"
#include "MnCallSendApp.h"
#include "MnCallReqProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_MN_CALL_PROC_TAF_C

/*****************************************************************************
   2 ��������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_RelAllNormalCall(
    TAF_CALL_TAF_REL_CALL_REQ_STRU     *pstMsg
)
{
    VOS_UINT8                                               i;
    VOS_UINT32                                              ulNumOfCalls;
    MN_CALL_ID_T                                            aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_SUPS_PARAM_STRU                                 stSupsParam;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);

    /* �쳣�������ó�����Ӧ�ó���, ����CS���д��ڱ�־ά���쳣�� */
    if (0 == ulNumOfCalls)
    {
        /* ���CS���д��ڱ�� */
        TAF_CALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);

        /* ����ȷ����Ϣ��SPM */
        TAF_CALL_SendTafRelCallCnf(pstMsg->usClientId, pstMsg->ucOpId, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    for (i = 0; i < ulNumOfCalls; i++)
    {
        /* �����ǰ�н�����������ѭ�� */
        if (VOS_TRUE == TAF_CALL_IsCallTypeEmgencyCall(aCallIds[i]))
        {
            /* ��ǰ�н��������ڣ���ֹ��ǰ���� */
            TAF_CALL_SendTafRelCallCnf(pstMsg->usClientId, pstMsg->ucOpId, TAF_CS_CAUSE_NOT_ALLOW);

            return;
        }
    } 

    /* �����ڲ��һ�����ΪTRUE */
    TAF_CALL_SetInternalHangUpFlag(VOS_TRUE);

    PS_MEM_SET(&stSupsParam, 0, sizeof(MN_CALL_SUPS_PARAM_STRU));
    
    stSupsParam.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ALL_CALL;
    
    /* �ͷ�����normal���� */    
    MN_CALL_CallSupsCmdRelAllCallReqProc(pstMsg->usClientId, pstMsg->ucOpId, &stSupsParam);

    return;
}


VOS_VOID TAF_CALL_RcvTafRelCallReq(
    TAF_CALL_TAF_REL_CALL_REQ_STRU                  *pstMsg
)
{
    if (TAF_CALL_REL_CALL_ALL_NORMAL == pstMsg->enRelType)
    {
        TAF_CALL_RelAllNormalCall(pstMsg);
    }
}
#endif
/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



