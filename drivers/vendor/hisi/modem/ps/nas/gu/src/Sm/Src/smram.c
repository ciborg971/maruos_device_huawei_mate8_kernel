/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : smram.c
  Description  : sm��ȫ�ֱ�������
  Function List:
  History:
      1.   ��־��      2004.04.01   �¹�����
*******************************************************************************/
#include "SmInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



VOS_UINT8                  g_TiMapToNsapi[256];                                     /* TI��NSAPI��ӳ���ϵ                      */

VOS_UINT8                  g_CrMapToNsapi[256];                                     /* CR��NSAPI��ӳ���ϵ                      */

VOS_UINT8                  g_ucTiExt;                                               /* ��¼ti�Ƿ�����չλ                       */

SM_ENTITY_STRU             g_SmEntity;                                              /* smʵ�嶨��                               */

SM_PDP_ADDR_AND_APN_STRU   g_SmPdpAddrApn;                                    /* ����pdp address��apn                     */

/*                           ��������NSAPIΪ����:
                             ��0��,��ucSapi[0][1]�����ݴ�SAPI,����״̬��ʱ�ٶ���SAPI�������λ��;
                             ��1�е���4�в�ʹ��;
                             ��5�е���15��ΪNSAPI������.
                             ��һ��Ϊ��Ч��ʶ,0-��Ч,1-��Ч;
                             �ڶ���ΪSAPI,��ucSapi[i][1]��ֵΪNSAPI i �� SAPI.*/
VOS_UINT8                       g_aucSapi[SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET][2];

GMMSM_SGSN_REL_VER_ENUM    g_SmSgsnVersion; /* ����GMM�ϱ��ĵ�ǰSGSN�汾��Ϣ */

VOS_UINT8 * NAS_SM_GetTiMapToNsapi(VOS_VOID)
{
    return &g_TiMapToNsapi[0];
}


VOS_UINT8 * NAS_SM_GetCrMapToNsapi(VOS_VOID)
{
    return &g_CrMapToNsapi[0];
}


VOS_UINT8 NAS_SM_GetTiExt(VOS_VOID)
{
    return g_ucTiExt;
}


VOS_VOID NAS_SM_SetTiExt(VOS_UINT8 ucTiExt)
{
    g_ucTiExt = ucTiExt;
    return;
}


SM_ENTITY_STRU * NAS_SM_GetSmEntity(VOS_VOID)
{
    return &g_SmEntity;
}


SM_PDP_ADDR_AND_APN_STRU * NAS_SM_GetSmPdpAddrApn(VOS_VOID)
{
    return &g_SmPdpAddrApn;
}


VOS_UINT8 * NAS_SM_GetSapi(VOS_UINT8 ucIndex)
{
    return &(g_aucSapi[ucIndex][0]);
}


GMMSM_SGSN_REL_VER_ENUM NAS_SM_GetSmSgsnVersion(VOS_VOID)
{
    return g_SmSgsnVersion;
}


VOS_VOID NAS_SM_SetSmSgsnVersion(GMMSM_SGSN_REL_VER_ENUM enSmSgsnVersion)
{
    g_SmSgsnVersion = enSmSgsnVersion;
    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

