/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mstp_api.h
*
*  Project Code: V100R007
*   Module Name:   
*  Date Created: 2008-10-22
*        Author: lianglong111779
*   Description: mstp cbb对外接口
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
#ifndef _MSTP_API_H_
#define _MSTP_API_H_


#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/mstp/include/mstp_cbb_api.h"


extern ULONG MSTP_PPI_HookRegister(MSTP_PPI_HOOK_FUNC pfMSTPPpiHook);


extern ULONG MSTP_PPI_SetDebugSwitch(ULONG ulSwitch);


extern ULONG MSTP_PPI_Count_Get(MSTP_PPI_COUNT_S *pstCount);


extern VOID MSTP_PPI_ShowCount(VOID);

/*******************************************************************************
*    Func Name: MSTP_PPI_Count_Reset
* Date Created: 2008-07-29
*       Author: wuhailan
*  Description: 清除MSTP PPI下发统计信息
*        Input: VOID
*       Output: 无
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_Count_Reset(VOID);


extern ULONG MSTP_PPI_ComputeUpdateCost(ULONG ulSetYes);


extern VOID MSTP_PPI_ShowUpdateCost(VOID);

#ifdef  __cplusplus
}
#endif

#endif

