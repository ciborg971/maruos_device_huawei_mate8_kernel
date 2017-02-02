



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasLmmPubMTimer.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMSTACK_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMSTACK_C
/*lint +e767*/

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


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PushStackCombine()
 Discription    : ��ջ�ۺϲ���������3������:
                                    ״̬��ջ��
                                    ��ʱ����ջ��
                                    ȫ�ֱ�����ջ;
                  Ŀǰֻ������MRRC��RRC���ӽ������ͷ����������漰�˲���,
                  ������Ȩ���̻��漰��
                  ��ջ��Ŀ��״̬���޸Ĳ��ڴ˺�����ִ�У�
 Input          : ����״̬��ID, UE1.0�й̶���NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_LMM_FSM_PushStackCombine(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{

    /* ��ڼ�� */
    if ( enParalFsmId >= NAS_LMM_PARALLEL_FSM_BUTT )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PushStackCombine, FsmId error, FsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PushStackCombine_ENUM
,LNAS_FUNCTION_LABEL1,
                            enParalFsmId );

        return;
    }




    /***************��ջ����***************/

    /* ״̬��ѹջ���� */
    NAS_LMM_FSM_PushState(enParalFsmId);

    /* ��ʱ��״̬��ջ */
    NAS_LMM_FSM_PushTimer(enParalFsmId);

    /* ���ȫ�ֱ�����ջ */
    NAS_LMM_FSM_PushGlobPar(enParalFsmId);

    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PushState
 Discription    : ��ǰ״̬��ѹջ�����޸�״̬������ջ�󣬵�ǰ״̬�Ա�����ջǰ
                  ��״̬��״̬�޸ĵĹ�����ִ����ջ������ģ����ʽִ�С�
 Input          : ״̬��ջ��ַ
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_FSM_PushState( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{

    NAS_LMM_FSM_STATE_STACK_STRU       *pstFsmStack;        /* ״̬��ջ��ַ */
    NAS_LMM_FSM_STATE_STRU             *pstCurFsm;          /* ״̬����ַ */
    NAS_LMM_FSM_STATE_STRU             *pstFsmStackTop;     /* ָ��ջ��״̬ */



    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_EMM_FSM_PushState, The input is illegal! enParalFsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PushState_ENUM
,LNAS_FUNCTION_LABEL1,
                            enParalFsmId );

        return;
    }

    /* ��ȡEMM״̬����ǰ״̬�ĵ�ַ��״̬��ջ�ĵ�ַ */
    pstCurFsm      = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pstFsmStack    = NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);


    /* ״̬��ջ�Ƿ����� */
    if ( pstFsmStack->ucStackDepth >= NAS_LMM_MAX_STACK_DEPTH )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_EMM_FSM_PushState, The stack depth overflow!, ucStackDepth",
                            pstFsmStack->ucStackDepth);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PushState_ENUM
,LNAS_FUNCTION_LABEL2,
                            pstFsmStack->ucStackDepth );

        /* ջ��Ӧ����Щ������ */

        return;
    }


    /* ��ȡ״̬ջջ����ַ */
    pstFsmStackTop              = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth]);

    /* ��ջ */
    pstFsmStackTop->enFsmId     = pstCurFsm->enFsmId;
    pstFsmStackTop->enMainState = pstCurFsm->enMainState;
    pstFsmStackTop->enSubState  = pstCurFsm->enSubState;
    pstFsmStackTop->enStaTId    = pstCurFsm->enStaTId;

    /* ջ��ȼ� 1 */
    pstFsmStack->ucStackDepth++;

    return;
}


VOS_VOID    NAS_LMM_FSM_PushTimer(  NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_FSM_STATE_STRU              *pstCurFsm;          /* ״̬����ַ */


    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(    enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR(           "NAS_LMM_FSM_PushTimer, The input is illegal! enParalFsmId",
                                        enParalFsmId);
       TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PushTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                        enParalFsmId );

        return;
    }

    pstCurFsm                           = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);

    /* ͣ��ǰ״̬���е�״̬������ʱ��*/
    NAS_LMM_StopStateTimer(              pstCurFsm->enStaTId);

    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PushGlobPar
 Discription    : ��ǰ״̬����ջǰ,������ǰ״̬�漰����Щ��Ҫ������ȫ�ֱ���
 Input          : ״̬��ջ��ַ ��״̬
 Output         : None
 Return         : None
 History:

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_PushGlobPar(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    (VOS_VOID)(enParalFsmId);
    /*��ʱû����Ҫ��ջ�ı���*/

    return;
}



/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PopStackCombine()
 Discription    : ��ջ�ۺϲ���������3������:
                                    ״̬��ջ��
                                    ��ʱ����ջ��
                                    ȫ�ֱ�����ջ��
                  Ŀǰֻ������MRRC��RRC���ӽ������ͷ����������漰�˲���,
                  ������Ȩ���̻��漰��;
 Input          : ����״̬��ID, UE1.0�й̶���NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_PopStackCombine(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{

    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("RRC_FSM_BeginProcess, FsmId error, FsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PopStackCombine_ENUM
,LNAS_FUNCTION_LABEL1,
                                        enParalFsmId );

        return;
    }


    /***************��ջǰ������ӡ����***************/

    /* ��ӡ��ǰ״̬�漰����ȫ�ֱ�����ֵ */




    /***************��ջ����***************/

    /* ״̬����ջ���� */
    NAS_LMM_FSM_PopState(enParalFsmId);

    /* ��ʱ��״̬��ջ*/
    NAS_LMM_FSM_PopTimer(enParalFsmId);

    /* ���ȫ�ֱ�����ջ*/
    NAS_LMM_FSM_PopGlobPar();



    /***************��ջ�󻷾���ӡ����***************/
    NAS_LMM_PUBM_LOG_NORM("======================================================================================");
    NAS_LMM_PUBM_LOG_NORM("======NAS_EMM Pop State To:======");
    TLPS_PRINT2LAYER_ERROR(NAS_LMM_FSM_PopStackCombine_ENUM
,LNAS_FUNCTION_LABEL2);

    /* ��ӡ��ǰ״̬ */
    NAS_LMM_PrintFsmState(enParalFsmId);
    NAS_LMM_PUBM_LOG_NORM("======================================================================================");
    /* ��ӡ��ǰ״̬�漰���Ķ�ʱ��״̬ */
   /* NAS_LMM_PrintFsmTimer(enParalFsmId);
    */
    /* ��ӡ��ǰ״̬�漰����ȫ�ֱ�����ֵ */


    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PopState
 Discription    : ��CCB״̬ջ��ջ����״̬������ջ�����뵱ǰ״̬��������ģ�����
                  RRC_FSM_EndProcessʱ��MAINģ���Զ���ɣ��ýӿڲ������ṩ��
 Input          : ״̬��ջ��ַ
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_FSM_PopState( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId )
{

    NAS_LMM_FSM_STATE_STACK_STRU       *pstFsmStack;        /* ״̬��ջ��ַ */
    NAS_LMM_FSM_STATE_STRU             *pstCurFsm;          /* ״̬����ַ */
    NAS_LMM_FSM_STATE_STRU             *pstFsmStackTop;     /* ָ��ջ��״̬ */


    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PopState, FsmId error, FsmId", enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PopState_ENUM
,LNAS_FUNCTION_LABEL1,enParalFsmId);
        return;
    }

    /* ��ȡEMM״̬����ǰ״̬�ĵ�ַ��״̬��ջ�ĵ�ַ */
    pstCurFsm      = NAS_LMM_GetCurFsmAddr(enParalFsmId);
    pstFsmStack    = NAS_LMM_GetFsmStackAddr(enParalFsmId);


    /* ջԽ�� */
    if ( (pstFsmStack->ucStackDepth) > NAS_LMM_MAX_STACK_DEPTH )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PopState, The stack depth overflow, ucStackDepth",
                            (pstFsmStack->ucStackDepth));
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PopState_ENUM
,LNAS_FUNCTION_LABEL2,
                            (pstFsmStack->ucStackDepth));
        return;
    }

    /* ջ�ѿ� */
    if ( 0 == (pstFsmStack->ucStackDepth) )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_FSM_PopState, The stack is empty!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_FSM_PopState_ENUM
,LNAS_FUNCTION_LABEL3);
        return;
    }


    /* ��ȡջ����һ����Ч״̬��λ�ã���ջ������һ��λ�� */
    pstFsmStack->ucStackDepth--;

    /* ��ȡջ����һ����Ч״̬ */
    pstFsmStackTop  = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth]);

    /* ���õ�ǰ״̬�� */
    pstCurFsm->enFsmId     = pstFsmStackTop->enFsmId;
    pstCurFsm->enMainState = pstFsmStackTop->enMainState;
    pstCurFsm->enSubState  = pstFsmStackTop->enSubState;
    pstCurFsm->enStaTId    = pstFsmStackTop->enStaTId;

    return;
}


VOS_VOID    NAS_LMM_FSM_PopTimer(  NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_FSM_STATE_STRU               *pstCurFsm;          /* ״̬����ַ */


    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(    enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR(           "NAS_LMM_FSM_PushTimer, The input is illegal! enParalFsmId",
                                        enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PopTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                        enParalFsmId);

        return;
    }

    pstCurFsm                           = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);

    /* ������ǰ״̬���е�״̬������ʱ������
        g_stMmMainContext.stNasEmmFsm.astCurFsm.enStaTId*/
    NAS_LMM_StartStateTimer(             pstCurFsm->enStaTId);

    return;

}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PopGlobPar
 Discription    : ��ǰ״̬����ջ
 Input          : ״̬��ջ��ַ ��״̬
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_PopGlobPar(VOS_VOID)
{

    /*��ʱû����Ҫ��ջ�ı���*/

    return;
}
VOS_UINT32  NAS_LMM_FSM_GetStaAtStackBase(
                                        NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    NAS_LMM_FSM_STATE_STACK_STRU        *pstFsmStack = VOS_NULL_PTR;
    NAS_LMM_FSM_STATE_STRU              *pstFsmStackBase = VOS_NULL_PTR;

    /* ��ȡ״̬ջջ�׵�ַ */
    pstFsmStack  =  NAS_LMM_GetFsmStackAddr(enParalFsmId);
    pstFsmStackBase = &((pstFsmStack->astFsmStack)[NAS_LMM_STACK_BASE]);

    /* ��״̬ջ��ȡ״̬ */
    enMainState                         = pstFsmStackBase->enMainState;
    enSubState                          = pstFsmStackBase->enSubState;

    return NAS_LMM_PUB_COMP_EMMSTATE(enMainState, enSubState);
}


VOS_UINT32  NAS_LMM_FSM_GetStaAtStackTop(
                                        NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    NAS_LMM_FSM_STATE_STACK_STRU        *pstFsmStack = VOS_NULL_PTR;
    NAS_LMM_FSM_STATE_STRU              *pstFsmStackTop = VOS_NULL_PTR;

    /* ��ȡ״̬ջջ�׵�ַ */
    pstFsmStack  =  NAS_LMM_GetFsmStackAddr(enParalFsmId);
    pstFsmStackTop = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth-1]);

    /* ��״̬ջ��ȡ״̬ */
    enMainState                         = pstFsmStackTop->enMainState;
    enSubState                          = pstFsmStackTop->enSubState;

    return NAS_LMM_PUB_COMP_EMMSTATE(enMainState, enSubState);
}



VOS_VOID  NAS_LMM_PrintFsmTimer(NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId)
{
    NAS_LMM_FSM_STATE_STRU              *pstCurFsm;          /* ״̬����ַ */
    NAS_LMM_TIMER_CTRL_STRU             *pstTimerSta;        /* ״̬��ʱ�� */
    NAS_LMM_TIMER_CTRL_STRU             *pstTimerPtl;        /* Э�鶨ʱ�� */
    VOS_UINT16                          usPtlTid;


    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParallelFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PushTimer, The input is illegal! enParalFsmId",
                             enParallelFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                        enParallelFsmId);

        return;
    }

    pstCurFsm      = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pstTimerSta    = NAS_LMM_GetMmTimerStaCtrlAddrByIdx(pstCurFsm->enStaTId);

    /*�жϵ�ǰ״̬��ʱ��״̬Ϊֹͣ�͹���*/
    if(VOS_NULL_PTR == pstTimerSta->psthTimer)
    {
        /*״̬��ʱ�����ڹ���״̬*/
        if((NAS_LMM_TIMER_SS_SUSPENDING == pstTimerSta->ucTimerSs)
           && (NAS_LMM_TIMER_RS_RUNNING == pstTimerSta->ucTimerRs))
        {
            NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PrintFsmTimer: State Timer is suspended! enStaTId:",
                                  pstCurFsm->enStaTId);
            TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                                        pstCurFsm->enStaTId);
        }
        /*״̬��ʱ������ֹͣ״̬*/
        else
        {
            NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PrintFsmTimer: State Timer is stoped! enStaTId:",
                                  pstCurFsm->enStaTId);
            TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL3,
                                        pstCurFsm->enStaTId);
        }

    }
    /*״̬��ʱ����������״̬*/

    /*Э�鶨ʱ��*/
    for(usPtlTid = TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START+1; usPtlTid < NAS_LMM_PTL_TI_BUTT; usPtlTid++)
    {
        pstTimerPtl    = NAS_LMM_GetMmTimerPtlCtrlAddrByIdx(usPtlTid);

        /*Э�鶨ʱ����������״̬*/
        if(VOS_NULL_PTR != pstTimerPtl->psthTimer)
        {
            NAS_LMM_PUBM_LOG1_NORM("NAS_LMM_PrintFsmTimer: Ptl Timer is running! PtlTid:",
                                  usPtlTid);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL4,
                                       usPtlTid);
        }
        /*Э�鶨ʱ������ֹͣ״̬*/
        else
        {
            NAS_LMM_PUBM_LOG1_NORM("NAS_LMM_PrintFsmTimer: Ptl Timer is stoped! PtlTid:",
                                  usPtlTid);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL5,
                                       usPtlTid);
        }
    }

    return;
}
VOS_VOID  NAS_LMM_FSM_ClearStackCombine( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{

    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("RRC_FSM_BeginProcess, FsmId error, FsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_ClearStackCombine_ENUM
,LNAS_FUNCTION_LABEL1,
                                       enParalFsmId);

        return;
    }


    /***************��ջǰ������ӡ����***************/
    /* ��ӡ��ջǰ��״̬ */
    NAS_LMM_PrintFsmState(enParalFsmId);

    /* ��ӡ��ǰ״̬�漰���Ķ�ʱ��״̬ */
    NAS_LMM_PrintFsmTimer(enParalFsmId);

    /* ��ӡ��ǰ״̬�漰����ȫ�ֱ�����ֵ */




    /***************��ջ����***************/

    /* ״̬����ջ���� */
    NAS_LMM_FSM_ClearState(enParalFsmId);

    /* ��ʱ��״̬��ջ*/
    NAS_LMM_FSM_ClearTimer(enParalFsmId);

    /* ���ȫ�ֱ�����ջ*/
    NAS_LMM_FSM_ClearGlobPar();



    /***************��ջ�󻷾���ӡ����***************/
    /* ��ӡ��ǰ״̬ */
    NAS_LMM_PrintFsmState(enParalFsmId);

    /* ��ӡ��ǰ״̬�漰���Ķ�ʱ��״̬ */
    NAS_LMM_PrintFsmTimer(enParalFsmId);

    /* ��ӡ��ǰ״̬�漰����ȫ�ֱ�����ֵ */


    return;
}
VOS_VOID NAS_LMM_FSM_ClearState( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId )
{

    NAS_LMM_FSM_STATE_STACK_STRU       *pstFsmStack;        /* ״̬��ջ��ַ */


    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PopState, FsmId error, FsmId", enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_ClearState_ENUM
,LNAS_PARAM_INVALID,
                                       enParalFsmId);
        return;
    }

    /* ��ȡEMM״̬����ǰ״̬�ĵ�ַ��״̬��ջ�ĵ�ַ */
    pstFsmStack    = NAS_LMM_GetFsmStackAddr(enParalFsmId);


    /* ջԽ�� */
    if ( (pstFsmStack->ucStackDepth) > NAS_LMM_MAX_STACK_DEPTH )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PopState, The stack depth overflow, ucStackDepth",
                            (pstFsmStack->ucStackDepth));
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_ClearState_ENUM
,LNAS_FUNCTION_LABEL1,
                                       (pstFsmStack->ucStackDepth));
        return;
    }

    /* ջ�ѿ� */
    if ( 0 == (pstFsmStack->ucStackDepth) )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_FSM_PopState, The stack is empty!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_FSM_ClearState_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }

    /*���ջ�ڴ洢��״̬��*/
    pstFsmStack->ucStackDepth           = 0;

    NAS_LMM_MEM_SET(pstFsmStack,0,sizeof(NAS_LMM_FSM_STATE_STACK_STRU));

    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_ClearTimer
 Discription    : ջ��״̬��ջ����ջ��״̬��Ӧ�Ķ�ʱ����ѹջʱͬ����ջ�ˣ���
                  ��ʱ��Ҫͬ���ָ�������������ǣ�����ͣ�Ķ�ʱ������������
                    ������ִֻ����������:
                               �ָ����г�ջ���״̬��״̬������ʱ��;
                               �޸�g_stMmMainContext�ж�Ӧ��ʱ�������б�ʶ
 Input          : ����״̬��ID, UE1.0�й̶���NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_ClearTimer(  NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_FSM_STATE_STRU              *pstCurFsm;          /* ״̬����ַ */



    /* ��ڼ�� */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_ClearTimer, The input is illegal! enParalFsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_ClearTimer_ENUM
,LNAS_PARAM_INVALID,
                            enParalFsmId);

        return;
    }

    pstCurFsm      = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);

    /* ������ǰ״̬���е�״̬������ʱ������
        g_stMmMainContext.stNasEmmFsm.astCurFsm.enStaTId*/
    NAS_LMM_StopStateTimer(pstCurFsm->enStaTId);

    return;

}
/*lint +e961*/
/*lint +e960*/


VOS_VOID    NAS_LMM_FSM_ClearGlobPar(VOS_VOID)
{

    /*��ʱû����Ҫ��ջ�ı���*/

    return;
}


/*****************************************************************************
 Function Name  : ���MM���״̬����ջ
 Discription    : NAS_LMM_FSM_ClearStackResource
 Input          :
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_ClearStackResource(VOS_VOID)
{
    VOS_UINT32                          ulFsmId;
    NAS_LMM_FSM_STATE_STACK_STRU        *pEmmStack;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_FSM_ClearStackResource enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_FSM_ClearStackResource_ENUM
,LNAS_ENTRY);

    for(ulFsmId = NAS_LMM_PARALLEL_FSM_EMM;
        ulFsmId < NAS_LMM_PARALLEL_FSM_BUTT;
        ulFsmId++)
    {
        pEmmStack   = NAS_LMM_GetFsmStackAddr(ulFsmId);

        /* ջ��λ��ָʾ����ջ��ȣ���Ϊ0 */
        pEmmStack->ucStackDepth             = NAS_EMM_STACK_EMPTY;
    }

    return;
}


/*****************************************************************************
 Function Name  :
 Discription    :
 Input          :
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
*****************************************************************************/





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ��ϵͳ+ģ��+�ļ���.c */
