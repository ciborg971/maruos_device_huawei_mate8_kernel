/******************************************************************************

    Copyright(C)2014,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : msp_service.c
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

#include "msp_errno.h"
#include "msp_drx.h"
#include "SCMProc.h"
#include "diag_common.h"
#include "msp_service.h"

#define    THIS_FILE_ID        MSP_FILE_ID_MSP_SERVICE_C


struct MSP_SERVICE_TABLE
{
    VOS_UINT32          ulSidType;
    MSP_SERVICE_FUNC    fnService;
};

struct MSP_SERVICE_TABLE g_astMspService[MSP_SID_BUTT] = {
    {MSP_SID_DEFAULT,           VOS_NULL},
    {MSP_SID_AT_SERVICE,        VOS_NULL},
    {MSP_SID_DIAG_SERVICE,      VOS_NULL},
    {MSP_SID_DATA_SERVICE,      VOS_NULL},
    {MSP_SID_NV_SERVICE,        VOS_NULL},
    {MSP_SID_USIM_SERVICE,      VOS_NULL},
    {MSP_SID_DM_SERVICE,        VOS_NULL},
    {MSP_SID_CBT_SERVICE,       VOS_NULL}
};


VOS_UINT32 msp_ServiceProc(SOCP_DECODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT32 ulSize,VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize)
{
    VOS_UINT32 ulRet = ERR_MSP_INVALID_PARAMETER;
    VOS_UINT32 ulTotalLen = 0;
    VOS_UINT8* pData;
    MSP_SERVICE_HEAD_STRU *pHeader;

    diag_PTR(EN_DIAG_PTR_MSP_SERVICE_1);

    /*入参检查*/
    if(pucData == VOS_NULL)
    {
        diag_PTR(EN_DIAG_PTR_MSP_SERVICE_ERR1);
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulTotalLen = ulSize + ulRBSize;
    if(!ulTotalLen)
    {
        diag_PTR(EN_DIAG_PTR_MSP_SERVICE_ERR2);
        return ERR_MSP_INVALID_PARAMETER;
    }

    pData = VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT, ulTotalLen);
    if(pData == VOS_NULL)
    {
        diag_PTR(EN_DIAG_PTR_MSP_SERVICE_ERR3);
        return ERR_MSP_MALLOC_FAILUE;
    }

    VOS_MemCpy(pData,pucData,ulSize);

    /*回卷指针可能为空*/
    if((VOS_NULL != pucRBData)&&(0 != ulRBSize))
    {
        VOS_MemCpy(pData+ulSize,pucRBData,ulRBSize);
    }

    diag_PTR(EN_DIAG_PTR_MSP_SERVICE_2);

    pHeader = (MSP_SERVICE_HEAD_STRU *)pData;

    if(pHeader->sid8b < MSP_SID_BUTT)
    {
        if(g_astMspService[pHeader->sid8b].fnService)
        {
            ulRet = g_astMspService[pHeader->sid8b].fnService(pHeader);
        }
    }

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT,pData);
    
    return ulRet;
}


VOS_VOID msp_ServiceInit(VOS_VOID)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    /* register to SCM */
    ret = SCM_RegDecoderDestProc(SOCP_DECODER_DST_LOM,(SCM_DECODERDESTFUCN)msp_ServiceProc);
    if(ret != ERR_MSP_SUCCESS)
    {
    }
    return ;
}


VOS_VOID msp_ServiceProcReg(MSP_SID_TYPE_U32 ulType, MSP_SERVICE_FUNC pServiceFn)
{
    /* coverity[cond_at_most] */
    if(ulType > MSP_SID_BUTT)
    {
        return;
    }
    
    g_astMspService[ulType].fnService = pServiceFn;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


