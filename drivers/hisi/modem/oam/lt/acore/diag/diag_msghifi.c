/******************************************************************************

    Copyright(C)2014,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_msghifi.c
  Description     :
  History         :
     1.cuijunqiang       2015-06-14     Draft Enact
     2.
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#include "diag_msghifi.h"
#include "diag_debug.h"
#include "diag_acore_common.h"
#include "diag_common.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGPS_C


/*****************************************************************************
 Function Name   : diag_HifiMsgProc
 Description     : HIFI����ֱ��͸����Ϣ��HIFI������MSP����ظ�
 Input           : VOS_UINT8* pstReq
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_HifiMsgProc(DIAG_FRAME_INFO_STRU* pstReq)
{
    VOS_UINT32 ulRet                    = ERR_MSP_SUCCESS;
    DIAG_COMM_CNF_STRU stHifiCnf        = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo   = {0};
    DIAG_OSA_MSG_STRU *pstMsg           = NULL;
    DIAG_OSA_MSG_STRU *pstVosMsg        = NULL;

    pstMsg = (DIAG_OSA_MSG_STRU *)(pstReq->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));
    
    pstVosMsg = (DIAG_OSA_MSG_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, pstMsg->ulLength);
    
    if (pstVosMsg != NULL)
    {
        pstVosMsg->ulReceiverPid  = pstMsg->ulReceiverPid;
    
        VOS_MemCpy(&pstVosMsg->ulMsgId, &pstMsg->ulMsgId, pstMsg->ulLength);
    
        ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstVosMsg);
        if (ulRet != VOS_OK)
        {
            diag_printf("diag_debug_write VOS_SendMsg failed!\n");
        }
    }

    stHifiCnf.ulRet  = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stHifiCnf, pstReq);

    stDiagInfo.ulMsgType = pstReq->stID.pri4b;

    /*����ظ�*/
    ulRet = DIAG_MsgReport(&stDiagInfo, &stHifiCnf, sizeof(stHifiCnf));

    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_HifiMsgInit
 Description     : MSG HIFI���ֳ�ʼ��
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_HifiMsgInit(VOS_VOID)
{
    /*ע��message��Ϣ�ص�*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_AUDIO, diag_HifiMsgProc);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

