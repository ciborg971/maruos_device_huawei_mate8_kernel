/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcMain.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2010��11��15��
  ����޸�   :
  ��������   : NAS MMC��ܴ�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��11��12��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/



#include "PsTypeDef.h"
#include "NasFsm.h"
#include "PsCommonDef.h"
#include "NasMmcTimerMgmt.h"
#include "NasComm.h"
#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "NasMmcFsmMainTbl.h"
#include "NasMmcMain.h"
#include "NasMmcFsmSyscfg.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasMmcFsmInterSysHoTbl.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcFsmSyscfgTbl.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"
#include "NasMmcFsmGetGeoTbl.h"

#include "NasMmcPreProcTbl.h"
#include "NasMmcPreProcAct.h"
#include "NasMmcSndInternalMsg.h"
#include "MM_Share.h"
#include "NasMmcSndOm.h"
/* ɾ��ExtAppMmcInterface.h*/
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"
#include "NasMmcMsgPrioCompare.h"
#include "NasUtranCtrlInterface.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMCMAIN_C


/* PC�طŰ��������ļ��ĺ��� */
/*extern VOS_UINT32 NAS_MM_SndOutsideContextData(VOS_VOID);
 */
/*extern VOS_UINT32 NAS_GMM_SndOutsideContextData(VOS_VOID);
 */


/*lint -save -e958 */

VOS_UINT32  NAS_MMC_IsExistCachedUserSearchMsg( VOS_VOID )
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;

    ulExistFlg = NAS_MMC_IsExistCacheMsg(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                                         &ulCacheMsgIdx);
    if ( VOS_TRUE == ulExistFlg )
    {
        return VOS_TRUE;
    }

    /* �յ��ڲ��������б���������,�ж��Ƿ���ָ���������б�����,���������Ϣ*/
    ulExistFlg = NAS_MMC_IsExistCacheMsg(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                                         &ulCacheMsgIdx);
    if ( VOS_TRUE == ulExistFlg )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedCacheMsg
 ��������  : �Ƚϻ�����Ϣ�뵱ǰ��Ϣ�����ȼ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����Ҫ������
             VOS_TRUE:��Ϣ��Ҫ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��25��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;

    switch (ulEventType)
    {
        /* �յ��ػ�����,������л�����Ϣ,������Ϣ��Ҫ����*/
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ):
            NAS_MMC_ClearAllCacheMsg();
            break;

        /* �յ�MSCC������ָ���������б�����*/
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ):
        case NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ):
        case NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST):

            /* ��������ڲ�ָ������ */
            ulCacheEventType = NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ);
            NAS_MMC_ClearCacheMsg(ulCacheEventType);

            break;

        case NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ):

            /* �յ��ڲ���������,�ж��Ƿ���ָ������,���������Ϣ*/
            ulExistFlg = NAS_MMC_IsExistCachedUserSearchMsg();
            if ( VOS_TRUE == ulExistFlg)
            {
                return VOS_FALSE;
            }

            /* �յ��ڲ���������,�ж��Ƿ����ڲ�����,�����ǰ���������*/

            /* ��������ڲ�ָ������ */
            ulCacheEventType = NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ);
            NAS_MMC_ClearCacheMsg(ulCacheEventType);

            break;

        default:
            break;
    }

    /* Ĭ�Ϸ��ر������Ϣ */
    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_TYPE_UINT8                enAbortType;
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enMsgPrio;


    enAbortType = NAS_MMC_ABORT_BUTT;

    enMsgPrio = NAS_MMC_GetMsgComparePrioRslt(ulEventType, pstMsg, &enAbortType);

    switch ( enMsgPrio )
    {
        /* ����Abort��Ϣ,��ǰ�Ѿ����״̬�� */
        case NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT :

            NAS_MMC_SndAbortFsmMsg(ulEventType, enAbortType);

            NAS_MMC_SaveCacheMsg(ulEventType,
                                (VOS_VOID *) pstMsg);

            return VOS_TRUE;

        /* ������Ϣ */
        case NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE :
            NAS_MMC_SaveCacheMsg(ulEventType,
                              (VOS_VOID *) pstMsg);

            return VOS_TRUE;

        /* ��״̬����Load �µ�״̬�� */
        case NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM :
            return VOS_FALSE;

        /* ��Ϣ��ֱ�Ӷ��� */
        case NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD :
            return VOS_FALSE;

        default:
            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_ProcMsgPrio:invlid msg priority",ulEventType);
            return VOS_FALSE;
    }

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_PostProcessMsg
 ��������  : MMC״̬��������,����ǰ�յ�����Ϣ��L2״̬���������Ϣ���бȽ�,
              �жϺ����Ķ���
 �������  : ulEventType:��Ϣ����
             pstMsg       :��Ϣ����
 �������  : ��
 �� �� ֵ  : ������Ϣ�Ƿ��Ѿ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��3��30��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��11��
   ��    ��   : zhoujun 40661
   �޸�����   : ���¶Ժ����������

*****************************************************************************/
VOS_UINT32  NAS_MMC_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �ж��Ƿ���Ҫ��ϵ�ǰ״̬�� */
    if (VOS_TRUE == NAS_MMC_ProcMsgPrio(ulEventType, pstMsg))
    {
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_PostProcessMsg:ulEventType", ulEventType);

        return VOS_TRUE;
    }


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_MsgPreProcess
 ��������  : MMC��ϢԤ����
 �������  : ulEventType:��Ϣ����
              pMsg       :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
              VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc;
    VOS_UINT32                          ulRet;

    /* ��ϢԤ���� */

    NAS_INFO_LOG1(WUEPS_PID_MMC,"NAS_MMC_PreProcessMsg", ulEventType);

    pstFsmDesc = NAS_MMC_GetPreFsmDescAddr();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, NAS_MMC_L1_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* Ԥ������Ϣ,��Ϊ������Ϣ,һ��ΪԤ��������ͷ���,����һ��ΪԤ����
        ������,��Ȼ��Ҫ���е�״̬���м�������,��˴˴�ֱ��ͨ����������Ԥ��
        ��������Ƿ���Ҫ����״̬������*/
        ulRet = (*pActFun) ( ulEventType, (struct MsgCB*)pstMsg);
        return ulRet;
    }

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��    : NAS_MMC_FSM_ProcessEvent
 ��������    : ״̬�����¼�������
 �������    :
               ulCurState :��ǰ״̬
               ulEventType:�����¼�
               ulMsgID    :��ϢID
               pRcvMsg    :��Ϣָ��
 �������    :
 ����ֵ      : VOS_UINT32:�����Ƿ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��13��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��4��19��
    ��    ��   : zhoujun /40661
    �޸�����   : ��������״̬�������޸�
 *****************************************************************************/
VOS_UINT32 NAS_MMC_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc;
    VOS_UINT32                          ulRet;

    NAS_INFO_LOG2(WUEPS_PID_MMC,"NAS_MMC_FSM_ProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = NAS_MMC_GetCurFsmDesc();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* ������ص��¼���������Ϊ��,�����������¼����� */
        ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
        NAS_INFO_LOG1(WUEPS_PID_MMC,"NAS_MMC_FSM_ProcessEvent", ulRet);
        return VOS_TRUE;
    }

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcessMsgInFsm
 ��������  : ��Ϣ״̬������
 �������  : ulEventType :  ��Ϣ����+PID
              pMsg        :  ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ϣ�Ƿ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��15��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    NAS_MMC_FSM_CTX_STRU               *pstCurFsm;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* ��ȡ��ǰMMC�Ķ���״̬ */
    pstCurFsm           = NAS_MMC_GetCurFsmAddr();

    /* ��ȡ��ǰMMC��ջ��� */
    usOldStackDepth    = NAS_MMC_GetFsmStackDepth();

    /* ��Ϣ���� */
    ulRet     = NAS_MMC_FSM_ProcessEvent( pstCurFsm->ulState,
                                          ulEventType,
                                          (VOS_VOID*)pstMsg );

    /* ��ȡ��ǰMMC����ջ��� */
    usNewStackDepth    = NAS_MMC_GetFsmStackDepth();

    /* ջ���û������,����û�д����µ�״̬���������˳�*/
    if ( usNewStackDepth <= usOldStackDepth )
    {
        return ulRet;
    }

    /* �µ�ջ��ȴ����ϵ�ջ��� ����������ѹջ,��Ҫ����Ϣ����״̬���м������� */
    /* ���»�ȡ��ǰMMC�Ķ���״̬ */
    pstCurFsm   = NAS_MMC_GetCurFsmAddr();

    /* ����Ϣ���붥��״̬������������ */
    ulRet       = NAS_MMC_FSM_ProcessEvent( pstCurFsm->ulState,
                                          ulEventType,
                                          (VOS_VOID*)pstMsg );


    return ulRet;
}


VOS_VOID NAS_MMC_InitTask( VOS_VOID )
{
    NAS_MMC_CONTEXT_STRU                *pstMmcCtx;
    NAS_MML_CTX_STRU                    *pstMmlCtx;

    /* ��ʼ��MMLģ��CTX */
    pstMmlCtx   = NAS_MML_GetMmlCtx();
    NAS_MML_InitCtx(NAS_MML_INIT_CTX_STARTUP, pstMmlCtx);

    /* ֧��TDʱ����UTRAN CTRLģ����г�ʼ�� */
    NAS_UTRANCTRL_InitCtx(NAS_MML_INIT_CTX_STARTUP);

    /* ��ʼ��MMCģ��CTX */
    pstMmcCtx   = NAS_MMC_GetMmcCtxAddr();
    NAS_MMC_InitCtx(NAS_MMC_INIT_CTX_STARTUP, pstMmcCtx);

    /*ע��״̬��*/
    NAS_MMC_RegFsm();

    return;
}

VOS_UINT32 NAS_MMC_InitPid(
    enum VOS_INIT_PHASE_DEFINE          ip
)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:

            /* ����MMCģ���ʼ������ */
            NAS_MMC_InitTask();
            break;

        case VOS_IP_INITIAL:
            NAS_PIHAPI_RegCardRefreshIndMsg(WUEPS_PID_MMC);
            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;

        default:
            break;
    }

    return VOS_OK;
}
VOS_VOID  NAS_MMC_InitCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_CONTEXT_STRU                *pstMmcCtx
)
{

    /* ��ʼ��MMC��ǰ״̬�������� */
    NAS_MMC_InitCurrFsmCtx(&(pstMmcCtx->stCurFsm));

    /* ��ʼ��MMC״̬��ջ������ */
    NAS_MMC_InitFsmStackCtx(&(pstMmcCtx->stFsmStack));

    /* ��ʼ��plmn�������������� */
    NAS_MMC_InitPlmnSearchCtrlCtx(enInitType, &(pstMmcCtx->stPlmnSearchCtrl));

    /* ��ʼ��plmnע�ᱻ�ܽ�������� */
    NAS_MMC_InitPlmnRegRejCtx(&(pstMmcCtx->stPlmnRegInfo));

    /* ��ʼ��������Ϣ������ */
    NAS_MMC_InitServiceInfo(&(pstMmcCtx->stServiceInfo));

    /* ��ʼ����ά�ɲ���Ϣ������ */
    NAS_MMC_InitMaintainCtx(&(pstMmcCtx->stMaintainInfo));

    /* ��ʼ�������ж�ʱ����Ϣ */
    NAS_MMC_InitAllTimers(pstMmcCtx->astMmcTimerCtx);

    /* ��ʼ���ڲ�������� */
    NAS_MMC_InitInternalBuffer(&(pstMmcCtx->stBufferEntryMsgQueue));


    /* ��ʼ�������ȼ��������������� */
    NAS_MMC_InitHighPrioPlmnSearchCtx(&(pstMmcCtx->stHighPrioPlmnSearchCtrl));


    NAS_MMC_InitNetScanReqCtx(&(pstMmcCtx->stNetScanReqCtx));

    /* Added by y00307564 for CDMA Iteration 8 2015-2-7 begin */
    NAS_MMC_InitPrefPlmnCtx(&(pstMmcCtx->stPreflmnInfo));
    /* Added by y00307564 for CDMA Iteration 8 2015-2-7 end */

    NAS_MMC_InitDetachReqCtx(&(pstMmcCtx->stDetachReqCtx));

    NAS_MMC_InitAttachReqCtx(&(pstMmcCtx->stAttachReqCtx));

    /* Added by l00305157 for ROAM_PLMN_SELECTION_OPTIMIZE_2.0, 2015-5-26, begin */
    NAS_MMC_InitNoRFBackUpSearchedInfoCtx(&(pstMmcCtx->stBackUpSearchInfo));
    /* Added by l00305157 for ROAM_PLMN_SELECTION_OPTIMIZE_2.0, 2015-5-26, end */
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RegFsm
 ��������  : ע��״̬��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��20��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_RegFsm( VOS_VOID )
{
    /* ע��Ԥ����״̬�� */
    NAS_MMC_RegPreFsm();

    /* ע��L1״̬�� */
    NAS_MMC_RegMainL1Fsm();

    /* ע��L2״̬�� */
    NAS_MMC_RegL2Fsm();
}
VOS_UINT32 NAS_MMC_ProcessBufferMsg( VOS_VOID )
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulOldCacheNum;
    VOS_UINT32                          ulNewCacheNum;

    /* �ڴ�ռ���� */
    pstEntryMsg = (NAS_MMC_ENTRY_MSG_STRU *)PS_MEM_ALLOC( WUEPS_PID_MMC,
                                             sizeof(NAS_MMC_ENTRY_MSG_STRU) );

    if ( VOS_NULL_PTR == pstEntryMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcessBufferMsg:ERROR: MEM ALLOC FAIL");
        return VOS_FALSE;
    }


    ulRet   = VOS_TRUE;

    while( VOS_TRUE == NAS_MMC_GetNextCachedMsg(pstEntryMsg) )
    {
        ulOldCacheNum    = NAS_MMC_GetCacheNum();

        if ( VOS_TRUE == NAS_MMC_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer) )
        {
            /* �����������������������ܼ������������� */
            ulNewCacheNum = NAS_MMC_GetCacheNum();

            if ( ulNewCacheNum > ulOldCacheNum )
            {
                ulRet   = VOS_FALSE;
                break;
            }
            continue;
        }

        /* ��ȡ��ǰMMC��ջ��� */
        usOldStackDepth     = NAS_MMC_GetFsmStackDepth();

        /* ����״̬������ */
        ulRet  = NAS_MMC_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer);

        /* ��ȡ��ǰMMC��ջ��� */
        usNewStackDepth     = NAS_MMC_GetFsmStackDepth();

        /* ���ջ���������,˵���϶�������ѹջ����,���ܼ���������Ϣ */
        if ( usNewStackDepth > usOldStackDepth )
        {
            ulRet   = VOS_FALSE;
            break;
        }

        /* ����Ϣ�����˺���,�������Ǵ�ϻ򻺴��,��������ܼ��������� */
        if (VOS_FALSE == ulRet)
        {
            if ( VOS_TRUE == NAS_MMC_PostProcessMsg(pstEntryMsg->ulEventType,
                            (struct MsgCB*)pstEntryMsg->aucEntryMsgBuffer))
            {
                ulRet   = VOS_FALSE;
                break;
            }
        }
    }


    PS_MEM_FREE(WUEPS_PID_MMC, pstEntryMsg);

    return ulRet;
}





VOS_VOID  NAS_MMC_MsgProc(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader;
    REL_TIMER_MSG                      *pRcvTimerMsg;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_MsgProc:null pointer");
        return;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* ���������ʱ����Ϣ���ܿ���Ϣͷ���ƽ������֣�������ṹ���ulName���������
       ���Դ˴����зֱ���
    */
    if ( VOS_PID_TIMER == pstMsgHeader->ulSenderPid )
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = NAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* ֹͣ��Ӧ�Ķ�ʱ�������¶�ʱ����״̬ */
        NAS_MMC_StopTimer((NAS_MMC_TIMER_ID_ENUM_UINT16)(pRcvTimerMsg->ulName));
    }
    else
    {
        ulEventType  = NAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* ����Ѿ����������ֱ�ӷ��� */
    if ( VOS_TRUE == NAS_MMC_PreProcessMsg(ulEventType, pstMsg))
    {
        return;
    }


    /* ��ȡ��ǰMMC��ջ��� */
    usOldStackDepth    = NAS_MMC_GetFsmStackDepth();

    /* ����״̬������ */
    ulRet  = NAS_MMC_ProcessMsgInFsm(ulEventType, pstMsg);

    /* ״̬���л��յ������ͷš�״̬���˳�����Ϣ,���Բ���ֱ�ӷ���
    ����Ҫ�ж��ܷ�����*/
    usNewStackDepth    = NAS_MMC_GetFsmStackDepth();

    /* ���ջ����ȼ���,˵���϶���������ջ����,��Ҫ���ȴ����״̬���Ľ����Ϣ,ֱ�ӷ��� */
    if ( usNewStackDepth < usOldStackDepth )
    {
        /* ��¼��ջ����,ֻҪ��������ջ�����Ϳ��Դ����� */
        NAS_MMC_SetFsmStackPopFlg(VOS_TRUE);
        return;
    }

    /* ����Ϣ��״̬�����Ѿ��������,�ɳ��Դ���һ�»��� */
    if ( VOS_TRUE == ulRet)
    {
        /* ��ǰ���յ�״̬�����˳���Ϣ���ܹ������� */
        if (VOS_TRUE == NAS_MMC_GetFsmStackPopFlg())
        {
            (VOS_VOID)NAS_MMC_ProcessBufferMsg();
            NAS_MMC_SetFsmStackPopFlg(VOS_FALSE);
        }
    }
    /* �ڵ�ǰ״̬����δ������ϣ��ж���Ϣ�Ƿ���Ҫ��ϵ�ǰ��L2״̬��,���� */
    else
    {
        (VOS_VOID)NAS_MMC_PostProcessMsg(ulEventType, pstMsg);
    }



    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_MainL1FsmReg
 ��������  : MMC L1״̬������״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��04��19��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_RegMainL1Fsm( VOS_VOID  )
{
    /* ״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetMainFsmDescAddr()),
                         "NAS:FSM:MMC:MAIN",
                         (VOS_UINT32)(NAS_MMC_GetL1MainStaTblSize()),
                         NAS_MMC_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_L1Main);

    return;
}
VOS_VOID NAS_MMC_RegL2Fsm( VOS_VOID  )
{

    /* SwitchOn״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetSwitchOnFsmDescAddr()),
                         "NAS:FSM:MMC:SwitchOn",
                         (VOS_UINT32)NAS_MMC_GetSwitchOnStaTblSize(),
                         NAS_MMC_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_SwitchOn);

    /* PowerOff״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetPowerOffFsmDescAddr()),
                         "NAS:FSM:MMC:PowerOff",
                         (VOS_UINT32)NAS_MMC_GetPowerOffStaTblSize(),
                         NAS_MMC_GetPowerOffStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_PowerOff);

    /* PlmnSelection״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetPlmnSelectionFsmDescAddr()),
                         "NAS:FSM:MMC:PlmnSelection",
                         (VOS_UINT32)NAS_MMC_GetPlmnSelectionStaTblSize(),
                         NAS_MMC_GetPlmnSelectionStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_PlmnSelection);

    /* AnyCell����״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetAnyCellSearchFsmDescAddr()),
                         "NAS:FSM:MMC:AnyCellSearch",
                         (VOS_UINT32)NAS_MMC_GetAnyCellSearchStaTblSize(),
                         NAS_MMC_GetAnyCellSearchStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_AnyCellSearch);

    /* SysCfg״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetSysCfgFsmDescAddr()),
                         "NAS:FSM:MMC:SysCfg",
                         (VOS_UINT32)NAS_MMC_GetSysCfgStaTblSize(),
                         NAS_MMC_GetSysCfgStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_SysCfg);

    /* ��ѡ״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetInterSysCellReselFsmDescAddr()),
                         "NAS:FSM:MMC:InterSysCellResel",
                         (VOS_UINT32)NAS_MMC_GetInterSysCellReselStaTblSize(),
                         NAS_MMC_GetInterSysCellReselStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_InterSysCellResel);

    /* Handover ״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetInterSysHoFsmDescAddr()),
                         "NAS:FSM:MMC:InterSysHo",
                         (VOS_UINT32)NAS_MMC_GetInterSysHoStaTblSize(),
                         NAS_MMC_GetInterSysHoStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_InterSysHo);

    /* CCO״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetInterSysCcoFsmDescAddr()),
                         "NAS:FSM:MMC:InterSysCCO",
                         (VOS_UINT32)NAS_MMC_GetInterSysCcoStaTblSize(),
                         NAS_MMC_GetInterSysCcoStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_InterSysCco);

    /* OOS״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetInterSysOosFsmDescAddr()),
                         "NAS:FSM:MMC:InterSysOos",
                         (VOS_UINT32)NAS_MMC_GetInterSysOosStaTblSize(),
                         NAS_MMC_GetInterSysOosStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_InterSysOos);

    /* PLMN LIST״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetPlmnListFsmDescAddr()),
                         "NAS:FSM:MMC:PlmnList",
                         (VOS_UINT32)NAS_MMC_GetPlmnListStaTblSize(),
                         NAS_MMC_GetPlmnListStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_PlmnList);

    /* BgPlmnSearch״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetBgPlmnSearchFsmDescAddr()),
                         "NAS:FSM:MMC:BgPlmnSearch",
                         (VOS_UINT32)NAS_MMC_GetBgPlmnSearchStaTblSize(),
                         NAS_MMC_GetBgPlmnSearchStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_BgPlmnSearch);

    /* GetGeo״̬��ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetGeoFsmDescAddr()),
                         "NAS:FSM:MMC:GetGeo",
                         (VOS_UINT32)NAS_MMC_GetGeoStaTblSize(),
                         NAS_MMC_GetGetGeoStaTbl(),
                         VOS_NULL_PTR,
                         NAS_MMC_InitFsmCtx_GetGeo);
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RegPreFsm
 ��������  : MMCԤ����״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��04��19��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_RegPreFsm( VOS_VOID  )
{
    /* Ԥ����ע�� */
    NAS_FSM_RegisterFsm((NAS_MMC_GetPreFsmDescAddr()),
                         "NAS:FSM:MMC:PreProcess",
                         NAS_MMC_GetPreProcessStaTblSize(),
                         NAS_MMC_GetPreProcessStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

