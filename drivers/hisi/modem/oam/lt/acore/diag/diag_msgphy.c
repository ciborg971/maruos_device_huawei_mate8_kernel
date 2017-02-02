/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2014, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName:                                                                 */
/*                                                                           */
/* Author:                                                                   */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2014-10                                                             */
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include <mdrv.h>
#include "diag_msgphy.h"
#include "diag_debug.h"
#include "diag_common.h"
#include "diag_cfg.h"


#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGDSP_C

#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))

DIAG_LDSP_STATE_ENUM_U32 g_diagDspState = LDSP_NOT_INIT;
VOS_UINT32 g_diagDspSocpPowerOnReq = VOS_FALSE;


/*****************************************************************************
 Function Name   : DIAG_DspInitFinished
 Description     : �ṩ��PS��֪ͨDIAG LDSP��ʼ�����
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :

*****************************************************************************/
VOS_VOID DIAG_DspInitFinished(VOS_VOID)
{
    g_diagDspState = LDSP_INITED;
    /* ����δ����,֪ͨLDSPֹͣʹ��SOCP */
    if(!(g_ulDiagCfgInfo & (1 << DIAG_CFG_CONN_BIT)))
    {
        diag_DspNotifySocpState(SOCP_DISABLE);
        g_diagDspState = LDSP_SOCP_DISABLE;
    }
}
VOS_VOID diag_DspVoteToSocp(SOCP_VOTE_TYPE_ENUM_U32 voteType)
{
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    DIAG_MSG_SOCP_VOTE_REQ_STRU * voteReq;

    voteReq = (DIAG_MSG_SOCP_VOTE_REQ_STRU *)VOS_AllocMsg(MSP_PID_DIAG_AGENT,(sizeof(DIAG_MSG_SOCP_VOTE_REQ_STRU) - 20));
    if(voteReq == NULL)
    {
        diag_printf("%s: alloc msg fail\n", __FUNCTION__);
        return;
    }
    voteReq->ulReceiverPid = MSP_PID_DIAG_APP_AGENT;
    voteReq->ulSenderPid   = MSP_PID_DIAG_AGENT;/*TODO:��ʱʹ��diag agent��Ϊsenderpid�����޸�Ϊdsp pid*/
    voteReq->ulLength      = sizeof(DIAG_MSG_SOCP_VOTE_REQ_STRU) - 20;
    voteReq->ulMsgId       = DIAG_MSG_PHY_SOCP_VOTE_REQ;
    voteReq->ulVoteId      = SOCP_VOTE_TL_DSP;
    voteReq->ulVoteType    = voteType;

    if(ERR_MSP_SUCCESS != VOS_SendMsg(MSP_PID_DIAG_AGENT, voteReq))
    {
        diag_printf("%s: send msg fail\n", __FUNCTION__);
    }
#endif
}
VOS_UINT32 diag_DspSocpVoteCnfMsgProc(MsgBlock * pMsgBlock)
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
    }
#endif
    return ERR_MSP_SUCCESS;
}



/*****************************************************************************
 Function Name   : DIAG_SocpPowerOn
 Description     : �ṩ��PS��SOCP�ϵ�ӿ�
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 DIAG_SocpPowerOn(VOS_VOID)
{

    g_diagDspState = LDSP_INITING;

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)

    if(g_diagDspSocpPowerOnReq == VOS_TRUE)
    {
        diag_printf("%s: power on req is running\n", __FUNCTION__);
        return ERR_MSP_SUCCESS;
    }

    g_diagDspSocpPowerOnReq = VOS_TRUE;

    if(0 != DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_FOR_WAKE))
    {
        diag_printf("%s: socp power on fail\n", __FUNCTION__);
        return ERR_MSP_FAILURE;
    }
#endif
    return ERR_MSP_SUCCESS;
}
VOS_SEM g_diagDspMbxSem = (VOS_SEM)0;
/*****************************************************************************
 Function Name   : diag_DspMailboxCb
 Description     :  ���������ע��Ļص���������DSP��DIAG����Ϣʱ����ص��˺���
 Input           : MAILBOX_INT_TYPE_E
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_DspMailboxCb(MAILBOX_INT_TYPE_E enIntType)
{
    (VOS_VOID)VOS_SmV(g_diagDspMbxSem);
}

/*****************************************************************************
 Function Name   : diag_DspMailboxSelfTask
 Description     : MSP����DSP��Ϣ�ظ��ִ�������
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_DspMailboxSelfTask(VOS_VOID)
{
    VOS_UINT32 len, ret;
    VOS_UINT8* pData = VOS_NULL;

    /*lint -save -e716*/
    while(1)
    /*lint -restore*/
    {
        if(VOS_OK != VOS_SmP(g_diagDspMbxSem, 0))
        {
            diag_printf("[%s] VOS_SmP failed.\n", __FUNCTION__);
            continue;
        }

        len = BSP_MailBox_ComMsgSize(EN_MAILBOX_SERVICE_RTT_SYS_CTRL);
        if(0 == len)
        {
            continue ;
        }

        /* �����ڴ� */
        pData = VOS_MemAlloc(MSP_PID_DIAG_AGENT,DYNAMIC_MEM_PT,len);
        if(VOS_NULL == pData)
        {
            diag_printf("[%s] Mem Alloc failed !\n",__FUNCTION__);
            pData = VOS_NULL;
            continue;

        }

        /* �������е�����ֱ�Ӷ�ȡ���ڴ��� */
        ret = BSP_MailBox_ComMsgRead(EN_MAILBOX_SERVICE_RTT_SYS_CTRL, (VOS_UINT8 *)pData, len, EN_MAILBOX_SLEEP_WAKEUP);
        if(ret)
        {
            diag_printf("[%s] BSP_MailBox_ComMsgRead failed !\n",__FUNCTION__);
            (VOS_VOID)VOS_MemFree(MSP_PID_DIAG_AGENT, pData);
            pData = VOS_NULL;
            continue;
        }

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
        /* LDSP�״μ��أ���Ҫ��MCOREͶƱ�µ� */
        if(g_diagDspSocpPowerOnReq == VOS_TRUE)
        {
            if(0 != DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_FOR_SLEEP))
            {
                diag_printf("%s: socp power on fail\n", __FUNCTION__);
            }
            else
            {
                g_diagDspSocpPowerOnReq = VOS_FALSE;
            }
        }
        else if(g_diagDspState == LDSP_SOCP_DISABLE)
        {
            diag_printf("%s: enter Vote Msg to Ap Ops!\n", __FUNCTION__);
            diag_DspVoteToSocp(SOCP_VOTE_FOR_SLEEP);
        }
#endif

        (VOS_VOID)VOS_MemFree(MSP_PID_DIAG_AGENT, pData);
        pData = VOS_NULL;

    }
}

/*****************************************************************************
 Function Name   : diag_DspNotifySocpState
 Description     : ������Ϣ��DSP,֪ͨDSP��ǰ��������״̬
 Input           : VOS_UINT32 state
 Output          : None
 Return          : VOS_VOID

 History         :

*****************************************************************************/
VOS_VOID diag_DspNotifySocpState(DIAG_SOCP_STATE_ENUM_U32 state)
{
    DIAG_MSG_TO_DSP_STRU pData;
    VOS_UINT32  ret;

    pData.ulMsgId = 0;
    pData.ulOpId  = 0;
    pData.ulReq   = state;

    ret = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_RTT_SYS_CTRL, &pData, sizeof(DIAG_MSG_TO_DSP_STRU), EN_MAILBOX_SLEEP_WAKEUP);
    if(ERR_MSP_SUCCESS != ret)
    {
        diag_printf("%s: send to dsp fail ret=0x%x\n", __FUNCTION__, ret);
        return ;
    }
}


/*****************************************************************************
 Function Name   : diag_DspConnMsgProc
 Description     : �����·����ӡ��Ͽ����������
 Input           : DIAG_CONNECT_CMD_ENUM_U32 connCmd
 Output          : None
 Return          : VOS_VOID

 History         :

*****************************************************************************/
VOS_VOID diag_DspConnMsgProc(DIAG_CONNECT_CMD_ENUM_U32 connCmd)
{
    if(connCmd >= DIAG_CONNECT_CMD_BUTT)
    {
        diag_printf("%s: invalid cmd 0x%x\n", __FUNCTION__, connCmd);
        return;
    }

    /* LDSPδ��ʼ���������ڳ�ʼ�� */
    if(g_diagDspState == LDSP_NOT_INIT || g_diagDspState == LDSP_INITING)
    {
        return;
    }

    /* LDSP�Ѿ���ʼ����������ã����ӡ��Ͽ�������Ҫ֪ͨLDSP SOCP״̬�仯 */
    if(DIAG_CONNECT_CMD == connCmd)
    {
        /* ֪ͨDSP SOCP���� */
        diag_DspVoteToSocp(SOCP_VOTE_FOR_WAKE);
        diag_DspNotifySocpState(SOCP_ENABLE);
        g_diagDspState = LDSP_SOCP_ENABLE;
        return;
    }

    if(DIAG_DISCONNECT_CMD == connCmd)
    {
        /* ֪ͨDSP SOCP�����ã��ڵȵ�����ظ���Ͷ�޳�Ʊ */
        diag_DspNotifySocpState(SOCP_DISABLE);
        g_diagDspState = LDSP_SOCP_DISABLE;
        return;
    }
    /* coverity[dead_error_line] */
}

/*****************************************************************************
 Function Name   : diag_DspSendMsg
 Description     : ������Ϣ��DSP
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :

*****************************************************************************/
VOS_UINT32 diag_DspSendMsg(MAILBOX_SERVICE_TYPE_E serType,VOS_UINT8* pstReq ,VOS_UINT32 ulCmdId,VOS_UINT32 ulDataLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    VOS_CHAR* pData = NULL;


    pData = (VOS_VOID*)VOS_MemAlloc(MSP_PID_DIAG_AGENT,DYNAMIC_MEM_PT, ulDataLen+sizeof(ulCmdId));
    if(VOS_NULL == pData)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    (VOS_VOID)VOS_MemCpy(pData, &ulCmdId, sizeof(ulCmdId));
    (VOS_VOID)VOS_MemCpy(pData+sizeof(ulCmdId),pstReq,ulDataLen);


    ulRet = BSP_MailBox_ComMsgWrite((MAILBOX_SERVICE_TYPE_E)serType, pData, ulDataLen+sizeof(ulCmdId), EN_MAILBOX_SLEEP_WAKEUP);
    if(ulRet != ERR_MSP_SUCCESS)
    {
        diag_printf("[%s]:BSP_MailBox_ComMsgWrite err! 0x%x\n",__FUNCTION__,ulRet);
    }

    (VOS_VOID)VOS_MemFree(MSP_PID_DIAG_AGENT, pData);

    return ulRet;
}



VOS_UINT32 diag_AppTransPhyProc(MsgBlock* pMsgBlock)
{
    DIAG_PHY_MSG_A_TRANS_C_STRU *pstInfo;

    pstInfo = (DIAG_PHY_MSG_A_TRANS_C_STRU *)pMsgBlock;

    return diag_DspMsgProc(&pstInfo->stInfo);
}
#endif


#if(VOS_OS_VER == VOS_LINUX)
/*****************************************************************************
 Function Name   : diag_GuDspTransProc
 Description     : GU DSP������ֱ��͸����Ϣ��GUDSP������MSP����ظ�
 Input           : pData    ����������������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GuDspTransProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet                    = ERR_MSP_SUCCESS;
    DIAG_COMM_CNF_STRU stRttCnf         = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo   = {0};
    DIAG_OSA_MSG_STRU *pstMsg           = NULL;
    DIAG_OSA_MSG_STRU *pstVosMsg        = NULL;

    pstMsg = (DIAG_OSA_MSG_STRU *)(pData->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

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

    stRttCnf.ulRet  = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stRttCnf, pData);

    stDiagInfo.ulMsgType = pData->stID.pri4b;

    /*����ظ�*/
    ulRet = DIAG_MsgReport(&stDiagInfo, &stRttCnf, sizeof(stRttCnf));

    return ulRet;
}

#endif


/*****************************************************************************
 Function Name   : diag_DspMsgProc
 Description     : DSP������Ϣ����������ӶϿ�
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_UINT32 diag_DspMsgProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet                    = ERR_MSP_SUCCESS;
    DIAG_COMM_CNF_STRU stRttCnf         = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo   = {0};

#if(VOS_OS_VER == VOS_LINUX)
    VOS_UINT32 ulLen;
    DIAG_PHY_MSG_A_TRANS_C_STRU *pstInfo;
#endif

    switch(pData->stID.mode4b)
    {
        /* GUDSP��������A��ֱ��͸����GUDSP���� */
#if(VOS_OS_VER == VOS_LINUX)
        case DIAG_MODE_GSM:
        case DIAG_MODE_UMTS:
        case DIAG_MODE_1X:
        case DIAG_MODE_HRPD:
            return diag_GuDspTransProc(pData);
            
        default:
            break;
#endif

        /* GU����Ϣ�Ѿ���A�˴���C��ֻ����TL������ */
#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))
        /*LDSP*/
        case DIAG_MODE_LTE:
            ulRet = diag_DspSendMsg(EN_MAILBOX_SERVICE_LTE_OM,pData->aucData+sizeof(MSP_DIAG_DATA_REQ_STRU),pData->ulCmdId,pData->ulMsgLen-sizeof(MSP_DIAG_DATA_REQ_STRU));
            break;
        /*TDSP*/
        case DIAG_MODE_TDS:
            ulRet = diag_DspSendMsg(EN_MAILBOX_SERVICE_TDS_OM,pData->aucData+sizeof(MSP_DIAG_DATA_REQ_STRU),pData->ulCmdId,pData->ulMsgLen-sizeof(MSP_DIAG_DATA_REQ_STRU));
            break;
        default:
            diag_printf("DIAG receive error mode message : %d.\n", pData->stID.mode4b);
            return ulRet;
#endif
    }

#if(VOS_OS_VER == VOS_LINUX)
    ulLen = sizeof(DIAG_PHY_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pData->ulMsgLen;
    pstInfo = (DIAG_PHY_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId       = DIAG_MSG_PHY_A_TRANS_C_REQ;
    ulLen = sizeof(DIAG_FRAME_INFO_STRU)+pData->ulMsgLen;
    (VOS_VOID)VOS_MemCpy(&pstInfo->stInfo, pData, ulLen);
    ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo);
    if(ulRet)
    {
        goto DIAG_ERROR;
    }

    return ulRet;
DIAG_ERROR:
#endif

    stRttCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stRttCnf, pData);

    stDiagInfo.ulMsgType = pData->stID.pri4b;
    stDiagInfo.ulMode    = pData->stID.mode4b;

    /*����ظ�*/
    ulRet = DIAG_MsgReport(&stDiagInfo, &stRttCnf, sizeof(stRttCnf));
    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_DspMsgInit
 Description     : MSP dsp���ֳ�ʼ��
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_DspMsgInit(VOS_VOID)
{
#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))
    VOS_UINT32 ulRet;

     /*��ʼ��DSP SOCPͨ��*/
    (VOS_VOID)DRV_SOCP_INIT_LTE_DSP(SOCP_CODER_SRC_LDSP1,LPHY_MAILBOX_HDLC_BUF_BASE_ADDR,LPHY_MAILBOX_HDLC_BUF_SIZE);

    /*�����Դ��������ź���*/
    ulRet = VOS_SmBCreate("diagmbx", 0, VOS_SEMA4_FIFO, &g_diagDspMbxSem);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        diag_printf("[%s]:create mailbox sem err!\n",__FUNCTION__);
        return ;
    }

    /* ������ע��ص����� */
    ulRet = BSP_MailBox_ComNotifyReg(EN_MAILBOX_SERVICE_RTT_SYS_CTRL, diag_DspMailboxCb);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        diag_printf("[%s]:BSP_MailBox_ComNotifyReg err!\n",__FUNCTION__);
        return ;
    }

    /*ע���Դ�������*/
    ulRet = VOS_RegisterSelfTask(MSP_FID_DIAG_CCPU, (VOS_TASK_ENTRY_TYPE)diag_DspMailboxSelfTask, VOS_PRIORITY_M2, 0x2000);
    if (VOS_NULL_BYTE  == ulRet)
    {
        diag_printf("[%s]:register task error!\n",__FUNCTION__);
        return ;
    }

    /*dsp ��ʼ����ʼͶ�޳�Ʊ*/
    diag_DspVoteToSocp(SOCP_VOTE_FOR_SLEEP);

#endif

#if (VOS_OS_VER == VOS_LINUX)
    /*ע��message��Ϣ�ص�*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_PHY, diag_DspMsgProc);
#endif

}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


