

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafCsCallMain.h"
#include "TafXCallMain.h"
#include "MnCall.h"
#include "TafSdcLib.h"
#include "TafCsCallCtx.h"
#include "MnCallTimer.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_CS_CALL_MAIN_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_CSCALL_Init(
    TAF_CSCALL_INIT_TYPE_ENUM_UINT8     enInitCtxType
)
{
    /* 初始化上下文 */
    TAF_CSCALL_InitCtx();
}
VOS_UINT32 TAF_CSCALL_IsNeedXcallProcAppReqMsg(struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    switch ( pstMsgHeader->ulMsgName )
    {
        case MN_CALL_APP_SET_UUSINFO_REQ:
        case MN_CALL_APP_QRY_UUSINFO_REQ:
        case MN_CALL_APP_SET_ALS_REQ:
        case MN_CALL_APP_QRY_ALS_REQ:
        case MN_CALL_APP_CLPR_GET_REQ:
        case MN_CALL_APP_SET_CSSN_REQ:
        case MN_CALL_QRY_ECALL_INFO_REQ:
            return VOS_FALSE;

        default:
            return VOS_TRUE;

    }
}


VOS_VOID TAF_CSCALL_ProcAppReqMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulRslt;

    /* CL互操作模式 */
    ulRslt = TAF_CSCALL_IsNeedXcallProcAppReqMsg(pstMsg);
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    if ((VOS_TRUE == TAF_SDC_IsConfigCLMode())
       &&(VOS_TRUE == ulRslt))
    {
        TAF_XCALL_ProcAppReqMsg(pstMsg);

        return;
    }
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */
#endif


    MN_CALL_ProcAppReqMsg(pstMsg);

    return;
}
VOS_VOID TAF_CSCALL_ProcVcMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_XCALL_ProcVcMsg(pstMsg);

        return;
    }
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */
#endif

    MN_CALL_ProcVCMsg(pstMsg);

    return;
}


VOS_VOID TAF_CSCALL_ProcMmaMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcMmaMsg(pstMsg);
#endif

    TAF_CALL_ProcMmaMsg(pstMsg);

    return;
}


VOS_VOID TAF_CSCALL_ProcTimerOutMsg(
    REL_TIMER_MSG                       *pTmrMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcTimerOutMsg(pTmrMsg);
#endif

    /* 调用CCA的定时器消息处理函数 */
    MN_CALL_ProcTimeoutMsg(pTmrMsg);

    return;
}
VOS_VOID TAF_CSCALL_ProcUsimMsg(
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcUsimMsg(pstMsg);
#endif

    /* 调用CCA的USIM消息处理函数 */
    MN_CALL_DispatchUsimMsg(pstMsg);

    return;
}


/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




