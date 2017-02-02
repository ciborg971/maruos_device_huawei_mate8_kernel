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

#include <product_config.h>
#include <mdrv.h>
#include <diag_mem.h>
#include "diag_msgbbp.h"
#include "msp_diag_comm.h"

#if(VOS_OS_VER == VOS_LINUX)
#include "diag_acore_common.h"
#endif

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGBBP_C


#if(VOS_OS_VER == VOS_LINUX)
DIAG_TRANS_HEADER_STRU g_stBbpTransHead = {{VOS_NULL, VOS_NULL}, 0};
#endif

#if ((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_RTOSCK))
DIAG_BBP_PROC_FUN_STRU g_DiagBbpFunc[] = {
    {diag_DrxSampleGenProc               ,DIAG_CMD_DRX_SAMPLE_GEN_REQ           ,0},
    {diag_DrxSampleGetAddrProc           ,DIAG_CMD_DRX_SAMPLE_ADDR_REQ          ,0},
    {diag_DrxSampleGetChnSizeProc        ,DIAG_CMD_DRX_SAMPLE_CHNSIZE_REQ       ,0},
    {diag_DrxSampleGetVersionProc        ,DIAG_CMD_DRX_SAMPLE_GET_VERSION_REQ   ,0},
    {diag_DrxSampleAbleChnProc           ,DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ      ,0},
};
VOS_UINT32 diag_DrxSampleGenProc(DIAG_FRAME_INFO_STRU *pData)
{
    DIAG_CMD_DRX_SAMPLE_REG_WR_REQ_STRU *psDrxSample = NULL;
	DIAG_CMD_DRX_SAMPLE_REG_WR_CNF_STRU stCnfDrxSample = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    VOS_UINT32 ulDataLen = 0;

	psDrxSample = (DIAG_CMD_DRX_SAMPLE_REG_WR_REQ_STRU*)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));

    ulDataLen = pData->ulMsgLen - sizeof(MSP_DIAG_DATA_REQ_STRU);

    stCnfDrxSample.ulRet = BSP_MailBox_ComMsgWrite(EN_MAILBOX_SERVICE_LTE_HS_DIAG, psDrxSample, ulDataLen, EN_MAILBOX_SLEEP_WAKEUP);
	if(stCnfDrxSample.ulRet != VOS_OK)
	{
        diag_printf("%s BSP_MailBox_ComMsgWrite failed  0x%x!\n",__FUNCTION__,ulRet);
		stCnfDrxSample.ulRet = ERR_MSP_FAILURE;
	}

    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_REG_WR_CNF_STRU));

    return ulRet;

}
/*****************************************************************************
 Function Name   : diag_DrxSampleGetAddrProc
 Description     : 低功耗数采获取基地址
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdSn
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleGetAddrProc(DIAG_FRAME_INFO_STRU *pData)
{
    DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU *psDrxSample = NULL;
	DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU stCnfDrxSample = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
	VOS_UINT32 ulAddrType 	= 0;

	psDrxSample = (DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU*)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));


	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_BBP_SAMPLE,psDrxSample->eDiagDrxSampleAddr,0,0);

	ulAddrType = psDrxSample->eDiagDrxSampleAddr;

    stCnfDrxSample.ulDrxSampleType = ulAddrType;
	/* 获取对应的寄存器地址*/
	switch (ulAddrType)
	{
		case DRX_SAMPLE_BBP_DMA_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBPDMA);
			/* add code here */
			break;
		case DRX_SAMPLE_BBP_DBG_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBPDBG);
			/* add code here */
			break;
		case DRX_SAMPLE_BBP_SRC_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_BBPSRC);
			/* add code here */
			break;
		case DRX_SAMPLE_POW_ONOFF_CLK_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SYSCTRL);
			/* add code here */
			break;
		case DRX_SAMPLE_SOCP_BASE_ADDR:
			stCnfDrxSample.ulDrxSampleAddr = (VOS_UINT32)mdrv_misc_get_ip_baseaddr(BSP_IP_TYPE_SOCP);
			/* add code here */
			break;
		default:
			break;
	}

    stCnfDrxSample.ulRet = VOS_OK;

    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU));

    return ulRet;
}


/*****************************************************************************
 Function Name	 : diag_DrxSampleGetChnSizeProc
 Description	 : 低功耗数采获取通道大小
 Input			 :VOS_UINT8* pstReq
				VOS_UINT32 ulCmdSn
 Output 		 : None
 Return 		 : VOS_UINT32

 History		 :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleGetChnSizeProc(DIAG_FRAME_INFO_STRU *pData)
{
	DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_REQ_STRU *psDrxSample = NULL;
	DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_CNF_STRU stCnfDrxSample = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
	VOS_UINT32 ulAddrType = 0;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

	psDrxSample = (DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_REQ_STRU*)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));


	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_BBP_SAMPLE,psDrxSample->eDiagDrxSampleChnSize,0,0);

	ulAddrType = psDrxSample->eDiagDrxSampleChnSize;
    /*lint -save -e40*/
	switch (ulAddrType)
	{
		case DRX_SAMPLE_BBP_DMA_LOG0_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_LOG0_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_LOG0_MEM_SIZE;
			break;
		case DRX_SAMPLE_BBP_DMA_LOG1_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_LOG1_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_LOG1_MEM_SIZE;
			break;
		case DRX_SAMPLE_BBP_DMA_LOG2_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_LOG2_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_LOG2_MEM_SIZE;
			break;
		case DRX_SAMPLE_BBP_DMA_LOG3_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_LOG3_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_LOG3_MEM_SIZE;
            break;
		case DRX_SAMPLE_BBP_DMA_LOG4_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_LOG4_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_LOG4_MEM_SIZE;
            break;
		case DRX_SAMPLE_BBP_DMA_LOG5_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_LOG5_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_LOG5_MEM_SIZE;
            break;
		case DRX_SAMPLE_BBP_DMA_LOG6_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_LOG6_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_LOG6_MEM_SIZE;
            break;
		case DRX_SAMPLE_BBP_DMA_LOG7_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_LOG7_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_LOG7_MEM_SIZE;
			break;
		case DRX_SAMPLE_BBP_DMA_DATA_CHNSIZE:
			stCnfDrxSample.ulChnAddr = BBP_DS_MEM_ADDR;
            stCnfDrxSample.ulChnSize = BBP_DS_MEM_SIZE; /*lint !e778*/
			break;
		default:
			break;
	}

	stCnfDrxSample.ulRet = ulRet;
    stCnfDrxSample.ulChnType = ulAddrType;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_CNF_STRU));

    return ulRet;
}



/*****************************************************************************
 Function Name   : diag_DrxSampleCfgChnAddrProc
 Description     : 低功耗数采配置通道地址
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdSn
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleGetVersionProc(DIAG_FRAME_INFO_STRU *pData)
{
	DIAG_CMD_DRX_SAMPLE_GET_VERSION_CNF_STRU stCnfDrxSample;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
	VOS_INT32 value = ERR_MSP_SUCCESS;
    /* coverity[assign_zero] */
	va_list arglist = {0};

	/* config regs */
    /*lint -save -e539*/
    /* coverity[uninit_use_in_call] */
    value = VOS_nvsprintf((VOS_CHAR*)(stCnfDrxSample.ulProductName), DIAG_PRODUCT_VERSION_LENGTH, (VOS_CHAR *)PRODUCT_NAME, arglist);
    if(value < 0){}
    /* coverity[var_deref_model] */
	value = VOS_nvsprintf((VOS_CHAR*)(stCnfDrxSample.ulSolutiongName), DIAG_PRODUCT_VERSION_LENGTH, (VOS_CHAR *)PRODUCT_CFG_CHIP_SOLUTION_NAME, arglist);
    if(value < 0){}
    /*lint -restore*/
	/*打包回复给FW*/
    ulRet = ERR_MSP_SUCCESS;
	stCnfDrxSample.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_GET_VERSION_CNF_STRU));

    return ulRet;

}

/*****************************************************************************
 Function Name   : diag_DrxSampleAbleChnProc
 Description     : 数采处理
 Input           :VOS_UINT8* pstReq
                VOS_UINT32 ulCmdSn
 Output          : None
 Return          : VOS_UINT32

 History         :

*****************************************************************************/
VOS_UINT32 diag_DrxSampleAbleChnProc(DIAG_FRAME_INFO_STRU *pData)
{
	DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ_STRU *psDrxSample = NULL;
	DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU stCnfDrxSample = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
	VOS_UINT32 ulRet = ERR_MSP_SUCCESS;

	VOS_UINT32 ulChnAbleType = 0;

	psDrxSample = (DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ_STRU*)((VOS_UINT8*)(pData->aucData)+sizeof(MSP_DIAG_DATA_REQ_STRU));

	/* 调用socp 通道使能函数打开通道或者关闭通道*/
	ulChnAbleType = psDrxSample->eDiagDrxSampleAbleChn;
	switch (ulChnAbleType)
	{
		case DRX_SAMPLE_SOCP_CHN_ENABLE:
			{
				if(VOS_OK != mdrv_socp_start(SOCP_CODER_SRC_LBBP9))
				{
					diag_printf("%s: enable channel failed!\n",__FUNCTION__);
				}
			break;
			}
		case DRX_SAMPLE_SOCP_CHN_DISABLE:
			{
				if(VOS_OK != mdrv_socp_stop(SOCP_CODER_SRC_LBBP9))
				{
					diag_printf("%s: disable channel failed!\n",__FUNCTION__);
				}
			break;
			}
		default:
			break;
	}

	stCnfDrxSample.ulRet = ulRet;

    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU));

    return ulRet;
}
VOS_UINT32 diag_AppTransBbpProc(MsgBlock* pMsgBlock)
{
    DIAG_BBP_MSG_A_TRANS_C_STRU *pstInfo;

    pstInfo = (DIAG_BBP_MSG_A_TRANS_C_STRU *)pMsgBlock;

    return diag_BbpMsgProc(&pstInfo->stInfo);
}

VOS_VOID diag_BbpInitSocpChan(VOS_VOID)
{
    /*lint -save -e40*/
    /*初始化BBP LOG通道*/
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(SOCP_CODER_SRC_LBBP1,BBP_LOG0_MEM_ADDR,BBP_LOG0_MEM_SIZE);
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(SOCP_CODER_SRC_LBBP2,BBP_LOG1_MEM_ADDR,BBP_LOG1_MEM_SIZE);
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(SOCP_CODER_SRC_LBBP3,BBP_LOG2_MEM_ADDR,BBP_LOG2_MEM_SIZE);
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(SOCP_CODER_SRC_LBBP4,BBP_LOG3_MEM_ADDR,BBP_LOG3_MEM_SIZE);
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(SOCP_CODER_SRC_LBBP5,BBP_LOG4_MEM_ADDR,BBP_LOG4_MEM_SIZE);
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(SOCP_CODER_SRC_LBBP6,BBP_LOG5_MEM_ADDR,BBP_LOG5_MEM_SIZE);
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(SOCP_CODER_SRC_LBBP7,BBP_LOG6_MEM_ADDR,BBP_LOG6_MEM_SIZE);
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_LOG(SOCP_CODER_SRC_LBBP8,BBP_LOG7_MEM_ADDR,BBP_LOG7_MEM_SIZE);
    /*初始化BBP DS通道*/
    (VOS_VOID)DRV_SOCP_INIT_LTE_BBP_DS(SOCP_CODER_SRC_LBBP9,BBP_DS_MEM_ADDR,BBP_DS_MEM_SIZE);   /*lint !e778*/
    /*lint -restore*/
}

VOS_BOOL ulChanEnableStat = FALSE;
VOS_VOID diag_BbpEnableSocpChan(VOS_VOID)
{
    /*lint -save -e539*/
    if(TRUE == ulChanEnableStat)
    {
        return ;
    }
	/*使能BBP LOG通道*/
	DRV_SOCP_ENABLE_LTE_BBP_DSP(SOCP_CODER_SRC_LBBP1);
	DRV_SOCP_ENABLE_LTE_BBP_DSP(SOCP_CODER_SRC_LBBP2);
	DRV_SOCP_ENABLE_LTE_BBP_DSP(SOCP_CODER_SRC_LBBP3);
	DRV_SOCP_ENABLE_LTE_BBP_DSP(SOCP_CODER_SRC_LBBP4);
	DRV_SOCP_ENABLE_LTE_BBP_DSP(SOCP_CODER_SRC_LBBP5);
	DRV_SOCP_ENABLE_LTE_BBP_DSP(SOCP_CODER_SRC_LBBP6);
	DRV_SOCP_ENABLE_LTE_BBP_DSP(SOCP_CODER_SRC_LBBP7);
	DRV_SOCP_ENABLE_LTE_BBP_DSP(SOCP_CODER_SRC_LBBP8);
    /*lint -restore*/
    ulChanEnableStat = TRUE;
}

VOS_VOID diag_BbpShowDebugInfo(VOS_VOID)
{
    VOS_UINT32 i = 0;

    for(i=0;i<sizeof(g_DiagBbpFunc)/sizeof(DIAG_BBP_PROC_FUN_STRU);i++)
    {
        diag_printf("Command ID :0x%x ,Ops Num %d\n",g_DiagBbpFunc[i].ulCmdId,g_DiagBbpFunc[i].ulReserve);
    }
}
#endif

/*****************************************************************************
 Function Name   : diag_BbpMsgProc
 Description     : MSP bbp部分消息处理函数
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_UINT32 diag_BbpMsgProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet = ERR_MSP_INVALID_PARAMETER ;
    DIAG_CMD_DRX_SAMPLE_COMM_CNF_STRU stCnfDrxSample;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};

#if (VOS_OS_VER == VOS_LINUX)
    VOS_UINT32 ulLen;
    DIAG_BBP_MSG_A_TRANS_C_STRU *pstInfo;

    /* GU的BBP命令采用透传处理机制 */
    if((DIAG_MODE_GSM == pData->stID.mode4b) || (DIAG_MODE_UMTS == pData->stID.mode4b))
    {
        return diag_TransReqProcEntry(pData, &g_stBbpTransHead);
    }

    ulLen = sizeof(DIAG_BBP_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pData->ulMsgLen;
    pstInfo = (DIAG_BBP_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId       = DIAG_MSG_BBP_A_TRANS_C_REQ;
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

#if ((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_RTOSCK))
    VOS_UINT32 i = 0;
    if(DIAG_MSG_TYPE_BBP != pData->stID.pri4b)
    {
        diag_printf("%s Rcv Error Msg Id 0x%x\n",__FUNCTION__,pData->ulCmdId);
        return ulRet;
    }

    for(i = 0; i< sizeof(g_DiagBbpFunc)/sizeof(g_DiagBbpFunc[0]);i++)
    {
        if(g_DiagBbpFunc[i].ulCmdId == pData->ulCmdId)
        {
            g_DiagBbpFunc[i].ulReserve ++;
            ulRet = g_DiagBbpFunc[i].pFunc(pData);
            return ulRet;
        }
    }

    diag_printf("%s Rcv Error Msg Id 0x%x\n",__FUNCTION__,pData->ulCmdId);
#endif


    stCnfDrxSample.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo,stCnfDrxSample,pData);
    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_BBP;

    ulRet = DIAG_MsgReport(&stDiagInfo,&stCnfDrxSample, sizeof(DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU));

    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_BbpMsgInit
 Description     : MSP bbp部分初始化
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_BbpMsgInit(VOS_VOID)
{
#if ((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_RTOSCK))
    diag_BbpInitSocpChan();
#else

    VOS_UINT32 ulRet;

    /* 创建节点保护信号量, Diag Trans Bbp */
    ulRet = VOS_SmBCreate("DTB", 1, VOS_SEMA4_FIFO,&g_stBbpTransHead.TransSem);
    if(VOS_OK != ulRet)
    {
        diag_printf("diag_BbpMsgInit VOS_SmBCreate failed.\n");
    }

    /* 初始化请求链表 */
    blist_head_init(&g_stBbpTransHead.TransHead);
    
    /*注册message消息回调*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_BBP,diag_BbpMsgProc);
#endif
    return;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


