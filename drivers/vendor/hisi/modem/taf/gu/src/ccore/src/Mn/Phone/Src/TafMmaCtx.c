


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "TafMmaCtx.h"
#include "TafMmaFsmMainTbl.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "TafLog.h"
#include "TafMmaSndInternalMsg.h"
#include "Taf_Tafm_Remote.h"
#include "TafMmaMntn.h"
#include "TafOamInterface.h"
#include "MmaUphyInterface.h"

#include "TafSdcLib.h"

#include "TafMmaFsmImsSwitchTbl.h"

/* Modified by l00301449 for Iteration 13, 2015-04-09, begin */
#include "TafMmaFsmSysCfgTbl.h"
/* Modified by l00301449 for Iteration 13, 2015-04-09, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_CTX_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* MMA CTX,用于保存MMA状态机,描述表 */
TAF_MMA_CONTEXT_STRU                    g_stTafMmaCtx;

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/


VOS_VOID TAF_MMA_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理MMA入口消息的缓冲区地址 */
    pstEntryMsg                 = TAF_MMA_GetCurrFsmMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;

}
VOS_VOID  TAF_MMA_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* 获取当前的状态信息 */
    pstCurFsm                   = TAF_MMA_GetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->ulState          = ulCurrState;

    /*  打印当前的L1和L2状态 */
    TAF_MMA_LogFsmInfo();

    return;
}
VOS_UINT32 TAF_MMA_FSM_GetFsmTopState( VOS_VOID )
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    VOS_UINT32                          ulState;

    /* 获取当前状态机 */
    pstCurFsm               = TAF_MMA_GetCurFsmAddr();
    ulState                 = pstCurFsm->ulState;

    return ulState;
}
TAF_MMA_CONTEXT_STRU* TAF_MMA_GetMmaCtxAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx);
}


TAF_MMA_FSM_CTX_STRU* TAF_MMA_GetCurFsmAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm);
}


TAF_MMA_FSM_STACK_STRU* TAF_MMA_GetFsmStackAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stFsmStack);
}


TAF_FSM_DESC_STRU* TAF_MMA_GetCurFsmDesc(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.pstFsmDesc);
}


TAF_MMA_ENTRY_MSG_STRU* TAF_MMA_GetCurrFsmMsgAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.stEntryMsg);
}


TAF_MMA_FSM_ID_ENUM_UINT32 TAF_MMA_GetCurrFsmId(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.enFsmId);
}


TAF_MMA_MSG_QUEUE_STRU* TAF_MMA_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stBufferEntryMsgQueue);
}


VOS_VOID TAF_MMA_FSM_PushFsm(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack,
    TAF_MMA_FSM_CTX_STRU                *pstNewFsm
)
{
    TAF_MMA_FSM_CTX_STRU                *pstCurFsm;

    if ( (VOS_NULL_PTR == pstFsmStack)
      || (VOS_NULL_PTR == pstNewFsm) )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                       "TAF_MMA_FSM_PushFsm,Para null ptr,pstFsmStack,pstNewFsm");

        return;
    }

    if ( pstFsmStack->usStackDepth >= TAF_MMA_MAX_STACK_DEPTH )
    {
        TAF_ERROR_LOG1(WUEPS_PID_MMA,
                       "TAF_MMA_FSM_PushFsm,Fsm Stack Depth Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    pstCurFsm               = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* 将当前状态机所有CTX都需要保存起来 */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(TAF_MMA_FSM_CTX_STRU));

    pstFsmStack->usStackDepth++;


    return;
}
VOS_VOID TAF_MMA_FSM_PopFsm( VOS_VOID )
{
    VOS_UINT16                          usPopFsmPos;
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* 根据并行状态机栈弹出的状态机获取当前状态机描述地址  */
    pstFsmStack                     = TAF_MMA_GetFsmStackAddr();
    pstCurFsm                       = TAF_MMA_GetCurFsmAddr();

    /* 栈已空 */
    if ( 0 == (pstFsmStack->usStackDepth) )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_FSM_PopFsm,FSM Stack empty");

        return;
    }

    pstFsmStack->usStackDepth--;
    usPopFsmPos   = pstFsmStack->usStackDepth;

    /* 设置当前状态机 */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[usPopFsmPos]),
              sizeof(TAF_MMA_FSM_CTX_STRU));

    return;
}
VOS_VOID  TAF_MMA_LoadSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm
)
{
    switch ( enFsmId )
    {
        case TAF_MMA_FSM_PHONE_MODE :
            pstCurFsm->ulState                  = TAF_MMA_PHONE_MODE_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetPhoneModeFsmDescAddr();
            break;

#if (FEATURE_IMS == FEATURE_ON)
        case TAF_MMA_FSM_IMS_SWITCH :
            pstCurFsm->ulState                  = TAF_MMA_IMS_SWITCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetImsSwitchFsmDescAddr();
            break;
#endif

        /* Modified by l00301449 for Iteration 13, 2015-04-09, begin */
        case TAF_MMA_FSM_SYS_CFG :
            pstCurFsm->ulState                  = TAF_MMA_SYS_CFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetSysCfgFsmDescAddr();
            break;

        /* Modified by l00301449 for Iteration 13, 2015-04-09, end */

        default:
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LoadSubFsm:Invalid Fsm Id");
            return;
    }


    /*执行初始化sub状态机的函数*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}
VOS_VOID TAF_MMA_FSM_InitSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
)
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;


    pstCurFsm                           = TAF_MMA_GetCurFsmAddr();
    pstFsmStack                         = TAF_MMA_GetFsmStackAddr();

    /*  打印压栈前的main和sub状态 */
    TAF_MMA_LogFsmInfo();

    /* 将当前状态机压栈操作 */
    TAF_MMA_FSM_PushFsm(pstFsmStack, pstCurFsm);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId                  = enFsmId;

    /* 加载sub状态机 */
    TAF_MMA_LoadSubFsm(enFsmId, pstCurFsm);

    /*  打印当前的main和sub状态 */
    TAF_MMA_LogFsmInfo();
}
VOS_VOID TAF_MMA_FSM_QuitSubFsm( VOS_VOID )
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm                           = TAF_MMA_GetCurFsmAddr();

    /* QUIT时清空当前sub状态机的CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    /*  打印压栈前的main和sub状态 */
    TAF_MMA_LogFsmInfo();

    /* 状态机出栈操作 */
    TAF_MMA_FSM_PopFsm();

    /*  打印当前的main和sub状态 */
    TAF_MMA_LogFsmInfo();

    return;
}


VOS_UINT16  TAF_MMA_GetFsmStackDepth( VOS_VOID )
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}


VOS_UINT32  TAF_MMA_IsExistCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_UINT32                         *pulIndex
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();
   *pulIndex                           = 0;

    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            *pulIndex   = i;
            return VOS_TRUE;
        }
    }

    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_IsExistCacheMsg:not match MSG");

    return VOS_FALSE;
}


VOS_UINT32  TAF_MMA_IsNeedCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                          ulIndex;

    switch (ulEventType)
    {
        /* 当前卡状态指示消息的缓存只需要缓存一条 */
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND):

            if (VOS_TRUE == TAF_MMA_IsExistCacheMsg(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND), &ulIndex))
            {
                return VOS_FALSE;
            }

            break;

        default:
            break;
    }

    /* 默认返回保存该消息 */
    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = TAF_MMA_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= TAF_MMA_MAX_MSG_QUEUE_NUM )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:buffer full");

        TAF_MMA_LogBufferQueueMsg(VOS_TRUE);

        return VOS_FALSE;
    }

    /* 比较消息优先级,判断是否需要保存在缓存池中 */
    if (VOS_FALSE == TAF_MMA_IsNeedCacheMsg(ulEventType, pstMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:already exist msg");

        return VOS_FALSE;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    TAF_MMA_LogBufferQueueMsg(VOS_FALSE);

    TAF_INFO_LOG1(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:Cache Num", pstMsgQueue->ucCacheMsgNum);

    return VOS_TRUE;
}
VOS_VOID  TAF_MMA_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* 先找到需要被清除的缓存 */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            cCachePos = (VOS_INT8)i;
        }
    }

    /* 未找到该消息类型直接返回 */
    if ( -1 == cCachePos )
    {
        TAF_INFO_LOG1(WUEPS_PID_MMA, "TAF_MMA_ClearCacheMsg:invalid msg type", ulEventType);
        return;
    }

    /* 为保证先入先出,需要将后面的消息移到前面 */
    for ( i = cCachePos ; i < (pstMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY消息内容 */
        PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(TAF_MMA_ENTRY_MSG_STRU));
    }

    /* 将缓存个数减一 */
    pstMsgQueue->ucCacheMsgNum--;

    /* 将当前缓存给打印出来 */
    TAF_MMA_LogBufferQueueMsg(VOS_FALSE);

    return;
}




VOS_VOID  TAF_MMA_InitFsmCtx_PhoneMode(VOS_VOID)
{
    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_NO_ERROR);


    return;
}

/* Modified by l00301449 for Iteration 13, 2015-04-09, begin */

VOS_VOID  TAF_MMA_InitFsmCtx_SysCfg(VOS_VOID)
{
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;

    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    PS_MEM_SET(pstSysCfgCtx, 0 , sizeof(TAF_MMA_FSM_SYS_CFG_CTX_STRU));

    pstSysCfgCtx->usOperType   = 0;
    pstSysCfgCtx->ucAttachOpId = 0xFF;

    return;
}
/* Modified by l00301449 for Iteration 13, 2015-04-09, end */

VOS_VOID  TAF_MMA_InitCurrFsmCtx(
    TAF_MMA_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   TAF_MMA_FSM_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   TAF_MMA_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   TAF_MMA_MAIN_STA_IDLE;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               TAF_MMA_MAX_MSG_BUFFER_LEN);
}


VOS_VOID  TAF_MMA_InitFsmStackCtx(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < TAF_MMA_MAX_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = TAF_MMA_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = TAF_MMA_MAIN_STA_BUTT;
    }
}


VOS_VOID  TAF_MMA_InitInternalBuffer(
    TAF_MMA_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
)
{
    pstBufferEntryMsgQueue->ucCacheMsgNum   = 0;
    PS_MEM_SET(pstBufferEntryMsgQueue->astMsgQueue,
               0x00,
               sizeof(TAF_MMA_CACH_MSG_INFO_STRU)*TAF_MMA_MAX_MSG_QUEUE_NUM);
}


VOS_VOID  TAF_MMA_InitInternalMsgQueue(
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MMA的内部消息队列 */
)
{
    VOS_UINT32                          i;

    pstInternalMsgQueue->ucHeader   = 0;
    pstInternalMsgQueue->ucTail     = 0;

    for ( i = 0 ; i < TAF_MMA_MAX_MSG_QUEUE_SIZE; i++ )
    {
        pstInternalMsgQueue->astMmaMsgQueue[i].usMsgID    = TAF_MMA_INVALID_INTERNAL_MSG_ID;
        PS_MEM_SET(pstInternalMsgQueue->astMmaMsgQueue[i].aucBuf,
                   0x00,
                   TAF_MMA_MAX_MSG_BUFFER_LEN);
    }

}
VOS_VOID  TAF_MMA_InitMaintainInfo(
    TAF_MMA_MAINTAIN_CTX_STRU          *pstMaintainInfo
)
{
    pstMaintainInfo->ucMmaLogInfoFlag   = VOS_FALSE;
}


VOS_VOID TAF_MMA_InitExternalModuleInitStatus(
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU      *pstInitStatusctx
)
{
    PS_MEM_SET(pstInitStatusctx, 0, sizeof(TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU));

    /* 无条件等待物理层初始化，不和DSDS宏绑定在一起 */
    pstInitStatusctx->enPhyInitStatus      = MMA_UPHY_INIT_STATUS_BUTT;

    return;

}
TAF_MMA_PHONE_MODE_CTRL_CTX_STRU *TAF_MMA_GetPhoneModeCtrl(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stPhoneModeCtrl);
}


VOS_UINT32  TAF_MMA_GetCacheNum( VOS_VOID )
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    return pstMsgQueue->ucCacheMsgNum;
}


TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   TAF_MMA_GetCachedMsgPrio(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio;

    switch (pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ):
        case TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ):

            enPrio = TAF_MMA_MSG_CACHE_PRIO_HIGH;
            break;

        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND):

            enPrio = TAF_MMA_MSG_CACHE_PRIO_MIDDLE;
            break;


        /* 查询预处理先返回了  */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ):

        default:

            enPrio = TAF_MMA_MSG_CACHE_PRIO_LOW;
            break;
    }

    return enPrio;
}
VOS_UINT32  TAF_MMA_GetNextPrioCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg,
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        if (enPrio == TAF_MMA_GetCachedMsgPrio(&pstMsgQueue->astMsgQueue[i].stMsgEntry))
        {
            PS_MEM_CPY(pstEntryMsg,
                       &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            /* 消息已经取出则清除当前缓存 */
            TAF_MMA_ClearCacheMsg(pstEntryMsg->ulEventType);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32  TAF_MMA_GetNextCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    if (0 == pstMsgQueue->ucCacheMsgNum )
    {
        TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_HIGH))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_MIDDLE))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_LOW))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID  TAF_MMA_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStackPopFlg;
}


VOS_UINT16  TAF_MMA_GetFsmStackPopFlg( VOS_VOID )
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}


VOS_VOID  TAF_MMA_SetAutoInitPsFlg(
    VOS_UINT32                          ulAutoInitPsFlg
)
{
    TAF_MMA_GetPhoneModeCtrl()->ulAutoInitPsFlg = ulAutoInitPsFlg;
}


VOS_UINT32  TAF_MMA_GetAutoInitPsFlg(VOS_VOID)
{
    return (TAF_MMA_GetPhoneModeCtrl()->ulAutoInitPsFlg);
}


VOS_VOID  TAF_MMA_SetAutoSwitchOnFlg(
    VOS_UINT32                          ulAutoSwitchOnFlg
)
{
    TAF_MMA_GetPhoneModeCtrl()->ulAutoSwitchOnFlg = ulAutoSwitchOnFlg;
}


VOS_UINT32  TAF_MMA_GetAutoSwitchOnFlg(VOS_VOID)
{
    return (TAF_MMA_GetPhoneModeCtrl()->ulAutoSwitchOnFlg);
}





VOS_VOID  TAF_MMA_SetCurPhoneErrorCode_PhoneMode(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    /* 如果当前状态机不是PHONE MODE, 异常打印 */
    if (TAF_MMA_FSM_PHONE_MODE != TAF_MMA_GetCurrFsmId())
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SetCurPhoneErrorCode_PhoneMode,ERROR:FsmId Error");
        return;
    }

    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stPhoneModeCtx.enPhoneError = enErrorCode;
}
TAF_ERROR_CODE_ENUM_UINT32  TAF_MMA_GetCurPhoneErrorCode_PhoneMode(VOS_VOID)
{
    /* 如果当前状态机不是PHONE MODE, 异常打印 */
    if (TAF_MMA_FSM_PHONE_MODE != TAF_MMA_GetCurrFsmId())
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetCurPhoneErrorCode_PhoneMode,ERROR:FsmId Error");
    }
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stPhoneModeCtx.enPhoneError);
}
TAF_MMA_TIMER_CTX_STRU*  TAF_MMA_GetTimerCtxAddr( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->astMmaTimerCtx;
}



TAF_MMA_OPER_CTX_STRU*  TAF_MMA_GetOperCtxAddr( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->astMmaOperCtx;
}




VOS_UINT8  TAF_MMA_GetMmaLogInfoFlag( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->stMaintainInfo.ucMmaLogInfoFlag;
}


VOS_VOID  TAF_MMA_SetMmaLogInfoFlag(
    VOS_UINT8                           ucMmaLogInfoFlag
)
{
    TAF_MMA_GetMmaCtxAddr()->stMaintainInfo.ucMmaLogInfoFlag = ucMmaLogInfoFlag;
}




VOS_VOID TAF_MMA_SetNetworkCapabilityInfo(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstNwCapInfo
)
{
    if (TAF_SDC_SYS_MODE_LTE == enSysMode)
    {
        TAF_SDC_SetLteNwCapInfo(pstNwCapInfo);
    }
    else
    {
        TAF_SDC_SetGuNwCapInfo(pstNwCapInfo);
    }
}


VOS_VOID TAF_MMA_SetPhyInitStatus(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enFlag
)
{
    TAF_MMA_GetMmaCtxAddr()->stMmaExternalModuleInitStatusCtx.enPhyInitStatus = enFlag;
}


MMA_UPHY_INIT_STATUS_ENUM_UINT16 TAF_MMA_GetPhyInitStatus( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->stMmaExternalModuleInitStatusCtx.enPhyInitStatus;
}



VOS_UINT16 TAF_MMA_IsExternalModuleInitCompeleted( VOS_VOID )
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enUsimstatus;
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enUphyInitStatus;

    enUsimstatus     = TAF_SDC_GetSimStatus();
    enUphyInitStatus = TAF_MMA_GetPhyInitStatus();

    if((TAF_SDC_USIM_STATUS_BUTT     == enUsimstatus)
    || (MMA_UPHY_INIT_STATUS_BUTT    == enUphyInitStatus))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_UINT32 TAF_MMA_IsOperTypeUsed(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  enOperType是否正在被使用  */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        if ( (enOperType == pstMmaOperCtx[ulIndex].enOperType)
          && (VOS_TRUE   == pstMmaOperCtx[ulIndex].ucUsedFlag) )
        {
            /* 将当前OPER_CTX信息LOG出来 */
            TAF_MMA_LogOperCtxInfo();

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}



VOS_UINT32 TAF_MMA_GetSpecOperTypeIndex(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                          *pucCtxIndex
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  enOperType是否正在被使用  */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        if ( (enOperType == pstMmaOperCtx[ulIndex].enOperType)
          && (VOS_TRUE   == pstMmaOperCtx[ulIndex].ucUsedFlag) )
        {
            *pucCtxIndex = (VOS_UINT8)ulIndex;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}
VOS_UINT32 TAF_MMA_GetUnusedOperCtxIndex(
    VOS_UINT8                          *pucCtxIndex
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  是否有空余的Ctx   */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        /* 找到了空余的CTX */
        if (VOS_FALSE == pstMmaOperCtx[ulIndex].ucUsedFlag)
        {
            *pucCtxIndex = (VOS_UINT8)ulIndex;

            return VOS_TRUE;
        }

    }

    /* 将当前OPER_CTX信息LOG出来 */
    TAF_MMA_LogOperCtxInfo();

    /* 没有找到空余的CTX */
    return VOS_FALSE;

}


VOS_VOID TAF_MMA_SetOperCtx(
    TAF_MMA_CTRL_STRU                   stCtrl,
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                           ucCtxIndex
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstMmaOperCtx[ucCtxIndex].stCtrl.ucOpId     = stCtrl.ucOpId;
    pstMmaOperCtx[ucCtxIndex].stCtrl.usClientId = stCtrl.usClientId;
    pstMmaOperCtx[ucCtxIndex].stCtrl.ulModuleId = stCtrl.ulModuleId;
    pstMmaOperCtx[ucCtxIndex].enOperType        = enOperType;
    pstMmaOperCtx[ucCtxIndex].ucUsedFlag        = VOS_TRUE;

    /* 将当前OPER_CTX信息LOG出来 */
    TAF_MMA_LogOperCtxInfo();

    return;
}
VOS_VOID TAF_MMA_ClearOperCtx(
    VOS_UINT8                           ucCtxIndex
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    PS_MEM_SET(&(pstMmaOperCtx[ucCtxIndex]), 0, sizeof(TAF_MMA_OPER_CTX_STRU));

    pstMmaOperCtx[ucCtxIndex].ucUsedFlag = VOS_FALSE;
    pstMmaOperCtx[ucCtxIndex].enOperType = TAF_MMA_OPER_BUTT;

    /* 将当前OPER_CTX信息LOG出来 */
    TAF_MMA_LogOperCtxInfo();

    return;
}


/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_GetCFreqLockSetPara
 功能描述  : 获取FREQLOCK信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新增函数
*****************************************************************************/
TAF_MMA_CFREQ_LOCK_SET_PARA_STRU* TAF_MMA_GetCFreqLockSetPara(VOS_VOID)
{
    return &g_stTafMmaCtx.stCFreqLockValue;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitCFreqLockPara
 功能描述  : 初始化FREQLOCK信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MMA_InitCFreqLockPara(VOS_VOID)
{
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstTafMmaCFreqLockPara;

    pstTafMmaCFreqLockPara = TAF_MMA_GetCFreqLockSetPara();

    PS_MEM_SET(pstTafMmaCFreqLockPara, 0x0, sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));

    return;
}
/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

/* Modified by l00301449 for Iteration 13, 2015-04-10, begin */



VOS_VOID TAF_MMA_SetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.usOperType = usOperType;

    return;
}


VOS_VOID TAF_MMA_SetSysCfgPara_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
    PS_MEM_CPY(&(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stSysCfgPara),
                pstSysCfgPara,
                sizeof(TAF_MMA_SYS_CFG_PARA_STRU));
    return;
}


TAF_MMA_SYS_CFG_PARA_STRU *TAF_MMA_GetSysCfgPara_SysCfg(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stSysCfgPara);
}


VOS_VOID TAF_MMA_SetAttachOpId_SysCfg(
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.ucAttachOpId = ucOpId;

    return;
}

/* Modified by l00301449 for Iteration 13, 2015-04-10, end */

#if (FEATURE_ON == FEATURE_LTE)
TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUserSetLteBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stUserSetBand.stUserSetLteBand);
}


TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUeSupportLteBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stUeBandCap.stUeSupportLteBand);
}
#endif


TAF_MMA_RAT_ORDER_STRU *TAF_MMA_GetRatPrioListAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stRatPrioList);
}


TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *TAF_MMA_GetLastSyscfgSetAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet);
}


TAF_MMA_SYSCFG_USER_SET_BAND_STRU *TAF_MMA_GetSyscfgUserSetBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stUserSetBand);
}


TAF_MMA_ROAM_MODE_ENUM_UINT8 TAF_MMA_GetSyscfgUserSetRoamValue(VOS_VOID)
{
    return (g_stTafMmaCtx.stLastSyscfgSet.enRoam);
}


TAF_MMA_UE_BAND_CAPA_ST *TAF_MMA_GetUeSupportBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stUeBandCap);
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetAttachOpId
 功能描述  : 获取attach操作的op id
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月13日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetAttachOpId(VOS_VOID)
{
    TAF_MMA_CONTEXT_STRU               *pstMmaCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucOpId;

    pstMmaCtx = TAF_MMA_GetMmaCtxAddr();

    ucOpId = pstMmaCtx->stAttachInfo.ucAttachOpId;

    pstMmaCtx->stAttachInfo.ucAttachOpId++;

    pstMmaCtx->stAttachInfo.ucAttachOpId %= 0xFF;

    return ucOpId;
}


TAF_MMA_GET_GEO_CTX_STRU* TAF_MMA_GetGeoCtxAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stGetGeoInfo);
}


VOS_VOID TAF_MMA_InitGetGeoCtx(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx = TAF_MMA_GetGeoCtxAddr();

    PS_MEM_SET(pstGetGeoCtx, 0x0, sizeof(TAF_MMA_GET_GEO_CTX_STRU));

    pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag        = VOS_FALSE;
    pstGetGeoCtx->stGetGeoNvCfg.ucCcpuResetFlag        = VOS_FALSE;
    pstGetGeoCtx->stGetGeoNvCfg.aucReserved[0]         = 0;
    pstGetGeoCtx->stGetGeoNvCfg.aucReserved[1]         = 10;
    pstGetGeoCtx->stGetGeoNvCfg.ulGetGeoTimerLen       = TAF_MMA_GET_GEO_TIMER_DEFAULT_LEN;
    pstGetGeoCtx->stGetGeoNvCfg.ulGeoEffectiveTimeLen  = TAF_MMA_GEO_EFFECTIVE_TIME_DEFAULT_LEN;

    pstGetGeoCtx->ulGetGeoTickTime       = VOS_GetTick() / PRE_SECOND_TO_TICK;
    pstGetGeoCtx->stGeoPlmnId.ulMcc      = TAF_SDC_INVALID_MCC;
    pstGetGeoCtx->stGeoPlmnId.ulMnc      = TAF_SDC_INVALID_MNC;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_InitSdcIccId
 功能描述  : 初始化卡的IccId
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_InitSdcIccId( VOS_VOID )
{
    TAF_SDC_ICCID_INFO_STRU             *pstIccIdInfo   = VOS_NULL_PTR;

    pstIccIdInfo        = TAF_SDC_GetIccIdInfo();

    PS_MEM_SET(pstIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));

    pstIccIdInfo->ucLen = TAF_SDC_ICC_ID_MAX_NUM + 1;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsValidIccId
 功能描述  : 判断当前是否为有效
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月26日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsValidIccId( VOS_VOID )
{
    TAF_SDC_ICCID_INFO_STRU              stNullIccIdInfo;

    PS_MEM_SET(&stNullIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));
    stNullIccIdInfo.ucLen   = TAF_SDC_ICC_ID_MAX_NUM + 1;

    if (0 == PS_MEM_CMP(TAF_SDC_GetIccIdInfo(), &stNullIccIdInfo, sizeof(TAF_SDC_ICCID_INFO_STRU)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT8  TAF_MMA_GetCfgGetGeoFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCfgGetGeoFlag;
}


VOS_UINT32 TAF_MMA_GetGeoTimerLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ulGetGeoTimerLen;
}


VOS_VOID TAF_MMA_SetCcpuResetFlag(VOS_UINT8 ucCcpuResetFlag)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCcpuResetFlag = ucCcpuResetFlag;
}


VOS_UINT8 TAF_MMA_GetCcpuResetFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCcpuResetFlag;
}


VOS_UINT32 TAF_MMA_GetGeoEffectiveTimeLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ulGeoEffectiveTimeLen;
}


VOS_UINT32 TAF_MMA_IsGeoValid(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCurrTickTime;
    VOS_UINT32                          ulGeoEffectiveTimeLen;
    VOS_UINT32                          ulIsPlmnIdValid;

    ulCurrTickTime          = VOS_GetTick() / PRE_SECOND_TO_TICK;
    ulGeoEffectiveTimeLen   = TAF_MMA_GetGeoEffectiveTimeLen();
    pstGetGeoCtx            = TAF_MMA_GetGeoCtxAddr();
    ulIsPlmnIdValid         = TAF_SDC_IsPlmnIdValid(&pstGetGeoCtx->stGeoPlmnId);

    /* get geo NV关闭时也认为无效 */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return VOS_FALSE;
    }

    /* 地理信息的PLMN无效或者超过有效时长，则认为国家码是无效的 */
    if ((VOS_FALSE == ulIsPlmnIdValid)
     || ((ulCurrTickTime - pstGetGeoCtx->ulGetGeoTickTime) > ulGeoEffectiveTimeLen))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_IsNeedGetGeoNoSimStart(VOS_VOID)
{
    VOS_UINT8                           ucCfgGetGeoFlag;
    VOS_UINT8                           ucCcpuResetFlag;

    ucCfgGetGeoFlag  = TAF_MMA_GetCfgGetGeoFlag();
    ucCcpuResetFlag  = TAF_MMA_GetCcpuResetFlag();

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果平台不支持L，则直接返回不支持 */
    if (VOS_FALSE == TAF_SDC_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }
#endif

    if ((VOS_TRUE  == ucCfgGetGeoFlag)
     && (VOS_TRUE  != ucCcpuResetFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID TAF_MMA_SetTestRoamFlag(VOS_UINT8 ucFlag)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[0] = ucFlag;
}


VOS_UINT8 TAF_MMA_GetTestRoamFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[0];
}


VOS_VOID TAF_MMA_SetWaitExtTimerLen(VOS_UINT8 ucLen)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[1] = ucLen;
}


VOS_UINT8 TAF_MMA_GetWaitExtTimerLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[1];
}


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_GetSrvAcqRatListAddr
 功能描述  : 获取业务触发搜网的网络模式列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_MMA_SRV_ACQ_RAT_LIST_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月16日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
TAF_MMA_SRV_ACQ_RAT_LIST_STRU* TAF_MMA_GetSrvAcqRatListAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stDsdsInfo.stSrvAcqRatList);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateSrvAcqRatList
 功能描述  : 更新业务触发搜网的网络模式列表
 输入参数  : TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月16日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSrvAcqRatList(
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
)
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatListAddr = VOS_NULL_PTR;

    pstSrvAcqRatListAddr = TAF_MMA_GetSrvAcqRatListAddr();

    PS_MEM_CPY(pstSrvAcqRatListAddr, pstSrvAcqRatList, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ClearSrvAcqRatList
 功能描述  : 清除业务触发搜网的网络模式列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月18日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ClearSrvAcqRatList(VOS_VOID)
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatListAddr = VOS_NULL_PTR;

    pstSrvAcqRatListAddr = TAF_MMA_GetSrvAcqRatListAddr();

    PS_MEM_SET(pstSrvAcqRatListAddr, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
}

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */

/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_SetDelayReportServiceStatusFlg
 功能描述  : 设置当前是否启用了短暂掉网延时上报功能
 输入参数  : ucDelayReportServiceStatusFlg - 短暂掉网延时上报功能是否打开
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
VOS_VOID TAF_MMA_SetDelayReportServiceStatusFlg(
    VOS_UINT8 ucDelayReportServiceStatusFlg
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayReportServiceInfo.ucEnable = ucDelayReportServiceStatusFlg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetDelayReportServiceStatusFlg
 功能描述  : 获取当前是否启用了短暂掉网延时上报功能
 输入参数  :
 输出参数  : 无
 返 回 值  : 短暂掉网延时上报功能是否开启的FLAG
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetDelayReportServiceStatusFlg(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayReportServiceInfo.ucEnable);
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SetDelayReportServiceStatusTimerLen
 功能描述  : 设置当前启用了短暂掉网延时上报功能的时长
 输入参数  : ulTimerLen -  时长，单位秒
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
VOS_VOID TAF_MMA_SetDelayReportServiceStatusTimerLen(
    VOS_UINT32 ulTimerLen
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayReportServiceInfo.ulRptSrvStaDelayTimerValue = ulTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetDelayReportServiceStatusCfgTimerLen
 功能描述  : 获取当前启用了短暂掉网延时上报功能的时长
 输入参数  :
 输出参数  : 无
 返 回 值     :  时长，单位秒
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetDelayReportServiceStatusCfgTimerLen(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayReportServiceInfo.ulRptSrvStaDelayTimerValue);
}
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



