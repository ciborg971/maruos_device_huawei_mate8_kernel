/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              acl_api.h
*
*  Project Code: VISP V1R6C02
*   Module Name: ACL
*  Date Created: 2008-03-31
*        Author: mafeng(59090)
*   Description: ACL��VISP����(��������ʹ��ACL CBB)ʱ�����ṩ�����ݽṹ���û�API����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-31   mafeng(59090)           Create
*  2008-09-10   liangjicheng          V1R7C02 ͬ��V1R7C01  
*    1 ���ӽṹ��
PPI_MSG_TYPE_ACL_E
PPI_ACL_BASE_S
PPI_ACL_EXTEND_S
ACL_PPI_COUNT_S
*2 ���Ӷ���
ACL_PPI_HOOK_FUNC
*3 ����extern
extern ULONG ACL_PPI_HookRegister(ACL_PPI_HOOK_FUNC pfAclPpiHook);
extern ULONG ACL_SetPpiDebugSwitch(ULONG ulSwitch);
extern ULONG ACL_PPI_Count_Get(ACL_PPI_COUNT_S *pstCount);
extern ULONG ACL_PPI_Count_Reset(VOID);
extern VOID ACL_PPI_ShowCount(VOID);
extern ULONG ACL_ComputeACLPPIUpdateCost(ULONG ulSetYes);
extern VOID ACL_ShowACLPPIUpdateCost(VOID);
*  2008-11-18      liangjicheng    BC3D00735 ��ACLFW��ͷ�ļ��ӿ��ṩ����ȫ 
                                   ACLFW_SetEnable �������޸�
                                   ACLFW_GetEnable ACLFW_GetDebug  ��������

*
*******************************************************************************/
#ifndef _ACL_API_H_
#define _ACL_API_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "acl/include/fw_acl_common.h"
#include "acl/include/fw_acl_cbb_api.h"
#include "acl/shell/include/fw_acl_sh.h"  
#include "acl/shell/include/fw_acl_ppi.h" 

ULONG ACL_SH_Init(VOID);

ULONG ACLFW_Init(ULONG ulRegPri);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

