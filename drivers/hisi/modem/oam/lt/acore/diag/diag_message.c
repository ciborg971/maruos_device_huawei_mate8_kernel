/******************************************************************************

    Copyright(C)2014,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_message.c
  Description     : 
  History         :
     1.cuijunqiang       2014-10-20     Draft Enact
     2.
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "diag_common.h"
#include "SCMProc.h"
#include "diag_api.h"
#include "diag_cfg.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MESSAGE_C

#if (VOS_OS_VER == VOS_LINUX)

struct DIAG_MESSAGE_PROC_STRU
{
    DIAG_MESSAGE_TYPE_U32   ulMsgType;
    DIAG_MESSAGE_FUNC       fnMsgProc;
};


/******************************************************************************
MSP----connect/disconnect
      |
      |-C_reset/get timestamp
      |
      |-LAYER/MSG/PRINT/AIR/USERPLANE/EVENT/Trans/L1 cfg

PS-----trans
      |
      |-PS_REPLAY
      |
      |-MMA鉴权
      |
      |-RTT GTR
      
PHY----TL trans
      |
      |-W trans
      |
      |-G trans
      
LBBP---GEN_REQ/ADDR_REQ/CHNSIZE_REQ/GET_VERSION_REQ/ABLE_CHN_REQ

BSP----Read NV/Write NV/NV_IMPORT/NV_EXPORT/GetNvIdList/BackupNv/NVID filterlist
      |
      |-FS_QUERY_DIR/FS_SCAN_DIR/FS_MAKE_DIR/FS_OPEN/FS_IMPORTFS_EXPORT/FS_DELETE/FS_SPACE
      |
      |-SYSVIEW_SWT/SYSVIEW_IND/AXI_DATA_CFG/AXI_REG_CFG/AXI_DATA_CTRL/AXI_MON_CFG/AXI_MON_START/AXI_MON_TERMINATE/UTRACE_START/UTRACE_TERMINATE/CPU_SWT
      
GUBBP---BBP dump/配置BBP数采/停止BBP数采/配置BBP上报/配置BBP收到EDMA错误消息后通知PC
******************************************************************************/

struct DIAG_MESSAGE_PROC_STRU g_aFnMsgTbl[DIAG_MSG_TYPE_BUTT] =
{
    {DIAG_MSG_TYPE_RSV,     VOS_NULL},
    {DIAG_MSG_TYPE_MSP,     VOS_NULL},
    {DIAG_MSG_TYPE_PS,      VOS_NULL},
    {DIAG_MSG_TYPE_PHY,     VOS_NULL},
    {DIAG_MSG_TYPE_BBP,     VOS_NULL},
    {DIAG_MSG_TYPE_HSO,     VOS_NULL},
    {DIAG_MSG_TYPE_RSV,     VOS_NULL},  /* reserve */
    {DIAG_MSG_TYPE_RSV,     VOS_NULL},  /* reserve */
    {DIAG_MSG_TYPE_RSV,     VOS_NULL},  /* reserve */
    {DIAG_MSG_TYPE_BSP,     VOS_NULL},
    {DIAG_MSG_TYPE_ISP,     VOS_NULL}
};

VOS_UINT32 diag_MessageProc(DIAG_FRAME_INFO_STRU *pData);
VOS_VOID diag_MessageInit(VOS_VOID)
{
    diag_ServiceProcReg(diag_MessageProc);
}



VOS_UINT32 diag_MessageProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet = VOS_ERR;
    DIAG_MESSAGE_TYPE_U32 ulMsgType;

    diag_PTR(EN_DIAG_PTR_MESSAGE_IN);

    if(VOS_NULL_PTR == pData)
    {
        return VOS_ERR;
    }

    ulMsgType = pData->stID.pri4b;

    if((ulMsgType < DIAG_MSG_TYPE_BUTT) && (g_aFnMsgTbl[ulMsgType].fnMsgProc))
    {
        diag_PTR(EN_DIAG_PTR_MESSAGE_PROC);
        ulRet = g_aFnMsgTbl[ulMsgType].fnMsgProc(pData);
    }

    return ulRet;
}



VOS_UINT32 DIAG_MsgProcReg (DIAG_MESSAGE_TYPE_U32 ulMsgType, DIAG_MESSAGE_FUNC pMsgfn)
{
    if((ulMsgType >= DIAG_MSG_TYPE_BUTT) || (VOS_NULL_PTR == pMsgfn))
    {
        return VOS_ERR;
    }

    g_aFnMsgTbl[ulMsgType].fnMsgProc = pMsgfn;

    return VOS_OK;
}
#endif


VOS_UINT32 DIAG_MsgReport (MSP_DIAG_CNF_INFO_STRU *pstDiagInfo, VOS_VOID *pstData, VOS_UINT32 ulLen)
{
    DIAG_MSG_REPORT_HEAD_STRU stDiagHead;

#if(VOS_OS_VER == VOS_LINUX)
    diag_PTR(EN_DIAG_PTR_MESSAGE_REPORT);
#endif

    /*检查DIAG是否初始化且HSO是否连接上*/
    if(!DIAG_IS_CONN_ON)
    {
        return ERR_MSP_NO_INITILIZATION;
    }

    if((VOS_NULL_PTR == pstDiagInfo) || (VOS_NULL_PTR == pstData) || (0 == ulLen))
    {
        diag_printf("%s,%d.\n",__FUNCTION__,__LINE__);
        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemSet(&stDiagHead, 0, sizeof(DIAG_MSG_REPORT_HEAD_STRU));

    stDiagHead.u.stID.pri4b     = (pstDiagInfo->ulMsgType & 0xf);
    stDiagHead.u.stID.mode4b    = (pstDiagInfo->ulMode & 0xf);
    stDiagHead.u.stID.sec5b     = (pstDiagInfo->ulSubType & 0x1f);
    stDiagHead.u.stID.cmdid19b  = (pstDiagInfo->ulMsgId & 0x7ffff);
    stDiagHead.ulSsid           = pstDiagInfo->ulSSId;
    stDiagHead.ulModemId        = pstDiagInfo->ulModemid;
    stDiagHead.ulDirection      = pstDiagInfo->ulDirection;
    stDiagHead.ulMsgTransId     = pstDiagInfo->ulTransId;
    stDiagHead.ulChanId         = SCM_CODER_SRC_LOM_CNF;
    stDiagHead.ulDataSize       = ulLen;
    stDiagHead.pData            = pstData;

    diag_LNR(EN_DIAG_LNR_CCORE_MSG, stDiagHead.u.ulID, VOS_GetSlice());

    (VOS_VOID)diag_ServicePackData(&stDiagHead);

    return VOS_OK;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


