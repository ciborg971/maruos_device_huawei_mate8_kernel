/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasLppIntraMsgProc.c
  版 本 号   : 初稿
  作    者   : XiaoJun
  生成日期   : 2015年7月30日
  最近修改   :
  功能描述   : LPP 模块的内部消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月30日
    作    者   : XiaoJun
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasLppPublic.h"
#include  "NasLppSendMsg.h"

#if (FEATURE_LPP == FEATURE_ON)
extern LPP_UPLINK_MSG_BUF_STRU*  NAS_LPP_GetLppMsgUpBuffByOpId
(
    VOS_UINT32              ulLmmLppOpId
);
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPINTRAMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPINTRAMSGPROC_C


/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 Function Name   : NAS_LPP_RcvIntraDataCnf
 Description     : 处理内部data cnf消息
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_RcvIntraDataCnf( NAS_LPP_INTRA_DATA_CNF_STRU *pRcvMsg)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU *pstTransEntity;
    VOS_UINT8 ucSessionIndex,ucSessionTransIndx;
    NAS_LPP_SUB_STATE_ENUM_UINT32 enSubState;
    LPP_UPLINK_MSG_BUF_STRU  *pstUplinkMsgBuff = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf enter!");

    /*停止所有的session的流程*/
    if (NAS_LPP_CONN_MANAGE_FAIL == pRcvMsg->enRslt)
    {
        NAS_LPP_ReleaseAllSession();
        return;
    }

    ucSessionIndex = NAS_LPP_SearchSessionIndx(pRcvMsg->stLppMsgIdentity.ulSessionId);

    pstUplinkMsgBuff = NAS_LPP_GetLppMsgUpBuffByOpId(pRcvMsg->ulOpId);
    if(NAS_LPP_NULL_PTR == pstUplinkMsgBuff)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_AckDataCnfSuccHandle: No buffer!");
        return;
    }


    /*先搜索到对应的SESSION和TRANSACTION*/
    pstTransEntity = NAS_LPP_SearchTransEntity(pRcvMsg->stLppMsgIdentity.ulSessionId,
                                               &(pRcvMsg->stLppMsgIdentity.stTransId),
                                               &ucSessionTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /* 如果已经有流程在请求辅助数据了，在收到辅助数据时会发送上行LPP ACK消息，这个时候收到DATA CNF时找不到TRANSACTION */
        NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
        NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf: Null!");
        return;
    }

    /*根据搜索到的TRANSACTION取当前的状态机状态，确定是否是要执行的消息:如果不是，退出*/
    if (NAS_LPP_SUCCESS != NAS_LPP_TransFsmCheck(pstTransEntity->enLppMainState,
                                                 pstTransEntity->enLppSubState,
                                                 (PS_MSG_HEADER_STRU *)pRcvMsg) )
    {
        NAS_LPP_ERR_LOG2("intra data msg not match fsm, Main State,SubState",
                          pstTransEntity->enLppMainState,
                          pstTransEntity->enLppSubState);
        return;
    }

    /*如果本transaction是在等待上行LPP ACK(对下行LPP ABORT /LPP ERROR)发送完成的状态*/
    if ( LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK == pstTransEntity->enLppSubState )
    {
        NAS_LPP_AbortAndErrorProcess(ucSessionIndex,
                                     ucSessionTransIndx,
                                     &(pRcvMsg->stLppMsgIdentity.stTransId));
        return;
    }

    /*结束本transaction的*/
    if (NAS_LPP_SUCCESS != pRcvMsg->enRslt)
    {
        NAS_LPP_ReleaseTransEntity(ucSessionIndex, ucSessionTransIndx);
    }

    /*upbuffer可能有2条LPPMSG: LPP ACK +  up lpp msg;满足此条件，肯定只有一个LPP ACK在发送，没有其他消息*/
/*
    else if ( (PS_TRUE == pstTransEntity->ucTransEndFlag)&&(NAS_LPP_AIR_MSG_UP_LPP_ACK == pstTransEntity->enLastUpMsgId))
    {
        NAS_LPP_ReleaseTransEntity(ucSessionIndex, ucSessionTransIndx);
    }
    else if (  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
    {
        if ((PS_TRUE != pstTransEntity->ucTransEndFlag))
        {
           NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
        }
        else
        {

        }

    }
*/
    else if (PS_TRUE == pstTransEntity->ucTransEndFlag)
    {
        if (NAS_LPP_AIR_MSG_UP_LPP_ACK == pstTransEntity->enLastUpMsgId)/*upbuffer可能有2条LPPMSG: LPP ACK +  up lpp msg;满足此条件，肯定只有一个LPP ACK在发送，没有其他消息*/
        {

            NAS_LPP_ReleaseTransEntity(ucSessionIndex, ucSessionTransIndx);
            return;

        }
        else if(  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
        {
            NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
            return;
        }
        else
        {
        }

    }
    else
    {
        if (  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
        {
            NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
            return;
        }
        else
        {

        }

    }

    /*成功的流程:转换状态机，启动等待ACK的定时器*/
    enSubState = NAS_LPP_GetWaitAckSubState( pstTransEntity->enLastUpMsgId, pstTransEntity->enLppMainState);
    NAS_LPP_INFO_LOG2("NAS_LPP_RcvIntraDataCnf: MainState, SubState", pstTransEntity->enLppMainState, enSubState);
    NAS_LPP_ChangeTransFsmState(ucSessionIndex, ucSessionTransIndx, pstTransEntity->enLppMainState, enSubState );

}

/*****************************************************************************
 Function Name   : NAS_LPP_LppMsgDistr
 Description     : LPP模块给LPP模块自己发的内部消息的处理入口函数
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_LppMsgDistr( VOS_VOID *pRcvMsg )
{
    NAS_LPP_INTRA_MSG_STRU *pstIntraMsg = NAS_LPP_NULL_PTR;

    NAS_LPP_WARN_LOG("NAS_LPP_LppMsgDistr enter!");

    pstIntraMsg = (NAS_LPP_INTRA_MSG_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch ( pstIntraMsg->ulMsgId )
    {
        case ID_NAS_LPP_INTRA_DATA_CNF :
            NAS_LPP_RcvIntraDataCnf((NAS_LPP_INTRA_DATA_CNF_STRU *)pstIntraMsg);
            break;
        /*
        case # :

            break;*/
        default:
            break;
    }

    return;
}









#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

