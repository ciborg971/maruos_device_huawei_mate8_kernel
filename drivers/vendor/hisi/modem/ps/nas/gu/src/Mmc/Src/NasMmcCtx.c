
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcCtx.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2011��04��22��
  ����޸�   :
  ��������   : NAS MMC CTX�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasCommDef.h"
#include "NasMmcSndOm.h"
#include "NasMmcFsmMainTbl.h"
#include "NasMmcCtx.h"
#include "NasMmcMain.h"
#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcFsmInterSysHoTbl.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"
/* Added by z00308719 for ROAM_PLMN_SELECTION_OPTIMIZE_2.0, 2015-5-23 Begin */
#include "NasMmcFsmGetGeoTbl.h"
/* Added by z00308719 for ROAM_PLMN_SELECTION_OPTIMIZE_2.0, 2015-5-23 End */
#include "NasMmcTimerMgmt.h"
#include "NasMmcFsmSyscfgTbl.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndLmm.h"
#include "NasMmcProcNvim.h"
#include "NasMmcComFunc.h"
#include "NasMmcFsmPowerOff.h"

#include "MsccMmcInterface.h"

/* Added by l00305157 for ROAM_PLMN_SELECTION_OPTIMIZE_2.0, 2015-5-26, begin */
#include "NasMmcFsmPlmnSelection.h"
/* Added by l00305157 for ROAM_PLMN_SELECTION_OPTIMIZE_2.0, 2015-5-26, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_CTX_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* MMC CTX,���ڱ���MMC״̬��,������ */
NAS_MMC_CONTEXT_STRU                    g_stNasMmcCtx;

/*lint -save -e958 */



VOS_UINT32 g_aulFsmEntryEventType[] =
{
    NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),

    NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_LIST_REQ),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ),

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_ANYCELL_SEARCH_REQ),

    NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_HPLMN_TIMER),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH),

    NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER),

    NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_GET_GEO_REQ),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND)
#endif
};



NAS_MMC_CONTEXT_STRU* NAS_MMC_GetMmcCtxAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx);
}


NAS_MMC_FSM_CTX_STRU* NAS_MMC_GetCurFsmAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm);
}


NAS_MMC_FSM_STACK_STRU* NAS_MMC_GetFsmStackAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stFsmStack);
}


NAS_FSM_DESC_STRU* NAS_MMC_GetCurFsmDesc(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.pstFsmDesc);
}


NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrFsmMsgAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm.stEntryMsg);
}


NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetCurrFsmId(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.enFsmId);
}


VOS_UINT32 NAS_MMC_GetCurrFsmEventType(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.stEntryMsg.ulEventType);
}


NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetParentFsmId(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.enParentFsmId);
}


VOS_UINT32 NAS_MMC_GetParentFsmEventType(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.ulParentEventType);
}


NAS_MMC_FSM_EXTRA_CTX_UNION* NAS_MMC_GetParentFsmCtx(VOS_VOID)
{
    return (g_stNasMmcCtx.stCurFsm.punParentFsmCtx);
}



NAS_MMC_MSG_QUEUE_STRU* NAS_MMC_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(g_stNasMmcCtx.stBufferEntryMsgQueue);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_PushFsm
 ��������  : ��״̬������ѹջ
 �������  : *pstFsmStack:״̬��ջ
             *pstNewFsm:��Ҫѹ���״̬��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��10��
   ��    ��   : zhoujun /40661
   �޸�����   :  �޸�ջ��ȵ�����

*****************************************************************************/
VOS_VOID NAS_MMC_FSM_PushFsm(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack,
    NAS_MMC_FSM_CTX_STRU                *pstNewFsm
)
{
    NAS_MMC_FSM_CTX_STRU                *pstCurFsm;

    if ( (VOS_NULL_PTR == pstFsmStack)
      || (VOS_NULL_PTR == pstNewFsm) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,
                       "NAS_MMC_FSM_PushFsm,Para null ptr,pstFsmStack,pstNewFsm");

        return;
    }

    if ( pstFsmStack->usStackDepth >= NAS_MMC_MAX_STACK_DEPTH )
    {
        NAS_ERROR_LOG1(WUEPS_PID_MMC,
                       "NAS_MMC_FSM_PushFsm,Fsm Stack Depth Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    pstCurFsm               = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* ����ǰ״̬������CTX����Ҫ�������� */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(NAS_MMC_FSM_CTX_STRU));

    pstFsmStack->usStackDepth++;


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_PopFsm
 ��������  : ��״̬�����г�ջ
 �������  : ��
             ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��10��
   ��    ��   : zhoujun /40661
   �޸�����   :  �޸�ջ��ȵ�����

*****************************************************************************/
VOS_VOID NAS_MMC_FSM_PopFsm( VOS_VOID )
{
    VOS_UINT16                          usPopFsmPos;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* ���ݲ���״̬��ջ������״̬����ȡ��ǰ״̬��������ַ  */
    pstFsmStack                     = NAS_MMC_GetFsmStackAddr();
    pstCurFsm                       = NAS_MMC_GetCurFsmAddr();

    /* ջ�ѿ� */
    if ( 0 == (pstFsmStack->usStackDepth) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_FSM_PopFsm,FSM Stack empty");

        return;
    }

    pstFsmStack->usStackDepth--;
    usPopFsmPos   = pstFsmStack->usStackDepth;

    /* ���õ�ǰ״̬�� */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[usPopFsmPos]),
              sizeof(NAS_MMC_FSM_CTX_STRU));

    return;
}
VOS_VOID NAS_MMC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����NAS_MMC�����Ϣ�Ļ�������ַ */
    pstEntryMsg                 =   NAS_MMC_GetCurrFsmMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;

    /* ����ǿ���Ϣ */
    if ( VOS_NULL_PTR == pstMsg )
    {
        pstEntryMsg->ulEventType    =   ulEventType;
        NAS_WARNING_LOG( WUEPS_PID_MMC, "NAS_MMC_SaveCurEntryMsg Entry Message Pointer is NULL!" );
        return;
    }

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;

}


VOS_VOID  NAS_MMC_LoadSubFsm(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm
)
{
    switch ( enFsmId )
    {
        case NAS_MMC_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = NAS_MMC_SWITCH_ON_STA_SWITCH_ON_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetSwitchOnFsmDescAddr();
            break;

        case NAS_MMC_FSM_POWER_OFF :
            pstCurFsm->ulState                  = NAS_MMC_POWER_OFF_STA_POWEROFF_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPowerOffFsmDescAddr();
            break;

        case NAS_MMC_FSM_PLMN_SELECTION :
            pstCurFsm->ulState                  = NAS_MMC_PLMN_SELECTION_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPlmnSelectionFsmDescAddr();
            break;

        case NAS_MMC_FSM_ANYCELL_SEARCH :
            pstCurFsm->ulState                  = NAS_MMC_ANYCELL_SEARCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetAnyCellSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_SYSCFG :
            pstCurFsm->ulState                  = NAS_MMC_SYSCFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetSysCfgFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CELLRESEL :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysCellReselFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_HO :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_HO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysHoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_CCO :
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_CCO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysCcoFsmDescAddr();
            break;

        case NAS_MMC_FSM_INTER_SYS_OOS:
            pstCurFsm->ulState                  = NAS_MMC_INTER_SYS_OOS_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetInterSysOosFsmDescAddr();
            break;



        case NAS_MMC_FSM_PLMN_LIST:
            pstCurFsm->ulState                  = NAS_MMC_PLMN_LIST_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetPlmnListFsmDescAddr();
            break;



        case NAS_MMC_FSM_BG_PLMN_SEARCH:
            pstCurFsm->ulState                  = NAS_MMC_BG_PLMN_SEARCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetBgPlmnSearchFsmDescAddr();
            break;

        case NAS_MMC_FSM_GET_GEO:
            pstCurFsm->ulState                  = NAS_MMC_GET_GEO_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MMC_GetGeoFsmDescAddr();
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadSubFsm:Invalid Fsm Id");
            break;
    }


    /*ִ�г�ʼ��L2״̬���ĺ���*/
    pstCurFsm->pstFsmDesc->pfInitHandle();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_InitFsmL2
 ��������  : MMC����һ��L2��L3��״̬�����������̵�ͬʱ����״̬�Լ�������ʱ��?
              �ú��������ѹջ����,�������Ҫ����Э��ջѹջ,���뱣֤�˳�ǰ����
 �������  : enFsmId:L2״̬��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��9��
   ��    ��   : huwen /44270
   �޸�����   : ���ӵ�ǰ״̬������һ��״̬���������Ϣ
*****************************************************************************/
VOS_VOID NAS_MMC_FSM_InitFsmL2(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enParentFsmId;
    VOS_UINT32                          ulParentEventType;

    VOS_UINT16                          usStackDepth;                           /* ��ǰѹջ��״̬���� */

    enParentFsmId                       = NAS_FSM_BUTT;

    pstCurFsm                           = NAS_MMC_GetCurFsmAddr();
    pstFsmStack                         = NAS_MMC_GetFsmStackAddr();

    /*  ��ӡѹջǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();


    /* ��¼ѹջǰ��״̬�����������Ϣ���� */
    enParentFsmId                       = pstCurFsm->enFsmId;
    ulParentEventType                   = pstCurFsm->stEntryMsg.ulEventType;

    /* ����ǰ״̬��ѹջ���� */
    NAS_MMC_FSM_PushFsm(pstFsmStack, pstCurFsm);

    /* ���õ�ǰ״̬�� */
    pstCurFsm->enFsmId                  = enFsmId;

    /* ����L2״̬�� */
    NAS_MMC_LoadSubFsm(enFsmId, pstCurFsm);

    /* ��¼�ϲ�״̬�����������Ϣ���� */
    pstCurFsm->enParentFsmId            = enParentFsmId;
    pstCurFsm->ulParentEventType        = ulParentEventType;

    usStackDepth = pstFsmStack->usStackDepth;

    pstCurFsm->punParentFsmCtx = VOS_NULL_PTR;

    /* ����״̬��ջ����쳣���� */
    if ( (0            < usStackDepth)
      && (usStackDepth <= NAS_MMC_MAX_STACK_DEPTH) )
    {
        /* ��¼�ϲ�״̬�����������ݵ�ַ */
        pstCurFsm->punParentFsmCtx          = &(pstFsmStack->astFsmStack[(usStackDepth - 1)].unFsmCtx);
    }


    /*  ��ӡ��ǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_QuitFsmL2
 ��������  : ����L2״̬��������������̣�״̬������״̬ջ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_FSM_QuitFsmL2( VOS_VOID )
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm                           = NAS_MMC_GetCurFsmAddr();

    /* QUITʱ��յ�ǰL2״̬����CTX */
    pstCurFsm->pstFsmDesc->pfInitHandle();

    /*  ��ӡѹջǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();

    /* ״̬����ջ���� */
    NAS_MMC_FSM_PopFsm();

    /*  ��ӡ��ǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_FSM_SetCurrState
 ��������  : ���õ�ǰ��ҪǨ�Ƶ�״̬
 �������  : ulCurrState:��ǰǨ�Ƶ�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm                   = NAS_MMC_GetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->ulState          = ulCurrState;

    /*  ��ӡ��ǰ��L1��L2״̬ */
    NAS_MMC_LogMmcFsmInfo();

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_FSM_GetFsmTopState
 ��������  : ��ȡ״̬�������״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬���Ķ���״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��19��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetFsmTopState( VOS_VOID )
{
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    VOS_UINT32                          ulState;

    /* ��ȡ��ǰ״̬�� */
    pstCurFsm               = NAS_MMC_GetCurFsmAddr();
    ulState                 = pstCurFsm->ulState;

    return ulState;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFsmStackDepth
 ��������  : ��ȡ��ǰЭ��ջ��ջ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��22��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��10��
   ��    ��   : zhoujun /40661
   �޸�����   :  �޸�ջ��ȵ�����
*****************************************************************************/
VOS_UINT16  NAS_MMC_GetFsmStackDepth( VOS_VOID )
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetTimerAddr
 ��������  : ��ȡMMC CTXģ���ж�ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��25��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_TIMER_CTX_STRU*  NAS_MMC_GetTimerAddr( VOS_VOID )
{
    return g_stNasMmcCtx.astMmcTimerCtx;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveCacheMsgInMsgQueue
 ��������  : ��������Ϣ����Ļ����ڴ����
 �������  : ulEventType:��ϢID+PID
             pMsg      :��Ϣ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��6��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = NAS_MMC_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= NAS_MMC_MAX_MSG_QUEUE_NUM )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsgInMsgQueue:No Empty buffer");

        NAS_MMC_LogBufferQueueMsg(VOS_TRUE);

        return ;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsgInMsgQueue:Cache Num", pstMsgQueue->ucCacheMsgNum);

    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveCacheMsg
 ��������  : ���浱ǰ��Ҫ����Ļ���
 �������  : ulEventType:��ϢID+PID
             pMsg      :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����ɹ�
             VOS_FALSE:����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if ( pstMsgHeader->ulLength >= ( NAS_MMC_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsg:Len too Long");
        return;
    }

    /* �Ƚ���Ϣ���ȼ�,�ж��Ƿ���Ҫ�����ڻ������ */
    if ( VOS_FALSE == NAS_MMC_IsNeedCacheMsg(ulEventType, pstMsg))
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveCacheMsg:already exist msg");
        return;
    }

    /* ����Ϣ�����ڻ����ڴ���� */
    NAS_MMC_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextInterSysCachedMsg
 ��������  : ��ȡ��ǰ���ڵ���ϵͳ��ѡ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��7��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextInterSysCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          ulCacheFlg;

    ulCacheFlg  = VOS_FALSE;

    switch ( pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND):
        case NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND):
            ulCacheFlg = VOS_TRUE;

            break;

        default:
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextInterSysCachedMsg:No Empty suspend buffer");
            break;
    }

    return ulCacheFlg;
}




VOS_UINT32  NAS_MMC_GetNextUserCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          ulCacheFlg;

    ulCacheFlg  = VOS_FALSE;

    switch ( pstEntryMsg->ulEventType)
    {
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ)  :
            ulCacheFlg = VOS_TRUE;

            break;

        default:
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextUserCachedMsg:No Empty buffer");
            break;
    }

    return ulCacheFlg;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextHighPrioCachedMsg
 ��������  : ɨ������ȼ��Ļ����Ƿ����
 �������  : ��
 �������  : pstEntryMsg:�����ȼ��Ļ���
 �� �� ֵ  : VOS_TRUE:�����ȼ��Ļ������
             VOS_FALSE:�����ȼ��Ļ��治����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��6��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��9��29��
    ��    ��   : zhoujun 40661
    �޸�����   : ���¸������ȼ���ȡ������Ϣ

  3.��    ��   : 2011��11��7��
    ��    ��   : zhoujun 40661
    �޸�����   : RRMM_SUSPEND_IND��Ϣ�����ȼ��Ƚϸ�,��Ҫ���Ȼ�ȡ����Ϣ��

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextHighPrioCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    VOS_UINT32                          i;
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          ulCacheFlg  ;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
    ulCacheFlg                          = VOS_FALSE;


    /* �����Ȼ�ȡ���е�״̬���ķ������Ϣ */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        /* ���Ȼ�ȡ״̬���������Ϣ */
        if ( VOS_FALSE == NAS_MMC_IsFsmEntryEventType(pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType) )
        {
            PS_MEM_CPY(pstEntryMsg,
                       &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       sizeof(NAS_MMC_ENTRY_MSG_STRU));

            ulCacheFlg = VOS_TRUE;

        }

        /* �ҵ������ȼ�����Ϣ����ɸ����ȼ���Ϣ�Ŀ�������� */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }

    /* ��Ϊintersys��Ϣ�����ȼ����û�������Ϣ�����ȼ���,Ŀǰ����BG��������
       ��,�յ�rrmm_suspend_ind��Ϣ����ϵ�ǰ״̬������intersys��Ϣ*/
    /* �����Ȼ�ȡ���е�intersys��Ϣ */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        if ( VOS_TRUE == NAS_MMC_GetNextInterSysCachedMsg(&(pstMsgQueue->astMsgQueue[i].stMsgEntry)) )
        {
            PS_MEM_CPY(pstEntryMsg,
                   &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));

            ulCacheFlg = VOS_TRUE;
        }

        /* �ҵ������ȼ�����Ϣ����ɸ����ȼ���Ϣ�Ŀ�������� */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }

    /* �����Ȼ�ȡ���еĸ����ȼ���Ϣ */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum; i++ )
    {
        /* �û��Ļ�����Ϣ���ȼ��θ� */
        ulCacheFlg = NAS_MMC_GetNextUserCachedMsg(&(pstMsgQueue->astMsgQueue[i].stMsgEntry));
        if ( VOS_TRUE == ulCacheFlg )
        {
            PS_MEM_CPY(pstEntryMsg,
                   &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));
        }


        /* �ҵ������ȼ�����Ϣ����ɸ����ȼ���Ϣ�Ŀ�������� */
        if ( VOS_TRUE == ulCacheFlg )
        {
            NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);
            return VOS_TRUE;
        }
    }



    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextNormalPrioCachedMsg
 ��������  : ��ȡ��ͨ�Ļ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��9��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextNormalPrioCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* ���������ȳ�ԭ��,Ĭ��ȡ��1���������� */
    PS_MEM_CPY(pstEntryMsg,
               &(pstMsgQueue->astMsgQueue[0].stMsgEntry),
               sizeof(NAS_MMC_ENTRY_MSG_STRU));

    /* ��Ϣ�Ѿ�ȡ���������ǰ���� */
    NAS_MMC_ClearCacheMsg(pstEntryMsg->ulEventType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextCachedMsg
 ��������  : ��ȡ��ǰ��Ҫ����Ļ���
 �������  : ��
 �������  : pstEntryMSg:��ǰ���ȼ���ߵĻ�����Ϣ
 �� �� ֵ  : VOS_OK:��ȡ�ɹ�
             VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��9��
   ��    ��   : zhoujun /40661
   �޸�����   : ���Ȼ�ȡ�����ȼ��Ļ�����Ϣ
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetNextCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }


    /* ������ڸ����ȼ�����Ϣ,�ȷ��ظ����ȼ�����Ϣ, ���ȼ��ߵ���Ϣ���ȵõ����� */
    if ( VOS_TRUE == NAS_MMC_GetNextHighPrioCachedMsg(pstEntryMsg) )
    {
        return VOS_TRUE;
    }

    /* ��ȡ��ͨ�Ļ�����Ϣ�ɹ�,������ͨ�Ļ�����Ϣ */
    if ( VOS_TRUE == NAS_MMC_GetNextNormalPrioCachedMsg(pstEntryMsg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsExistCacheMsg
 ��������  : �жϵ�ǰ��Ϣ�Ƿ��Ѿ�����
 �������  : ulEventType:��ϢID
 �������  : pulIndex   :�������Ϣ����
 �� �� ֵ  : VOS_TRUE:���ڻ������Ϣ
             VOS_FALSE:�����ڻ������Ϣ
 ���ú���  :pulIndex
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��25��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsExistCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_UINT32                         *pulIndex
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
   *pulIndex                           = 0;

    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            *pulIndex   = i;
            return VOS_TRUE;
        }

    }


    NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_IsExistCacheMsg:not match MSG");

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearCacheMsg
 ��������  : ���ָ���Ļ�����Ϣ
 �������  : ulEventType:������󻺴����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��8��06��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* ���ҵ���Ҫ������Ļ��� */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(NAS_MMC_ENTRY_MSG_STRU));
            cCachePos = (VOS_INT8)i;
        }
    }

    /* δ�ҵ�����Ϣ����ֱ�ӷ��� */
    if ( -1 == cCachePos )
    {
        NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_ClearCacheMsg:invalid msg type", ulEventType);
        return;
    }

    /* Ϊ��֤�����ȳ�,��Ҫ���������Ϣ�Ƶ�ǰ�� */
    for ( i = cCachePos ; i < (pstMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY��Ϣ���� */
        PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));

    }

    /* �����������һ */
    pstMsgQueue->ucCacheMsgNum--;

    /* ����ǰ�������ӡ���� */
    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearAllCacheMsg
 ��������  : ������еĻ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��25��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ClearAllCacheMsg( VOS_VOID )
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    pstMsgQueue->ucCacheMsgNum          = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_MSG_QUEUE_NUM ; i++ )
    {
        PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   0x00,
                   sizeof(NAS_MMC_ENTRY_MSG_STRU));
    }

    NAS_MMC_LogBufferQueueMsg(VOS_FALSE);
    return;
}



VOS_VOID  NAS_MMC_InitFsmCtx_L1Main(VOS_VOID)
{
    NAS_MMC_ClearAllRegAdditionalAction_L1Main();

    NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main();
    NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn();
    NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn();

    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    NAS_MMC_ClearAllRegAttemptCount_L1Main();

    /* Ĭ��AVAILABLE COUNTERΪNORMAL���� */
    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);
}
VOS_VOID  NAS_MMC_InitFsmCtx_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio;

    VOS_UINT8                                              *pucLastImsi = VOS_NULL_PTR;

    VOS_UINT32                                              i;

    /* ��ȡ״̬���е�Ҫ����SYSCFG����ģ����Ӧ���������б��ַ */
    pstSwitchOnRecord                   = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    pucSwitchOnRatPrio                  = pstSwitchOnRecord->aucSwitchOnRatPrio;

    pucLastImsi = NAS_MMC_GetLastImsi_SwitchOn();

    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn();
    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn();

    /* Switch On״̬�������������ý���㿪�����ȼ�˳����Ϣ�ĳ�ʼ��:
       ����������ʼ��Ϊ0,ÿ�����㷢�Ϳ����󣬸���������1����ʾҪ��������ģ�Ľ���ģʽ */
    pstSwitchOnRecord->ucSwitchOnIndex = 0;

    /* ������Ҫ�·��������뼼�����ܸ��� */
    pstSwitchOnRecord->ucTotalSwitchOnRatNum = 0;

    /* SYSCFG״̬�������������ý�������ȼ�˳����Ϣ�ĳ�ʼ��:
       ����ģʽȫ����ʼ��ΪNAS_MML_NET_RAT_TYPE_BUTT */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pucSwitchOnRatPrio[i]           = NAS_MML_NET_RAT_TYPE_BUTT;
    }


    /* ��ʼ��״̬���������еĿ���Ǯ��IMSI��Ϣ */
    for ( i = 0 ; i < NAS_MML_MAX_IMSI_LEN ; i++ )
    {
        pucLastImsi[i] = NAS_MML_IMSI_INVALID;
    }
}
NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU* NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;
    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSwitchOnSettingRecord_SwitchOn,ERROR:FsmId Error");
    }

    return &(pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.stSwitchOnRecord);
}
VOS_VOID NAS_MMC_AddSwitchOnIndex_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;

    /* �����ǰ״̬������NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSwitchOnIndex_SwitchOn,ERROR:FsmId Error");
    }

    /* ��ȡ״̬���е�Ҫ����SwitchOn����ģ����Ӧ���������б��ַ */
    pstSwitchOnRecord   = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* ����INDEX����,ָ����һ��Ҫ����SwitchOn���õĽ��뼼�� */
    pstSwitchOnRecord->ucSwitchOnIndex ++;

    /* ���� */
    return ;
}




NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSendingRat_SwitchOn(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio;
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnRecord;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         ucNextSwitchOnRat;

    /* �����ǰ״̬������NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSendingRat_SwitchOn,ERROR:FsmId Error");
    }

    pstSwitchOnRecord      = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* ��ȡ״̬���е�Ҫ����SwitchOn����ģ����Ӧ���������б��ַ */
    pucSwitchOnRatPrio     = pstSwitchOnRecord->aucSwitchOnRatPrio;

    /* ��������Ե������õ��ܸ��������ؽ��뼼��Ϊ��Чֵ����ʾSwitchOn���ý��� */
    if ( pstSwitchOnRecord->ucSwitchOnIndex >= pstSwitchOnRecord->ucTotalSwitchOnRatNum )
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* ȡ����������������Ӧ�Ľ��뼼�� */
    ucNextSwitchOnRat                     = pucSwitchOnRatPrio[pstSwitchOnRecord->ucSwitchOnIndex];

    /* ������ҪSwitchOn���õĽ��뼼�� */
    return ucNextSwitchOnRat;
}
VOS_VOID NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn(VOS_VOID)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnSettingRecord = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *pucSwitchOnRatPrio       = VOS_NULL_PTR;
    VOS_UINT8                                               ucRatIndex;

    /* �����ǰ״̬������NAS_MMC_FSM_SwitchOn */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSwitchOnSendingOrder_SwitchOn,ERROR:FsmId Error");
    }

    ucRatIndex                          = 0;

    /* ȡ�õ�ǰ SwitchOn״̬���������еļ�¼���ý�������ȼ�˳����Ϣ */
    pstSwitchOnSettingRecord            = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    pucSwitchOnRatPrio                  = pstSwitchOnSettingRecord->aucSwitchOnRatPrio;

    /* �����·�SwitchOn�����˳��ΪGLW,��LTE��֧�֣���ΪGW */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_GSM;
        ucRatIndex++;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_LTE;
        ucRatIndex++;
    }
#endif

    /* ���ƽ̨֧��W��TD����Ҫ��Uģ���������� */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pucSwitchOnRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_WCDMA;
        ucRatIndex++;
    }

    /* ������Ҫ�·������������ܸ��� */
    pstSwitchOnSettingRecord->ucTotalSwitchOnRatNum = ucRatIndex;

    return;
}
VOS_UINT8* NAS_MMC_GetLastImsi_SwitchOn(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SWITCH_ON */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastImsi_SwitchOn,ERROR:FsmId Error");
    }

    /* ���ش洢����ǰNV�б����IMSI�����ݵ��׵�ַ */
    return pstNasMmcCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.aucLastImsi;
}




VOS_VOID  NAS_MMC_InitFsmCtx_PowerOff(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff();
    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

    NAS_MMC_SetMasterModeRat_PowerOff( NAS_MML_NET_RAT_TYPE_BUTT );

    /* ��ʼ���ػ�ʱ�Ĵ�ģ�б� */
    pstSlaveModeRatList           = NAS_MMC_GetSlaveModeRatList_PowerOff();
    pstSlaveModeRatList->ucRatNum = 0;
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstSlaveModeRatList->aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;
    }
}


VOS_VOID  NAS_MMC_InitFsmCtx_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_RAT_STRU                              stInvalidPlmnId;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
#endif

    /* ����Abort��־ΪVOS_FALSE */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_FALSE);

    /* ����Rel Request��־ΪVOS_FALSE */
    NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

    NAS_MMC_SetInterSysSuspendRat_PlmnSelection(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ���õȴ�ע���־ΪNULL */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    /* ����CSע���������ĺ�������ΪBUTT */
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* ����PSע���������ĺ�������ΪBUTT */
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* ��ʼ��CS��PS causeֵΪBUTT */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    /* ��ʼ�������б� */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    PS_MEM_SET(pstPlmnSelectionListInfo, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* ��ʼ������״̬���������в�ͬ���뼼���ĸ��Ǽ�������Ϣ */
    NAS_MMC_InitSearchRatInfo_PlmnSelection();

    pstForbRoamLaInfo = NAS_MMC_GetForbRoamLaInfo_PlmnSelection();
    PS_MEM_SET(pstForbRoamLaInfo, 0X0, sizeof(NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU));

    PS_MEM_SET(NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(),
               0X0, sizeof(NAS_MML_PLMN_ID_STRU));

#if (FEATURE_ON == FEATURE_LTE)
    stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(&stPlmnId);
#endif

    PS_MEM_SET(&stInvalidPlmnId, 0x0, sizeof(stInvalidPlmnId));
    stInvalidPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stInvalidPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stInvalidPlmnId.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;

    NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(&stInvalidPlmnId);

    NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_BUTT);

    NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_FALSE);

    NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(MMC_LMM_CL_REG_STATUS_BUTT);

    return;
}
VOS_VOID  NAS_MMC_InitFsmCtx_AnyCellSearch(VOS_VOID)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList      = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucRatNum;

    pstAnyCellSearchCtx = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();

    /* ��ȡMS��ǰ֧�ֵĽ��뼼�� */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    /* ��ʼ��ANYCELL״̬���Ľ��뼼��Ϊ��ǰMS֧�ֵĽ��뼼�� */
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio = (*pstRatPrioList);

    ucRatNum = NAS_MMC_GetRatNum_AnyCellSearch();

    /* ��ʼ�����뼼��Ϊδ������ */
    for (i = 0; i < ucRatNum; i++)
    {
        pstAnyCellSearchCtx->aucSearchedFlag[i] = VOS_FALSE;
    }

    /* ����Abort��־ΪVOS_FALSE */
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_FALSE);

}


VOS_VOID  NAS_MMC_InitFsmCtx_BgPlmnSearch()
{
    NAS_MML_PLMN_ID_STRU                stInvalidPlmnId;
    NAS_MML_EQUPLMN_INFO_STRU           stEquPlmnInfo;

    stInvalidPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stInvalidPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    PS_MEM_SET(&stEquPlmnInfo, 0x00, sizeof(stEquPlmnInfo));


    /* ��¼״̬����������Abort�¼�����0xFFFFFFFF */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(NAS_MML_INVALID_EVENT_TYPE);

    /* ��ʼ��ABORT��־Ϊ�޴�� */
    NAS_MMC_SetAbortType_BgPlmnSearch(NAS_MMC_ABORT_BUTT);

    NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(VOS_FALSE);

#if (FEATURE_OFF == FEATURE_LTE)
    /* ��ʼ�������ֶ� */
    PS_MEM_SET(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.aucReserve,
               0X00,
               sizeof(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.aucReserve));
#endif

    /* ��ʼ��RegInfo��Ϣ */
    NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* ��ʼ����ǰ���ڳ��Եĸ����ȼ����缰����뼼����Ϣ */
    NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&stInvalidPlmnId, NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ʼ��VPlmn��Ϣ */
    NAS_MMC_SetPreCampPlmn_BgPlmnSearch(&stInvalidPlmnId, NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ʼ��EPlmn��Ϣ */
    NAS_MML_InitEquPlmnInfo(&stEquPlmnInfo);
    NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(&stInvalidPlmnId, &stEquPlmnInfo);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(VOS_FALSE);
    NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_FALSE);
#endif
}



VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCellResel(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel();
    NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel();
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_FALSE);
    NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(VOS_FALSE);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_BUTT);
}

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysHo(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysHo();
    NAS_MMC_ClearAllResumeRspFlag_InterSysHo();

    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);
}




VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCco(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysCco();
    NAS_MMC_ClearAllResumeRspFlag_InterSysCco();
}




VOS_VOID  NAS_MMC_InitFsmCtx_InterSysOos(VOS_VOID)
{
    NAS_MMC_ClearAllSuspendRspFlag_InterSysOos();
    NAS_MMC_ClearAllResumeRspFlag_InterSysOos();
}



VOS_VOID  NAS_MMC_InitFsmCtx_PlmnList(VOS_VOID)
{
    /* ��ʼ�������Ľ��뼼����Ϣ*/
    NAS_MMC_InitSearchRatInfo_PlmnList();

    /* ����״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_FALSE);

    /* ����֪ͨMSCC���Ϊ�� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_FALSE);

    /* ��ʼ�����ѵ��ĸ���������Ϣ */
    NAS_MMC_InitSearchedPlmnListInfo_PlmnList();

    /* ����ȴ�������ı����Ϣ */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* ���CS/PS��additionֵ */
    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

#if (FEATURE_ON == FEATURE_LTE)
    /* ���浱ǰL disable״̬��״̬�������� */
    NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
#endif

    /* ����anycell������� */
    NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_FALSE);

}



VOS_VOID  NAS_MMC_InitFsmCtx_GetGeo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_FSM_GET_GEO_CTX_STRU       *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx    = NAS_MMC_GetFsmCtxAddr_GetGeo();

    /* ״̬�������������ʼ�� */
    PS_MEM_SET(pstGetGeoCtx, 0, sizeof(NAS_MMC_FSM_GET_GEO_CTX_STRU));

    /* ����״̬��ABORT��ʶΪ��Ч */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_FALSE);

    /* ����֪ͨMSCC�ظ����Ϊ��Ч */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_FALSE);

    /* ����״̬������׶�ΪBUTT */
    NAS_MMC_SetFsmTaskPhase_GetGeo(NAS_MMC_GET_GEO_FSM_TASK_PHASE_BUTT);

    /* ��ʼ��GET GEO���뼼�����ȼ��б� */
    pstGetGeoCtx->stGetGeoRatInfoList.ucRatNum = 0;
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].enRatType      = NAS_MML_NET_RAT_TYPE_BUTT;
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].enCoverageType = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstGetGeoCtx->stGetGeoRatInfoList.astGetGeoRatInfo[i].ucIsSrchedFlag = VOS_FALSE;
    }

    return;
}




VOS_VOID  NAS_MMC_InitPlmnSearchCtrlCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU   *pstPlmnSearchCtrl
)
{
    pstPlmnSearchCtrl->ucWrrLimitServiceInd             = VOS_FALSE;
    pstPlmnSearchCtrl->stUserSpecPlmnId.enRat           = NAS_MML_NET_RAT_TYPE_BUTT;

    if ( NAS_MMC_INIT_CTX_STARTUP  == enInitType )
    {
        pstPlmnSearchCtrl->enSelectionMode                  = NAS_MMC_PLMN_SELECTION_MODE_AUTO;
        pstPlmnSearchCtrl->stUserSpecPlmnId.stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
        pstPlmnSearchCtrl->stUserSpecPlmnId.stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;

        pstPlmnSearchCtrl->ucUserSpecPlmnRegStatus          = VOS_TRUE;
    }

    pstPlmnSearchCtrl->stUserReselPlmnId.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;
    pstPlmnSearchCtrl->stUserReselPlmnId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stUserReselPlmnId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    pstPlmnSearchCtrl->stBufferedPlmnSearchInfo.ulPlmnSearchFlg   = VOS_FALSE;
    pstPlmnSearchCtrl->stBufferedPlmnSearchInfo.enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    pstPlmnSearchCtrl->enAsCellCampOn                   = NAS_MMC_AS_CELL_NOT_CAMP_ON;
    pstPlmnSearchCtrl->enSpecPlmnSearchState            = NAS_MMC_SPEC_PLMN_SEARCH_STOP;

    NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_FALSE);
    pstPlmnSearchCtrl->stOtherModemPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnSearchCtrl->stOtherModemPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    /* Ĭ�ϲ�֧��ncell���� */
    NAS_MMC_SetNcellSearchFirstTimerLen(0);
    NAS_MMC_SetNcellSearchSecondTimerLen(0);


    NAS_MMC_SetNcellSearchFlag(VOS_FALSE);
    NAS_MML_InitEquPlmnInfo(&pstPlmnSearchCtrl->stNcellSearchInfo.stOtherModemEplmnInfo);
    PS_MEM_SET(&pstPlmnSearchCtrl->stNcellSearchInfo.stTdsNcellInfo, 0,
               sizeof(pstPlmnSearchCtrl->stNcellSearchInfo.stTdsNcellInfo));
    PS_MEM_SET(&pstPlmnSearchCtrl->stNcellSearchInfo.stLteNcellInfo, 0,
               sizeof(pstPlmnSearchCtrl->stNcellSearchInfo.stLteNcellInfo));


    NAS_MMC_SetRegCtrl(NAS_MMC_REG_CONTROL_BY_3GPP_MMC);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    NAS_MMC_InitUserDPlmnNPlmnInfo(&pstPlmnSearchCtrl->stDplmnNplmnInfo);

    NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
    NAS_MMC_ClearDisabledLtePlmnId();

    NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(VOS_FALSE);
    NAS_MMC_InitGetGeoInfo(&pstPlmnSearchCtrl->stGetGeoInfo);
    NAS_MMC_InitHistorySearchInfo(&pstPlmnSearchCtrl->stHistorySearchInfo);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitServiceInfo
 ��������  : ��ʼ��MMC�ķ���״̬��Ϣ
 �������  : ��
 �������  : pstServiceInfo:�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��13��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_InitServiceInfo(
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo
)
{
    pstServiceInfo->enCsCurrService = NAS_MMC_NO_SERVICE;
    pstServiceInfo->enPsCurrService = NAS_MMC_NO_SERVICE;
}


VOS_VOID  NAS_MMC_InitMaintainCtx(
    NAS_MMC_MAINTAIN_CTX_STRU           *pstMaintainInfo
)
{
    pstMaintainInfo->ucGcfCh9_4_3_AND_Ch26_7_4_3    = VOS_FALSE;

    pstMaintainInfo->ucActionType                   = NAS_MMC_AT_ACTION_TYPE_START_FOREVER;
    pstMaintainInfo->ucMsgType                      = NAS_MMC_AT_MSG_TYPE_CELL_SIGN;
    pstMaintainInfo->ucMsgType                     |= NAS_MMC_AT_MSG_TYPE_CELL_ID;
    pstMaintainInfo->ucMsgType                     |= NAS_MMC_AT_MSG_TYPE_CELL_BLER;


    pstMaintainInfo->ucSignThreshold       = 0;   /* Ĭ�Ͻ����ȡȱʡֵ*/

    pstMaintainInfo->ucMinRptTimerInterval = 0; /*Ĭ�ϼ��ʱ��*/
}



VOS_VOID  NAS_MMC_InitPlmnRegRejCtx(
    NAS_MMC_PLMN_REG_REJ_CTX_STRU          *pstPlmnRegRejInfo
)
{
    VOS_UINT32                          i;

    pstPlmnRegRejInfo->ucPlmnRegInfoNum     = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_REG_PLMN_INFO_NUM ; i++ )
    {
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enGPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enWCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
#if (FEATURE_ON == FEATURE_LTE)
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLCsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
        pstPlmnRegRejInfo->astPlmnRegInfoList[i].enLPsRegStatus = NAS_MML_REG_FAIL_CAUSE_NULL;
#endif

    }
}



VOS_VOID  NAS_MMC_InitCurrFsmCtx(
    NAS_MMC_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   NAS_MMC_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   NAS_MMC_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   NAS_MMC_L1_STA_NULL;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;
    pstCurrFsmCtx->enParentFsmId            =   NAS_FSM_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;


    /* Ĭ��AVAILABLE COUNTERΪNORMAL���� */
    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);

    NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main();
    NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn();
    NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn();

    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               NAS_MMC_MAX_MSG_BUFFER_LEN);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitFsmStackCtx
 ��������  : ��ʼ��״̬��ջ������
 �������  : ��
 �������  : pstFsmStack:״̬��ջ��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��30��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��9��
   ��    ��   : zhoujun /40661
   �޸�����   : ����ջpop��־��ʼ��
*****************************************************************************/
VOS_VOID  NAS_MMC_InitFsmStackCtx(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < NAS_MMC_MAX_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = NAS_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = NAS_MMC_L1_STA_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitInternalBuffer
 ��������  : ����ڲ�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��15��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_InitInternalBuffer(
    NAS_MMC_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
)
{
    pstBufferEntryMsgQueue->ucCacheMsgNum   = 0;
    pstBufferEntryMsgQueue->ucCurrIndex     = 0;
    PS_MEM_SET(pstBufferEntryMsgQueue->astMsgQueue,
               0x00,
               sizeof(pstBufferEntryMsgQueue->astMsgQueue));
}


VOS_VOID NAS_MMC_InitNetScanReqCtx(
    NAS_MMC_NET_SCAN_REQ_CTX_STRU      *pstNetScanReqCtx
)
{
    PS_MEM_SET( &(pstNetScanReqCtx->stNetScanReq), 0X00, sizeof(MSCC_MMC_NET_SCAN_REQ_STRU) );

    pstNetScanReqCtx->stNetScanReq.ucRat = NAS_MML_NET_RAT_TYPE_BUTT;

    return;
}



NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrEntryMsg(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.stEntryMsg);
}



NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU *NAS_MMC_GetPlmnSearchCtrl(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl);
}


NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionMode(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSelectionMode);
}


VOS_UINT8 NAS_MMC_GetUtranSkipWPlmnSearchFlag(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag);
}


NAS_MML_PLMN_ID_STRU* NAS_MMC_GetOtherModemPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOtherModemPlmnId);
}


VOS_VOID NAS_MMC_SetOtherModemPlmnId(NAS_MML_PLMN_ID_STRU *pstPlmnId)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stOtherModemPlmnId = *pstPlmnId;

}



VOS_VOID NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8 ucUtranSkipWPlmnSearchFlag)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag = ucUtranSkipWPlmnSearchFlag;
}



NAS_MMC_NCELL_SEARCH_INFO_STRU* NAS_MMC_GetNcellSearchInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stNcellSearchInfo);
}



VOS_UINT8 NAS_MMC_GetNcellSearchFlag(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFlag);
}


VOS_VOID NAS_MMC_SetNcellSearchFlag(VOS_UINT8 ucNcellSearchFlag)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFlag = ucNcellSearchFlag;
}


VOS_UINT8 NAS_MMC_GetNcellSearchFirstTimerLen(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFirstTimerLen);
}


VOS_VOID NAS_MMC_SetNcellSearchFirstTimerLen(VOS_UINT8 ucNcellSearchTimerLen)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchFirstTimerLen = ucNcellSearchTimerLen;
}


VOS_UINT8 NAS_MMC_GetNcellSearchSecondTimerLen(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchSecondTimerLen);
}


VOS_VOID NAS_MMC_SetNcellSearchSecondTimerLen(VOS_UINT8 ucNcellSearchTimerLen)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDsdaPlmnSearchEnhancedCfg.ucNcellSearchSecondTimerLen = ucNcellSearchTimerLen;
}




VOS_VOID Mmc_ComGetPlmnSearchMode(VOS_UINT8 *pucReselMode)
{
    *pucReselMode = NAS_MMC_GetPlmnSelectionMode();
    return;
}


VOS_VOID NAS_MMC_SetPlmnSelectionMode(
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8      enSelectionMode
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSelectionMode = enSelectionMode;
}


NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8 NAS_MMC_GetAsCellCampOn(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enAsCellCampOn);
}


VOS_VOID NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8   enAsCellCampOn)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enAsCellCampOn = enAsCellCampOn;
}


NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 NAS_MMC_GetSpecPlmnSearchState(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSpecPlmnSearchState);
}


VOS_VOID NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 enSpecPlmnSearchState)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enSpecPlmnSearchState = enSpecPlmnSearchState;
}



NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserSpecPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserSpecPlmnId);
}



VOS_UINT32 NAS_MMC_GetUserSpecPlmnRegisterStatus()
{
    return NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucUserSpecPlmnRegStatus;
}



NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserReselPlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserReselPlmnId);
}



VOS_VOID NAS_MMC_SetUserSpecPlmnId(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnInfo
)
{
    PS_MEM_CPY(&(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stUserSpecPlmnId),
               pstPlmnInfo,
               sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
}



VOS_VOID NAS_MMC_SetUserSpecPlmnRegisterStatus(
    VOS_UINT8                           ucRegisterStatus
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucUserSpecPlmnRegStatus = ucRegisterStatus;
}



VOS_VOID NAS_MMC_SetUserReselPlmnId(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserReselPlmn = VOS_NULL_PTR;

    pstUserReselPlmn = NAS_MMC_GetUserReselPlmnId();

    pstUserReselPlmn->stPlmnId.ulMcc = pstPlmnId->ulMcc;
    pstUserReselPlmn->stPlmnId.ulMnc = pstPlmnId->ulMnc;
    pstUserReselPlmn->enRat          = enRat;
}



NAS_MMC_PLMN_REG_REJ_CTX_STRU *NAS_MMC_GetPlmnRegRejInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnRegInfo);
}


NAS_MMC_SERVICE_INFO_CTX_STRU *NAS_MMC_GetServiceInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stServiceInfo);
}



NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrCsService(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService);
}


NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrPsService(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService);
}




VOS_UINT32 NAS_MMC_IsCsNormalService( VOS_VOID )
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsPsNormalService( VOS_VOID )
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MMC_IsNormalServiceStatus(VOS_VOID)
{
    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enCsCurrService )
    {
        return VOS_TRUE;
    }

    if ( NAS_MMC_NORMAL_SERVICE == NAS_MMC_GetMmcCtxAddr()->stServiceInfo.enPsCurrService )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



NAS_MMC_MAINTAIN_CTX_STRU *NAS_MMC_GetMaintainInfo(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stMaintainInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverMmStatusToMmc
 ��������  : MM��GMM�ķ���״̬ת��ΪMMC�ķ���״̬
 �������  : enServiceStatus:MM��GMM�ķ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_SERVICE_ENUM_UINT8  NAS_MMC_ConverMmStatusToMmc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8           enRegDomain,
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8    enServiceStatus
)
{
    switch ( enServiceStatus )
    {
        case MM_COM_SRVST_NORMAL_SERVICE :
            return NAS_MMC_NORMAL_SERVICE;

        case MM_COM_SRVST_LIMITED_SERVICE :
            return NAS_MMC_LIMITED_SERVICE;

        case MM_COM_SRVST_LIMITED_SERVICE_REGION :
            return NAS_MMC_LIMITED_SERVICE_REGION;

        case MM_COM_SRVST_NO_IMSI :
            return NAS_MMC_LIMITED_SERVICE;

        case MM_COM_SRVST_NO_SERVICE :
            return NAS_MMC_NO_SERVICE;

        default:
            NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_ConverMmStatusToMmc,", enServiceStatus);
            break;
    }

    if ( NAS_MMC_REG_DOMAIN_CS == enRegDomain )
    {
        return NAS_MMC_GetCsServiceStatus();
    }
    else
    {
        return NAS_MMC_GetPsServiceStatus();
    }
}





VOS_VOID NAS_MMC_UpdateDomainServiceStatus(
    VOS_UINT8                           enCurrDomain,
    NAS_MMC_SERVICE_ENUM_UINT8          enCurrService
)
{
    /* �������CS�������CS��Ľ�� */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_CS == (NAS_MMC_WAIT_REG_RESULT_IND_CS & enCurrDomain) )
    {
        NAS_MMC_SetCsServiceStatus(enCurrService);
    }

    /* �������PS�������PS��Ľ�� */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_PS == (NAS_MMC_WAIT_REG_RESULT_IND_PS & enCurrDomain) )
    {
        NAS_MMC_SetPsServiceStatus(enCurrService);
    }
}





VOS_VOID    NAS_MMC_SetCsServiceStatus(
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService
)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    pstServiceInfo->enCsCurrService = enCsCurrService;
}



VOS_UINT32  NAS_MMC_IsInValidCampPlmn( VOS_VOID )
{
    NAS_MML_CAMP_PLMN_INFO_STRU         *pstCampPlmnInfo = VOS_NULL_PTR;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* �ж���ǰפ��PLMNΪ��Чֵ */
    if ( (NAS_MML_INVALID_MCC == pstCampPlmnInfo->stLai.stPlmnId.ulMcc )
      && (NAS_MML_INVALID_MNC == pstCampPlmnInfo->stLai.stPlmnId.ulMnc ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID    NAS_MMC_SetPsServiceStatus(NAS_MMC_SERVICE_ENUM_UINT8   enPsCurrService)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    pstServiceInfo->enPsCurrService = enPsCurrService;
}



NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCsServiceStatus( VOS_VOID )
{
    NAS_MMC_SERVICE_INFO_CTX_STRU*          pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    return pstServiceInfo->enCsCurrService;
}



NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetPsServiceStatus( VOS_VOID )
{
    NAS_MMC_SERVICE_INFO_CTX_STRU*          pstServiceInfo = VOS_NULL_PTR;

    pstServiceInfo =  NAS_MMC_GetServiceInfo();

    return pstServiceInfo->enPsCurrService;
}


VOS_UINT32  NAS_MMC_GetNextAvailableTimerValue(VOS_VOID)
{
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulTimerLen;
    NAS_MML_AVAIL_TIMER_CFG_STRU       *pstAvailTimerCfg = VOS_NULL_PTR;

    pstAvailTimerCfg           = NAS_MML_GetAvailTimerCfg();

    ulCount                    = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();

    /* ����history�ѵ���ش��� */
    if (VOS_TRUE == NAS_MMC_IsNeedStartHistoryTimer())
    {
        ulTimerLen  = NAS_MMC_GetNextHistoryTimerLen();
    }
    else if (VOS_TRUE == NAS_MMC_IsNeedStartNcellAvailableTimer())
    {
        /* NCELLȫ�ֱ����д��ֻ�����֣�����ת�����Ժ���Ϊ��λ */
        if (ulCount < pstAvailTimerCfg->ulFirstSearchTimeCount)
        {
            ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * NAS_MMC_GetNcellSearchFirstTimerLen();
        }
        else
        {
            ulTimerLen = NAS_MML_ONE_THOUSAND_MILLISECOND * NAS_MMC_GetNcellSearchSecondTimerLen();
        }
    }
    else
    {
        /* �����ǰ�����Ĵ���������available ��ʱ���ĵ�һ�δ���,ʹ�õ�һ��ʱ��,����ʹ�õڶ��ε� */
        if (ulCount < pstAvailTimerCfg->ulFirstSearchTimeCount)
        {
            ulTimerLen =  (pstAvailTimerCfg->ulFirstSearchTimeLen)*NAS_MML_ONE_THOUSAND_MILLISECOND;
        }
        else
        {
            ulTimerLen =  (pstAvailTimerCfg->ulDeepSearchTimeLen)*NAS_MML_ONE_THOUSAND_MILLISECOND;
        }
    }


    return ulTimerLen;
}


VOS_UINT32 NAS_MMC_GetNextHistoryTimerLen(VOS_VOID)
{
    NAS_MML_AVAIL_TIMER_CFG_STRU       *pstAvailTimerCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulCurAvailCount;
    VOS_UINT32                          ulCurHistoryCount;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT32                          ulTotalHistoryCount;
    VOS_UINT32                          ulHistoryTimerLen;

    pstAvailTimerCfg            = NAS_MML_GetAvailTimerCfg();
    ulCurAvailCount             = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();
    ulCurHistoryCount           = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();
    ulTotalHistoryCount         = 0;


    /* ����availableʱ����historyʱ�������������������������ʱ�����һ��history��ʱ��ʱ��ȡʣ��ʱ��
       ��: history�ڶ��׶ζ�ʱ��ʱ��Ϊ20s, available�ڶ��׶ζ�ʱ��ʱ��Ϊ65s
           ��65s������������ʱ���ܴ���Ϊ(65/20 = 3)��
           ��һ�ζ�ʱ��ʱ��Ϊhistory�ڶ��׶ζ�ʱ��ʱ��:20s
           �ڶ��ζ�ʱ��ʱ��Ϊhistory�ڶ��׶ζ�ʱ��ʱ��:20s
           �����ζ�ʱ��ʱ��Ϊʣ��ʱ��:(65-2*20) = 25s
    */

    /* Historyȫ�ֱ����д����sΪ��λ������ת�����Ժ���Ϊ��λ */
    if (ulCurAvailCount < pstAvailTimerCfg->ulFirstSearchTimeCount)
    {
        ulHistoryTimerLen        = NAS_MMC_GetHistorySearchFirstTimerLen();

        if (0 != ulHistoryTimerLen)
        {
            ulTotalHistoryCount = ((pstAvailTimerCfg->ulFirstSearchTimeLen) / ulHistoryTimerLen);
        }

        if ((ulCurHistoryCount + 1) == ulTotalHistoryCount)
        {
            /* ��N��ȡʣ��ʱ�� */
            ulTimerLen  = NAS_MML_ONE_THOUSAND_MILLISECOND * (pstAvailTimerCfg->ulFirstSearchTimeLen - ulCurHistoryCount * ulHistoryTimerLen);
        }
        else
        {
            /* ȡNV�����õ�historyʱ��*/
            ulTimerLen  = NAS_MML_ONE_THOUSAND_MILLISECOND * ulHistoryTimerLen;
        }
    }
    else
    {
        ulHistoryTimerLen        = NAS_MMC_GetHistorySearchSecondTimerLen();

        if (0 != ulHistoryTimerLen)
        {
            ulTotalHistoryCount = ((pstAvailTimerCfg->ulDeepSearchTimeLen) / ulHistoryTimerLen);
        }

        if ((ulCurHistoryCount + 1) == ulTotalHistoryCount)
        {
            /* ��N��ȡʣ��ʱ�� */
            ulTimerLen  = NAS_MML_ONE_THOUSAND_MILLISECOND * (pstAvailTimerCfg->ulDeepSearchTimeLen - ulCurHistoryCount * ulHistoryTimerLen);
        }
        else
        {
            /* ȡNV�����õ�historyʱ��*/
            ulTimerLen  = NAS_MML_ONE_THOUSAND_MILLISECOND * ulHistoryTimerLen;
        }
    }


    return ulTimerLen;
}



/*************************************** L1 MAIN״̬�������Ĳ������� *************************************************/

VOS_UINT32  NAS_MMC_GetCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount;
}
VOS_VOID    NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount = 0;
}
VOS_VOID    NAS_MMC_AddCurNormalAvailableTimerCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurNormalAvailableTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount++;
}
VOS_VOID   NAS_MMC_SetCurNormalAvailableTimerCount(
    VOS_UINT32                          ulCurTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurTimerCount = ulCurTimerCount;
}


VOS_UINT8  NAS_MMC_IsNeedStartNcellAvailableTimer(VOS_VOID)
{
    VOS_UINT8                           ucNcellSearchFlag;
    VOS_UINT32                          ulCount;
    NAS_MML_AVAIL_TIMER_CFG_STRU       *pstAvailTimerCfg   = VOS_NULL_PTR;
    VOS_UINT8                           ucNcellSearchTimerLen;
    VOS_UINT32                          ulAvailableSearchTimeLen;

    VOS_UINT8                           ucPsAttachAllowFlag;
    VOS_UINT8                           ucCsAttachAllowFlag;

    ulCount                    = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();
    ucNcellSearchFlag          = NAS_MMC_GetNcellSearchFlag();
    pstAvailTimerCfg           = NAS_MML_GetAvailTimerCfg();
    ucPsAttachAllowFlag        = NAS_MML_GetPsAttachAllowFlg();
    ucCsAttachAllowFlag        = NAS_MML_GetCsAttachAllowFlg();

    if (ulCount < pstAvailTimerCfg->ulFirstSearchTimeCount)
    {
        /* ��ȡ��һ�׶�availableʱ������ncellʱ���� */
        ulAvailableSearchTimeLen = (pstAvailTimerCfg->ulFirstSearchTimeLen);
        ucNcellSearchTimerLen      = NAS_MMC_GetNcellSearchFirstTimerLen();
    }
    else
    {
        /* ��ȡ�ڶ��׶�availableʱ������ncellʱ���� */
        ulAvailableSearchTimeLen = (pstAvailTimerCfg->ulDeepSearchTimeLen);
        ucNcellSearchTimerLen      = NAS_MMC_GetNcellSearchSecondTimerLen();
    }

    /*
       1��֧��ncell��������nv����:
        -- modem1 gas�ϱ�����t��l������Ƶ����Ϣ����������Ϊ0ʱҲ������ncell�Ѷ�ʱ��
        -- ��ǰΪPS attach not allow/cs attach not allow,��ֹ������������ù���
        -- �����ͨavailable��ʱ��Ϊ5s��NCELL availableʱ��Ϊ10s��
          ��ʱ����Ҫ����NCELL available��ʱ������������5s ��ͨavailable��ʱ������ʱ��
          ��ͨ available������
          ���Ҫ����NCELL available��ʱ���Ļ�������������ͨavailable��ʱ��ʱ����
          ���ٿ���������NCELL available��ʱ������һ��NCELL available��ʱ����ʱ��NCELL�����ѣ�
          �ڶ��γ�ʱ����ͨAvailable��
        -- ���ncellʱ��Ϊ0����������ͨavailable��ʱ��
   */
    if ((VOS_TRUE == ucNcellSearchFlag)
     && (0 != ucNcellSearchTimerLen)
     && (ulAvailableSearchTimeLen >= (2*ucNcellSearchTimerLen))
     && (VOS_FALSE == ucPsAttachAllowFlag)
     && (VOS_FALSE == ucCsAttachAllowFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT8 NAS_MMC_IsNeedStartHistoryTimer(VOS_VOID)
{
    NAS_MMC_HISTORY_SEARCH_INFO_STRU   *pstHistoryinfo      = VOS_NULL_PTR;
    NAS_MML_AVAIL_TIMER_CFG_STRU       *pstAvailTimerCfg    = VOS_NULL_PTR;
    /* Deleted by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
    /* Deleted by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulAvailableSearchTimeLen;
    VOS_UINT32                          ulHistoryTimerLen;

    pstHistoryinfo      = NAS_MMC_GetHistorySearchInfo();
    pstAvailTimerCfg    = NAS_MML_GetAvailTimerCfg();
    /* Deleted by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
    
    /* Deleted by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */
    ulCount             = NAS_MMC_GetCurNormalAvailableTimerCount_L1Main();

    /* history�� active��־Ϊfalse������Ҫ����history�Ѷ�ʱ�� */
    if (VOS_FALSE == pstHistoryinfo->ucActiveFlg)
    {
        return VOS_FALSE;
    }

    /* Deleted by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */

    /* Deleted by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */
    
    if (ulCount < pstAvailTimerCfg->ulFirstSearchTimeCount)
    {
        /* ��ȡ��һ�׶�availableʱ������historyʱ���� */
        ulAvailableSearchTimeLen = (pstAvailTimerCfg->ulFirstSearchTimeLen);
        ulHistoryTimerLen        = pstHistoryinfo->ulFirstTimerLen;
    }
    else
    {
        /* ��ȡ�ڶ��׶�availableʱ������historyʱ���� */
        ulAvailableSearchTimeLen = (pstAvailTimerCfg->ulDeepSearchTimeLen);
        ulHistoryTimerLen        = pstHistoryinfo->ulSecondTimerLen;
    }

    /* ��ʱ��ʱ��Ϊ0������Ҫ����history�Ѷ�ʱ�� */
    if (0 == ulHistoryTimerLen)
    {
        return VOS_FALSE;
    }

    /* �ý׶�availableʱ�� >= 2*history��ʱ�� */
    if (ulAvailableSearchTimeLen >= (2 * ulHistoryTimerLen))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8  NAS_MMC_GetAvailableTimerType_OnPlmn(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAvailableTimerType_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.enAvailableTimerType;
}
VOS_VOID  NAS_MMC_SetAvailableTimerType_OnPlmn(
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8                 enAvailableTimerType
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAvailableTimerType_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.enAvailableTimerType = enAvailableTimerType;
}
VOS_UINT32  NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount;
}
VOS_VOID  NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount = 0;
}
VOS_VOID  NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurNcellSearchTimerCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurNcellSearchTimerCount++;
}
VOS_UINT32  NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount;
}
VOS_VOID  NAS_MMC_SetCurHistorySearchTimerCount(
    VOS_UINT32                          ulCurHistorySearchTimerCount
)
{
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount = ulCurHistorySearchTimerCount;
}



VOS_VOID NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount = 0;

    return;
}
VOS_VOID  NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHistorySearchTimerCount++;

    return;
}
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_L1Main(VOS_VOID)
{

    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction;
}
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction;
}
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}
VOS_VOID NAS_MMC_ClearAllRegAdditionalAction_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllRegAdditionalAction_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.enPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
}
VOS_VOID NAS_MMC_SetCsRegAttemptCount_L1Main(
    VOS_UINT32      ulCsCount
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount = ulCsCount;
}
VOS_VOID NAS_MMC_SetPsRegAttemptCount_L1Main(
    VOS_UINT32      ulPsCount
)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount = ulPsCount;
}
VOS_UINT32 NAS_MMC_GetCsRegAttemptCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAttemptCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount;
}
VOS_UINT32 NAS_MMC_GetPsRegAttemptCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAttemptCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount;
}
VOS_VOID NAS_MMC_ClearAllRegAttemptCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllRegAttemptCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulCsAttemptCount = 0;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.stRegRsltInfo.ulPsAttemptCount = 0;
}

/*************************************** �������״̬�������Ĳ������� *************************************************/



NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8    NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg;
}



NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32   NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitSimFilesFlg_SwitchOn:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg;
}


VOS_VOID    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(
    NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8                    enMmStartCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg &= ~enMmStartCnfFlg;
}


VOS_VOID    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg = NAS_MMC_WAIT_MMGMM_START_CNF_NULL;
}




VOS_VOID    NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(
    NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32                   enSimFileCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg &= ~enSimFileCnfFlg;
}


VOS_VOID    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitSimFilesFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg = NAS_MML_READ_USIM_FILE_FLG_NULL;
}


VOS_VOID    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(
    NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8                    enMmStartCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ucMmcMmStartCnfFlg |= enMmStartCnfFlg;
}


VOS_VOID    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(
    NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32                   enSimFileCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (NAS_MMC_FSM_SWITCH_ON != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulMmcReadSimFileFlg |= enSimFileCnfFlg;
}

/*************************************** �ػ����״̬�������Ĳ������� *************************************************/

NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetMmPowerOffCnfFlg_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetMmPowerOffCnfFlg_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg;
}


NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetAsPowerOffCnfFlg_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAsPowerOffCnfFlg_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg;
}


VOS_VOID    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff(
    NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8                     enMmPowerOffFlg
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg |= enMmPowerOffFlg;
}


VOS_VOID    NAS_MMC_SetAsPowerOffCnfFlag_PowerOff(
    NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8                     enAsPowerOffFlg
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAsPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg |= enAsPowerOffFlg;
}


VOS_VOID    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff(
    NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8                     enMmPowerOffFlg
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg &= ~enMmPowerOffFlg;
}


NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetMasterModeRat_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetMasterModeRat_PowerOff:ENTERED");
    }

    return  g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.enMasterModeRat;
}


VOS_VOID NAS_MMC_SetMasterModeRat_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetMasterModeRat_PowerOff:ENTERED");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.enMasterModeRat = enMasterModeRat;
}


NAS_MML_PLMN_RAT_PRIO_STRU *NAS_MMC_GetSlaveModeRatList_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSlaveModeRatList_PowerOff:ENTERED");
    }

    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stPowerOffCtx.stSlaveModeList);
}


VOS_VOID NAS_MMC_BuildSlaveModeRatList_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                 *pstSlaveModeList = VOS_NULL_PTR; /* ���͹ػ�����Ĵ�ģ�б� */
    VOS_UINT8                                   ucRatIndex;
    VOS_UINT8                                   i;

    pstSlaveModeList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    ucRatIndex = 0;

    /* �Ȱ�ƽ̨���뼼��������LWG���ӵ���ģ�б��� */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_LTE;
        ucRatIndex++;
    }
#endif


    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_WCDMA;
        ucRatIndex++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pstSlaveModeList->aucRatPrio[ucRatIndex]      = NAS_MML_NET_RAT_TYPE_GSM;
        ucRatIndex++;
    }

    pstSlaveModeList->ucRatNum = ucRatIndex;

    /* ����ģ���б���ɾ�� */
    for (i = 0; i < ucRatIndex; i++)
    {
        if (pstSlaveModeList->aucRatPrio[i] == enMasterModeRat)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstSlaveModeList->aucRatPrio[i]),
                        &(pstSlaveModeList->aucRatPrio[i+1]),
                        (NAS_MML_MAX_RAT_NUM-i-1) * sizeof(pstSlaveModeList->aucRatPrio[i]));
            /*lint +e961*/
            pstSlaveModeList->ucRatNum--;
            break;
        }
    }

    return;

}
VOS_VOID    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff(
    NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8                     enAsPowerOffFlg
)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg &= ~enAsPowerOffFlg;
}



VOS_VOID    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcMmPowerOffCnfFlg = NAS_MMC_MMGMM_POWER_OFF_NULL_FLG;
}


VOS_VOID    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (NAS_MMC_FSM_POWER_OFF != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff:ENTERED");

    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucMmcAsPowerOffCnfFlg = NAS_MMC_AS_POWER_OFF_NULL_FLG;

    return;
}

/*************************************** ��ϵͳ��ѡ���״̬�������Ĳ������� *************************************************/

NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg;
}


NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg;
}


MMC_RESUME_ORIGEN_ENUM_UINT8 NAS_MMC_GetResumeOrign_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCellResel:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.enResumeOrign;
}


VOS_VOID NAS_MMC_SetResumeOrign_InterSysCellResel(
    MMC_RESUME_ORIGEN_ENUM_UINT8        enResumeOrign
)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeOrign_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.enResumeOrign = enResumeOrign;
}


VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}


VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}



VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}



VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}




VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}




VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCELLREL */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}


VOS_VOID NAS_MMC_SetAbortFlag_InterSysCellResel(
    VOS_UINT8                           ucAbortFlg
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucAbortFlg = ucAbortFlg;
}
VOS_UINT8 NAS_MMC_GetAbortFlag_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucAbortFlg;
}
VOS_VOID NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(
    VOS_UINT8                           ucSndSuspendRelReqFlg
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_InterSysCellResel,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucSndSuspendRelReqFlg = ucSndSuspendRelReqFlg;
}
VOS_UINT8 NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_INTER_SYS_CELLRESEL != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCellReselCtx.ucSndSuspendRelReqFlg;
}


/*************************************** ��ϵͳOOS���״̬�������Ĳ������� *************************************************/

NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysOos(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysOos:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg;
}


NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysOos(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysOos:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg;
}


VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}


VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}



VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}



VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}




VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysOos(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}




VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysOos(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSOOS */
    if (NAS_MMC_FSM_INTER_SYS_OOS != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysOos:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysOosCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}

/*************************************** ��ϵͳHO���״̬�������Ĳ������� *************************************************/

NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg;
}


NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg;
}


VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}


VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}



VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}



VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}




VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}




VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}


VOS_VOID NAS_MMC_SetCsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsSigExistFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucCsSigExistFlg = ucSigExistFlg;
}


VOS_VOID NAS_MMC_SetPsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsSigExistFlag_InterSysHo:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucPsSigExistFlg = ucSigExistFlg;
}



VOS_UINT8  NAS_MMC_GetCsSigExistFlag_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsSigExistFlag_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucCsSigExistFlg;
}


VOS_UINT8  NAS_MMC_GetPsSigExistFlag_InterSysHo(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSHO */
    if (NAS_MMC_FSM_INTER_SYS_HO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsSigExistFlag_InterSysHo:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysHoCtx.ucPsSigExistFlg;
}



/*************************************** ��ϵͳCCO���״̬�������Ĳ������� *************************************************/

NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCco(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSuspendRspFlg_InterSysCco:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg;
}


NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCco(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetResumeRspFlg_InterSysCco:ENTERED");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg;
}


VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg &= ~(enMmSuspendRsp);
}


VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg&= ~(enMmResumeRsp);
}



VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg |= enMmSuspendRsp;
}



VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg|= enMmResumeRsp;
}




VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCco(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllSuspendRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcSuspendRspFlg = NAS_MMC_SUSPEND_RSP_NULL_FLG;
}




VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCco(VOS_VOID)
{
    /* �����ǰ״̬������INTERSYSCCO */
    if (NAS_MMC_FSM_INTER_SYS_CCO != NAS_MMC_GetCurrFsmId())
    {
        /* �쳣�¼� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllResumeRspFlag_InterSysCco:ENTERED");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stInterSysCcoCtx.ucMmcResumeRspFlg= NAS_MMC_RESUME_RSP_NULL_FLG;
}




NAS_MMC_FSM_L1_MAIN_CTX_STRU* NAS_MMC_GetL1MainCtx_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetL1MainCtx_L1Main,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx);
}
NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU* NAS_MMC_GetPlmnSelectionCtx_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSelectionCtx_PlmnSelection,ERROR:FsmId Error");

        return VOS_NULL_PTR;
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx);
}
VOS_UINT32 NAS_MMC_GetAbortFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg);
}
VOS_VOID NAS_MMC_SetAbortFlag_PlmnSelection(
    VOS_UINT8                           ucAbortFlg
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucAbortFlg = ucAbortFlg;
}
VOS_UINT32 NAS_MMC_GetRelRequestFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRelRequestFlg);
}
VOS_VOID NAS_MMC_SetRelRequestFlag_PlmnSelection(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPlmnSelectionRelRequestFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucRelRequestFlg = ucRelRequestFlg;
}
VOS_UINT8 NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucExistRplmnOrHplmnFlag);
}
VOS_VOID NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(
    VOS_UINT8                           ucExistRplmnOrHplmnFlag
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucExistRplmnOrHplmnFlag = ucExistRplmnOrHplmnFlag;
    return;
}
VOS_VOID NAS_MMC_SetInterSysSuspendRat_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetInterSysSuspendRat_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucInterSysSuspendRat = enRat;

    return;
}
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetInterSysSuspendRat_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetInterSysSuspendRat_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucInterSysSuspendRat);
}

/* Added by l0130025 for V7R1 phase II , 2011-07-15, begin */


VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag);
}
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(VOS_UINT8 ucWaitFlag)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(
    VOS_UINT8                           ucRegDomain
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag &= ~ucRegDomain;
}
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection()
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(VOS_VOID)
{

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegAdditionalAction;
}
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegAdditionalAction;
}
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}
NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetCsRegCause_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegCause_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegCause;
}
NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetPsRegCause_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegCause_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegCause;
}
VOS_VOID NAS_MMC_SetCsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegCause_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enCsRegCause = enCsCause;
}
VOS_VOID NAS_MMC_SetPsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegCause_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enPsRegCause = enPsCause;
}
NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU * NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection()
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stPlmnSelectionListInfo);
}
VOS_UINT8 NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchedRoamPlmnSortedFlag
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag = ucSearchedRoamPlmnSortedFlag;
            return;
        }
    }
}


VOS_UINT8 NAS_MMC_GetHistorySearchedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetHistorySearchedFlag_PlmnSelection,ERROR:FsmId Error");

        return VOS_FALSE;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucHistorySearchedFlag;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetHistorySearchedFlag_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}



VOS_VOID NAS_MMC_SetHistorySearchedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucHistorySearchedFlag
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetHistorySearchedFlag_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucHistorySearchedFlag = ucHistorySearchedFlag;

            return;
        }
    }

    return;
}


VOS_UINT8 NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection,ERROR:FsmId Error");
    }

    for ( i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        /* �ҵ�δ����HISTORY�ѵ�RAT */
        if (VOS_FALSE == NAS_MMC_GetHistorySearchedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]) )
        {
            return VOS_FALSE;
        }
    }

    /* ָ���Ľ��뼼���б��������HISTORY���� */
    return VOS_TRUE;
}
VOS_UINT8 NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection,ERROR:FsmId Error");
    }

    for ( i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        /* �ҵ��Ź����RAT,�򷵻�TRUE */
        if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]) )
        {
            return VOS_TRUE;
        }
    }

    /* ��û���Ź���,�򷵻�FALSE */
    return VOS_FALSE;
}
VOS_UINT8 NAS_MMC_GetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAllBandSearch_PlmnSelection,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchAllBand;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAllBandSearch_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucAllBandSearch
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAllBandSearch_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchAllBand = ucAllBandSearch;
            return;
        }
    }
}


VOS_VOID NAS_MMC_SetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatCoverage_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if ( enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType) )
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enCoverageType = enCoverType;
            return ;
        }
    }

    /* ��δ�ҵ����µĽ��뼼���������LOG��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatCoverage_PlmnSelection,ERROR:NOT FOUND THE enRAT");
}
NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_GetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRatCoverage_PlmnSelection,ERROR:FsmId Error");
        return NAS_MMC_COVERAGE_TYPE_BUTT;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if ( enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType) )
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enCoverageType;
            
        }
    }

    return NAS_MMC_COVERAGE_TYPE_BUTT;
}




VOS_UINT8 NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndHplmnFlg,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndHplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndHplmnFlg,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndHplmnFlg
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchRplmnAndHplmnFlg,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = ucSearchRplmnAndHplmnFlg;
            return;
        }
    }
}



VOS_UINT8 NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndEplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndEplmnFlg
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = ucSearchRplmnAndEplmnFlg;
            return;
        }
    }
}


/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection
 ��������  : �����Ż������п�������HPLMN���ȣ���ȡ�Ƿ��Ѿ��ѹ�HPLMN�ı�ʾ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��18��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:FsmId Error");
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchDplmnAndHplmnFlg;
        }
    }

    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:enRatType Error");

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection
 ��������  : �����Ż������п�������HPLMN���ȣ������Ƿ��Ѿ��ѹ�HPLMN�ı�ʾ
 �������  : enRat                        - ���뼼��
             ucSwithOnAddHplmnFlg         - �Ƿ��Ѿ��ѹ�HPLMN�ı�ʾ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��18��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchDplmnAndHplmnFlg
)
{
    VOS_UINT32                          i;

    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����ѡ��״̬������������enRat��ͬ�Ľ��뼼������ */
    for (i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRat == (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].enRatType))
        {
            g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = ucSearchDplmnAndHplmnFlg;
            return;
        }
    }
}
/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

/*lint -e438 -e830*/

VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo = VOS_NULL_PTR;

    pstSearchRatInfo = &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[0]);

     /* �Ƚ��г�ʼ������ʣ��ĳ�ʼ��Ϊ��Чֵ */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg   = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucHistorySearchedFlag    = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

    }

    i = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        /* ����LTE���뼼��δȫƵ����,�����ڸ��� */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_LTE;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchedRoamPlmnSortedFlag = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

        i++;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        /* ����WCDMA���뼼��δȫƵ����,�����ڸ��� */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

        i++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        /* ����GSM���뼼��δȫƵ����,�����ڸ��� */
        pstSearchRatInfo[i].enRatType       = NAS_MML_NET_RAT_TYPE_GSM;
        pstSearchRatInfo[i].ucSearchAllBand = VOS_FALSE;
        pstSearchRatInfo[i].enCoverageType  = NAS_MMC_COVERAGE_TYPE_BUTT;
        pstSearchRatInfo[i].ucSearchRplmnAndHplmnFlg = VOS_FALSE;

        pstSearchRatInfo[i].ucSearchRplmnAndEplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
        pstSearchRatInfo[i].ucSearchDplmnAndHplmnFlg = VOS_FALSE;
        /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

        i++;
    }

    return;
}

/*lint +e438 +e830*/

NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU* NAS_MMC_GetForbRoamLaInfo_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetForbRoamLaInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stForbRoamLaInfo);
}
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stForbGprsPlmn);
}
VOS_VOID NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId
)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurrSearchingPlmn_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCurrSearchingPlmn = *pstPlmnId;
}
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurrSearchingPlmn_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrSearchingPlmn_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCurrSearchingPlmn);
}
VOS_VOID NAS_MMC_SetCurrSearchingType_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enCurrSearchingType
)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurrSearchingType_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.enCurrSearchingType = enCurrSearchingType;
}
NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32 NAS_MMC_GetCurrSearchingType_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurrSearchingType_PlmnSelection,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.enCurrSearchingType);
}



#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCsPsMode1ReCampLtePlmn = *pstPlmnId;
}
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection()
{
    /* �����ǰ״̬������PLMN SELECTION, �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId() )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stCsPsMode1ReCampLtePlmn);
}
#endif
VOS_UINT32 NAS_MMC_GetAbortFlag_AnyCellSearch(VOS_VOID)
{
    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_AnyCellSearch,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.ucAbortFlag);
}
VOS_VOID NAS_MMC_SetAbortFlag_AnyCellSearch(
    VOS_UINT8                           ucAbortFlg
)
{
    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_AnyCellSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.ucAbortFlag = ucAbortFlg;
}
NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU* NAS_MMC_GetFsmCtxAddr_AnyCellSearch(VOS_VOID)
{
    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetFsmCtxAddr_AnyCellSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx);
}
VOS_UINT8 NAS_MMC_GetRatNum_AnyCellSearch(VOS_VOID)
{
    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRatNum_AnyCellSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio.ucRatNum;
}
VOS_VOID NAS_MMC_DelMsUnsupportRat(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stNewPrioList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstMsPrioRatList  = VOS_NULL_PTR;
    VOS_UINT32                          ulRatIndex;
    VOS_UINT32                          ulMsRatIndex;

    VOS_UINT8                          ucNewRatNum;
    ucNewRatNum      = NAS_MMC_NUM_ZERO;
    pstMsPrioRatList = NAS_MML_GetMsPrioRatList();

    /*��ʼ���м�ṹ����*/
    stNewPrioList.ucRatNum = ucNewRatNum;
    for ( ulRatIndex = 0 ; ulRatIndex < NAS_MML_MAX_RAT_NUM; ulRatIndex++ )
    {
        stNewPrioList.aucRatPrio[ulRatIndex] = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    for ( ulRatIndex = 0 ; ulRatIndex < pstRatPrioList->ucRatNum; ulRatIndex++ )
    {
        for ( ulMsRatIndex = 0 ; ulMsRatIndex < pstMsPrioRatList->ucRatNum; ulMsRatIndex++ )
        {
            if (pstRatPrioList->aucRatPrio[ulRatIndex] == pstMsPrioRatList->aucRatPrio[ulMsRatIndex])
            {
                stNewPrioList.aucRatPrio[ucNewRatNum]= pstRatPrioList->aucRatPrio[ulRatIndex];
                ucNewRatNum++;
                stNewPrioList.ucRatNum = ucNewRatNum;
            }
        }
    }

    pstRatPrioList->ucRatNum = stNewPrioList.ucRatNum;
    for ( ulRatIndex = 0 ; ulRatIndex < NAS_MML_MAX_RAT_NUM; ulRatIndex++ )
    {
        pstRatPrioList->aucRatPrio[ulRatIndex] = stNewPrioList.aucRatPrio[ulRatIndex];
    }

    return;
}
VOS_VOID NAS_MMC_SetRatPrioList_AnyCellSearch(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstAnycellPrioList = VOS_NULL_PTR;
    VOS_UINT32                          i;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulIsLteOnly;
    VOS_UINT8                           ucSupportCsServiceFlg;
    VOS_UINT8                           ucSimCsPsRegStatus;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulIsSupportLte;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    
    VOS_UINT8                           ucLowPrioAnycellSearchLteFlg;
    ucLowPrioAnycellSearchLteFlg        = NAS_MML_GetLowPrioAnycellSearchLteFlg();

    pstSimStatus          = NAS_MML_GetSimStatus();
    ucSimCsPsRegStatus    = VOS_TRUE;
    ulIsLteOnly           = NAS_MML_IsLteOnlyMode(pstRatPrioList);
    ucSupportCsServiceFlg = NAS_MML_GetSupportCsServiceFLg();
    ulIsSupportLte        = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                       pstRatPrioList);
    ucIndex               = 0;
    enMsMode              = NAS_MML_GetMsMode();
    PS_MEM_SET(&stAnycellSrchRatList, (VOS_CHAR)0x0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    if (( VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
     && ( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
    {
        ucSimCsPsRegStatus = VOS_FALSE;
    }
#endif

    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatPrioList_AnyCellSearch,ERROR:FsmId Error");
    }

    pstAnycellPrioList = &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stAnyCellSearchCtx.stMmcPlmnRatPrio);

    pstAnycellPrioList->ucRatNum = pstRatPrioList->ucRatNum;

    for ( i = 0 ; i < pstRatPrioList->ucRatNum; i++ )
    {
        pstAnycellPrioList->aucRatPrio[i] = pstRatPrioList->aucRatPrio[i];
    }

    /* 45008Э������: If the mobile station supports CS voice services,the MS shall avoid
       reselecting acceptable(but not suitable) E-UTRA cells regardless of the priorities
       in system information,֧��cs����ҵ���޿���csps������Ч���µ�anycell�ѣ���L��ģ������ps only
       (����������ps only��3��6��8�ܾ���Ҫ����L),��L�Ľ��뼼��������� */
#if (FEATURE_ON == FEATURE_LTE)

    if ( (((VOS_FALSE == NAS_MML_GetSimPresentStatus())
         || (VOS_FALSE == ucSimCsPsRegStatus)
         || (VOS_TRUE == ucLowPrioAnycellSearchLteFlg))
        && (VOS_TRUE == ucSupportCsServiceFlg)
        && (VOS_FALSE == ulIsLteOnly)
        && (VOS_TRUE == ulIsSupportLte)
        && (NAS_MML_MS_MODE_PS_ONLY != enMsMode)))
    {
        for (i = 0; i < pstRatPrioList->ucRatNum; i++)
        {
            if (pstRatPrioList->aucRatPrio[i] != NAS_MML_NET_RAT_TYPE_LTE)
            {
                stAnycellSrchRatList.aucRatPrio[ucIndex] = pstRatPrioList->aucRatPrio[i];
                ucIndex++;
            }
        }

        stAnycellSrchRatList.aucRatPrio[ucIndex] = NAS_MML_NET_RAT_TYPE_LTE;
        ucIndex++;
        stAnycellSrchRatList.ucRatNum = ucIndex;
        PS_MEM_CPY(pstAnycellPrioList, &stAnycellSrchRatList, sizeof(stAnycellSrchRatList));
    }
#endif

    return;
}



NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSearchRat_AnyCellSearch(VOS_VOID)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               ucRatNum;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif

    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSearchRat_AnyCellSearch,ERROR:FsmId Error");
    }

    pstAnyCellSearchCtx   = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();
    ucRatNum = NAS_MMC_GetRatNum_AnyCellSearch();

    for ( i = 0; i < ucRatNum; i++)
    {
#if (FEATURE_ON == FEATURE_LTE)

        /* ��ȡLTE������״̬ */
        enLteCapabilityStatus   = NAS_MML_GetLteCapabilityStatus();

        /* ���뼼��ΪLTE�ҵ�ǰLTE״̬Ϊdisableʱ����ѡ��LTE�Ľ��뼼�� */
        if (((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == enLteCapabilityStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS  == enLteCapabilityStatus))
         && (NAS_MML_NET_RAT_TYPE_LTE   == pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i]))
        {
            continue;
        }
#endif

        if ( VOS_FALSE == pstAnyCellSearchCtx->aucSearchedFlag[i])
        {
            /* ��ȡ�¸�δ�������Ľ��뼼�� */
            return pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i];
        }
    }

    /* ��ȡ�¸�δ�������Ľ��뼼��ʧ�� */
    return NAS_MML_NET_RAT_TYPE_BUTT;
}

VOS_VOID NAS_MMC_SetSearchedFlag_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                    *pstAnyCellSearchCtx = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    /* �����ǰ״̬������ANYCELL PLMN SRCH */
    if (NAS_MMC_FSM_ANYCELL_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedFlag_AnyCellSearch,ERROR:FsmId Error");
        return;
    }

    /* ��ȡAnyCell����״̬���������ĵ�ַ */
    pstAnyCellSearchCtx   = NAS_MMC_GetFsmCtxAddr_AnyCellSearch();

    for (i = 0; i < NAS_MMC_GetRatNum_AnyCellSearch(); i++)
    {
        if ( enSpecRat == pstAnyCellSearchCtx->stMmcPlmnRatPrio.aucRatPrio[i])
        {
            /* ���øý��뼼��Ϊ���ѹ� */
            pstAnyCellSearchCtx->aucSearchedFlag[i] = VOS_TRUE;
        }
    }

    return;

}
VOS_VOID NAS_MMC_InitFsmCtx_SysCfg(VOS_VOID)
{
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSyscfgSettingRecord  = VOS_NULL_PTR;

    NAS_MML_PLMN_RAT_PRIO_STRU          stPrePrioRatList;

    /* ��ȡ״̬���е�Ҫ����SYSCFG����ģ����Ӧ���������б��ַ */
    pstSyscfgSettingRecord              = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    NAS_MMC_SetRelRequestFlag_SysCfg(VOS_FALSE);

    /* SYSCFG״̬���������������ĳ�ʼ��:Ĭ�ϲ���Ҫ���� */
    NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_FALSE);

    /* SYSCFG״̬�������������ý�������ȼ�˳����Ϣ�ĳ�ʼ��:
       ����������ʼ��Ϊ0,ÿ����SYSCFG�󣬸���������1����ʾҪ����SYSCFG�Ľ���ģʽ */
    pstSyscfgSettingRecord->ucSetCurrSyscfgIndex = 0;

    /* ������Ҫ�·�SYSCFG���ܸ��� */
    pstSyscfgSettingRecord->ucTotalSyscfgNum = 0;

    /* Added by wx270776 for syscfg_sort, 2015-9-16, begin */
    /* ��ʼ�����·�SYSCFG�����˳��ΪLUG�����ƽ̨��֧��ĳ�����뼼���������ý��뼼���������� */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_LTE;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        pstSyscfgSettingRecord->aucSyscfgRatPrio[pstSyscfgSettingRecord->ucTotalSyscfgNum] = NAS_MML_NET_RAT_TYPE_GSM;
        pstSyscfgSettingRecord->ucTotalSyscfgNum++;
    }
    /* Added by wx270776 for syscfg_sort, 2015-9-16, end */

#if (FEATURE_ON == FEATURE_LTE)
    stPrePrioRatList.ucRatNum     = 0;
    stPrePrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[2]= NAS_MML_NET_RAT_TYPE_BUTT;
#else
    stPrePrioRatList.ucRatNum     = 0;
    stPrePrioRatList.aucRatPrio[0]= NAS_MML_NET_RAT_TYPE_BUTT;
    stPrePrioRatList.aucRatPrio[1]= NAS_MML_NET_RAT_TYPE_BUTT;
#endif

    NAS_MMC_SetPrePrioRatList_SysCfg(&stPrePrioRatList);
    return ;
}



NAS_MMC_SYSCFG_SETTING_CTRL_STRU* NAS_MMC_GetSysCfgSettingRecord_SysCfg(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;
    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSysCfgSettingRecord_SysCfg,ERROR:FsmId Error");
    }

    return &(pstNasMmcCtx->stCurFsm.unFsmCtx.stSyscfgCtx.stSyscfgSettingRecord);
}
VOS_VOID NAS_MMC_SetPrePrioRatList_SysCfg(
    NAS_MML_PLMN_RAT_PRIO_STRU          *pstPrePrioRatList
)
{
    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrePrioRatList_SysCfg,ERROR:FsmId Error");
    }

    NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stSyscfgCtx.stPrePrioRatList
                   = *pstPrePrioRatList;
    return;
}
NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MMC_GetPrePrioRatList_SysCfg(VOS_VOID)
{
    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPrePrioRatList_SysCfg,ERROR:FsmId Error");
    }

    return &(NAS_MMC_GetMmcCtxAddr()->stCurFsm.unFsmCtx.stSyscfgCtx.stPrePrioRatList);
}
VOS_VOID NAS_MMC_AddSysCfgIndex_SysCfg(VOS_VOID)
{
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSysCfgRecord     = VOS_NULL_PTR;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSysCfgIndex_SysCfg,ERROR:FsmId Error");
    }

    /* ��ȡ״̬���е�Ҫ����SYSCFG����ģ����Ӧ���������б��ַ */
    pstSysCfgRecord   = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* ����INDEX����,ָ����һ��Ҫ����SYSCFG���õĽ��뼼�� */
    pstSysCfgRecord->ucSetCurrSyscfgIndex ++;

    /* ���� */
    return ;
}




NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSettingRat_SysCfg(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *pucSyscfgRatPrio    = VOS_NULL_PTR;
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSysCfgRecord     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     ucNextSyscfgRat;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    pstSysCfgRecord      = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* ��ȡ״̬���е�Ҫ����SYSCFG����ģ����Ӧ���������б��ַ */
    pucSyscfgRatPrio     = pstSysCfgRecord->aucSyscfgRatPrio;

    /* ��������Ե������õ��ܸ��������ؽ��뼼��Ϊ��Чֵ����ʾSYSCFG���ý��� */
    if ( pstSysCfgRecord->ucSetCurrSyscfgIndex >= pstSysCfgRecord->ucTotalSyscfgNum )
    {
        return NAS_MML_NET_RAT_TYPE_BUTT;
    }

    /* ȡ����������������Ӧ�Ľ��뼼�� */
    ucNextSyscfgRat                     = pucSyscfgRatPrio[pstSysCfgRecord->ucSetCurrSyscfgIndex];

    /* ������ҪSYSCFG���õĽ��뼼�� */
    return ucNextSyscfgRat;
}
VOS_UINT32  NAS_MMC_GetPlmnSearchFlag_SysCfg(VOS_VOID)
{
    NAS_MMC_CONTEXT_STRU               *pstNasMmcCtx        = VOS_NULL_PTR;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    pstNasMmcCtx = NAS_MMC_GetMmcCtxAddr();

    return (pstNasMmcCtx->stCurFsm.unFsmCtx.stSyscfgCtx.ulNeedSearchPlmnFlag);
}
VOS_VOID NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_UINT32 ulNeedSearchPlmnFlag)
{
    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSettingRat_SysCfg,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ulNeedSearchPlmnFlag = ulNeedSearchPlmnFlag;
    return;
}
/* Modified by wx270776 for syscfg_sort, 2015-9-2, begin */
VOS_VOID NAS_MMC_SetSysCfgSendingOrder_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg
)
{
    VOS_UINT32                          i;
    /* ���������Ľ��뼼���б� */
    NAS_MML_PLMN_RAT_PRIO_STRU          stTempRatList;
    /* ����SYSCFG�ϱ���˳�� */
    NAS_MML_PLMN_RAT_PRIO_STRU          stSyscfgSendingOrder;
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU   *pstSyscfgSettingRecord = VOS_NULL_PTR;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSysCfgSendingOrder_SysCfg,ERROR:FsmId Error");
    }

    /* ȡ�õ�ǰ SYSCFG״̬���������еļ�¼���ý�������ȼ�˳����Ϣ */
    pstSyscfgSettingRecord  = NAS_MMC_GetSysCfgSettingRecord_SysCfg();

    /* ��ʼ�� */
    PS_MEM_SET(&stSyscfgSendingOrder, 0x00, sizeof(stSyscfgSendingOrder));
    stSyscfgSendingOrder.ucRatNum = pstSyscfgSettingRecord->ucTotalSyscfgNum;
    PS_MEM_CPY( stSyscfgSendingOrder.aucRatPrio,
                pstSyscfgSettingRecord->aucSyscfgRatPrio,
                sizeof(pstSyscfgSettingRecord->aucSyscfgRatPrio) );

    /* 1. �ҳ������Ľ��뼼����������ʱ���б��� */
    NAS_MML_GetNewRatFromRatList( NAS_MML_GetMsPrioRatList(),
                                  &(pstSysCfgMsg->stRatPrioList),
                                  &stTempRatList );

    /* 2. ����ǰ��ģ���ȼ����õ���� */
    NAS_MML_SortSpecRatPrioHighest( NAS_MML_GetCurrNetRatType(),
                                    &stSyscfgSendingOrder );

    /* 3. �������Ľ��뼼�����򵽽��뼼���б���� */
    for ( i = stTempRatList.ucRatNum; i > 0 ; i-- )
    {
        NAS_MML_SortSpecRatPrioHighest( stTempRatList.aucRatPrio[i-1],
                                        &stSyscfgSendingOrder );
    }

    /* ��SYSCFG�ϱ�˳�����ȫ�ֱ����� */
    pstSyscfgSettingRecord->ucTotalSyscfgNum = stSyscfgSendingOrder.ucRatNum;
    PS_MEM_CPY( pstSyscfgSettingRecord->aucSyscfgRatPrio,
                stSyscfgSendingOrder.aucRatPrio,
                sizeof(pstSyscfgSettingRecord->aucSyscfgRatPrio) );

    return;
}
/* Modified by wx270776 for syscfg_sort, 2015-9-2, end */


VOS_UINT8 NAS_MMC_GetRelRequestFlag_SysCfg(VOS_VOID)
{
    /* �����ǰ״̬������ SysCfg, �쳣��ӡ */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_SysCfg,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ucRelRequestFlg);
}
VOS_VOID NAS_MMC_SetRelRequestFlag_SysCfg(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* �����ǰ״̬������ SysCfg, �쳣��ӡ  */
    if (NAS_MMC_FSM_SYSCFG !=NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRelRequestFlag_SysCfg,ERROR:FsmId Error");
        return ;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stSyscfgCtx.ucRelRequestFlg = ucRelRequestFlg;
}


VOS_UINT32 NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
)
{
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfg          = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId           = VOS_NULL_PTR;
    VOS_UINT32                          ulFlg;

    /* �����ǰ״̬������NAS_MMC_FSM_SYSCFG */
    if (NAS_MMC_FSM_SYSCFG != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg,ERROR:FsmId Error");
    }

    pstRoamCfg      = NAS_MML_GetRoamCfg();

    /* ȡ�õ�ǰפ����PLMN ID */
    pstPlmnId       = NAS_MML_GetCurrCampPlmnId();

    /* ��HPLMN��ͬ��ֱ�ӷ������� */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmnId))
    {
        return VOS_TRUE;
    }

    /* �������Կ��عرգ�ֱ�ӷ������� */
    if (VOS_FALSE == pstRoamCfg->ucRoamFeatureFlg)
    {
        return VOS_TRUE;
    }

    /* ��������ʱֱ�ӷ������� */
    if (NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_ON == pstSysCfgSetParm->enRoamCapability)
    {
        return VOS_TRUE;
    }


    /* �жϵ�ǰ�����Ƿ���������������б��� */
    ulFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNationalRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );

    /* ��SYSCFG����׼����й������Σ��ҵ�ǰ������������������б��У�����׼������ */
    if ( (NAS_MSCC_PIF_ROAM_NATION_ON_INTERNATION_OFF == pstSysCfgSetParm->enRoamCapability)
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }

    /* ��SYSCFG���ò�׼����й������Σ��ҵ�ǰ���������β�֧��ʱ����ע�������У�����׼������ */
    ulFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList( pstPlmnId,
                                            pstRoamCfg->ucNotRoamNum,
                                            pstRoamCfg->astRoamPlmnIdList );
    if ( ( (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_ON == pstSysCfgSetParm->enRoamCapability)
        || (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF == pstSysCfgSetParm->enRoamCapability) )
      && (VOS_TRUE == ulFlg) )
    {
        return VOS_TRUE;
    }

    /* ���򷵻ز��������� */
    return VOS_FALSE;
}

/* LIST����״̬�������Ĳ������� */


VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stTmpPrioRatList;

    PS_MEM_SET(&stTmpPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitSearchRatInfo_PlmnList,ERROR:FsmId Error");

        return;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    pstRatPrioList      = NAS_MML_GetMsPrioRatList();

    /* ����һ����ʱ���뼼���б�, ���ڵ��� */
    PS_MEM_CPY(&stTmpPrioRatList, pstRatPrioList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ǰ���뼼������,��ǰ���뼼��������ǰ�� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stTmpPrioRatList);
    }

    /* ��ʼ�����뼼�����ȼ��б��Լ�������� */
    for (i = 0; i < stTmpPrioRatList.ucRatNum; i++ )
    {
        pstSearchRatInfo[i].enRat           = stTmpPrioRatList.aucRatPrio[i];
        pstSearchRatInfo[i].ucSearchedFlag  = VOS_FALSE;
    }
}



NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *NAS_MMC_GetSearchCtrlInfo_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchRatInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.astPlmnListCtrlInfo[0]);
}

VOS_UINT32  NAS_MMC_GetNextSearchingRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucRatNum;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNextSearchRat_PlmnList,ERROR:FsmId Error");
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    ucRatNum            = NAS_MML_GetMsPrioRatList()->ucRatNum;

    for ( i = 0; i < ucRatNum; i++)
    {
        if ( VOS_FALSE == pstSearchRatInfo[i].ucSearchedFlag)
        {
            /* ��ȡ�¸�δ�������Ľ��뼼�� */
            *penRat  = pstSearchRatInfo[i].enRat;
            return VOS_TRUE;
        }
    }

    /* ��ȡ�¸�δ�������Ľ��뼼��ʧ�� */
    return VOS_FALSE;
}

VOS_VOID NAS_MMC_GetOrigenSearchRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
)
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *pstSearchRatInfo = VOS_NULL_PTR;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetOrigenSearchRat_PlmnList,ERROR:FsmId Error");
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();

    *penRat = pstSearchRatInfo[0].enRat;
}

VOS_VOID NAS_MMC_SetSearchedFlag_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
)
{
    VOS_UINT32                              i;
    VOS_UINT8                               ucRatNum;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU     *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU   *pstListInfo      = VOS_NULL_PTR;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSearchedFlag_PlmnList,ERROR:FsmId Error");
       return ;
    }

    pstSearchRatInfo    = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    ucRatNum            = NAS_MML_GetMsPrioRatList()->ucRatNum;
    pstListInfo         = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for ( i = 0; i < ucRatNum; i++)
    {
       if ( enSpecRat == pstSearchRatInfo[i].enRat )
       {
           pstSearchRatInfo[i].ucSearchedFlag = VOS_TRUE;

           /* �����������������б��������Ľ��뼼�������ں������ݽ��뼼�����б���и��� */
           pstListInfo[i].enRatType           = enSpecRat;
           break;
       }
    }

    return;
}



VOS_UINT8 NAS_MMC_GetAbortFlag_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAbortFlg;
}

VOS_VOID NAS_MMC_SetAbortFlag_PlmnList(
    VOS_UINT8                           ucAbortFlg
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAbortFlg = ucAbortFlg;
}

VOS_UINT8 NAS_MMC_GetNotifyMsccFlag_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNotifyMsccFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucNotifyMsccFlg;
}

VOS_VOID NAS_MMC_SetNotifyMsccFlag_PlmnList(
    VOS_UINT8                           ucNotifyFlg
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNotifyMsccFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucNotifyMsccFlg= ucNotifyFlg;
}
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag;
}
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnList(
    VOS_UINT8       ucWaitFlag
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(
    VOS_UINT8                           ucRegRslt
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag &= ~ucRegRslt;
}
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList,ERROR:FsmId Error");
       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnList(VOS_VOID)
{

    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enCsRegAdditionalAction;
}
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnList(VOS_VOID)
{
    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enPsRegAdditionalAction;
}
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
)
{
    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_PlmnList,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}
NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU *NAS_MMC_GetRegRsltInfo_PlmnList(VOS_VOID)
{
    /* �����ǰ״̬������PLMN LIST */
    if (NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRegRsltInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.stRegRsltInfo);
}

VOS_VOID NAS_MMC_InitSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo     = VOS_NULL_PTR;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId() )
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_InitSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    pstListInfo         = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    for ( i= 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstListInfo[i].enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstListInfo[i].ulHighPlmnNum    = 0;
        pstListInfo[i].ulLowPlmnNum     = 0;
        pstListInfo[i].enCoverType      = NAS_MMC_COVERAGE_TYPE_BUTT;

        /* �����ȼ��б� */
        for ( j = 0; j < NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM; j++ )
        {
            pstListInfo[i].astHighPlmnList[j].ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astHighPlmnList[j].ulMnc = NAS_MML_INVALID_MNC;
        }

        /* �����ȼ��б� */
        for ( k = 0; k < NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM; k++)
        {
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
            pstListInfo[i].astLowPlmnList[k].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
            pstListInfo[i].astLowPlmnList[k].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}




NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *NAS_MMC_GetSearchedPlmnListInfo_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ*/
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.astPlmnSearchInfo[0]);
}

VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(
    RRC_PLMN_ID_LIST_STRU              *pstRrcList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulIndex;
    VOS_UINT32                                              ucRatNum;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList,ERROR:FsmId Error");
       return;
    }

    pstListInfo     = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();
    ucRatNum        = NAS_MML_GetMsPrioRatList()->ucRatNum;

    /* ����������б���������Ӧ���뼼�����б� */
    for ( i = 0; i < ucRatNum; i++ )
    {
        for ( j = 0; j < pstRrcList->ulHighPlmnNum; j++ )
        {
            /* ת��RRC��ʽ�Ľ��뼼�� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aHighPlmnList[j].ulRat, &enRat);

            if ( enRat == pstListInfo[i].enRatType )
            {
                ulIndex = pstListInfo[i].ulHighPlmnNum;
                pstListInfo[i].astHighPlmnList[ulIndex].ulMcc
                       = pstRrcList->aHighPlmnList[j].stPlmnId.ulMcc;

                pstListInfo[i].astHighPlmnList[ulIndex].ulMnc
                       = pstRrcList->aHighPlmnList[j].stPlmnId.ulMnc;

                pstListInfo[i].ulHighPlmnNum ++;

                /* ��֤���鲻Խ�� */
                if (pstListInfo[i].ulHighPlmnNum >= NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM)
                {
                    /* ����Խ�磬�������ѭ�� */
                    i = ucRatNum;
                    break;
                }
            }

        }
    }

    /* ����������б���������Ӧ���뼼�����б� */
    for ( i = 0; i < ucRatNum; i++ )
    {
        for ( j = 0; j < pstRrcList->ulLowPlmnNum; j++ )
        {
            /* ת��RRC��ʽ�Ľ��뼼�� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstRrcList->aLowPlmnList[j].PlmnId.ulRat, &enRat);

            if ( enRat == pstListInfo[i].enRatType )
            {
                ulIndex = pstListInfo[i].ulLowPlmnNum;
                pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMcc
                       = pstRrcList->aLowPlmnList[j].PlmnId.stPlmnId.ulMcc;

                pstListInfo[i].astLowPlmnList[ulIndex].stPlmnId.ulMnc
                       = pstRrcList->aLowPlmnList[j].PlmnId.stPlmnId.ulMnc;

                pstListInfo[i].astLowPlmnList[ulIndex].lRscp
                       = pstRrcList->aLowPlmnList[j].lRscp;

                pstListInfo[i].ulLowPlmnNum ++;

                /* ��֤���鲻Խ�� */
                if (pstListInfo[i].ulLowPlmnNum >= NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM)
                {
                    /* ����Խ�磬�������ѭ�� */
                    i = ucRatNum;
                    break;
                }
            }
        }
    }

    /* ���ݸߵ������������¸������� */
    for ( i = 0; i < ucRatNum; i++ )
    {
        if (pstListInfo[i].ulHighPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_HIGH;
        }
        else if (pstListInfo[i].ulLowPlmnNum > 0)
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_LOW;
        }
        else
        {
            pstListInfo[i].enCoverType = NAS_MMC_COVERAGE_TYPE_NONE;
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT8 NAS_MMC_GetPreLteDisableFlg_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreLteDisableFlg_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucPreLteDisableFlg;
}

VOS_VOID NAS_MMC_SetPreLteDisableFlg_PlmnList(
    VOS_UINT8                           ucPreLteDisableFlg
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucPreLteDisableFlg = ucPreLteDisableFlg;
    return;

}
#endif

VOS_UINT8 NAS_MMC_GetAnyCellSrchFlg_PlmnList(VOS_VOID)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAnyCellSrchFlg_PlmnList,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAnyCellSrchFlg;
}

VOS_VOID NAS_MMC_SetAnyCellSrchFlg_PlmnList(
    VOS_UINT8                           ucAnyCellSrchFlg
)
{
    /* ��ǰ����PLMN LIST״̬�� �쳣��ӡ */
    if ( NAS_MMC_FSM_PLMN_LIST != NAS_MMC_GetCurrFsmId())
    {
       NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAnyCellSrchFlg_PlmnList,ERROR:FsmId Error");

       return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnListCtx.ucAnyCellSrchFlg = ucAnyCellSrchFlg;
    return;
}
VOS_VOID NAS_MMC_InitHighPrioPlmnSearchCtx(NAS_MMC_HIGH_PRIO_PLMN_SEARCH_CTRL_CTX_STRU *pstHighPrioPlmnSearchCtrl)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    pstHighPrioPlmnSearchCtrl->ucFirstStartHPlmnTimerFlg                       = VOS_TRUE;
    pstHighPrioPlmnSearchCtrl->enPlmnSelectionListType                         = NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST;
    pstHighPrioPlmnSearchCtrl->ucTdHighRatSearchCount                          = 0;
    pstHighPrioPlmnSearchCtrl->aucReserve[0]                                   = 0;

    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.usSearchPlmnNum = 0;
    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.aucReserve[0]   = 0;
    pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.aucReserve[1]   = 0;

    for (i = 0; i < NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST; i++)
    {
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].enPlmnType     = NAS_MMC_PLMN_TYPE_BUTT;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].ucRatNum       = 0;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].aucReserve[0]  = 0;
        pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].aucReserve[1]  = 0;

        for (j = 0; j < NAS_MML_MAX_RAT_NUM; j++)
        {
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].enQuality   = NAS_MMC_NET_QUALITY_BUTT;

            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].ucReserve   = 0;

            pstHighPrioPlmnSearchCtrl->stHighPrioPlmnSearchListInfo.astPlmnSelectionList[i].astPlmnRatInfo[j].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        }
    }
}


NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *NAS_MMC_GetHighPrioPlmnList(VOS_VOID)
{

    return &(g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.stHighPrioPlmnSearchListInfo);
}


NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionListType(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.enPlmnSelectionListType;
}


VOS_VOID NAS_MMC_SetPlmnSelectionListType(
    NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8             enListType
)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.enPlmnSelectionListType = enListType;

    return;
}


VOS_UINT8 NAS_MMC_GetTdHighRatSearchCount(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount;
}


VOS_VOID NAS_MMC_AddTdHighRatSearchCount(VOS_VOID)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount++;

    return;
}


VOS_VOID NAS_MMC_InitTdHighRatSearchCount(VOS_VOID)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucTdHighRatSearchCount = 0;

    return;
}


MSCC_MMC_NET_SCAN_REQ_STRU *NAS_MMC_GetNetScanReq(VOS_VOID)
{
    return &(g_stNasMmcCtx.stNetScanReqCtx.stNetScanReq);
}


VOS_VOID NAS_MMC_SetNetScanReq(
    MSCC_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq
)
{
    PS_MEM_CPY(&(g_stNasMmcCtx.stNetScanReqCtx.stNetScanReq),
                pstNetScanReq,
                sizeof(MSCC_MMC_NET_SCAN_REQ_STRU));

    return;
}





RRMM_RAT_PRIO_ENUM_UINT8 NAS_MMC_GetSpecRatPrio(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList
)
{
    VOS_UINT32                          i;

    /* ���Ҷ�Ӧ���뼼���Ƿ���֧���б��� */
    for ( i = 0; i < pstRatList->ucRatNum; i++ )
    {
        if ( (pstRatList->aucRatPrio[i] == enRat)
          && (enRat < NAS_MML_NET_RAT_TYPE_BUTT) )
        {
            break;
        }
    }

    /* ���ҳɹ�,���ض�Ӧ�Ľ��뼼�����ȼ� */
    if ( i < pstRatList->ucRatNum )
    {
        /*���뼼�������ȼ����Ӹߵ������� */
        return (VOS_UINT8)(RRMM_RAT_PRIO_HIGH - i);
    }

    /* ����֧���б���ʱ���������ȼ�ΪNULL*/
    else
    {
        return RRMM_RAT_PRIO_NULL;
    }

}





VOS_UINT32 NAS_MMC_GetEHPlmn(
    RRC_PLMN_ID_STRU                   *pstEHPlmn,
    VOS_UINT8                          *pucEHPlmnNum
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEHplmn = VOS_NULL_PTR;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT8                           ucSimFlg;

    /* ��ȡ��ǰ��SIM��״̬��Ϣ */
    pstSimStatus = NAS_MML_GetSimStatus();
    ucSimFlg    = pstSimStatus->ucSimPresentStatus;

    if ((VOS_NULL_PTR == pstEHPlmn) || (VOS_NULL_PTR == pucEHPlmnNum))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetEHPlmn, input para is null.");
        return VOS_ERR;
    }

    if (VOS_FALSE == ucSimFlg)
    {

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetEHPlmn, sim is absent or locked");
        return VOS_ERR;
    }

    pstSimEHplmn = NAS_MML_GetSimEhplmnList();

    /* ���EHPLMN�ĸ��� */
    *pucEHPlmnNum  = pstSimEHplmn->ucEhPlmnNum;

    /* ��ȡEHPLMN */
    for (i = 0; i < (*pucEHPlmnNum); i++)
    {
        pstEHPlmn[i].ulMcc = pstSimEHplmn->astEhPlmnInfo[i].stPlmnId.ulMcc;
        pstEHPlmn[i].ulMnc = pstSimEHplmn->astEhPlmnInfo[i].stPlmnId.ulMnc;
    }

    return VOS_OK;
}
VOS_VOID NAS_MMC_UpdateGURegRlstRPlmnIdInNV(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;                               /* PlMN��ʶ */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    VOS_UINT32                          ulGRplmnChangeFlag;
    VOS_UINT32                          ulWRplmnChangeFlag;
    VOS_UINT32                          ulRatChangeFlag;

    ulGRplmnChangeFlag = VOS_FALSE;
    ulWRplmnChangeFlag = VOS_FALSE;
    ulRatChangeFlag    = VOS_FALSE;

    /* ���ڻ�ȡRPLMN�Ķ���������Ϣ */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* ��ȡ��ǰ�Ľ��뼼�� */
    enCurrRat = NAS_MML_GetCurrNetRatType();

    /* �������һ��ע��ɹ���PLMN,û��Rplmnʱ������ʧ�� */
    if (VOS_FALSE == NAS_MML_GetRPlmn(enCurrRat, &stPlmnId))
    {
        return;
    }

    /* ����ȫ�ֱ����е�LastRPLMN�Ľ��뼼�� */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        ulRatChangeFlag = VOS_TRUE;
        NAS_MML_SetLastRplmnRat(enCurrRat);
    }


    /* ����ȫ�ֱ����е�RPLMN */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stGRplmnInNV);
        ulWRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stWRplmnInNV);
        /* ��֧��˫RPLMN����W��G��RPLMN������ */
        pstRplmnCfgInfo->stGRplmnInNV = stPlmnId;
        pstRplmnCfgInfo->stWRplmnInNV = stPlmnId;

    }
    else
    {
        /* ֧��˫RPLMN, ��ֻ���¶�Ӧ���뼼����RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                            &pstRplmnCfgInfo->stGRplmnInNV);
            pstRplmnCfgInfo->stGRplmnInNV = stPlmnId;

        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnChangeFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,
                                                                 &pstRplmnCfgInfo->stWRplmnInNV);
            pstRplmnCfgInfo->stWRplmnInNV = stPlmnId;
        }
        else
        {
            ;
        }
    }

    if ((VOS_TRUE ==ulRatChangeFlag)
     || (VOS_TRUE == ulWRplmnChangeFlag)
     || (VOS_TRUE == ulGRplmnChangeFlag))
    {
        NAS_MMC_WriteRplmnWithRatNvim();
    }

    return;

}

VOS_VOID NAS_MMC_SaveUserReselPlmnInfo(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatList    = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        /* ����������״̬�£����浱ǰפ��������ID�Ͷ�Ӧ��RAT */
        NAS_MMC_SetUserReselPlmnId( NAS_MML_GetCurrCampPlmnId(),
                                    NAS_MML_GetCurrNetRatType() );
    }
    else
    {
        /* ԭ�����Զ�ģʽ����Ҫ���档
           ԭ�����ֶ�����ģʽ�������Ʒ���״̬��˵���ɵ�PLMN��Ϣ�Ѿ�����,��ʱ����
           Ҫ�ٱ��棬�����ԭ����PLMN ID��Ϣ��� */
        if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
        {
            enRatType    = NAS_MML_GetCurrNetRatType();

            /* ��ȡMML�б���ĵ�ǰMS֧�ֵĽ���ģʽ�ͽ������ȼ� */
            pstPlmnRatList = NAS_MML_GetMsPrioRatList();

            /* ��ȡ�û����õ����ȼ�RAT */
            if (pstPlmnRatList->ucRatNum != 0)
            {
                enRatType = pstPlmnRatList->aucRatPrio[0];
            }

            /* �����Ʒ����£�����HOME PLMN�����û����õ����ȼ�RAT */
            NAS_MMC_SetUserReselPlmnId(&(NAS_MML_GetSimEhplmnList()->astEhPlmnInfo[0].stPlmnId),
                                       enRatType);
        }
    }
}
VOS_VOID  NAS_MMC_SetPlmnRegRejInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    NAS_MML_LAI_STRU                   *pstCurrLai;
    VOS_UINT32                          i;
    VOS_UINT8                           ucCurrCampRac;

    if (VOS_NULL_PTR == pstPlmnRegInfo)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPlmnRegRejInfo:WARNING:pstPlmnRegInfo IS NULL POINTER");
        return;
    }

    /* ��ȡ��ǰ�Ľ��뼼�� */
    enCurrRat     = NAS_MML_GetCurrNetRatType();
    pstCurrLai    = NAS_MML_GetCurrCampLai();
    ucCurrCampRac = NAS_MML_GetCurrCampRac();

    pstPlmnRegInfo->stPlmnId = *pstPlmnId;

    for (i = 0 ; i < NAS_MML_MAX_LAC_LEN ; i++ )
    {
        pstPlmnRegInfo->aucLac[i] = pstCurrLai->aucLac[i];
    }
    pstPlmnRegInfo->ucRac = ucCurrCampRac;

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enWCsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS == enDomain)
        {
            pstPlmnRegInfo->enWPsRegStatus  = enCause;
            return;
        }

        if (NAS_MMC_REG_DOMAIN_PS_CS == enDomain)
        {
            pstPlmnRegInfo->enGCsRegStatus  = enCause;
            pstPlmnRegInfo->enGPsRegStatus  = enCause;
            return;
        }

    }
#if   (FEATURE_ON == FEATURE_LTE)
    else if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
    {
        if (NAS_MMC_REG_DOMAIN_EPS == enDomain)
        {
            pstPlmnRegInfo->enLPsRegStatus  = enCause;
            return;
        }
        if (NAS_MMC_REG_DOMAIN_CS == enDomain)
        {
            pstPlmnRegInfo->enLCsRegStatus = enCause;
            return;
        }
    }
#endif
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_FillPlmnRegInfo: NORMAL: enCurrRat is wrong!");
    }


}
VOS_VOID NAS_MMC_UpdatePlmnRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstPlmnRegRejInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstPlmnRegRejInfo = NAS_MMC_GetPlmnRegRejInfo();

    /* ��ȡע��ԭ���б��ָ�� */
    pstPlmnRegList = pstPlmnRegRejInfo->astPlmnRegInfoList;

    /* �жϵ�ǰ�����Ƿ�����ע���б���   */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmn,
                            pstPlmnRegRejInfo->ucPlmnRegInfoNum, pstPlmnRegList);


    /* ��ǰ������ע�ᱻ���б��� */
    if ( ulIndex < NAS_MML_MIN(pstPlmnRegRejInfo->ucPlmnRegInfoNum ,(NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)))
    {
        /* �����������б��д���,����ע��ԭ��ֵ */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause, (pstPlmnRegList + ulIndex));
        /*lint -e961*/
        /* �ж������Ƿ����ע��ʧ�ܵ�����Ϣ����δ����ע��ʧ�ܵ�����Ϣ���򽫴�����ӱ�����Ϣ����ɾ�� */
        if ( VOS_TRUE == NAS_MMC_IsPlmnRegInfoAllSucc( pstPlmnRegList + ulIndex ) )
        {
            (VOS_VOID)PS_MEM_MOVE(pstPlmnRegList + ulIndex, (pstPlmnRegList + ulIndex + 1),
                (pstPlmnRegRejInfo->ucPlmnRegInfoNum - ulIndex - 1) * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

            /* �����б��еĸ��� */
            pstPlmnRegRejInfo->ucPlmnRegInfoNum--;
        }
        /*lint +e961*/
        return;
    }

    /* �����粻��ע�������ע��ԭ��ֵΪNULL,�򲻱��� */
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == enCause )
    {
        return;
    }

    /* ��ǰ���粻�ڱ�����б��л��б�Ϊ�� */
    if (pstPlmnRegRejInfo->ucPlmnRegInfoNum < NAS_MMC_MAX_REG_PLMN_INFO_NUM)
    {
        /* �б�δ����׷��ע��ԭ���б��� */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause,
                     (pstPlmnRegList + pstPlmnRegRejInfo->ucPlmnRegInfoNum));

        /* �����б��еĸ��� */
        pstPlmnRegRejInfo->ucPlmnRegInfoNum++;
    }
    else
    {
        /* �б�����, ����ļ�¼�ƶ������� */
        (VOS_VOID)PS_MEM_MOVE(pstPlmnRegList, (pstPlmnRegList + 1),
                   (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1) * sizeof(NAS_MMC_PLMN_REG_INFO_STRU));

        /* ����ע��ԭ���б��� */
        NAS_MMC_SetPlmnRegRejInfo(pstPlmn, enDomain, enCause,
              (pstPlmnRegList + (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)));
    }

    return;

}
VOS_VOID NAS_MMC_ConvertHplmnRegStatusToDomainInfo(
    VOS_UINT8                          *pucDomainInfo,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;

    enNetRatType   = NAS_MML_GetCurrNetRatType();
    *pucDomainInfo = NAS_MMC_REG_DOMAIN_NONE;

    switch (enNetRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enGPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS;
                return;
            }
            return;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enWPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS;
                return;
            }
            return;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLCsRegStatus)
             && (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLPsRegStatus))
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_PS_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLCsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_CS;
                return;
            }

            if (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == pstPlmnRegInfo->enLPsRegStatus)
            {
                *pucDomainInfo = NAS_MMC_REG_DOMAIN_EPS;
                return;
            }
            return;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConvertHplmnRegStatusToDomainInfo:invalid rat type");
            return;
    }
}



VOS_VOID NAS_MMC_GetHplmnRejDomainInfo(
    VOS_UINT8                          *pucRejDomainRlst
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* ��ȡ��ǰפ����PLMN */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    /* ���ڻ�ȡHPLMNע�ᱻ�ܵ��б� */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* ��ǰפ��PLMN����HPLMN�б��У���ֱ�ӷ��� */
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
        *pucRejDomainRlst = NAS_MMC_REG_DOMAIN_NONE;

        return;
    }

    /* �жϵ�ǰ�����Ƿ���HPLMNע�ᱻ���б��� */
    ulIndex = NAS_MMC_GetPlmnIndexInRegInfoList(pstCurrPlmn,
                             pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);


    if (ulIndex < NAS_MML_MIN(pstRegRejCtx->ucPlmnRegInfoNum, (NAS_MMC_MAX_REG_PLMN_INFO_NUM - 1)))
    {
        /* ����������HPLMNע�ᱻ���б��У������䱻���� */
        NAS_MMC_ConvertHplmnRegStatusToDomainInfo(pucRejDomainRlst,
                                             &pstRegRejCtx->astPlmnRegInfoList[ulIndex]);

    }
    else
    {
        *pucRejDomainRlst = NAS_MMC_REG_DOMAIN_NONE;
    }

    return;
}
VOS_VOID NAS_MMC_ClearHplmnRejDomainInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    VOS_UINT8                           ucAcceptCnDomain
)
{
    NAS_MMC_PLMN_REG_REJ_CTX_STRU      *pstRegRejCtx       = VOS_NULL_PTR;
    VOS_UINT8                           ucIdx;

    /* ��ȡHPLMNע�ᱻ�ܵ��б� */
    pstRegRejCtx       = NAS_MMC_GetPlmnRegRejInfo();

    /* ��HPLMNע�ᱻ���б���δ���ҵ���ǰפ��PLMN����ֱ�ӷ��� */
    ucIdx = (VOS_UINT8)NAS_MMC_GetPlmnIndexInRegInfoList(pstPlmn,
                            pstRegRejCtx->ucPlmnRegInfoNum, pstRegRejCtx->astPlmnRegInfoList);

    if (ucIdx >= pstRegRejCtx->ucPlmnRegInfoNum)
    {
        return;
    }

    /* �����Ӧ��ı�����Ϣ */
    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                      ucAcceptCnDomain, NAS_MML_REG_FAIL_CAUSE_NULL);

}
VOS_UINT32 NAS_MMC_GetAbortEventType_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortEventType_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ulAbortEventType);
}
VOS_VOID NAS_MMC_SetAbortEventType_BgPlmnSearch(
    VOS_UINT32                          ulAbortEventType
)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortEventType_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ulAbortEventType = ulAbortEventType;
}
NAS_MMC_ABORT_FSM_TYPE_UINT8 NAS_MMC_GetAbortType_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortType_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.enAbortType);
}
VOS_VOID NAS_MMC_SetAbortType_BgPlmnSearch(
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortType
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortType_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.enAbortType = enAbortType;
}
VOS_UINT8 NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedSndSysInfo;
}
VOS_VOID NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(
    VOS_UINT8                           ucNeedSndSysInfo
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedSndSysInfo = ucNeedSndSysInfo;
}
VOS_UINT8 NAS_MMC_GetRelRequestFlag_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRelRequestFlag_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucRelRequestFlg);
}
VOS_VOID NAS_MMC_SetRelRequestFlag_BgPlmnSearch(
    VOS_UINT8                           ucRelRequestFlg
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ  */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH !=NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRelRequestFlag_BgPlmnSearch,ERROR:FsmId Error");
        return ;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucRelRequestFlg = ucRelRequestFlg;
}
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag);
}
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucWaitFlag
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag |= ucWaitFlag;
}
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucRegDomain
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag &= ~ucRegDomain;
}
VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.ucWaitRegRsltFlag = NAS_MMC_WAIT_REG_RESULT_IND_NULL;
}
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enCsRegAdditionalAction);
}
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enCsRegAdditionalAction = enCsAddtionalAction;
}
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
    }

    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enPsRegAdditionalAction);
}
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAddtionalAction
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmnRegInfo.enPsRegAdditionalAction = enPsAddtionalAction;
}
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn);
}
VOS_VOID NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn.stPlmnId = *pstPlmnId;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stCurHighPrioPlmn.enRat    = enRat;
}
NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetPreCampPlmn_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn);
}
VOS_VOID NAS_MMC_SetPreCampPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.stPlmnId = *pstPlmnId;
    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.enRat    = enRat;
}
VOS_VOID NAS_MMC_SetPreCampPlmnRat_BgPlmnSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* �����ǰ״̬������ BG PLMN SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreCampPlmn_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreCampPlmn.enRat    = enRat;
}
NAS_MML_EQUPLMN_INFO_STRU* NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo);
}
VOS_VOID NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch,ERROR:FsmId Error");

        return;
    }

    /* ��һ��EQUPLMN(��RPLMN)�뵱ǰפ��������ͬ, �򱣴浱ǰפ�������EQUPLMN��״̬�������� */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurrCampPlmnId,
                                                       &(pstEquPlmnInfo->astEquPlmnAddr[0])))
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo = *pstEquPlmnInfo;
    }
    else
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo.ucEquPlmnNum = 0x1;
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.stPreEquPlmnInfo.astEquPlmnAddr[0] = *pstCurrCampPlmnId;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus
)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg = VOS_TRUE;
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg = VOS_FALSE;
    return;
}
VOS_UINT32 NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucPreLteDisableFlg;
}
VOS_VOID NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_UINT8 ucNeedEnableLteFlg)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedEnableLteFlg = ucNeedEnableLteFlg;
    return;
}
VOS_UINT32 NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch(VOS_VOID)
{
    /* �����ǰ״̬������ BG_PLMN_SEARCH, �쳣��ӡ */
    if (NAS_MMC_FSM_BG_PLMN_SEARCH != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stBgPlmnSearchCtx.ucNeedEnableLteFlg;
}
#endif
VOS_VOID NAS_MMC_SetFirstStartHPlmnTimerFlg(
    VOS_UINT8                           ucFirstStartHPlmnTimer
)
{
    g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucFirstStartHPlmnTimerFlg = ucFirstStartHPlmnTimer;
}


VOS_UINT8 NAS_MMC_GetFirstStartHPlmnTimerFlg(VOS_VOID)
{
    return g_stNasMmcCtx.stHighPrioPlmnSearchCtrl.ucFirstStartHPlmnTimerFlg;
}


VOS_UINT32  NAS_MMC_GetHplmnTimerLen( VOS_VOID )
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg = VOS_NULL_PTR;
    VOS_UINT32                          ulHplmnTimerLen;

    pstBgSearchCfg = NAS_MML_GetBgSearchCfg();

    if (VOS_TRUE == NAS_MMC_GetFirstStartHPlmnTimerFlg())
    {
        /* �״���������NV��en_NV_Item_HPlmnFirstTimer�ж�ȡ��Ĭ��Ϊ2���� */
        ulHplmnTimerLen = pstBgSearchCfg->ulFirstStartHplmnTimerLen;
    }
    else
    {
        ulHplmnTimerLen = NAS_MML_GetSimHplmnTimerLen();
    }

    /* H3G����: VPLMN�·��״���HPLMN���ڿ���NV������ */
    if (VOS_TRUE == pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ucNvimActiveFlg)
    {
        if (VOS_TRUE != NAS_MMC_GetFirstStartHPlmnTimerFlg())
        {
            /* ���״���������NV: en_NV_Item_SearchHplmnTtimerValue�л�ȡ������USIM�ļ���
               ��ȡֵ��NV: en_NV_Item_Default_Max_Hplmn_Srch_Peri��ȡ��ֵ�Ƿ���Ч */
            ulHplmnTimerLen = pstBgSearchCfg->stNonFirstHplmnTimerPeriod.ulNonFirstHplmnTimerLen;
        }
    }

    return ulHplmnTimerLen;
}





/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCacheNum
 ��������  : ��ȡ��ǰ���ڵĻ������
 �������  : ��
 �������  : ��ǰ���ڵĻ������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��29��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCacheNum( VOS_VOID )
{
    NAS_MMC_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = NAS_MMC_GetCachMsgBufferAddr();

    return pstMsgQueue->ucCacheMsgNum;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetFsmStackPopFlg
 ��������  : ����״̬��ջpop��־
 �������  : ucStachPopFlg:ջpop��־
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_SetFsmStackPopFlg(
    VOS_UINT16                          ucStachPopFlg
)
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStachPopFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFsmStackPopFlg
 ��������  : ��ȡ״̬��ջpop��־
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16  NAS_MMC_GetFsmStackPopFlg( VOS_VOID )
{
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsFsmEntryEventType
 ��������  : �ж���Ϣ�Ƿ���״̬�������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsFsmEntryEventType(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < (sizeof(g_aulFsmEntryEventType) / sizeof(VOS_UINT32)) ; i++ )
    {
        if ( ulEventType == g_aulFsmEntryEventType[i] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32  NAS_MMC_GetBufferedPlmnSearchFlg( VOS_VOID )
{

    return g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.ulPlmnSearchFlg;
}


NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32  NAS_MMC_GetBufferedPlmnSearchScene( VOS_VOID )
{

    return g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.enPlmnSearchScene;
}



VOS_VOID NAS_MMC_SetBufferedPlmnSearchInfo(
    VOS_UINT32                                              ulPlmnSearchFlg,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.ulPlmnSearchFlg   = ulPlmnSearchFlg;
    g_stNasMmcCtx.stPlmnSearchCtrl.stBufferedPlmnSearchInfo.enPlmnSearchScene = enPlmnSearchScene;
}



NAS_MMC_SRV_STA_CHNG_INFO_STRU* NAS_MMC_GetSrvStaChngInfo( VOS_VOID )
{
    return &g_stNasMmcCtx.stPlmnSearchCtrl.stLastSrvStaInfo;
}


NAS_MML_PLMN_ID_STRU* NAS_MMC_GetLastCampedPlmnid( VOS_VOID )
{
    return &g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.stPlmnId;
}


/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastCampedPlmnRat
 ��������  : ��ȡ���פ����PLMN ���뼼��
 �������  :
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��09��
   ��    ��   : c00318887
   �޸�����   : Ԥ��Ƶ�������Ż�

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetLastCampedPlmnRat( VOS_VOID )
{
    return g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.enRat;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLastCampedPlmnRat
 ��������  : �������פ����PLMN ���뼼��
 �������  :
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��09��
   ��    ��   : c00318887
   �޸�����   : Ԥ��Ƶ�������Ż�

*****************************************************************************/
VOS_VOID NAS_MMC_SetLastCampedPlmnRat(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enRat)
{
    g_stNasMmcCtx.stPlmnSearchCtrl.stLastCampedPlmnId.enRat = enRat;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
VOS_VOID NAS_MMC_SaveLastCampedPlmnWithRat(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_ID_STRU             *pstLastPlmnid;

    pstLastPlmnid = NAS_MMC_GetLastCampedPlmnid();

    pstLastPlmnid->ulMcc = ulMcc;
    pstLastPlmnid->ulMnc = ulMnc;

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
    NAS_MMC_SetLastCampedPlmnRat(enRat);
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */
    
    return;
}
/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */





VOS_UINT32  NAS_MMC_IsFsmIdInFsmStack(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    VOS_UINT32                          i;
    NAS_MMC_FSM_STACK_STRU             *pstFsmStack;

    pstFsmStack = NAS_MMC_GetFsmStackAddr();

    for (i = 0; i < pstFsmStack->usStackDepth; i++)
    {
        if (enFsmId == pstFsmStack->astFsmStack[i].enFsmId)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

VOS_UINT32 NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn(VOS_VOID)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsCurrService;


    pstSimStatus     = NAS_MML_GetSimStatus();
    enCsCurrService  = NAS_MMC_GetCsServiceStatus();
    enPsCurrService  = NAS_MMC_GetPsServiceStatus();

    /* �û�ָ����ǰפ��Plmn,CS/PSͬʱ��Ϊ��������ʱ������Ҫ�������� */
    if (( NAS_MMC_NORMAL_SERVICE == enCsCurrService)
     && ( NAS_MMC_NORMAL_SERVICE == enPsCurrService))
    {
        return VOS_FALSE;
    }

    /* �û�ָ����ǰפ��Plmn,CS��������,PS������ע���PS����Чʱ������Ҫ�������� */
    if ((( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        ||( VOS_FALSE == pstSimStatus->ucSimPsRegStatus))
      &&(NAS_MMC_NORMAL_SERVICE == enCsCurrService))
    {
        return VOS_FALSE;
    }

    /* �û�ָ����ǰפ��Plmn,PS��������,CS������ע���CS����Чʱ������Ҫ�������� */
    if (( (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        ||( VOS_FALSE == pstSimStatus->ucSimCsRegStatus))
      &&(NAS_MMC_NORMAL_SERVICE == enPsCurrService))
    {
        return VOS_FALSE;
    }

    /* ��������£���Ҫ�������� */
    return VOS_TRUE;

}







VOS_UINT32 NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();
    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();

    /* ���ͬʱ֧��FDD��TDD����ʱ��ʱ��Ϊ301s */
    if ( (VOS_TRUE == ulSupportFddFlg)
      && (VOS_TRUE == ulSupportTddFlg) )
    {
        return TI_NAS_MMC_WAIT_UTRAN_PLMN_SEARCH_CNF_LEN;
    }

    /* ���ֻ֧��FDD��TDD�е�һ������ʱ��ʱ��Ϊ150s */
    if (ulSupportFddFlg != ulSupportTddFlg)
    {
        return TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN;
    }
#endif

    return TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN;

}












VOS_VOID  NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection(
    VOS_UINT8                           ucSrvTriggerPlmnSearchFlag
)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucSrvTrigPlmnSearchFlag = ucSrvTriggerPlmnSearchFlag;
    return;
}
VOS_UINT8 NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection(VOS_VOID)
{
    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.ucSrvTrigPlmnSearchFlag;
}
VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerLen( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;
    VOS_UINT32                                              ulHplmnTimerLen;
    VOS_UINT32                                              ulCount;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();
    ulCount                 = NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();

    if (ulCount < pstHighRatHplmnTimerCfg->ulFirstSearchTimeCount)
    {
        ulHplmnTimerLen = pstHighRatHplmnTimerCfg->ulFirstSearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* ��Ҫת��Ϊ���� */
    }
    else
    {
        ulHplmnTimerLen = pstHighRatHplmnTimerCfg->ulNonFirstSearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* ��Ҫת��Ϊ���� */
    }

    return ulHplmnTimerLen;
}


VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerRetryLen( VOS_VOID )
{
    NAS_MML_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU             *pstHighRatHplmnTimerCfg = VOS_NULL_PTR;

    pstHighRatHplmnTimerCfg = NAS_MML_GetHighPrioRatHplmnTimerCfg();

    return pstHighRatHplmnTimerCfg->ulRetrySearchTimeLen * NAS_MML_ONE_THOUSAND_MILLISECOND;/* ��Ҫת��Ϊ���� */
}
VOS_UINT32  NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount;
}
VOS_VOID    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount= 0;
}
VOS_VOID    NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID)
{
    /* �����ǰ״̬������L1 MAIN */
    if (NAS_MMC_FSM_L1_MAIN != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main,ERROR:FsmId Error");

        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stL1MainCtx.ulCurHighRatHplmnTimerCount++;
}
NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU* NAS_MMC_GetDPlmnNPlmnCfgInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDplmnNplmnInfo);
}


VOS_VOID  NAS_MMC_InitUserDPlmnNPlmnInfo(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
)
{
    VOS_UINT32                          i;

    pstDPlmnNPlmnCfgInfo->ucActiveFlg    = VOS_FALSE;
    pstDPlmnNPlmnCfgInfo->ucCMCCHplmnNum= 0;
    pstDPlmnNPlmnCfgInfo->ucUNICOMHplmnNum = 0;
    pstDPlmnNPlmnCfgInfo->ucCTHplmnNum = 0;

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_HPLMN_NUM; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astCMCCHplmnList[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astCMCCHplmnList[i].ulMnc   = NAS_MML_INVALID_MNC;
    }
    for ( i = 0 ; i < NAS_MMC_MAX_CFG_HPLMN_NUM; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astUNICOMHplmnList[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astUNICOMHplmnList[i].ulMnc   = NAS_MML_INVALID_MNC;
    }
    for ( i = 0 ; i < NAS_MMC_MAX_CFG_HPLMN_NUM; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astCTHplmnList[i].ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astCTHplmnList[i].ulMnc   = NAS_MML_INVALID_MNC;
    }

    pstDPlmnNPlmnCfgInfo->usDplmnListNum =0;
    pstDPlmnNPlmnCfgInfo->usNplmnListNum =0;

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_DPLMN_NUM ; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstDPlmnNPlmnCfgInfo->astDPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_NONE;
    }

    for ( i = 0 ; i < NAS_MMC_MAX_CFG_NPLMN_NUM ; i++ )
    {
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc   = NAS_MML_INVALID_MCC;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc   = NAS_MML_INVALID_MNC;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].stSimPlmnWithRat.usSimRat         = NAS_MML_INVALID_SIM_RAT;
        pstDPlmnNPlmnCfgInfo->astNPlmnList[i].enRegDomain                       = NAS_MMC_REG_DOMAIN_NONE;
    }

    return;
}



VOS_UINT8 NAS_MMC_GetRoamPlmnSelectionSortActiveFlg( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucRoamPlmnSelectionSortFlg);
}


VOS_VOID NAS_MMC_SetRoamPlmnSelectionSortActiveFlg(
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stRoamPlmnSeletionSortCfgInfo.ucRoamPlmnSelectionSortFlg = ucRoamPlmnSelectionSortFlg;
}



NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetGeoPlmn(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stGetGeoInfo.stGeoPlmn);
}


VOS_VOID NAS_MMC_SetGeoPlmn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstGeoPlmn
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stGetGeoInfo.stGeoPlmn = *pstGeoPlmn;
    return;
}


NAS_MMC_HISTORY_SEARCH_INFO_STRU* NAS_MMC_GetHistorySearchInfo( VOS_VOID )
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stHistorySearchInfo);
}



VOS_UINT8 NAS_MMC_GetNvHistorySearchActiveFlg( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stHistorySearchInfo.ucActiveFlg);
}


VOS_UINT32 NAS_MMC_GetHistorySearchFirstTimerLen( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stHistorySearchInfo.ulFirstTimerLen);
}


VOS_UINT32 NAS_MMC_GetHistorySearchSecondTimerLen( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stHistorySearchInfo.ulSecondTimerLen);
}


VOS_VOID NAS_MMC_InitHistorySearchInfo(
    NAS_MMC_HISTORY_SEARCH_INFO_STRU   *pstHistoryInfo
)
{
    PS_MEM_SET(pstHistoryInfo->aucReserve, 0, sizeof(pstHistoryInfo->aucReserve));

    /* Ĭ�ϲ�����history������ */
    pstHistoryInfo->ucActiveFlg                         = VOS_FALSE;
    pstHistoryInfo->ulFirstTimerLen                     = 0;
    pstHistoryInfo->ulSecondTimerLen                    = 0;
    
    return;
}
VOS_VOID NAS_MMC_InitGetGeoInfo(
    NAS_MMC_GET_GEO_INFO_STRU          *pstGetGeoInfo
)
{
    /* ��ʼ��GEO PLMN */
    NAS_MMC_InitGeoPlmn();

    return;
}
VOS_VOID NAS_MMC_InitGeoPlmn(VOS_VOID)
{

    NAS_MML_PLMN_WITH_RAT_STRU                              stGeoPlmn;

    PS_MEM_SET(&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    stGeoPlmn.enRat             = NAS_MML_NET_RAT_TYPE_BUTT;
    stGeoPlmn.stPlmnId.ulMcc    = NAS_MML_INVALID_MCC;
    stGeoPlmn.stPlmnId.ulMnc    = NAS_MML_INVALID_MNC;

    NAS_MMC_SetGeoPlmn(&stGeoPlmn);

    return;
}


NAS_MML_PLMN_ID_STRU *NAS_MMC_GetDisabledLtePlmnId(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId);
}


VOS_VOID NAS_MMC_SetDisabledLtePlmnId(
    NAS_MML_PLMN_ID_STRU              *pstPlmnId
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMcc = pstPlmnId->ulMcc;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMnc = pstPlmnId->ulMnc;
    return;
}


VOS_VOID NAS_MMC_ClearDisabledLtePlmnId(VOS_VOID)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMcc = NAS_MML_INVALID_MCC;
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.stDisabledLtePlmnId.ulMnc = NAS_MML_INVALID_MNC;
    return;
}


VOS_UINT8 NAS_MMC_GetEnableLteTimerExpireFlag( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucEnableLteTimerExpireFlag);
}


VOS_VOID NAS_MMC_SetEnableLteTimerExpireFlag(
    VOS_UINT8                           ucEnableLteTimerExpireFlag
)
{
    NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucEnableLteTimerExpireFlag = ucEnableLteTimerExpireFlag;
    return;
}




NAS_MMC_REG_CONTROL_ENUM_UINT8 NAS_MMC_GetRegCtrl( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enRegCtrl);
}


VOS_VOID NAS_MMC_SetRegCtrl(
    NAS_MMC_REG_CONTROL_ENUM_UINT8      enRegCtrl
)
{
    (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.enRegCtrl) = enRegCtrl;
}


VOS_UINT8 NAS_MMC_GetAsAnyCampOn( VOS_VOID )
{
    return (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucAsAnyCampOn);
}


VOS_VOID NAS_MMC_SetAsAnyCampOn(
    VOS_UINT8                          ucAsAnyCampOn
)
{
    (NAS_MMC_GetMmcCtxAddr()->stPlmnSearchCtrl.ucAsAnyCampOn) = ucAsAnyCampOn;
}



VOS_VOID NAS_MMC_SaveRegReqNCellInfo(
    MSCC_MMC_REG_CELL_INFO_STRU         *pstCellInfo
)
{
    NAS_MMC_NCELL_SEARCH_INFO_STRU     *pstMmcNcellSearchInfo = VOS_NULL_PTR;

    /* Ŀǰ��֧��ע��������Я��LTE��NCell��Ϣ */
    if (NAS_MML_NET_RAT_TYPE_LTE != pstCellInfo->ucRat)
    {
        return;
    }

    /* ����NCELL��Ϣ */
    pstMmcNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();
    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteArfcnNum       = 1;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    pstMmcNcellSearchInfo->stLteNcellInfo.aulLteArfcnList[0]  = pstCellInfo->ulArfcn;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    pstMmcNcellSearchInfo->stLteNcellInfo.ucLteCellNum        = NAS_MML_MIN(pstCellInfo->ucCellNum, NAS_MMC_LTE_CELL_MAX_NUM);
    PS_MEM_CPY(pstMmcNcellSearchInfo->stLteNcellInfo.ausLteCellList, pstCellInfo->ausCellId,
               ((pstMmcNcellSearchInfo->stLteNcellInfo.ucLteCellNum) * sizeof(VOS_UINT16)));

    pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum = NAS_MML_MIN(pstCellInfo->ucPlmnNum, NAS_MML_MAX_EQUPLMN_NUM);
    PS_MEM_CPY(pstMmcNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr, pstCellInfo->astPlmnId,
               ((pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum) * sizeof(NAS_MML_PLMN_ID_STRU)));

    return;
}

/* Added by y00307564 for CDMA Iteration 8 2015-2-6 begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPrefPlmnPara
 ��������  : ���ڴ�MMC�л�ȡMMC��ȫ�ֱ�����Ϣ
 �������  : MMC_MMA_SHARE_PARA_ST *pMmcPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32  VOS_FALSE:��ʾʧ�ܣ�VOS_TRUE:��ʾ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPrefPlmnPara(
    MMC_MMA_SHARE_PARA_ST              *pstMmcPara
)
{
    /* ������Ч���ж� */
    if (VOS_NULL_PTR == pstMmcPara)
    {
        /* ָ��Ϊ��ָ�룬���ش��� */
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:NULL PTR ");
        return VOS_FALSE;
    }

    if (pstMmcPara->enMmaParaType >= EN_MMC_BEGIN_SET_MMC_PARA)
    {
        /* ���Ͳ�������,���ش���ֵ */
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:PARA TYPE WRONG");
        return VOS_FALSE;
    }

    switch (pstMmcPara->enMmaParaType)
    {
        case EN_MMC_OPLMN_INFO:
            NAS_MMC_GetOperPlmnInfoForMscc(&(pstMmcPara->u.stOPlmnInfo));
            break;

        case EN_MMC_UPLMN_INFO:
            NAS_MMC_GetUserPlmnInfoForMscc(&(pstMmcPara->u.stUPlmnInfo));
            break;

        case EN_MMC_HPLMN_INFO:
            NAS_MMC_GetHPlmnInfoForMscc(&(pstMmcPara->u.stHPlmnInfo));
            break;


        /* PLMNSEL �� UPLMN ֻ���ܳ���һ�����ʶ����� stUPlmnInfo �� */
        case EN_MMC_PLMNSEL_INFO:
            NAS_MMC_GetSelPlmnInfoForMscc(&(pstMmcPara->u.stUPlmnInfo));
            break;

        default:
            /* ��ӡ������Ϣ,���س����־ */
            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_GetPrefPlmnPara:WARNING:PARA TYPE WRONG IN DEFAULT");
            return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetPrefPlmnPara
 ��������  : ��������MMC��ȫ�ֱ�����Ϣ
 �������  : MMC_MMA_SHARE_PARA_ST *pMmcPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32  VOS_FALSE:��ʾʧ�ܣ�VOS_TRUE:��ʾ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_SetPrefPlmnPara(
    MMC_MMA_SHARE_PARA_ST              *pstMmcPara
)
{
    VOS_UINT32                          ulI = 0;
    NAS_MML_SIM_SELPLMN_INFO_STRU      *pstSelPlmn  = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU     *pstUserPlmn = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMmcPara)
    {
        /* ָ��Ϊ��ָ�룬���ش��� */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:Set Para Point is NULL");
        return VOS_FALSE;
    }

    pstUserPlmn = NAS_MML_GetSimUserPlmnList();
    pstSelPlmn  = NAS_MML_GetSimSelPlmnList();

    if ((pstMmcPara->enMmaParaType < EN_MMC_BEGIN_SET_MMC_PARA)
      || (pstMmcPara->enMmaParaType > EN_MMC_END_SET_MMC_PARA))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:PARA TYPE WRONG");
        return VOS_FALSE;
    }

    switch (pstMmcPara->enMmaParaType)
    {
        case EN_MMC_SET_UPLMN_INFO:
             pstUserPlmn->ucUserPlmnNum      = (VOS_UINT8)pstMmcPara->u.stUPlmnInfo.usCurPlmnNum;
             for (ulI = 0; ulI < pstMmcPara->u.stUPlmnInfo.usCurPlmnNum ; ulI++)
             {
                 pstUserPlmn->astUserPlmnInfo[ulI].stPlmnId.ulMcc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMcc;
                 pstUserPlmn->astUserPlmnInfo[ulI].stPlmnId.ulMnc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMnc;
                 pstUserPlmn->astUserPlmnInfo[ulI].usSimRat       = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].usRaMode;
             }

             break;

        case  EN_MMC_SET_PLMNSEL_INFO:
            pstSelPlmn->ucSelPlmnNum    = (VOS_UINT8)pstMmcPara->u.stUPlmnInfo.usCurPlmnNum;
            for (ulI = 0; ulI < pstMmcPara->u.stUPlmnInfo.usCurPlmnNum ; ulI++)
            {
                pstSelPlmn->astPlmnId[ulI].ulMcc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMcc;
                pstSelPlmn->astPlmnId[ulI].ulMnc = pstMmcPara->u.stUPlmnInfo.astPlmnInfo[ulI].stPlmn.ulMnc;
            }

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SetPrefPlmnPara:WARNING:PARA TYPE WRONG IN DEFAULT");
            return VOS_FALSE;

    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnInfo
 ��������  : ��MMC�л�ȡMMC��ȫ�ֱ�����Ϣ
 �������  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType,
            NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPlmnInfo(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPlmnParaType,
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstPlmnInfo
)
{
    VOS_UINT32                          ulLoop;
    MMC_TAF_PLMN_LIST_INFO_ST          *pstRptMsccSelPlmnList = VOS_NULL_PTR;

    pstRptMsccSelPlmnList = (MMC_TAF_PLMN_LIST_INFO_ST *)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(MMC_TAF_PLMN_LIST_INFO_ST));
    if (VOS_NULL_PTR == pstRptMsccSelPlmnList)
    {
        return VOS_FALSE;
    }

    switch (enPrefPlmnParaType)
    {
        case NAS_MSCC_OPLMN_INFO:
            NAS_MMC_GetOperPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        case NAS_MSCC_UPLMN_INFO:
            NAS_MMC_GetUserPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        case NAS_MSCC_HPLMN_INFO:
            NAS_MMC_GetHPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        /* PLMNSEL �� UPLMN ֻ���ܳ���һ�����ʶ����� stUPlmnInfo �� */
        case NAS_MSCC_PLMNSEL_INFO:
            NAS_MMC_GetSelPlmnInfoForMscc(pstRptMsccSelPlmnList);
            break;

        default:
            /* ��ӡ������Ϣ,���س����־ */
            PS_MEM_FREE(WUEPS_PID_MMC, pstRptMsccSelPlmnList);
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnInfo:WARNING:PARA TYPE WRONG IN DEFAULT ");
            return VOS_FALSE;
    }

    pstPlmnInfo->usPlmnNum = pstRptMsccSelPlmnList->usCurPlmnNum;
    for ( ulLoop = 0; ulLoop < pstRptMsccSelPlmnList->usCurPlmnNum ; ulLoop++ )
    {
        pstPlmnInfo->Plmn[ulLoop].ulMcc = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].stPlmn.ulMcc;
        pstPlmnInfo->Plmn[ulLoop].ulMnc = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].stPlmn.ulMnc;
        NAS_MMC_PlmnId2Bcd(&(pstPlmnInfo->Plmn[ulLoop]));
        pstPlmnInfo->ausPlmnRat[ulLoop] = pstRptMsccSelPlmnList->astPlmnInfo[ulLoop].usRaMode;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstRptMsccSelPlmnList);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecificPlmnTblSize
 ��������  : ��ȡplmn tbl size
 �������  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8            enPrefPLMNType
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetSpecificPlmnTblSize(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType
)
{
    VOS_UINT16                                              usCurPlmnNum;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                         *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_USERPLMN_INFO_STRU                         *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_HPLMN_WITH_RAT_INFO_STRU                   *pstHplmnWithRat = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU                          *pstSelPlmnInfo  = VOS_NULL_PTR;

    usCurPlmnNum = 0;
    switch(enPrefPLMNType)
    {
        case NAS_MSCC_UPLMN_INFO:
            pstUserPlmnList = NAS_MML_GetSimUserPlmnList();
            usCurPlmnNum    = pstUserPlmnList->ucUserPlmnNum;
            break;
        case NAS_MSCC_PLMNSEL_INFO:
            pstSelPlmnInfo  = NAS_MML_GetSimSelPlmnList();
            usCurPlmnNum    = pstSelPlmnInfo->ucSelPlmnNum;
            break;
        case NAS_MSCC_OPLMN_INFO:
            pstOperPlmnList = NAS_MML_GetSimOperPlmnList();
            usCurPlmnNum    = pstOperPlmnList->usOperPlmnNum;
            break;
        case NAS_MSCC_HPLMN_INFO:
            pstHplmnWithRat = NAS_MML_GetSimHplmnWithRatList();
            usCurPlmnNum    = pstHplmnWithRat->ucHPlmnWithRatNum;
            break;
        default:
            break;
    }

    return usCurPlmnNum;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePlmnInfo
 ��������  : ����pref plmn
 �������  : VOS_UINT16                          usEfId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnInfo(
    VOS_UINT16                          usEfId
)
{
    MMC_MMA_SHARE_PARA_ST              *pstMsccPara;
    VOS_UINT16                          usIndex;
    MMC_MODIFY_PLMN_INFO_STRU          *pstPrefPlmnCtx;

    pstMsccPara = (MMC_MMA_SHARE_PARA_ST *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                            sizeof(MMC_MMA_SHARE_PARA_ST));

    if (VOS_NULL_PTR == pstMsccPara)
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MMC_UpdatePlmnInfo: Alloc memory fail.");
        return ;
    }

    if (USIMM_GSM_EFPLMNSEL_ID == usEfId ) /* EFPLMNsel */
    {
        pstMsccPara->enMmaParaType = EN_MMC_PLMNSEL_INFO;
    }
    else if ((USIMM_USIM_EFPLMNWACT_ID == usEfId) /* EFPLMNwAcT */
         || ((USIMM_GSM_EFPLMNWACT_ID  == usEfId)))
    {
        pstMsccPara->enMmaParaType = EN_MMC_UPLMN_INFO;
    }
    else if ((USIMM_USIM_EFOPLMNWACT_ID == usEfId)
          || (USIMM_GSM_EFOPLMNWACT_ID  == usEfId)) /* EFOPLMNwAcT */
    {
        pstMsccPara->enMmaParaType = EN_MMC_OPLMN_INFO;
    }
    else
    {
        pstMsccPara->enMmaParaType = EN_MMC_HPLMN_INFO;
    }

    pstPrefPlmnCtx = NAS_MMC_GetPrefPlmnCtxAddr();

    usIndex = pstPrefPlmnCtx->usIndex;

    if (usIndex >= NAS_MML_MAX_USERPLMN_NUM)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstMsccPara);
        return ;
    }

    (VOS_VOID)NAS_MMC_GetPrefPlmnPara(pstMsccPara);

    if ( (USIMM_GSM_EFPLMNSEL_ID   == usEfId ) /* EFPLMNsel */
      || (USIMM_USIM_EFPLMNWACT_ID == usEfId)
      || (USIMM_GSM_EFPLMNWACT_ID  == usEfId)) /* EFPLMNwAcT */
    {
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stUPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;

        /* UPLMN��Ҫ���и��� */
        NAS_MMC_SndMmcUpdateUplmnNotify();
    }
    else if ((USIMM_USIM_EFOPLMNWACT_ID == usEfId)
          || (USIMM_GSM_EFOPLMNWACT_ID  == usEfId)) /* EFOPLMNwAcT */
    {
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stOPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;

    }
    else
    {
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMcc = pstPrefPlmnCtx->stPlmnId.ulMcc;
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn.ulMnc = pstPrefPlmnCtx->stPlmnId.ulMnc;
        NAS_MMC_PlmnId2NasStyle(&(pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].stPlmn));
        pstMsccPara->u.stHPlmnInfo.astPlmnInfo[usIndex].usRaMode     = pstPrefPlmnCtx->PlmnRat;
    }


    if (EN_MMC_UPLMN_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_UPLMN_INFO;
    }
    else if (EN_MMC_PLMNSEL_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_PLMNSEL_INFO;
    }
    else if (EN_MMC_OPLMN_INFO == pstMsccPara->enMmaParaType)
    {
        pstMsccPara->enMmaParaType = EN_MMC_SET_OPLMN_INFO;
    }
    else
    {
        pstMsccPara->enMmaParaType = MMC_MMA_PARA_TYPE_BUTT;
    }

    (VOS_VOID)NAS_MMC_SetPrefPlmnPara(pstMsccPara);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsccPara);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_QryPrefPlmnId
 ��������  : ��ѯpref plmn
 �������  : NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8   enPrefPLMNType,
             VOS_UINT32                          ulFromIndex,
             VOS_UINT32                          ulPlmnNum,
             NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU  *pstPlmnInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_QryPrefPlmnId(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8       enPrefPLMNType,
    VOS_UINT32                              ulFromIndex,
    VOS_UINT32                              ulPlmnNum,
    NAS_MSCC_CPOL_PLMN_NAME_LIST_STRU      *pstPlmnInfo
)
{
    VOS_UINT32                                              i;
    NAS_MSCC_PIF_USER_PLMN_LIST_STRU                       *pstOrgPlmnInfo;

    pstOrgPlmnInfo = (NAS_MSCC_PIF_USER_PLMN_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOrgPlmnInfo)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pstOrgPlmnInfo, 0x00, sizeof(NAS_MSCC_PIF_USER_PLMN_LIST_STRU));

    /* ��ȡ���������б� */
    if (VOS_TRUE != NAS_MMC_GetPlmnInfo(enPrefPLMNType, pstOrgPlmnInfo))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstOrgPlmnInfo);

        return VOS_FALSE;
    }

    pstPlmnInfo->ulPlmnNum = pstOrgPlmnInfo->usPlmnNum;

    for (i = 0; i < ulPlmnNum; i++ )
    {
        pstPlmnInfo->ausPlmnRat[i]                         = pstOrgPlmnInfo->ausPlmnRat[(i + ulFromIndex)];
        pstPlmnInfo->astPlmnName[i].stOperatorPlmnId.ulMcc = pstOrgPlmnInfo->Plmn[(i + ulFromIndex)].ulMcc;
        pstPlmnInfo->astPlmnName[i].stOperatorPlmnId.ulMnc = pstOrgPlmnInfo->Plmn[(i + ulFromIndex)].ulMnc;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstOrgPlmnInfo);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPrefPlmnCtx
 ��������  : ��ʼ������pref plmn��������������
 �������  : MMC_MODIFY_PLMN_INFO_STRU          *pstPreflmnInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��15��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitPrefPlmnCtx(
    MMC_MODIFY_PLMN_INFO_STRU          *pstPreflmnInfo
)
{
    pstPreflmnInfo->stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
    pstPreflmnInfo->stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    pstPreflmnInfo->usIndex         = 0;
    pstPreflmnInfo->PlmnRat         = NAS_MMC_RAT_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPrefPlmnCtx
 ��������  : ��ʼ������pref plmn��������������
 �������  : ��
 �������  : prefPlmn nas_mmc_ctx�����ĵ�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��15��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
MMC_MODIFY_PLMN_INFO_STRU* NAS_MMC_GetPrefPlmnCtxAddr(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stPreflmnInfo);
}
/* Added by y00307564 for CDMA Iteration 8 2015-2-6 end */

VOS_VOID NAS_MMC_InitDetachReqCtx(
    NAS_MMC_DETACH_REQ_CTX_STRU        *pstDetachReqCtx
)
{
    pstDetachReqCtx->enDetachReason = NAS_MSCC_PIF_DETACH_REASON_BUTT;

    pstDetachReqCtx->enDetachType   = NAS_MSCC_PIF_DETACH_TYPE_BUTT;

    return;
}


NAS_MMC_DETACH_REQ_CTX_STRU *NAS_MMC_GetDetachReqCtxAddr(VOS_VOID)
{
    return &(NAS_MMC_GetMmcCtxAddr()->stDetachReqCtx);
}


VOS_VOID NAS_MMC_InitAttachReqCtx(
    NAS_MMC_ATTACH_REQ_CTX_STRU        *pstAttachReqCtx
)
{
    pstAttachReqCtx->ulOpID = 0;

    return;
}


VOS_UINT32 NAS_MMC_GetAttachReqOpId(VOS_VOID)
{
    return (NAS_MMC_GetMmcCtxAddr()->stAttachReqCtx.ulOpID);
}


VOS_VOID NAS_MMC_SetAttachReqOpId(VOS_UINT32 ulOpId)
{
    NAS_MMC_GetMmcCtxAddr()->stAttachReqCtx.ulOpID = ulOpId;
}

/*lint -restore */

NAS_MMC_FSM_GET_GEO_CTX_STRU* NAS_MMC_GetFsmCtxAddr_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetFsmCtxAddr_GetGeo,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx);
}
NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU* NAS_MMC_GetGeoRatInfoList_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetGeoRatListInfo_GetGeo,ERROR:FsmId Error");
    }

    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.stGetGeoRatInfoList);
}
VOS_UINT8 NAS_MMC_GetAbortFlag_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET_GEO, �쳣��ӡ  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetAbortFlag_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucAbortFlag;
}
VOS_VOID NAS_MMC_SetAbortFlag_GetGeo(
    VOS_UINT8                           ucAbortFlag
)
{
    /* �����ǰ״̬������GET_GEO, �쳣��ӡ  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetAbortFlag_GetGeo,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucAbortFlag = ucAbortFlag;
    return;
}
VOS_UINT8 NAS_MMC_GetNotifyMsccFlag_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET_GEO, �쳣��ӡ  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetNotifyMsccFlag_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucNotifyMsccFlg;
}
VOS_VOID NAS_MMC_SetNotifyMsccFlag_GetGeo(
    VOS_UINT8                           ucNotifyMsccFlg
)
{
    /* �����ǰ״̬������GET_GEO, �쳣��ӡ  */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetNotifyMsccFlag_GetGeo,ERROR:FsmId Error");
        return;
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.ucNotifyMsccFlg = ucNotifyMsccFlg;

    return;
}
NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8 NAS_MMC_GetFsmTaskPhase_GetGeo(VOS_VOID)
{
    /* �����ǰ״̬������GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetTaskPhase_GetGeo,ERROR:FsmId Error");
    }

    return g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.enGetGeoTaskPhase;
}
VOS_VOID NAS_MMC_SetFsmTaskPhase_GetGeo(
    NAS_MMC_GET_GEO_FSM_TASK_PHASE_ENUM_UINT8     enGetGeoTaskPhase
)
{
    /* �����ǰ״̬������GET GEO */
    if (NAS_MMC_FSM_GET_GEO != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_GetTaskPhase_GetGeo,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stGetGeoCtx.enGetGeoTaskPhase = enGetGeoTaskPhase;

    return;
}

/* Added by l00305157 for ROAM_PLMN_SELECTION_OPTIMIZE_2.0, 2015-5-26, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection
 ��������  : ��ȡ��ǰMMC�����ȫ�ֱ����еĵ�NO RF�µ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : l00305157
    �޸�����   : �����ɺ��� ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection(VOS_VOID)
{
    return g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.enPlmnSearchScene;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNoRfPlmnSearchScene_PlmnSelection
 ��������  : ���õ�ǰ��MMC��ȫ�ֱ����б����NO RF�µ���������
 �������  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32:���õ�ǰ��MMC��ȫ�ֱ����б����NO RF�µ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : l00305157
    �޸�����   : �����ɺ��� ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
VOS_VOID NAS_MMC_SetBackUpNoRfPlmnSearchScene_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32             enPlmnSearchScene
)
{
    g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.enPlmnSearchScene = enPlmnSearchScene;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection
 ��������  : ��ȡ��ǰMMC�����ȫ�ֱ����еĵ�NO RF�µ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : l00305157
    �޸�����   : �����ɺ��� ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU* NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection(VOS_VOID)
{
    return &(g_stNasMmcCtx.stBackUpSearchInfo.stNoRFBackUpSearchInfo.astHistorySearchRatInfo[0]);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BackupNoRfSearchInfo_PlmnSelection
 ��������  : ��ȡ�����б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_RAT_SEARCH_INFO_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
NAS_MMC_RAT_SEARCH_INFO_STRU* NAS_MMC_GetSearchRatInfo_PlmnSelection(VOS_VOID)
{
    return &(g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.astSearchRatInfo[0]);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BackupNoRfSearchInfo_PlmnSelection
 ��������  : NO RF�����,����HISTORY���������Լ������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU                   *pstHsirotySearchRatInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;


    /* �����ǰ״̬������PLMN SELECTION */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection,ERROR:FsmId Error");
        return;
    }

    /* ����HISTORY�������� */
    pstSearchRatInfo                    = NAS_MMC_GetSearchRatInfo_PlmnSelection();
    pstHsirotySearchRatInfo             = NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection();

    PS_MEM_SET(pstHsirotySearchRatInfo, 0, sizeof(NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstHsirotySearchRatInfo[i].enRatType                = pstSearchRatInfo[i].enRatType;
        pstHsirotySearchRatInfo[i].ucHistorySearchedFlag    = pstSearchRatInfo[i].ucHistorySearchedFlag;
    }

    /* ������������ */
    enPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    NAS_MMC_SetBackUpNoRfPlmnSearchScene_PlmnSelection(enPlmnSearchScene);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection
 ��������  : NO RF�����,��ȡ����HISTORY�����б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_RAT_SEARCH_INFO_STRU*  astSearchRatInfo
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection(
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo

)
{
    VOS_UINT32                                              i;
    NAS_MMC_RAT_HISTORY_SEARCH_INFO_STRU                   *pstHsirotySearchRatInfo = VOS_NULL_PTR;

    pstHsirotySearchRatInfo             = NAS_MMC_GetBackUpNoRfHistorySearchRatInfo_PlmnSelection();

    /* �ָ�HISTORY�������� */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstSearchRatInfo[i].enRatType             = pstHsirotySearchRatInfo[i].enRatType;
        pstSearchRatInfo[i].ucHistorySearchedFlag = pstHsirotySearchRatInfo[i].ucHistorySearchedFlag;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitNoRFBackUpSearchedInfoCtx
 ��������  : NO RF�����,��ʼ�����ݵ�HISTORY�����б�/��������
 �������  : NAS_MMC_NO_RF_BACK_UP_SEARCH_INFO_STRU*         pstNoRFBackSearchInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : l00305157
    �޸�����   : �����ɺ���  ROAM_PLMN_SELECTION_OPTIMIZE_2.0

*****************************************************************************/
VOS_VOID NAS_MMC_InitNoRFBackUpSearchedInfoCtx(
    NAS_MMC_BACK_UP_SEARCH_INFO_STRU*         pstBackSearchInfo
)
{
    VOS_UINT32                                              i;

    pstBackSearchInfo->stNoRFBackUpSearchInfo.enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].enRatType                        = NAS_MML_NET_RAT_TYPE_BUTT;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].ucHistorySearchedFlag            = VOS_FALSE;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].aucReserved[0]                   = 0;
        pstBackSearchInfo->stNoRFBackUpSearchInfo.astHistorySearchRatInfo[i].aucReserved[1]                   = 0;
    }
    return;
}
/* Added by l00305157 for ROAM_PLMN_SELECTION_OPTIMIZE_2.0, 2015-5-26, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLmmAttachReqSendRslt_PlmnSelection
 ��������  : ��ȡLMM������Attachע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ȫ�ֱ���g_stNasMmcCtx�е�Attachע��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��22��
   ��    ��   : wx270776
   �޸�����   : �����ɺ���

*****************************************************************************/
MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8 NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection( VOS_VOID )
{
    return (g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enLmmAttachClRegStatus);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLmmAttachReqSendRslt_PlmnSelection
 ��������  : ����LMM������Attachע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��22��
   ��    ��   : wx270776
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8                     enLmmAttachClRegStatus
)
{
    /* �����ǰ״̬������PLMN SELECTION�쳣��ӡ */
    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection,ERROR:FsmId Error");
    }

    g_stNasMmcCtx.stCurFsm.unFsmCtx.stPlmnSelectionCtx.stRegRlstInfo.enLmmAttachClRegStatus = enLmmAttachClRegStatus;

    return;
}

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


