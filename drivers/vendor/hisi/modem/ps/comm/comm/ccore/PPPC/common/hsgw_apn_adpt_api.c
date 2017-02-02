/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hsgw_apn_adpt_api.c
  版 本 号   : 初稿
  作    者   : honglei 50774
  生成日期   : 2013年5月17日
  最近修改   :
  功能描述   : HSGW产品APN/DOMAIN适配接口
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月17日
    作    者   : honglei 50774
    修改内容   : 创建文件

******************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "srv_common_inc.h"

#include "am_public.h"
#include "apn_adpt_api.h"
#include "a11_spu_sru_pub.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

S_CFG_DOMAINNODE *g_pstApnByIndex = NULL;
extern VOS_UINT32 A11_GetDomainByIndex( VOS_UINT16 usAPNIndex, S_CFG_DOMAINNODE **pstAPN);
extern ULONG USM_GetApnCfgByApnIndex(USHORT usApnIndex, HSGW_APN_INFO_S **ppstHsgwApn);

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

ULONG AM_ApnApiGetL2tpGroup(USHORT usApnIdx, USHORT *pusL2tpGroup)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    ULONG ulRet = VOS_OK;

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* 未使能L2TP */
    if (VOS_TRUE != pstDomain->ucL2tp)
    {
        return VOS_ERR;
    }

    *pusL2tpGroup = pstDomain->usGroupNum;
    return VOS_OK;
}
ULONG AM_ApnApiGetApnIdx(UCHAR *pucApnInfo, USHORT *pusApnIdx)
{
    S_CFG_DOMAINNODE *pstDomain = (S_CFG_DOMAINNODE*)pucApnInfo;

    if (VOS_NULL == pstDomain)
    {
        return VOS_ERR;
    }

    *pusApnIdx = pstDomain->usApnIndex;

    return VOS_OK;
}


ULONG AM_ApnApiGetApnIdxByName(UCHAR *pucApnName, USHORT *pusApnIdx)
{
    ULONG ulRet = VOS_OK;
    S_CFG_CDB_CONDITION sCondition = {0};
    S_CFG_DOMAINNODE tmpApn = {0};

    if ((NULL == pusApnIdx) || (NULL == pucApnName))
    {
        return VOS_ERR;
    }

    sCondition.ucOper = M_CFG_CDB_EQUAL;
    sCondition.udwFieldId = M_HSGW_APN_COMMOM_TBL_APN_FLD_ID;

    VOS_StrCpy((CHAR*)sCondition.aValue, (CHAR*)pucApnName);

    /*  查询CDB 中的APN信息配置表 */
    ulRet = DBApiQuerySingle(M_HSGW_APN_COMMOM_TBL_ID, 1, &sCondition, (CHAR *)&tmpApn);
    if (ulRet == CDB_EC_SUCCESS)
    {
        *pusApnIdx = tmpApn.usApnIndex;
        return VOS_OK;
    }

    return VOS_ERR;
}

ULONG AM_ApnApiGetRadiusInfo(UCHAR *pucApnNodeAddr, USHORT *pusApnIdx, USHORT *pusServerGroupID)
{
    S_CFG_DOMAINNODE *pstApn = (S_CFG_DOMAINNODE*)pucApnNodeAddr;

    if ((NULL == pstApn) || (NULL == pusApnIdx) || (NULL == pusServerGroupID))
    {
        return VOS_ERR;
    }

    *pusApnIdx = pstApn->usApnIndex;
    *pusServerGroupID = pstApn->usServerGroupID;
    return VOS_OK;
}



ULONG AM_ApnApiGetAcctInfo(USHORT usApnIdx, APN_ACCT_INFO *pstAcctInfo)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    ULONG ulRet = VOS_OK;

    if (NULL == pstAcctInfo)
    {
        return VOS_ERR;
    }

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    pstAcctInfo->pucAPN         = &pstDomain->aucAPN[0];
    pstAcctInfo->ucTransAccess  = pstDomain->ucTransAccess;
    pstAcctInfo->usServerGroupID = pstDomain->usServerGroupID;

    return VOS_OK;
}


ULONG AM_ApnApiGetCmApnType(USHORT usApnIdx, APN_CM_TYPE_S *pstApnType)
{
    return VOS_OK;
}


ULONG AM_ApnApiGetIdleSwitch(USHORT usApnIdx, UCHAR *pucIdleSwitch, UCHAR *pucUpdateSwitch)
{
    return VOS_OK;
}


UCHAR* AM_ApnApiGetApnName(USHORT usApnIdx)
{
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL;
    ULONG ulRet = VOS_OK;

    ulRet = A11_GetDomainByIndex(usApnIdx, &pstDomain);
    if (VOS_OK != ulRet)
    {
        return VOS_NULL;
    }

    return &pstDomain->aucAPN[0];
}


ULONG AM_ApnApiGetAliasApnName(USHORT usAliasApnIdx, UCHAR *pucAliasApnName)
{
    UCHAR *pucApnName = NULL;

    pucApnName = AM_ApnApiGetApnName(usAliasApnIdx);

    if (NULL != pucApnName)
    {
        VOS_StrNCpy(pucAliasApnName, pucApnName, M_CFG_MAX_APN_STRING_LEN - 1);
        pucAliasApnName[M_CFG_MAX_APN_STRING_LEN - 1] = '\0';
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}


ULONG AM_ApnApiGetMultiServiceMod(USHORT usApnIdx, UCHAR *pucMultiServiceMod)
{
    return VOS_OK;
}


ULONG AM_ApnApiGetApnNameForHsgw(USHORT usApnIndex, UCHAR *pucApnName)
{
    ULONG ulRet = VOS_OK;
    HSGW_APN_INFO_S *pstApn = VOS_NULL;

    if ( NULL == pucApnName )
    {
        return VOS_ERR;
    }

    ulRet = USM_GetApnCfgByApnIndex(usApnIndex, &pstApn);
    if ( VOS_OK != ulRet )
    {
        return ulRet;
    }

    VOS_StrCpy(pucApnName, pstApn->aucApnInfoName);
    return VOS_OK;
}



ULONG AM_ApnApiGetApnSoftParaVaule(USHORT usAPNIndex , UCHAR ucSoftParaIndex, UCHAR *pucSoftParaValue)
{
    if ((NULL == g_pstApnByIndex) || (NULL == pucSoftParaValue))
    {
        VOS_ASSERT(0);
        return VOS_ERR;
    }

    *pucSoftParaValue = 0;
    return VOS_OK;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
