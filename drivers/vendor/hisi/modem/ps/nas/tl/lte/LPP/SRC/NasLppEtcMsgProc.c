/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasLppEtcMsgProc.c
  版 本 号   : 初稿
  作    者   : LIFUXIN
  生成日期   : 2015年7月30日
  最近修改   :
  功能描述   : LPP 模块的内部消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月1日
    作    者   : LIFUXIN
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
//#include  "vos.h"
#include  "NasLppPublic.h"
#include  "NasLppSendMsg.h"
#include  "EtcLppInterface.h"
#include  "NasLppSendMsg.h"
#include  "NasLppEtcMsgProc.h"

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPETCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPETCMSGPROC_C


/*****************************************************************************
  3 函数实现
*****************************************************************************/



VOS_VOID NAS_LPP_RcvLppEtcResetPostitionInfoInd( ETC_LPP_RESET_POSTION_INFO_STRU *pRcvMsg )
{
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLocTechmap = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd is entered!");

    switch(pRcvMsg->enRestType)
    {
        case ETC_LPP_RESET_TYPE_GNSS:
            /*TODO*/
            break;

        case ETC_LPP_RESET_TYPE_OTDOA:
            NAS_LPP_NORM_LOG("NAS_LPP_RcvLppEtcResetPostitionInfoInd: Reset OTDOA Information!");

            /*复位OTDOA的辅助信息*/
            /*清空本地存贮的辅助信息*/
            NAS_LPP_MEM_SET(&(NAS_LPP_GetLppEntityCtx()->stMeasResult.stOtdoaMeasRslt),
                            0,
                            sizeof(NAS_LPP_OTDOA_MEAS_RESLT_STRU));

            NAS_LPP_MEM_SET(&(NAS_LPP_GetLppEntityCtx()->stLppConfig.stOtdoaAssisCfg),
                            0,
                            sizeof(NAS_LPP_OTDOA_ASSIST_CFG_STRU));

            /*查找running表，得到transactionIndex，sessionTransactionIndx*/
            pstLocTechmap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_OTDOA);
            if (NAS_LPP_NULL_PTR != pstLocTechmap)
            {
                /*给LRRC发送测量停止*/
                NAS_LPP_SndOtdoaMeasReq(pstLocTechmap->ucSessionIndx,
                                              pstLocTechmap->ucSessionTranIndx,
                                              LPP_LRRC_LCS_MEAS_CMD_REL);
            }
            break;

        default:
            break;
    }

    return;
}
VOS_VOID NAS_LPP_EtcMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_EtcMsgDistr is entered!");

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pEmmMsg->ulMsgName)
    {
        /*收到的是ID_ETC_LPP_RESET_POSTION_INFO_IND消息*/
        case ID_ETC_LPP_RESET_POSTION_INFO_IND:
            NAS_LPP_RcvLppEtcResetPostitionInfoInd((ETC_LPP_RESET_POSTION_INFO_STRU *)pRcvMsg);
            break;

        default:
            NAS_LPP_WARN_LOG("NAS_LPP_EtcMsgDistr:NORM: Error SenderPid!");
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

