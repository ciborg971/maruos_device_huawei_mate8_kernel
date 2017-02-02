


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "vos.h"
#include "mdrv.h"
#include "diag_mem.h"
#include "diag_common.h"
#include "msp_debug.h"
#include "diag_debug.h"
#include "diag_msgmsp.h"
#include "diag_msgbsp.h"
#include "diag_msgbbp.h"
#include "diag_msgphy.h"
#include "lte_sleepflow.h"
#include "msp_errno.h"
#include "msp_drx.h"
#include "omerrorlog.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_CCORE_COMMON_C
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

extern VOS_UINT32 OM_ErrLogMsgProc(MsgBlock* pMsg);

typedef VOS_UINT32 (*DIAG_APPMSG_PROC_FUNC)(MsgBlock* pMsgBlock);

typedef struct
{
    VOS_UINT32              ulMsgId;
    DIAG_APPMSG_PROC_FUNC   pfnProc;
}DIAG_APP_MSG_PROC_STRU;


DIAG_APP_MSG_PROC_STRU g_stAppMsgTable[] =
{
    {DIAG_MSG_MSP_CONN_REQ,         diag_ConnMsgProc},
    {ID_MSG_DIAG_HSO_DISCONN_IND,   diag_SetChanDisconn},
    {DIAG_MSG_MSP_A_TRANS_C_REQ,    diag_AppTransMspProc},
    {DIAG_MSG_BSP_A_TRANS_C_REQ,    diag_AppTransBspProc},
    {DIAG_MSG_BBP_A_TRANS_C_REQ,    diag_AppTransBbpProc},
    {DIAG_MSG_PHY_A_TRANS_C_REQ,    diag_AppTransPhyProc},
    {DIAG_MSG_DIAG_SOCP_VOTE_CNF,   diag_AgentSocpVoteCnfMsgProc},
    {DIAG_MSG_PHY_SOCP_VOTE_CNF,    diag_AgentSocpVoteCnfMsgProc},

#if (FEATURE_ON == FEATURE_PTM)
    {ID_OM_ERR_LOG_CTRL_IND,        OM_ErrLogMsgProc},
    {ID_OM_ERR_LOG_REPORT_REQ,      OM_ErrLogMsgProc},
    {ID_OM_FTM_CTRL_IND,            OM_ErrLogMsgProc},
    {ID_OM_FTM_REQUIRE_IND,         OM_ErrLogMsgProc},
#endif

    {DIAG_MSG_MSP_A_DEBUG_C_REQ,    diag_DebugMsgProc}
    
};

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
SOCP_VOTE_TYPE_ENUM_U32 g_diagSocpState = SOCP_VOTE_FOR_WAKE;
#endif

/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_UINT32 diag_ProcAppAgentMsg(MsgBlock* pMsgBlock)
{
    VOS_UINT32 ulMsgId;
    VOS_UINT32 i;
    VOS_UINT32 ret = ERR_MSP_FAILURE;

    ulMsgId = *(VOS_UINT32*)(pMsgBlock->aucValue);/* [false alarm]:alarm */

    diag_LNR(EN_DIAG_LNR_CCORE_MSG, ulMsgId, VOS_GetSlice());

    for(i = 0; i < sizeof(g_stAppMsgTable)/sizeof(DIAG_APP_MSG_PROC_STRU); i++)
    {
        if(ulMsgId == g_stAppMsgTable[i].ulMsgId)
        {
            ret = g_stAppMsgTable[i].pfnProc(pMsgBlock);
        }
    }

    return ret;
}
VOS_UINT32 diag_AgentSocpVoteCnfMsgProc(MsgBlock * pMsgBlock)
{
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU * voteCnf;

    voteCnf = (DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU *)pMsgBlock;
    if(voteCnf->ulVoteType == SOCP_VOTE_FOR_WAKE)
    {
        if(voteCnf->ulVoteRst != ERR_MSP_SUCCESS)
        {
            diag_printf("%s: vote fail", __FUNCTION__);
            return ERR_MSP_FAILURE;
        }
        else
        {
            g_diagSocpState = SOCP_VOTE_FOR_WAKE;
        }
    }
#endif
    return ERR_MSP_SUCCESS;
}


VOS_VOID diag_AgentVoteToSocp(SOCP_VOTE_TYPE_ENUM_U32 voteType)
{
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    DIAG_MSG_SOCP_VOTE_REQ_STRU * voteReq;

    voteReq = (DIAG_MSG_SOCP_VOTE_REQ_STRU *)VOS_AllocMsg(MSP_PID_DIAG_AGENT,(sizeof(DIAG_MSG_SOCP_VOTE_REQ_STRU) - 20));
    if(voteReq == NULL)
    {
        diag_printf("%s: alloc msg fail\n", __FUNCTION__);
        return;
    }
    voteReq->ulReceiverPid  = MSP_PID_DIAG_APP_AGENT;
    voteReq->ulSenderPid    = MSP_PID_DIAG_AGENT;
    voteReq->ulLength       = sizeof(DIAG_MSG_SOCP_VOTE_REQ_STRU) - 20;
    voteReq->ulVoteId       = SOCP_VOTE_DIAG_COMM;
    voteReq->ulVoteType     = voteType;
    voteReq->ulMsgId        = DIAG_MSG_DIAG_SOCP_VOTE_REQ;

    if(SOCP_VOTE_FOR_SLEEP == voteType)
    {
        g_diagSocpState = SOCP_VOTE_FOR_SLEEP;
    }

    if(ERR_MSP_SUCCESS != VOS_SendMsg(MSP_PID_DIAG_AGENT, voteReq))
    {
        diag_printf("%s: send msg fail\n", __FUNCTION__);
    }
#endif
}



VOS_UINT32 diag_AgentMsgProcInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            diag_CfgResetAllSwt();
            break;
            
        case VOS_IP_RESTART:
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_AGENT_INIT,0,0,0);
            diag_ServiceInit();
            diag_BbpMsgInit();
            diag_AgentVoteToSocp(SOCP_VOTE_FOR_SLEEP);
            break;

        default:
            break;
    }

    return VOS_OK;
}


#define DIAG_PS_TRANS_HEAD_LEN                (20)

/*****************************************************************************
 Function Name   : diag_AgentPsTransRcv
 Description     : DIAG �ϱ�PS·����Ϣ�ӿ�
 Input           : MsgBlock* pMsgBlock
 Output          : None
 Return          : VOS_UINT32
*****************************************************************************/
VOS_VOID diag_AgentPsTransRcv(MsgBlock* pMsgBlock)
{
    DIAG_TRANS_IND_STRU stData;

    VOS_MemSet(&stData, 0, sizeof(stData));

    stData.ulModule = pMsgBlock->ulSenderPid;
    stData.ulMsgId  = (((DIAG_DATA_MSG_STRU*)pMsgBlock)->ulMsgId);
    stData.ulLength = (pMsgBlock->ulLength - DIAG_PS_TRANS_HEAD_LEN);

    /* coverity[illegal_address] */
    stData.pData    = (VOS_VOID*)(pMsgBlock->aucValue + DIAG_PS_TRANS_HEAD_LEN);/*lint !e416*/

    (VOS_VOID)DIAG_TransReport(&stData);
}


VOS_VOID diag_AgentMsgProc(MsgBlock* pMsgBlock)
{
     /*����ж�*/
    if (NULL == pMsgBlock)/*lint !e830*/
    {
        return;
    }

    /*����ʼ����������˯��*/
	drx_msp_fid_vote_lock(DRX_DIAG_MODEM_AGENT_VOTE);/*lint !e539*/

    /*���ݷ���PID��ִ�в�ͬ����*/
    switch(pMsgBlock->ulSenderPid)
    {
        case MSP_PID_DIAG_APP_AGENT:
            (VOS_VOID)diag_ProcAppAgentMsg(pMsgBlock);
            break;

        /*PS·����Ϣ�ϱ�*/
        /* TODO:Ӧ����Э��ջ���е���͸���ϱ��ӿ� */
        case PS_PID_ERRC:
        case PS_PID_MM:
        case PS_PID_ESM:
            diag_AgentPsTransRcv(pMsgBlock);
            break;

         default:
            break;
    }

    /*����ʼ����������˯��*/
    drx_msp_fid_vote_unlock(DRX_DIAG_MODEM_AGENT_VOTE);
    return;
}


VOS_UINT32 MSP_DiagFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRelVal = 0;

    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:
        
        VOS_RegisterMsgGetHook((VOS_MSG_HOOK_FUNC)DIAG_TraceReport);

        ulRelVal = VOS_RegisterPIDInfo(MSP_PID_DIAG_AGENT, (Init_Fun_Type) diag_AgentMsgProcInit, (Msg_Fun_Type) diag_AgentMsgProc);

        if (ulRelVal != VOS_OK)
        {
            return VOS_ERR;
        }
        ulRelVal = VOS_RegisterMsgTaskPrio(MSP_FID_DIAG_CCPU, VOS_PRIORITY_M2);
        if (ulRelVal != VOS_OK)
        {
            return VOS_ERR;
        }
        if(VOS_OK != TLSLEEP_Init())
        {
            return VOS_ERR;
        }
        diag_DspMsgInit();
        break;
    default:
         break;
    }

    return VOS_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



