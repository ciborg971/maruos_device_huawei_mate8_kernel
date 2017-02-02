
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_MAIN_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafLog.h"
#include "TafXpdsMain.h"
#include "TafXpdsMntn.h"
#include "TafXpdsCtx.h"
#include "TafXpdsFsmMainTbl.h"
#include "TafXpdsPreProcTbl.h"
#include "TafXpdsFsmUpLinkCtrlTbl.h"
#include "TafXpdsFsmCpLinkCtrlTbl.h"
#include "TafXpdsFsmMpcProcTbl.h"
#include "TafXpdsFsmPdeProcTbl.h"
#include "TafXpdsFsmCpPdeProcTbl.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*lint -save -e958*/

VOS_UINT32 TAF_XPDS_RegPreFsm(VOS_VOID)
{
    /* Ԥ����״̬��ע�� */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetPreProcFsmDescAddr()),
                         "TAF:FSM:XPDS:PRE",
                         (VOS_UINT32)(TAF_XPDS_GetPreProcStaTblSize()),
                         TAF_XPDS_GetPreProcStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RegMainL1Fsm(VOS_VOID)
{
    /* main״̬��ע�� */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetMainFsmDescAddr()),
                         "TAF:FSM:XPDS:MAIN",
                         (VOS_UINT32)(TAF_XPDS_GetMainStaTblSize()),
                         TAF_XPDS_GetMainStaTblAddr(),
                         VOS_NULL_PTR,
                         TAF_XPDS_InitFsmCtx_L1Main);

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RegL2Fsm(VOS_VOID)
{
    /* �û�����·״̬��ע�� */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetFsmUpLinkFsmDescAddr()),
                         "TAF:FSM:XPDS:UP_LINK_CTRL",
                         (VOS_UINT32)TAF_XPDS_GetUpLinkCtrlStaTblSize(),
                         TAF_XPDS_GetUpLinkCtrlStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* ��������·״̬��ע�� */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetFsmCpLinkFsmDescAddr()),
                         "TAF:FSM:XPDS:CP_LINK_CTRL",
                         (VOS_UINT32)TAF_XPDS_GetCpLinkCtrlStaTblSize(),
                         TAF_XPDS_GetCpLinkCtrlStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* MPC״̬��ע�� */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetL2MpcProcFsmDescAddr()),
                         "TAF:FSM:XPDS:MPC",
                         (VOS_UINT32)TAF_XPDS_GetL2MpcProcStaTblSize(),
                         TAF_XPDS_GetL2MpcProcStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* PDE״̬��ע�� */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetL2PdeProcFsmDescAddr()),
                         "TAF:FSM:XPDS:PDE",
                         (VOS_UINT32)TAF_XPDS_GetL2PdeProcStaTblSize(),
                         TAF_XPDS_GetL2PdeProcStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* ������PDE״̬��ע�� */
    TAF_FSM_RegisterFsm((TAF_XPDS_GetCpL2PdeProcFsmDescAddr()),
                         "TAF:FSM:XPDS:CP_PDE",
                         (VOS_UINT32)TAF_XPDS_GetCpL2PdeProcStaTblSize(),
                         TAF_XPDS_GetCpL2PdeProcStaTblAddr(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return VOS_TRUE;
}
VOS_VOID  TAF_XPDS_RegFsm(VOS_VOID)
{
    /* ע��Ԥ����״̬�� */
    TAF_XPDS_RegPreFsm();

    /* ע��L1״̬�� */
    TAF_XPDS_RegMainL1Fsm();

    /* ע��L2״̬�� */
    TAF_XPDS_RegL2Fsm();
}
VOS_UINT32 TAF_XPDS_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt = VOS_FALSE;
    TAF_ACTION_FUNC                     pActFun;
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ȡԤ���������е���Ӧ�Ķ��������� */
    pstFsmDesc = TAF_XPDS_GetPreProcFsmDescAddr();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, TAF_XPDS_L1_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* Ԥ������Ϣ,��Ϊ������Ϣ,һ��ΪԤ��������ͷ���,����һ��ΪԤ����
        ������,��Ȼ��Ҫ���е�״̬���м�������,��˴˴�ֱ��ͨ����������Ԥ��
        ��������Ƿ���Ҫ����״̬������*/
        ulRslt = (*pActFun) ( ulEventType, pstMsg);
    }

    return ulRslt;
}


VOS_UINT32 TAF_XPDS_FsmProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    TAF_ACTION_FUNC                     pActFun;
    TAF_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    TAF_INFO_LOG2(UEPS_PID_XPDS, "TAF_XPDS_FsmProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = TAF_XPDS_GetCurFsmDesc();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* ������ص��¼���������Ϊ��,�����������¼����� */
        ulRet   = (*pActFun)(ulEventType, (struct MsgCB*)pRcvMsg);

        TAF_INFO_LOG1(UEPS_PID_XPDS, "TAF_XPDS_FsmProcessEvent", ulRet);

        return VOS_TRUE;
    }

    /* ��Ϣδ��������������� */
    return VOS_FALSE;
}
VOS_UINT32 TAF_XPDS_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    TAF_XPDS_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* ��ȡ��ǰXREG��״̬�������� */
    pstCurFsm          = TAF_XPDS_GetCurFsmAddr();

    /* ��ȡ��ǰXREG��ջ��� */
    usOldStackDepth    = TAF_XPDS_GetFsmStackDepth();

    /* ��Ϣ���� */
    ulRet              = TAF_XPDS_FsmProcessEvent(pstCurFsm->ulState,
                                                   ulEventType,
                                                   (VOS_VOID*)pstMsg);

    /* ��ȡ��ǰXREG����ջ��� */
    usNewStackDepth    = TAF_XPDS_GetFsmStackDepth();

    /* ջ���û������,����û�д����µ�״̬���������˳�*/
    if (usNewStackDepth <= usOldStackDepth)
    {
        return ulRet;
    }

    /* �µ�ջ��ȴ����ϵ�ջ��� ����������ѹջ,��Ҫ����Ϣ����״̬���м������� */
    /* ���»�ȡ��ǰXREG�Ķ���״̬ */
    pstCurFsm   = TAF_XPDS_GetCurFsmAddr();

    /* ����Ϣ���붥��״̬������������ */
    ulRet       = TAF_XPDS_FsmProcessEvent(pstCurFsm->ulState,
                                            ulEventType,
                                            (VOS_VOID*)pstMsg);


    return ulRet;
}


VOS_VOID TAF_XPDS_ProcessIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstIntMsg = (MSG_HEADER_STRU *)TAF_XPDS_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* ��Ϣ���� */
        TAF_XPDS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                                  pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                                  (VOS_VOID *)pstIntMsg);

        ulEventType = TAF_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        /* ����Ѿ����������ȡ������Ϣ�������� */
        if (VOS_TRUE == TAF_XPDS_PreProcessMsg(ulEventType, (struct MsgCB*)pstIntMsg))
        {
            /* �ͷ��ڲ���Ϣ */
            PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

            /* ������һ����Ϣ���� */
            pstIntMsg = (MSG_HEADER_STRU *)TAF_XPDS_GetNextIntMsg();

            continue;
        }

        /* ��Ϣ��״̬������ */
        TAF_XPDS_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);

        /* �ͷ��ڲ���Ϣ */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* ������һ����Ϣ���� */
        pstIntMsg = (MSG_HEADER_STRU *)TAF_XPDS_GetNextIntMsg();
    }

    return;
}
VOS_VOID TAF_XPDS_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;

    /* ��ָ���� */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* ��ӡ������Ϣ */
        return;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* �����¼����� */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* ֹͣ��Ӧ�Ķ�ʱ�� */
        TAF_XPDS_StopTimer(pRcvTimerMsg->ulName);
    }
    else
    {
        ulEventType  = TAF_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* ����Ѿ����������ֱ�ӷ��� */
    if (VOS_TRUE == TAF_XPDS_PreProcessMsg(ulEventType, pstMsg))
    {
        /* �����ڲ���Ϣ���� */
        TAF_XPDS_ProcessIntMsg();

        return;
    }

    /* ��ȡ��ǰXREG��ջ��� */
    usOldStackDepth = TAF_XPDS_GetFsmStackDepth();

    /* ����״̬������ */
    TAF_XPDS_ProcessMsgInFsm(ulEventType, pstMsg);

    /* ��״̬���˳��󣬻�ȡ�µ�ջ��� */
    usNewStackDepth = TAF_XPDS_GetFsmStackDepth();

    /* �����ڲ���Ϣ���� */
    TAF_XPDS_ProcessIntMsg();

    /* ���ջ����ȼ���,˵���϶���������ջ����,��Ҫ���ȴ����״̬���Ľ����Ϣ,ֱ�ӷ��� */
    if (usNewStackDepth < usOldStackDepth)
    {
        /* To do: ��¼��ջ����,ֻҪ��������ջ�����Ϳ��Դ����� */
        return;
    }

    return;
}


VOS_UINT32 TAF_XPDS_InitTask(VOS_VOID)
{
    /* ��ʼ�������� */
    TAF_XPDS_InitCtx();

    /* ע��״̬�� */
    TAF_XPDS_RegFsm();

    return VOS_OK;
}


VOS_UINT32 TAF_XPDS_InitPid(
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* ����XPDSģ���ʼ������ */
            TAF_XPDS_InitTask();
            break;

        default:
            break;
    }

    return VOS_OK;
}
/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

